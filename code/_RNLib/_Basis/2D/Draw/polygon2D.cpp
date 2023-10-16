//========================================
// 
// �|���S��2D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ polygon2D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CPolygon2D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CPolygon2D::CPolygon2D() {
	m_pDrawSet    = NULL;	// �`��ݒ���
	m_nDrawSetNum = 0;		// �`��ݒ萔
	m_ppVtxBuff   = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CPolygon2D::~CPolygon2D() {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CPolygon2D::Init(void) {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CPolygon2D::Uninit(void) {
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
void CPolygon2D::Draw(void) {
	if (m_nDrawSetNum <= 0) {
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_ppVtxBuff[nCntSet], 0, sizeof(VERTEX_2D));

		// �e�N�X�`���̐ݒ�
		RNLib::Texture()->Set(pDevice, m_pDrawSet[nCntSet].nTex);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//========================================
// �ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void CPolygon2D::Set(
	const float fScaleX,
	const float fScaleY,
	const D3DXVECTOR3 pos,
	const D3DXVECTOR3 rot,
	const Color col,
	const int nTex,
	const int nPtn,
	const int nPtnX,
	const int nPtnY,
	const bool bMirror) {
	float fWidth        = (RNLib::Texture()->GetWidth2D (nTex) * fScaleX) / nPtnX;
	float fHeight       = (RNLib::Texture()->GetHeight2D(nTex) * fScaleY) / nPtnY;
	float fLength       = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) * 0.5f;
	float fAngle        = atan2f(fWidth,  fHeight);
	float fInverseAngle = D3DX_PI - fAngle;

	// ���_���W��ݒ�
	D3DXVECTOR3 aPos[4];
	{
		float fAngleResult;
		fAngleResult = rot.z - fInverseAngle;
		aPos[0].x = pos.x + sinf(fAngleResult) * fLength;
		aPos[0].y = pos.y + cosf(fAngleResult) * fLength;
		fAngleResult = rot.z + fInverseAngle;
		aPos[1].x = pos.x + sinf(fAngleResult) * fLength;
		aPos[1].y = pos.y + cosf(fAngleResult) * fLength;
		fAngleResult = rot.z - fAngle;
		aPos[2].x = pos.x + sinf(fAngleResult) * fLength;
		aPos[2].y = pos.y + cosf(fAngleResult) * fLength;
		fAngleResult = rot.z + fAngle;
		aPos[3].x = pos.x + sinf(fAngleResult) * fLength;
		aPos[3].y = pos.y + cosf(fAngleResult) * fLength;
	}
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++) {
		aPos[nCntVtx].z = 0.0f;
	}

	SetVtx(
		aPos[0],
		aPos[1],
		aPos[2],
		aPos[3],
		col,
		nTex,
		nPtn,
		nPtnX,
		nPtnY,
		bMirror);
}

//========================================
// �ݒ菈��(�Q�[�W)
// Author:RIKU NISHIMURA
//========================================
void CPolygon2D::SetGauge(
	const float       fRate,
	const float       fScaleX,
	const float       fScaleY,
	const D3DXVECTOR3 pos,
	const Color       col,
	const int         nTex,
	const int         nPtn,
	const int         nPtnX,
	const int         nPtnY,
	const bool        bMirror) {
	float fWidth  = RNLib::Texture()->GetWidth2D (nTex) * fScaleX * fRate;
	float fHeight = RNLib::Texture()->GetHeight2D(nTex) * fScaleY;

	// ���_���W��ݒ�
	D3DXVECTOR3 aPos[4];

	aPos[0].x =
	aPos[2].x = pos.x;
	aPos[1].x =
	aPos[3].x = pos.x + fWidth;

	float fHeightHalf = fHeight * 0.5f;
	aPos[0].y = 
	aPos[1].y = pos.y - fHeightHalf;
	aPos[2].y =
	aPos[3].y = pos.y + fHeightHalf;
	
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++) {
		aPos[nCntVtx].z = 0.0f;
	}

	SetVtx(
		aPos[0],
		aPos[1],
		aPos[2],
		aPos[3],
		col,
		nTex,
		nPtn,
		nPtnX,
		nPtnY,
		bMirror);
}

//========================================
// �ݒ菈��(Vtx)
// Author:RIKU NISHIMURA
//========================================
void CPolygon2D::SetVtx(
	const D3DXVECTOR3 aVtxPos0,
	const D3DXVECTOR3 aVtxPos1,
	const D3DXVECTOR3 aVtxPos2,
	const D3DXVECTOR3 aVtxPos3,
	const Color       col,
	const int         nTex,
	const int         nPtn,
	const int         nPtnX,
	const int         nPtnY,
	const bool        bMirror) {
	// �ߋ��̌�&���݂̔ԍ�
	int nNumOld = m_nDrawSetNum;

	m_nDrawSetNum++;	// �`��ݒ萔�����Z

	{// �`��ݒ���̃������Ċm��
		DrawSet* pNew = new DrawSet[m_nDrawSetNum];
		int nCopySize = m_nDrawSetNum < nNumOld ? m_nDrawSetNum : nNumOld;
		if (nCopySize > 0) {
			memcpy(pNew, m_pDrawSet, sizeof(DrawSet) * nCopySize);
			delete m_pDrawSet;
		}
		m_pDrawSet = pNew;
	}

	// �`��ݒ������
	m_pDrawSet[nNumOld].nTex = nTex;

	{// ���_�o�b�t�@�ւ̃_�u���|�C���^�̃������Ċm��
		LPDIRECT3DVERTEXBUFFER9* pNew = new LPDIRECT3DVERTEXBUFFER9[m_nDrawSetNum];
		int nCopySize = m_nDrawSetNum < nNumOld ? m_nDrawSetNum : nNumOld;
		if (nCopySize > 0) {
			memcpy(pNew, m_ppVtxBuff, sizeof(LPDIRECT3DVERTEXBUFFER9) * nCopySize);
			delete m_ppVtxBuff;
		}
		m_ppVtxBuff = pNew;
	}

	m_ppVtxBuff[nNumOld] = NULL;

	// ���_�o�b�t�@�̐���
	RNLib::Window()->GetD3DDevice()->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_ppVtxBuff[nNumOld],
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	VERTEX_2D* pVtx;
	m_ppVtxBuff[nNumOld]->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = aVtxPos0 * RNLib::Window()->GetResolution();
	pVtx[1].pos = aVtxPos1 * RNLib::Window()->GetResolution();
	pVtx[2].pos = aVtxPos2 * RNLib::Window()->GetResolution();
	pVtx[3].pos = aVtxPos3 * RNLib::Window()->GetResolution();
	if (RNLib::GetUseImGui()) {
		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++) {
			pVtx[nCntVtx].pos.x *= IMGUI_CORRECT_X;
			pVtx[nCntVtx].pos.y *= IMGUI_CORRECT_Y;
		}
	}

	// ���_�J���[�̐ݒ�
	SetVtxCol(pVtx, col);

	// �e�N�X�`�����W�̐ݒ�
	SetVtxTex(pVtx,
		nPtn,
		nPtnX,
		nPtnY,
		NULL,
		bMirror);

	// rhw�̐ݒ�
	SetVtxRHW(pVtx);

	// ���_���W���A�����b�N����
	m_ppVtxBuff[nNumOld]->Unlock();
}

//========================================
// �ݒ胊�Z�b�g
// Author:RIKU NISHIMURA
//========================================
void CPolygon2D::SetReset(void) {
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

//========================================
// ���_2D�̍��W�ݒ�
//========================================
void CPolygon2D::SetVtxPos(VERTEX_2D *vtxs, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float width, const float height) {

	// �Ίp���̒����ƌ���
	float length = sqrtf((width * width) + (height * height)) * 0.5f;
	float angle  = atan2f(width, height);

	// ���_���W��ݒ�
	float inverseAngle = D3DX_PI - angle;
	vtxs[0].pos.x = pos.x + sinf(rot.z - inverseAngle) * length;
	vtxs[0].pos.y = pos.y + cosf(rot.z - inverseAngle) * length;
	vtxs[1].pos.x = pos.x + sinf(rot.z + inverseAngle) * length;
	vtxs[1].pos.y = pos.y + cosf(rot.z + inverseAngle) * length;
	vtxs[2].pos.x = pos.x + sinf(rot.z - angle) * length;
	vtxs[2].pos.y = pos.y + cosf(rot.z - angle) * length;
	vtxs[3].pos.x = pos.x + sinf(rot.z + angle) * length;
	vtxs[3].pos.y = pos.y + cosf(rot.z + angle) * length;

	// �𑜓x��K�p
	ApplyResolution(vtxs);
}

//========================================
// ���_2D�̍��W�ݒ�
//========================================
void CPolygon2D::SetVtxPos(VERTEX_2D* vtxs, const D3DXVECTOR3 pos0, const D3DXVECTOR3 pos1, const D3DXVECTOR3 pos2, const D3DXVECTOR3 pos3) {
	
	vtxs[0].pos = pos0;
	vtxs[1].pos = pos1;
	vtxs[2].pos = pos2;
	vtxs[3].pos = pos3;

	// �𑜓x��K�p
	ApplyResolution(vtxs);
}

//========================================
// ���_2D�̍��W�ݒ�
//========================================
void CPolygon2D::SetVtxPos_TopLeft(VERTEX_2D* vtxs, const D3DXVECTOR3 pos, const float width, const float height) {

	vtxs[0].pos = D3DXVECTOR3(pos.x        , pos.y         , 0.0f);
	vtxs[1].pos = D3DXVECTOR3(pos.x + width, pos.y         , 0.0f);
	vtxs[2].pos = D3DXVECTOR3(pos.x        , pos.y + height, 0.0f);
	vtxs[3].pos = D3DXVECTOR3(pos.x + width, pos.y + height, 0.0f);

	// �𑜓x��K�p
	ApplyResolution(vtxs);
}

//========================================
// ���_2D�ɉ𑜓x��K�p
//========================================
void CPolygon2D::ApplyResolution(VERTEX_2D* vtxs) {

	float resolution = RNLib::Window()->GetResolution();
	vtxs[0].pos *= resolution;
	vtxs[1].pos *= resolution;
	vtxs[2].pos *= resolution;
	vtxs[3].pos *= resolution;

	if (RNLib::GetUseImGui()) {
		for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++) {
			vtxs[nCntVtx].pos.x *= IMGUI_CORRECT_X;
			vtxs[nCntVtx].pos.y *= IMGUI_CORRECT_Y;
		}
	}
}

//========================================
// ���_2D�̍��W�ϊ��p�W���ݒ�
//========================================
void CPolygon2D::SetVtxRHW(VERTEX_2D *pVtx) {

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
}

//========================================
// ���_2D�̐F�ݒ�
//========================================
void CPolygon2D::SetVtxCol(VERTEX_2D *pVtx, const Color col) {

	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
}

//========================================
// ���_2D�̃e�N�X�`�����W�ݒ�
//========================================
void CPolygon2D::SetVtxTex(VERTEX_2D *pVtx, const int nPtn, const int nPtnMaxX, const int nPtnMaxY, const D3DXVECTOR3 *pPos, const bool bMirror) {

	// �p�^�[���̏����0�̎��A�������I������
	if (nPtnMaxX * nPtnMaxY == 0)
		return;

	D3DXVECTOR3 pos = INITD3DXVECTOR3;

	// �ʒu��NULL�łȂ����A�ʒu��-�␳���đ��
	if (pPos != NULL) {
		pos = -(*pPos);
	}

	// �v�Z�ɕK�v�ȗv�f
	int   nPtnX      = nPtn % nPtnMaxX;
	int   nPtnY      = (nPtn / nPtnMaxX) % nPtnMaxY;
	float fWidthDiv  = 1.0f / nPtnMaxX;
	float fHeightDiv = 1.0f / nPtnMaxY;
	float fX         = (nPtnX * fWidthDiv) + pos.x;
	float fY         = (nPtnY * fHeightDiv) + pos.y;

	// ���E���]�t���O�ɉ������e�N�X�`�����W�̐ݒ�
	if (bMirror) {
		pVtx[0].tex = D3DXVECTOR2(fX + fWidthDiv, fY);
		pVtx[1].tex = D3DXVECTOR2(fX            , fY);
		pVtx[2].tex = D3DXVECTOR2(fX + fWidthDiv, fY + fHeightDiv);
		pVtx[3].tex = D3DXVECTOR2(fX            , fY + fHeightDiv);
	}
	else {
		pVtx[0].tex = D3DXVECTOR2(fX            , fY);
		pVtx[1].tex = D3DXVECTOR2(fX + fWidthDiv, fY);
		pVtx[2].tex = D3DXVECTOR2(fX            , fY + fHeightDiv);
		pVtx[3].tex = D3DXVECTOR2(fX + fWidthDiv, fY + fHeightDiv);
	}
}

//========================================
// ���_2D�̃e�N�X�`�����W�ݒ�
//========================================
void CPolygon2D::SetVtxTex_Cut(VERTEX_2D* vtxs, const D3DXVECTOR2 cutPos, const float size) {

	SetVtxTex_Cut(vtxs, cutPos, size, size);
}

//========================================
// ���_2D�̃e�N�X�`�����W�ݒ�
//========================================
void CPolygon2D::SetVtxTex_Cut(VERTEX_2D* vtxs, const D3DXVECTOR2 cutPos, const float width, const float height) {

	float widthHalf  = width  * 0.5f;
	float heightHalf = height * 0.5f;
	float left       = cutPos.x - widthHalf;
	float right      = cutPos.x + widthHalf;
	float top        = cutPos.y - heightHalf;
	float bottom     = cutPos.y + heightHalf;

	vtxs[0].tex = D3DXVECTOR2(left , top   );
	vtxs[1].tex = D3DXVECTOR2(right, top   );
	vtxs[2].tex = D3DXVECTOR2(left , bottom);
	vtxs[3].tex = D3DXVECTOR2(right, bottom);
}