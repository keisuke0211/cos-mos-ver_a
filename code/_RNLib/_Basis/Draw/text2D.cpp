//========================================
// 
// �e�L�X�g2D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"
#include <locale.h>

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �e�L�X�g2D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �ݒu����
//========================================
CText2D::CRegistInfo* CText2D::Put(const D3DXVECTOR2& pos, const float& angle, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen) {

	// �o�^��t���łȂ����A�I��
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng()->PutText2D(pos, angle, isOnScreen)
		->SetString(string)
		->SetAlignment(alignment)
		->SetFontIdx(fontIdx);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �o�^���N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CText2D::CRegistInfo::CRegistInfo() {

	m_string = NULL;
	m_alignment = CText::ALIGNMENT::CENTER;
	m_fontIdx = DATANONE;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_isFactScale = false;
	m_pos = INITD3DXVECTOR2;
	m_angle = 0.0f;
	m_col = INITCOLOR;
	m_isZtest = true;
	m_isLighting = true;
	m_isBillboard = false;
	m_priority = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CText2D::CRegistInfo::~CRegistInfo() {

	// ������̃��������
	RNLib::Memory()->Release(&m_string);
}

//========================================
// �ݒu����(�|���S��2D)
//========================================
void CText2D::CRegistInfo::PutPolygon2D(const bool& isOnScreen) {

	// �t�H���g�f�[�^���擾
	CText::FontData fontData = RNLib::Text()->GetFont(m_fontIdx);

	//----------------------------------------
	// ��/����/�Ԋu���Z�o
	//----------------------------------------
	float charWidth = 0.0f;
	float charHeight = 0.0f;
	float charSpace = 0.0f;
	if (m_isFactScale) {
		charWidth = m_scaleX;
		charHeight = m_scaleY;
	}
	else {
		charWidth = (RNLib::Texture()->GetWidth(fontData.nTexIdx) * PIXEL2D_SIZE) / fontData.nPtnWidth;
		charHeight = (RNLib::Texture()->GetHeight(fontData.nTexIdx) * PIXEL2D_SIZE) / fontData.nPtnHeight;
	}
	charSpace = charWidth * m_scaleX * fontData.fSpaceRate;

	//----------------------------------------
	// ���P�[����ݒ肵�ă}���`�o�C�g�����ɑΉ�
	//----------------------------------------
	setlocale(LC_ALL, "");

	//----------------------------------------
	// char�^�̕������wchar_t�^�̕�����ɕϊ�
	//----------------------------------------
	size_t   length(strlen(m_string));
	wchar_t* wstr((wchar_t*)malloc((length + 1) * sizeof(wchar_t)));
	mbstowcs(wstr, m_string, length + 1);

	//----------------------------------------
	// �ꕶ�����ݒu���Ă���
	//----------------------------------------
	int strLen = (int)wcslen(wstr);
	for (int cntChar = 0; cntChar < strLen; cntChar++) {

		// �J�E���g�̕������󔒂̎��A�܂�Ԃ�
		if (m_string[cntChar] == ' ')
			continue;

		// [[[ �\���`���ɉ������ݒ�ʒu�̐ݒ� ]]]
		D3DXVECTOR2 setPos = INITD3DXVECTOR2;
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

			{// �ʏ�̎��A
				D3DXVECTOR3 charPos = D3DXVECTOR3(setPos.x, setPos.y, 0.0f);
				baseMtx = ConvPosRotToMatrix(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, m_angle));
				textMtx = ConvPosRotToMatrix(charPos, INITD3DXVECTOR3);
			}

			// ��}�g���b�N�X�ƃe�L�X�g�}�g���b�N�X���|�����킹��
			resultMtx = MultiplyMatrix(baseMtx, textMtx);
		}

		// �|���S��2D��ݒu
		RNLib::DrawMng()->PutPolygon2D(ConvMatrixToPos(resultMtx), ConvMatrixToRot(resultMtx).z, isOnScreen)
			->SetSize(charWidth, charHeight)
			->SetCol(m_col)
			->SetTex(fontData.nTexIdx, (int)wstr[cntChar] - (int)fontData.nStartCode, fontData.nPtnWidth, fontData.nPtnHeight)
			->SetZTest(m_isZtest);
	}

	// wchar_t�^������̉��
	free(wstr);
}

//========================================
// �ʒu��ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetPos(const D3DXVECTOR2& pos) {

	if (this == NULL)
		return NULL;

	m_pos = pos;

	return this;
}

//========================================
// �p�x��ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetAngle(const float& angle) {

	if (this == NULL)
		return NULL;

	m_angle = angle;

	return this;
}

//========================================
// �������ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetString(const char* string) {

	if (this == NULL)
		return NULL;

	StrCpyDynamicMemory(&m_string, string);

	return this;
}

//========================================
// �z�u��ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetAlignment(const CText::ALIGNMENT& alignment) {

	if (this == NULL)
		return NULL;

	m_alignment = alignment;

	return this;
}

//========================================
// �t�H���g�ԍ���ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetFontIdx(const short& fontIdx) {

	if (this == NULL)
		return NULL;

	m_fontIdx = fontIdx;

	return this;
}

//========================================
// �F��ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetCol(const Color& col) {

	if (this == NULL)
		return NULL;

	m_col = col;

	return this;
}

//========================================
// �傫����ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetSize(const float& width, const float& height) {

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
CText2D::CRegistInfo* CText2D::CRegistInfo::SetSize_TexBaseScale(const float& scaleX, const float& scaleY) {

	if (this == NULL)
		return NULL;

	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_isFactScale = false;

	return this;
}

//========================================
// �D��x�ݒ�
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetPriority(const short& priority) {

	if (this == NULL)
		return NULL;

	m_priority = priority;

	return this;
}