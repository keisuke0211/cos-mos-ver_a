//========================================
// 
// �|���S��3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �|���S��3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �ݒu����
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::Put(const D3DXMATRIX& mtx, const bool& isOnScreen) {

	// �o�^��t���łȂ����A�I��
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng()->PutPolygon3D(mtx, isOnScreen);
}

//========================================
// �ݒu����(�ʒu�ƌ����w��)
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::Put(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const bool& isOnScreen) {

	return Put(ConvPosRotToMatrix(pos, rot), isOnScreen);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �`����N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

LPDIRECT3DVERTEXBUFFER9 CPolygon3D::CDrawInfo::m_vtxBuff = NULL;
int CPolygon3D::CDrawInfo::m_idxCount = 0;

//========================================
// [�ÓI] ���_�o�b�t�@��������
//========================================
void CPolygon3D::CDrawInfo::CreateVertexBuffer(void) {

	// �ԍ��J�E���g������
	m_idxCount = 0;

	// ���_�o�b�t�@��j�����Ă���
	ReleaseVertexBuffer();

	// �o�^����0�ȉ��Ȃ�I��
	if (CPolygon3D::CRegistInfo::m_resistCount <= 0)
		return;

	// ���_�o�b�t�@�̐���
	RNLib::Window()->GetD3DDevice()->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * CPolygon3D::CRegistInfo::m_resistCount,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_vtxBuff,
		NULL);
}

//========================================
// [�ÓI] ���_�o�b�t�@�������
//========================================
void CPolygon3D::CDrawInfo::ReleaseVertexBuffer(void) {

	// ���_�o�b�t�@�̔j��
	if (m_vtxBuff != NULL) {
		m_vtxBuff->Release();
		m_vtxBuff = NULL;
	}
}

//========================================
// �R���X�g���N�^
//========================================
CPolygon3D::CDrawInfo::CDrawInfo() {

	m_idx         = 0;
	m_mtx         = INITD3DXMATRIX;
	m_texIdx      = DATANONE;
	m_texCamera   = NULL;
	m_isZTest     =
	m_isLighting  =
	m_isBillboard =
	m_distance    = 0.0f;
	for (int cntVtx = 0; cntVtx < 4; cntVtx++) {
		m_vtxs[cntVtx] = {};
	}
}

//========================================
// �f�X�g���N�^
//========================================
CPolygon3D::CDrawInfo::~CDrawInfo() {

}

//========================================
// �`�揈��
//========================================
void CPolygon3D::CDrawInfo::Draw(LPDIRECT3DDEVICE9& device, const D3DXMATRIX& viewMtx) {

	// ���_�o�b�t�@��NULL�̎��A�I��
	if (m_vtxBuff == NULL)
		return;

	//----------------------------------------
	// ���O����
	//----------------------------------------
	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	device->SetStreamSource(0, m_vtxBuff, 0, sizeof(VERTEX_3D));

	//----------------------------------------
	// �ꎞ�I�ȕ`�惂�[�h�ݒ���J�n
	//----------------------------------------
	RNLib::DrawStateMng()->StartTemporarySetMode();

	//----------------------------------------
	// �p�����[�^�[�ɉ������ݒ�
	//----------------------------------------
	// [[[ Z�e�X�g��L��/�����ɂ��� ]]]
	RNLib::DrawStateMng()->SetZTestMode(m_isZTest, device);

	// [[[ ���C�e�B���O��L��/�����ɂ��� ]]]
	RNLib::DrawStateMng()->SetLightingMode(m_isLighting, device);

	{
		D3DXMATRIX mtxTrans = INITD3DXMATRIX;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxSelf = INITD3DXMATRIX;	// �{�̃}�g���b�N�X
		
		// [[[ �r���{�[�h�t���O�ɉ����Č�����ݒ� ]]]
		if (m_isBillboard) {

			// �ʒu�}�g���b�N�X��ݒ�
			D3DXVECTOR3 setPos = ConvMatrixToPos(m_mtx);
			D3DXMatrixTranslation(&mtxTrans, setPos.x, setPos.y, setPos.z);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&mtxSelf, NULL, &viewMtx);
			mtxSelf._41 = 0.0f;
			mtxSelf._42 = 0.0f;
			mtxSelf._43 = 0.0f;

			// �ʒu�}�g���b�N�X��ݒ�
			D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);
		}
		else {
			// �ʒu�ƌ����𔽉f
			D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &m_mtx);
		}

		// [[[ ���[���h�}�g���b�N�X�̐ݒ� ]]]
		device->SetTransform(D3DTS_WORLD, &mtxSelf);
	}

	// [[[ �e�N�X�`���̐ݒ� ]]]
	if (m_texCamera != NULL) {
		m_texCamera->SetUpTexture(device);
		RNLib::DrawStateMng()->SetTextureAlphaMode(false, device);	// �e�N�X�`���̓��߂𖳌���
	}
	else
		RNLib::Texture()->Set(device, m_texIdx);

	//----------------------------------------
	// �`��
	//----------------------------------------
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * m_idx, 2);

	//----------------------------------------
	// �ꎞ�I�ȕ`�惂�[�h�ݒ���I��
	//----------------------------------------
	RNLib::DrawStateMng()->EndTemporarySetMode(device);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �o�^���N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

int CPolygon3D::CRegistInfo::m_resistCount = 0;

//========================================
// �R���X�g���N�^
//========================================
CPolygon3D::CRegistInfo::CRegistInfo() {

	m_resistCount++;

	m_scaleX       = 1.0f;
	m_scaleY       = 1.0f;
	m_isFactScale  = false;
	m_mtx          = INITD3DXMATRIX;
	m_col          = INITCOLOR;
	m_texIdx       = DATANONE;
	m_texCamera    = NULL;
	m_ptn          = 0;
	m_ptnX         = 1;
	m_ptnY         = 1;
	m_ptnScaleX    = 1.0f;
	m_ptnScaleY    = 1.0f;
	m_ptnPos       = INITD3DXVECTOR3;
	m_isZtest      = true;
	m_isLighting   = true;
	m_isBillboard  = false;
	m_isTexMirrorX = false;
	m_priority     = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CPolygon3D::CRegistInfo::~CRegistInfo() {

}

//========================================
// �`����ɕϊ�
//========================================
CPolygon3D::CDrawInfo* CPolygon3D::CRegistInfo::ConvToDrawInfo(void) {

	// �`����̃������m��
	CDrawInfo* drawInfo = NULL;
	RNLib::Memory()->Alloc<CDrawInfo>(&drawInfo);

	// ������
	// (���)
	drawInfo->m_type        = CDrawInfoBase::TYPE::POLYGON3D;
	drawInfo->m_priority    = m_priority;
	// (�p��)
	drawInfo->m_idx         = CPolygon3D::CDrawInfo::m_idxCount++;
	drawInfo->m_mtx         = m_mtx;
	drawInfo->m_texIdx      = m_texIdx;
	drawInfo->m_texCamera   = m_texCamera;
	drawInfo->m_isZTest     = m_isZtest;
	drawInfo->m_isLighting  = m_isLighting;
	drawInfo->m_isBillboard = m_isBillboard;
	drawInfo->m_distance    = Find_DistToCameraPlane(ConvMatrixToPos(m_mtx));

	//----------------------------------------
	// ���_���̐ݒ�
	//----------------------------------------
	{// [[[ �ʒu ]]]
		float widthHalf;
		float heightHalf;

		if (m_isFactScale) {
			widthHalf  = m_scaleX * 0.5f;
			heightHalf = m_scaleY * 0.5f;
		}
		else {
			float fWidth  = (RNLib::Texture()->GetWidth (m_texIdx) * PIXEL3D_SIZE) / m_ptnX;
			float fHeight = (RNLib::Texture()->GetHeight(m_texIdx) * PIXEL3D_SIZE) / m_ptnY;
			widthHalf  = fWidth  * m_scaleX * 0.5f;
			heightHalf = fHeight * m_scaleY * 0.5f;
		}

		drawInfo->m_vtxs[0].pos = D3DXVECTOR3(-widthHalf,  heightHalf, 0.0f);
		drawInfo->m_vtxs[1].pos = D3DXVECTOR3( widthHalf,  heightHalf, 0.0f);
		drawInfo->m_vtxs[2].pos = D3DXVECTOR3(-widthHalf, -heightHalf, 0.0f);
		drawInfo->m_vtxs[3].pos = D3DXVECTOR3( widthHalf, -heightHalf, 0.0f);
	}

	// [[[ �@�� ]]]
	drawInfo->m_vtxs[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	drawInfo->m_vtxs[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	drawInfo->m_vtxs[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	drawInfo->m_vtxs[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// [[[ �F ]]]
	drawInfo->m_vtxs[0].col =
	drawInfo->m_vtxs[1].col =
	drawInfo->m_vtxs[2].col =
	drawInfo->m_vtxs[3].col = D3DCOLOR_RGBA(m_col.r, m_col.g, m_col.b, m_col.a);

	// [[[ UV���W ]]]
	if (m_ptn == 0 && m_ptnX == 1 && m_ptnY == 1) {
		if (m_isTexMirrorX) {
			drawInfo->m_vtxs[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			drawInfo->m_vtxs[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			drawInfo->m_vtxs[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			drawInfo->m_vtxs[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else {
			drawInfo->m_vtxs[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			drawInfo->m_vtxs[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			drawInfo->m_vtxs[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			drawInfo->m_vtxs[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	else {
		float divX = (1.0f / m_ptnX) * m_ptnScaleX;
		float divY = (1.0f / m_ptnY) * m_ptnScaleY;
		float x = ((m_ptn % m_ptnX) * divX) + m_ptnPos.x;
		float y = (((m_ptn / m_ptnX) % m_ptnY) * divY) + m_ptnPos.y;

		if (m_isTexMirrorX) {
			float left   = x + divX;
			float bottom = y + divY;
			drawInfo->m_vtxs[0].tex = D3DXVECTOR2(left, y     );
			drawInfo->m_vtxs[1].tex = D3DXVECTOR2(x   , y     );
			drawInfo->m_vtxs[2].tex = D3DXVECTOR2(left, bottom);
			drawInfo->m_vtxs[3].tex = D3DXVECTOR2(x   , bottom);
		}
		else {
			float right  = x + divX;
			float bottom = y + divY;
			drawInfo->m_vtxs[0].tex = D3DXVECTOR2(x    , y     );
			drawInfo->m_vtxs[1].tex = D3DXVECTOR2(right, y     );
			drawInfo->m_vtxs[2].tex = D3DXVECTOR2(x    , bottom);
			drawInfo->m_vtxs[3].tex = D3DXVECTOR2(right, bottom);
		}
	}

	return drawInfo;
}

//========================================
// �}�g���b�N�X��ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetMtx(const D3DXMATRIX& mtx) {

	if (this == NULL)
		return NULL;

	m_mtx = mtx;

	return this;
}

//========================================
// �F��ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetCol(const Color& col) {

	if (this == NULL)
		return NULL;

	m_col = col;

	return this;
}

//========================================
// �傫����ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetSize(const float& width, const float& height) {

	if (this == NULL)
		return NULL;

	m_scaleX = width;
	m_scaleY = height;
	m_isFactScale = true;

	return this;
}

//========================================
// �傫����ݒ�(�e�N�X�`����Ŋg��)
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetSize_TexBaseScale(const float& scaleX, const float& scaleY) {

	if (this == NULL)
		return NULL;

	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_isFactScale = false;

	return this;
}

//========================================
// �e�N�X�`����ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetTex(const short& texIdx, const unsigned short& ptn, const unsigned short& ptnX, const unsigned short& ptnY, const D3DXVECTOR3& ptnPos) {

	if (this == NULL)
		return NULL;

	m_texIdx = texIdx;
	m_ptn = ptn;
	m_ptnX = ptnX;
	m_ptnY = ptnY;
	m_ptnPos = ptnPos;

	return this;
}

//========================================
// �e�N�X�`����ݒ�(�J����)
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetTex_Camera(CCamera* camera) {

	if (this == NULL)
		return NULL;

	m_texCamera = camera;

	return this;
}

//========================================
// �e�N�X�`�����Œ肵��X�����ɐL�΂�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::ExtendFixedTexX(const float& rateX) {

	if (this == NULL)
		return NULL;

	m_scaleX *= rateX;
	m_ptnScaleX = rateX;

	return this;
}

//========================================
// �e�N�X�`�����Œ肵��Y�����ɐL�΂�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::ExtendFixedTexY(const float& rateY) {

	if (this == NULL)
		return NULL;

	m_scaleY *= rateY;
	m_ptnScaleY = rateY;
	
	return this;
}

//========================================
// Z�e�X�g��ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetZTest(const bool& isZTest) {

	if (this == NULL)
		return NULL;

	m_isZtest = isZTest;
	
	return this;
}

//========================================
// ���C�e�B���O��ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetLighting(const bool& isLighting) {

	if (this == NULL)
		return NULL;

	m_isLighting = isLighting;
	
	return this;
}

//========================================
// �r���{�[�h��ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetBillboard(const bool& isBillboard) {

	if (this == NULL)
		return NULL;

	m_isBillboard = isBillboard;
	
	return this;
}

//========================================
// �e�N�X�`����X���]�ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetTexMirrorX(const bool& isMirror) {
	
	if (this == NULL)
		return NULL;

	m_isTexMirrorX = isMirror;
	
	return this;
}

//========================================
// �D��x�ݒ�
//========================================
CPolygon3D::CRegistInfo* CPolygon3D::CRegistInfo::SetPriority(const short& priority) {

	if (this == NULL)
		return NULL;

	m_priority = priority;

	return this;
}