//========================================
// 
// �J�����̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define VIB_DAMPING                    (0.75f)
#define VIB_MIN	                       (0.01f)
#define CONTROLLER_VIB_TIME_DIAMETER   (5)
#define CONTROLLER_VIB_MAX    	       (4.0f)
#define INITT_RANS_RATE                (0.25f)
#define INITT_RANS_RATE_OPP            (0.75f)
#define SPIN_DAMP                      (0.15f)
#define ROT_X_MAX                      (D3DX_PI * 0.499999f)
#define ROT_X_MIN                      (D3DX_PI * -0.499999f)
#define INIT_RADIAN                    (45.0f)
#define FEEDBACK_POLYGON_COLOR         (Color{255,255,255,127})
#define FEEDBACK_POLYGON_TEX_CUT_SCALE (0.99f)

//****************************************
// �萔��`
//****************************************
namespace {
	// �U����
	const float VIB_POWERS[] = { 2.0f, 16.0f, 32.0f, };
}
CHECK_ARRAY_SIZE(VIB_POWERS, (int)CCamera::VIB_POWER::MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CCamera3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CCamera::CCamera() {
	m_posV          = INITD3DXVECTOR3;
	m_posR          = INITD3DXVECTOR3;
	m_posVib        = INITD3DXVECTOR3;
	m_rot           = INITD3DXVECTOR3;
	m_spin          = INITD3DXVECTOR3;
	m_dist          = 0.0f;
	m_radian        = INIT_RADIAN;
	m_radianGoal    = INIT_RADIAN;
	m_vibForce      = 0.0f;
	m_isPivotToPosV = true;
	m_isFixed       = false;
	m_state         = STATE::NONE;
	m_stateInfo     = NULL;
	for (int cnt = 0; cnt < 2; cnt++) {
		m_texturesMT[cnt] = NULL;
		m_rendersMT [cnt] = NULL;
	}
	m_ZBuffMT       = NULL;
	m_viewportMT    = INITD3DVIEWPORT9;
	m_vtxBuffMT     = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CCamera::~CCamera() {

}

//========================================
// ����������
//========================================
void CCamera::Init(void) {

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 device = RNLib::Window()->GetD3DDevice();

	 //----------------------------------------
	 // �����_�����O�ݒ�
	{//----------------------------------------
		float areaWidth  = RNLib::Window()->GetAreaWidth();
		float areaHeight = RNLib::Window()->GetAreaHeight();

		for (int cnt = 0; cnt < 2; cnt++) {

			// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̐���
			device->CreateTexture(
				areaWidth,
				areaHeight,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&m_texturesMT[cnt],
				NULL);

			// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̐���
			m_texturesMT[cnt]->GetSurfaceLevel(0, &m_rendersMT[cnt]);
		}

		// �e�N�X�`�������_�����O�pZ�o�b�t�@�̐���
		device->CreateDepthStencilSurface(
			areaWidth,
			areaHeight,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0,
			TRUE,
			&m_ZBuffMT,
			NULL);

		// �r���[�|�[�g�̐ݒ�
		m_viewportMT.X = 0;
		m_viewportMT.Y = 0;
		m_viewportMT.Width  = areaWidth;
		m_viewportMT.Height = areaHeight;
		m_viewportMT.MinZ = 0.0f;
		m_viewportMT.MaxZ = 1.0f;
	}

	//----------------------------------------
	// ���_�o�b�t�@�̐ݒ�
	//----------------------------------------
	// ���_�o�b�t�@�̐���
	RNLib::Window()->GetD3DDevice()->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_vtxBuffMT, NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	VERTEX_2D* vtxs;
	m_vtxBuffMT->Lock(0, 0, (void**)&vtxs, 0);

	// [[[ ���_�ʒu�̐ݒ� ]]]
	RNLib::Polygon2D()->SetVtxPos_TopLeft(vtxs, INITD3DXVECTOR3, RNLib::Window()->GetWidth(), RNLib::Window()->GetHeight());

	// [[[ ���_�J���[�̐ݒ� ]]]
	RNLib::Polygon2D()->SetVtxCol(vtxs, FEEDBACK_POLYGON_COLOR);

	// [[[ �e�N�X�`�����W�̐ݒ� ]]]
	RNLib::Polygon2D()->SetVtxTex_Cut(vtxs, D3DXVECTOR2(0.5f, 0.5f), FEEDBACK_POLYGON_TEX_CUT_SCALE);

	// [[[ RHW�̐ݒ� ]]]
	RNLib::Polygon2D()->SetVtxRHW(vtxs);

	// ���_���W���A�����b�N����
	m_vtxBuffMT->Unlock();
}

//========================================
// �I������
//========================================
void CCamera::Uninit(void) {

	// ��ԏI������
	ProcessState(PROCESS::UNINIT);

	// �����_�����O�^�[�Q�b�g�p�e�N�X�`�����
	for (int cnt = 0; cnt < 2; cnt++) {
		if (m_texturesMT[cnt] != NULL) {
			m_texturesMT[cnt]->Release();
			m_texturesMT[cnt] = NULL;
		}
	}

	// �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@�̔j��
	if (m_vtxBuffMT != NULL) {
		m_vtxBuffMT->Release();
		m_vtxBuffMT = NULL;
	}
}

//========================================
// �X�V����
//========================================
void CCamera::Update(void) {

	//----------------------------------------
	// �U��
	//----------------------------------------
	if (m_vibForce >= VIB_MIN) {
		if (RNLib::GetBlinkF2()) {
			float fAngle = -D3DX_PI + fRand() * D3DX_PI_DOUBLE;
			m_posVib.x = sinf(fAngle) * m_vibForce;
			m_posVib.y = cosf(fAngle) * m_vibForce;
			m_vibForce *= VIB_DAMPING;
		}
	}
	else {
		m_posVib = INITD3DXVECTOR3;
	}

	//----------------------------------------
	// �Œ�Ȃ�I��
	//----------------------------------------
	if (m_isFixed)
		return;

	//----------------------------------------
	// ��ԍX�V����
	//----------------------------------------
	ProcessState(PROCESS::UPDATE);

	//----------------------------------------
	// ��] & ��]�ʌ���
	//----------------------------------------
	m_rot += m_spin;
	m_spin += -m_spin * SPIN_DAMP;

	//----------------------------------------
	// �����𐧌�
	//----------------------------------------
	FloatControl(&m_rot.x, ROT_X_MAX, ROT_X_MIN);
	FloatLoopControl(&m_rot.y, D3DX_PI, -D3DX_PI);

	//----------------------------------------
	// ���_/�����_�ʒu���Z�o
	//----------------------------------------
	// ��]�������_   > �����_�ʒu���Z�o
	// ��]���������_ > ���_�ʒu  ���Z�o
	if (m_isPivotToPosV) m_posR = m_posV + Find_RotVec(m_rot) * m_dist;
	else                 m_posV = m_posR - Find_RotVec(m_rot) * m_dist;

	//----------------------------------------
	// ���W�A������
	//----------------------------------------
	m_radian = (m_radian * INITT_RANS_RATE_OPP) + (m_radianGoal * INITT_RANS_RATE);
}

//========================================
// �X�N���[���̃����_�����O�J�n����
//========================================
void CCamera::StartRenderingScreen(LPDIRECT3DDEVICE9 device) {

	//----------------------------------------
	// ��ʂ��N���A
	//----------------------------------------
	device->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0);

	//----------------------------------------
	// �r���[�}�g���b�N�X�̍쐬
	//----------------------------------------
	D3DXMATRIX mtxView = INITD3DXMATRIX; {
		D3DXVECTOR3 posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		D3DXVECTOR3 posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &posU);
	}

	//----------------------------------------
	// �r���[�}�g���b�N�X�̐ݒ�
	//----------------------------------------
	device->SetTransform(D3DTS_VIEW, &mtxView);

	//----------------------------------------
	// �v���W�F�N�V�����}�g���b�N�X�̃Z�b�g�A�b�v
	//----------------------------------------
	SetUpProjectionMatrix(device, INIT_RADIAN);
}

//========================================
// �����_�����O�J�n����
//========================================
void CCamera::StartRendering(LPDIRECT3DDEVICE9 device) {

	//----------------------------------------
	// �����_�����O�ݒ�
	//----------------------------------------
	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	device->SetRenderTarget(0, m_rendersMT[0]);

	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	device->SetDepthStencilSurface(m_ZBuffMT);

	// �r���[�|�[�g��ݒ�
	device->SetViewport(&m_viewportMT);

	//----------------------------------------
	// ��ʂ��N���A
	//----------------------------------------
	device->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), ColorToD3DXCOLOR(GetColorInfo()->bgCol), 1.0f, 0);

	//----------------------------------------
	// �r���[�}�g���b�N�X�̍쐬
	//----------------------------------------
	D3DXMATRIX mtxView = INITD3DXMATRIX; {
		D3DXVECTOR3 posV = m_posV;
		D3DXVECTOR3 posR = m_posR;

		// �U���ʒu�ɕϓ������鎞�A
		if (m_posVib != INITD3DXVECTOR3) {
			float fAngle = Find_Angle_LookDown(m_posV, m_posR) - D3DX_PI_HALF;
			D3DXVECTOR3 addPos;
			addPos.x = sinf(fAngle) * m_posVib.x;
			addPos.z = cosf(fAngle) * m_posVib.x;
			addPos.y = m_posVib.y;

			// ���_/�����_�ɉ��Z�ʒu��K�p
			posV += addPos;
			posR += addPos;
		}

		// �r���[�}�g���b�N�X�̍쐬
		D3DXVECTOR3 posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &posU);
	}
	
	//----------------------------------------
	// �r���[�}�g���b�N�X�̐ݒ�
	//----------------------------------------
	device->SetTransform(D3DTS_VIEW, &mtxView);

	//----------------------------------------
	// �v���W�F�N�V�����}�g���b�N�X�̃Z�b�g�A�b�v
	//----------------------------------------
	SetUpProjectionMatrix(device, m_radian);
}

//========================================
// �X�N���[���̃����_�����O�I������
//========================================
void CCamera::EndRendering(LPDIRECT3DDEVICE9 device) {

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();

	if (RNLib::Input()->GetKeyPress(DIK_F)) {

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_vtxBuffMT, 0, sizeof(VERTEX_2D));

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_texturesMT[1]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// �e�N�X�`��0��1�����ւ���
	LPDIRECT3DTEXTURE9 m_texturesWk = m_texturesMT[0];
	m_texturesMT[0] = m_texturesMT[1];
	m_texturesMT[1] = m_texturesWk;

	LPDIRECT3DSURFACE9 m_rendersWk = m_rendersMT[0];
	m_rendersMT[0] = m_rendersMT[1];
	m_rendersMT[1] = m_rendersWk;
}

//========================================
// �v���W�F�N�V�����}�g���b�N�X�̃Z�b�g�A�b�v
//========================================
void CCamera::SetUpProjectionMatrix(LPDIRECT3DDEVICE9 device, const float radian) {

	D3DXMATRIX mtxProjection = INITD3DXMATRIX;
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(radian), RNLib::Window()->GetWidth() / RNLib::Window()->GetHeight(), 10.0f, 4000.0f);

	device->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//========================================
// ��������ݒ�
//========================================
void CCamera::SetGeometryInfo(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR) {

	m_posV = posV;
	m_posR = posR;
	m_dist = Find_Dist(m_posV, m_posR);

	if (m_isPivotToPosV)
		m_rot = Find_Rot(m_posV, m_posR);
	else
		m_rot = Find_Rot(m_posR, m_posV);
}

//========================================
// �U����ݒ�
//========================================
void CCamera::SetVib(const VIB_POWER vibPower) {

	if (m_vibForce > VIB_POWERS[(int)vibPower])
		return;

	// �U���̋�����ݒ�
	m_vibForce = VIB_POWERS[(int)vibPower];

	// �R���g���[���[�ɐU����`����
	RNLib::Input()->SetVibration(
		m_vibForce / CONTROLLER_VIB_MAX,
		m_vibForce * CONTROLLER_VIB_TIME_DIAMETER);
}