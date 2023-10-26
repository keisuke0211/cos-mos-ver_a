//========================================
// 
// �e�L�X�g3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"
#include <locale.h>

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �e�L�X�g3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �ݒu����
//========================================
CText3D::CRegistInfo* CText3D::Put(const D3DXMATRIX& mtx, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen) {

	// �o�^��t���łȂ����A�I��
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng()->PutText3D(mtx, isOnScreen)
		->SetString(string)
		->SetAlignment(alignment)
		->SetFontIdx(fontIdx);
}

//========================================
// �ݒu����(�ʒu�ƌ����w��)
//========================================
CText3D::CRegistInfo* CText3D::Put(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen) {

	return Put(ConvPosRotToMatrix(pos, rot), string, alignment, fontIdx, isOnScreen);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �o�^���N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CText3D::CRegistInfo::CRegistInfo() {

	m_string      = NULL;
	m_alignment   = CText::ALIGNMENT::CENTER;
	m_fontIdx     = DATANONE;
	m_scaleX      = 1.0f;
	m_scaleY      = 1.0f;
	m_isFactScale = false;
	m_mtx         = INITD3DXMATRIX;
	m_col         = INITCOLOR;
	m_isZtest     = true;
	m_isLighting  = true;
	m_isBillboard = false;
	m_priority    = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CText3D::CRegistInfo::~CRegistInfo() {

}

//========================================
// �ݒu����(�|���S��3D)
//========================================
void CText3D::CRegistInfo::PutPolygon3D(const bool& isOnScreen) {

	// �t�H���g�f�[�^���擾
	CText::FontData fontData = RNLib::Text()->GetFont(m_fontIdx);
	
	//----------------------------------------
	// ��/����/�Ԋu���Z�o
	//----------------------------------------
	float charWidth  = 0.0f;
	float charHeight = 0.0f;
	float charSpace  = 0.0f;
	if (m_isFactScale) {
		charWidth  = m_scaleX;
		charHeight = m_scaleY;
	}
	else {
		charWidth  = (RNLib::Texture()->GetWidth(fontData.nTexIdx) * PIXEL3D_SIZE) / fontData.nPtnWidth;
		charHeight = (RNLib::Texture()->GetHeight(fontData.nTexIdx) * PIXEL3D_SIZE) / fontData.nPtnHeight;
	}
	charSpace = charWidth * m_scaleX * fontData.fSpaceRate;

	//----------------------------------------
	// ���P�[����ݒ肵�ă}���`�o�C�g�����ɑΉ�
	//----------------------------------------
	setlocale(LC_ALL, "");

	//----------------------------------------
	// char�^�̕������wchar_t�^�̕�����ɕϊ�
	//----------------------------------------
	size_t   length = strlen(m_string);
	wchar_t* wstr = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
	mbstowcs(wstr, m_string, length + 1);

	//----------------------------------------
	// �ꕶ�����ݒu���Ă���
	//----------------------------------------
	D3DXVECTOR3 cameraNorRToV = RNLib::Camera3D()->GetNor();
	int         strLen        = (int)strlen(m_string);
	for (int cntChar = 0; cntChar < strLen; cntChar++) {

		// �J�E���g�������󔒂̎��A�܂�Ԃ�
		if (m_string[cntChar] == ' ') {
			continue;	
		}

		// [[[ �\���`���ɉ������ݒ�ʒu�̐ݒ� ]]]
		D3DXVECTOR3 setPos = INITD3DXVECTOR3;
		switch (m_alignment) {
		case CText::ALIGNMENT::CENTER: {
			setPos.x += ((strLen * -0.5f) + cntChar + 0.5f) * charSpace;
		}break;
		case CText::ALIGNMENT::LEFT: {
			setPos.x += cntChar * charSpace;
		}break;
		case CText::ALIGNMENT::RIGHT: {
			setPos.x += (-strLen + cntChar + 1) * charSpace;
		}break;
		}

		// [[[ ���ʃ}�g���b�N�X�̎Z�o ]]]
		D3DXMATRIX resultMtx; {

			// ��}�g���b�N�X�ƃe�L�X�g�}�g���b�N�X�����߂�
			D3DXMATRIX baseMtx = INITD3DXMATRIX;
			D3DXMATRIX textMtx = INITD3DXMATRIX;

			if (m_isBillboard) 
			{// �r���{�[�h�̎��A
				D3DXVECTOR3 charPos = INITD3DXVECTOR3;
				D3DXVec3Cross(&charPos, &setPos, &cameraNorRToV);
				baseMtx = ConvPosRotToMatrix(ConvMatrixToPos(m_mtx), INITD3DXVECTOR3);
				textMtx = ConvPosRotToMatrix(charPos, INITD3DXVECTOR3);
			}
			else 
			{// �ʏ�̎��A
				D3DXVECTOR3 charPos = setPos;
				baseMtx = m_mtx;
				textMtx = ConvPosRotToMatrix(charPos, INITD3DXVECTOR3);
			}

			// ��}�g���b�N�X�ƃe�L�X�g�}�g���b�N�X���|�����킹��
			resultMtx = MultiplyMatrix(baseMtx, textMtx);
		}

		// �|���S��3D��ݒu
		RNLib::DrawMng()->PutPolygon3D(resultMtx, isOnScreen)
			->SetSize(charWidth, charHeight)
			->SetCol(m_col)
			->SetTex(fontData.nTexIdx, (int)wstr[cntChar] - (int)fontData.nStartCode, fontData.nPtnWidth, fontData.nPtnHeight)
			->SetZTest(m_isZtest)
			->SetLighting(m_isLighting)
			->SetBillboard(m_isBillboard)
			->SetPriority(m_priority);
	}

	// wchar_t�^������̉��
	free(wstr);

	// ������̃��������
	RNLib::Memory()->Release<char>(&m_string);
}

//========================================
// �}�g���b�N�X��ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetMtx(const D3DXMATRIX& mtx) {

	if (this == NULL)
		return NULL;

	m_mtx = mtx;

	return this;
}

//========================================
// �������ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetString(const char* string) {

	if (this == NULL)
		return NULL;

	StrCpyDynamicMemory(&m_string, string);

	return this;
}

//========================================
// �z�u��ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetAlignment(const CText::ALIGNMENT& alignment) {

	if (this == NULL)
		return NULL;

	m_alignment = alignment;

	return this;
}

//========================================
// �t�H���g�ԍ���ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetFontIdx(const short& fontIdx) {

	if (this == NULL)
		return NULL;

	m_fontIdx = fontIdx;

	return this;
}

//========================================
// �F��ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetCol(const Color& col) {

	if (this == NULL)
		return NULL;

	m_col = col;

	return this;
}

//========================================
// �傫����ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetSize(const float& width, const float& height) {

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
CText3D::CRegistInfo* CText3D::CRegistInfo::SetSize_TexBaseScale(const float& scaleX, const float& scaleY) {

	if (this == NULL)
		return NULL;

	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_isFactScale = false;

	return this;
}

//========================================
// Z�e�X�g��ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetZTest(const bool& isZTest) {

	if (this == NULL)
		return NULL;

	m_isZtest = isZTest;

	return this;
}

//========================================
// ���C�e�B���O��ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetLighting(const bool& isLighting) {

	if (this == NULL)
		return NULL;

	m_isLighting = isLighting;

	return this;
}

//========================================
// �r���{�[�h��ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetBillboard(const bool& isBillboard) {

	if (this == NULL)
		return NULL;

	m_isBillboard = isBillboard;

	return this;
}

//========================================
// �D��x�ݒ�
//========================================
CText3D::CRegistInfo* CText3D::CRegistInfo::SetPriority(const short& priority) {

	if (this == NULL)
		return NULL;

	m_priority = priority;

	return this;
}