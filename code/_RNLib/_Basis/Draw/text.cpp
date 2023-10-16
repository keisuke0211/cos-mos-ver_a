//========================================
// 
// �e�L�X�g�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ text.cpp ]]]
//========================================
#include "../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define FONTDATA_PATH "data\\_RNData\\FontList.txt"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CText�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CText::CText() {
	m_pFont    = NULL;	// �t�H���g���̃|�C���^
	m_nFontNum = 0;		// �t�H���g��
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CText::~CText() {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CText::Uninit(void) {
	// �t�H���g���̃|�C���^�̃��������
	RNLib::Memory()->Release(&m_pFont);
}

//========================================
// �t�H���g�̓ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
void CText::LoadFont(void) {
	if (!RNLib::File()->OpenLoadFile(FONTDATA_PATH))
		return;

	// �ǂݍ��݃��[�v
	while (RNLib::File()->SearchLoop("END")) {
		if (false) {}
		else if (RNLib::File()->CheckIdentifier(/* �t�H���g�ݒ��� */"FONTSET{")) {
			while (RNLib::File()->SearchLoop("}")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier(/* �t�H���g��� */"FONT{")) {
					int nNumOld_and_idx = m_nFontNum;
					m_nFontNum++;	// �t�H���g�������Z

					{// �t�H���g���̃|�C���^�̃������Ċm��
						FontData* pNew = new FontData[m_nFontNum];
						int nCopySize = m_nFontNum < nNumOld_and_idx ? m_nFontNum : nNumOld_and_idx;
						if (nCopySize > 0) {
							memcpy(pNew, m_pFont, sizeof(FontData) * nCopySize);
							delete m_pFont;
						}
						m_pFont = pNew;
					}

					while (RNLib::File()->SearchLoop("}")) {
						if (false) {}
						else if (RNLib::File()->CheckIdentifier(/* �e�N�X�`���p�X */"TEXTURE_PATH:")) { RNLib::File()->Scan(CFile::SCAN::TEXIDX,&m_pFont[nNumOld_and_idx].nTexIdx); }
						else if (RNLib::File()->CheckIdentifier(/* �J�n����       */"START_CODE:"))   { RNLib::File()->Scan(CFile::SCAN::INT, &m_pFont[nNumOld_and_idx].nStartCode); }
						else if (RNLib::File()->CheckIdentifier(/* �p�^�[����     */"PTN_WIDTH:"))    { RNLib::File()->Scan(CFile::SCAN::INT, &m_pFont[nNumOld_and_idx].nPtnWidth); }
						else if (RNLib::File()->CheckIdentifier(/* �p�^�[������   */"PTN_HEIGHT:"))   { RNLib::File()->Scan(CFile::SCAN::INT, &m_pFont[nNumOld_and_idx].nPtnHeight); }
						else if (RNLib::File()->CheckIdentifier(/* �Ԋu�䗦       */"SPACE_RATE:"))   { RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_pFont[nNumOld_and_idx].fSpaceRate); }
					}
				}
			}
		}
	}

	// �t�@�C�������
	RNLib::File()->CloseFile();
}

//========================================
// �t�H���g�̕��擾
// Author:RIKU NISHIMURA
//========================================
float CText::GetFontWidth(int nFont) {
	return RNLib::Texture()->GetWidth(m_pFont[nFont].nTexIdx) / m_pFont[nFont].nPtnWidth;
}

//========================================
// �t�H���g�̕��擾(2D)
// Author:RIKU NISHIMURA
//========================================
float CText::GetFontWidth2D(int nFont) {
	return RNLib::Texture()->GetWidth2D(m_pFont[nFont].nTexIdx) / m_pFont[nFont].nPtnWidth;
}

//========================================
// �t�H���g�̍����擾
// Author:RIKU NISHIMURA
//========================================
float CText::GetFontHeight(int nFont) {
	return RNLib::Texture()->GetHeight(m_pFont[nFont].nTexIdx) / m_pFont[nFont].nPtnHeight;
}

//========================================
// �t�H���g�̍����擾(2D)
// Author:RIKU NISHIMURA
//========================================
float CText::GetFontHeight2D(int nFont) {
	return GetFontHeight(nFont) * PIXEL2D_SIZE;
}