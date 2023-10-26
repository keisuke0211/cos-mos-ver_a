//========================================
// 
// ���C��3D�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ line3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define SPHERE_DIVISION   (16)	// ���̕�����
#define CYLINDER_DIVISION (16)	// ���̕�����

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CLine3D::CLine3D() {
	m_pDrawSet    = NULL;	// �`��ݒ���
	m_nDrawSetNum = 0;		// �`��ݒ萔
	m_ppVtxBuff   = NULL;	// ���_�o�b�t�@�ւ̃_�u���|�C���^
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CLine3D::~CLine3D() {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Init(void) {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Uninit(void) {
	// ���_�o�b�t�@�̔j��
	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		if (m_ppVtxBuff[nCntSet] != NULL) {
			m_ppVtxBuff[nCntSet]->Release();
			m_ppVtxBuff[nCntSet] = NULL;
		}
	}
	RNLib::Memory()->Release(&m_ppVtxBuff);
}

//========================================
// �`�揈��
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Draw(bool bZTest) {
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();
	D3DXMATRIX mtxSelf;				// �{�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�������l�Őݒ�
	D3DXMatrixIdentity(&mtxSelf);
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	// �����_�����O�X�e�[�g��ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`����ݒ肵�Ȃ�
	RNLib::Texture()->Set(pDevice, DATANONE);

	// Z�e�X�g�t���O�ɉ������L��/�����ݒ�
	if (bZTest) {
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
	else {
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		if (m_pDrawSet[nCntSet].bZTest != bZTest)
			continue;

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_ppVtxBuff[nCntSet], 0, sizeof(Vertex3D));

		// �|���S��3D�̕`��
		pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	}

	// �����_�����O�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//========================================
// �ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, Color col, bool bZTest) {
	// �ߋ��̌�&���݂̔ԍ�
	int nNumOld_and_idx = m_nDrawSetNum;

	m_nDrawSetNum++;	// �`��ݒ萔�����Z

	{// �`��ݒ���̃������Ċm��
		DrawSet* pNew = new DrawSet[m_nDrawSetNum];
		int nCopySize = m_nDrawSetNum < nNumOld_and_idx ? m_nDrawSetNum : nNumOld_and_idx;
		if (nCopySize > 0) {
			memcpy(pNew, m_pDrawSet, sizeof(DrawSet) * nCopySize);
			delete m_pDrawSet;
		}
		m_pDrawSet = pNew;
	}
	
	// �`��ݒ������
	m_pDrawSet[nNumOld_and_idx].bZTest = bZTest;

	{// ���_�o�b�t�@�ւ̃_�u���|�C���^�̃������Ċm��
		LPDIRECT3DVERTEXBUFFER9* pNew = new LPDIRECT3DVERTEXBUFFER9[m_nDrawSetNum];
		int nCopySize = m_nDrawSetNum < nNumOld_and_idx ? m_nDrawSetNum : nNumOld_and_idx;
		if (nCopySize > 0) {
			memcpy(pNew, m_ppVtxBuff, sizeof(LPDIRECT3DVERTEXBUFFER9) * nCopySize);
			delete m_ppVtxBuff;
		}
		m_ppVtxBuff = pNew;
	}

	m_ppVtxBuff[nNumOld_and_idx] = NULL;

	// ���_�o�b�t�@�̐���
	if (FAILED(RNLib::Window()->GetD3DDevice()->CreateVertexBuffer(
		sizeof(Vertex3D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_ppVtxBuff[nNumOld_and_idx],
		NULL))) {
		assert(false);	// !���s
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	Vertex3D* pVtx;
	m_ppVtxBuff[nNumOld_and_idx]->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = pos0;
	pVtx[1].pos = pos1;

	// �F����
	pVtx[0].col = 
	pVtx[1].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);

	// ���_���W���A�����b�N����
	m_ppVtxBuff[nNumOld_and_idx]->Unlock();
}

//========================================
// �ݒ菈��(�~)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Circle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col, bool bZTest) {
	D3DXVECTOR3 aVtxPos[CYLINDER_DIVISION];

	for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
		// �����J�E���g�ɉ�����XZ���W��ݒ�
		aVtxPos[nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));
		aVtxPos[nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));

		// ���i�̕�/����/���s���𔽉f
		aVtxPos[nCntDiv].x *= fRadius;
		aVtxPos[nCntDiv].z *= fRadius;
		aVtxPos[nCntDiv].y = 0.0f;

		// ���_�ʒu��
		// �ʒu����mtx�ƒ��_�ʒumtx���|�����킹�č��W�l�ɕϊ��������̂ɂ���
		D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
		D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntDiv], INITD3DXVECTOR3);
		aVtxPos[nCntDiv] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
	}

	for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
		Set(aVtxPos[nCntDiv],
			aVtxPos[(nCntDiv + 1) % CYLINDER_DIVISION],
			col, bZTest);
	}
}

//========================================
// �ݒ菈��(��)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Sphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col, bool bZTest) {
	enum { l_SIRCLE_XZ, l_SIRCLE_XY, l_SIRCLE_YZ, l_SIRCLE_MAX };
	D3DXVECTOR3 aVtxPos[l_SIRCLE_MAX][SPHERE_DIVISION];

	for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++) {
		for (int nCntDiv = 0; nCntDiv < SPHERE_DIVISION; nCntDiv++) {
			aVtxPos[nCntCircle][nCntDiv] = INITD3DXVECTOR3;

			// �~�J�E���g�ƕ����J�E���g�ɉ����č��W��ݒ�
			switch (nCntCircle) {
			case l_SIRCLE_XZ:
				aVtxPos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				aVtxPos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				break;
			case l_SIRCLE_XY:
				aVtxPos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				aVtxPos[nCntCircle][nCntDiv].y = cosf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				break;
			case l_SIRCLE_YZ:
				aVtxPos[nCntCircle][nCntDiv].y = sinf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				aVtxPos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				break;
			}
			

			// ���_�ʒu��
			// �ʒu����mtx�ƒ��_�ʒumtx���|�����킹�č��W�l�ɕϊ��������̂ɂ���
			D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
			D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntCircle][nCntDiv], INITD3DXVECTOR3);
			aVtxPos[nCntCircle][nCntDiv] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
		}
	}

	// ���C���ݒ�
	for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++) {
		for (int nCntDiv = 0; nCntDiv < SPHERE_DIVISION; nCntDiv++) {
			Set(aVtxPos[nCntCircle][nCntDiv],
				aVtxPos[nCntCircle][(nCntDiv + 1) % SPHERE_DIVISION],
				col, bZTest);
		}
	}
}

//========================================
// �ݒ菈��(������)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Cube(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, Color col, bool bZTest) {
	//   A1-----B1
	//  /      /|
	// C1-----D1B2
	// |      |/
	// C2-----D2
	enum { l_A1, l_B1, l_C1, l_D1, l_A2, l_B2, l_C2, l_D2, l_MAX };
	D3DXVECTOR3 aVtxPos[l_MAX] = {
		D3DXVECTOR3(-1, 1, 1),
		D3DXVECTOR3( 1, 1, 1),
		D3DXVECTOR3(-1, 1,-1),
		D3DXVECTOR3( 1, 1,-1),
		D3DXVECTOR3(-1,-1, 1),
		D3DXVECTOR3( 1,-1, 1),
		D3DXVECTOR3(-1,-1,-1),
		D3DXVECTOR3( 1,-1,-1)
	};

	// ���i�̕�/����/���s���𔽉f
	for (int nCntVtx = 0; nCntVtx < l_MAX; nCntVtx++) {
		aVtxPos[nCntVtx] *= 0.5f;
		aVtxPos[nCntVtx].x *= fWidth;
		aVtxPos[nCntVtx].y *= fHeight;
		aVtxPos[nCntVtx].z *= fDepth;

		// ���_�ʒu��
		// �ʒu����mtx�ƒ��_�ʒumtx���|�����킹�č��W�l�ɕϊ��������̂ɂ���
		D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
		D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntVtx], INITD3DXVECTOR3);
		aVtxPos[nCntVtx] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
	}

	// ��̕�
	Set(aVtxPos[l_A1], aVtxPos[l_B1], col, bZTest);
	Set(aVtxPos[l_A1], aVtxPos[l_C1], col, bZTest);
	Set(aVtxPos[l_D1], aVtxPos[l_C1], col, bZTest);
	Set(aVtxPos[l_D1], aVtxPos[l_B1], col, bZTest);
	// ���̕�
	Set(aVtxPos[l_A2], aVtxPos[l_B2], col, bZTest);
	Set(aVtxPos[l_A2], aVtxPos[l_C2], col, bZTest);
	Set(aVtxPos[l_D2], aVtxPos[l_C2], col, bZTest);
	Set(aVtxPos[l_D2], aVtxPos[l_B2], col, bZTest);
	// �c�̕�
	Set(aVtxPos[l_A1], aVtxPos[l_A2], col, bZTest);
	Set(aVtxPos[l_B1], aVtxPos[l_B2], col, bZTest);
	Set(aVtxPos[l_C1], aVtxPos[l_C2], col, bZTest);
	Set(aVtxPos[l_D1], aVtxPos[l_D2], col, bZTest);
}

//========================================
// �ݒ菈��(��)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Cylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, Color col, bool bZTest) {
	enum { l_SIRCLE_UPPER, l_SIRCLE_BOTTOM, l_SIRCLE_MAX };
	D3DXVECTOR3 aVtxPos[l_SIRCLE_MAX][CYLINDER_DIVISION];

	for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++) {
		for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
			// �~�̃J�E���g�ɉ�����Y���W��ݒ�
			switch (nCntCircle) {
			case l_SIRCLE_UPPER:
				aVtxPos[nCntCircle][nCntDiv].y = 1;
				break;
			case l_SIRCLE_BOTTOM:
				aVtxPos[nCntCircle][nCntDiv].y = -1;
				break;
			}

			// �����J�E���g�ɉ�����XZ���W��ݒ�
			aVtxPos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));
			aVtxPos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));

			// ���i�̕�/����/���s���𔽉f
			aVtxPos[nCntCircle][nCntDiv].x *= fRadius;
			aVtxPos[nCntCircle][nCntDiv].z *= fRadius;
			aVtxPos[nCntCircle][nCntDiv].y *= fHeight * 0.5f;

			// ���_�ʒu��
			// �ʒu����mtx�ƒ��_�ʒumtx���|�����킹�č��W�l�ɕϊ��������̂ɂ���
			D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
			D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntCircle][nCntDiv], INITD3DXVECTOR3);
			aVtxPos[nCntCircle][nCntDiv] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
		}
	}

	for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
		// �c�̕�
		Set(aVtxPos[l_SIRCLE_UPPER][nCntDiv],
			aVtxPos[l_SIRCLE_BOTTOM][nCntDiv],
			col, bZTest);

		// ��̎��͕�
		Set(aVtxPos[l_SIRCLE_UPPER][nCntDiv],
			aVtxPos[l_SIRCLE_UPPER][(nCntDiv + 1) % CYLINDER_DIVISION],
			col, bZTest);

		// ���̎��͕�
		Set(aVtxPos[l_SIRCLE_BOTTOM][nCntDiv],
			aVtxPos[l_SIRCLE_BOTTOM][(nCntDiv + 1) % CYLINDER_DIVISION],
			col, bZTest);
	}
}

//========================================
// �ݒ胊�Z�b�g
// Author:RIKU NISHIMURA
//========================================
void CLine3D::SetReset(void) {
	// ���_�o�b�t�@�̔j��
	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		if (m_ppVtxBuff[nCntSet] != NULL) {
			m_ppVtxBuff[nCntSet]->Release();
			m_ppVtxBuff[nCntSet] = NULL;
		}
	}
	RNLib::Memory()->Release(&m_ppVtxBuff);
	RNLib::Memory()->Release(&m_pDrawSet);

	m_nDrawSetNum = 0;	// �`��ݒ萔��������
}