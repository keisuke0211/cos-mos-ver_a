//========================================
// 
// �e�L�X�g2D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ text2D.cpp ]]]
//========================================
#include "../../../RNlib.h"
#include <wchar.h>
#include <locale.h>

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CText2D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void CText2D::Set(
		const char* pString,
		const float fScaleX,
		const float fScaleY,
		const D3DXVECTOR3 pos,
	    const D3DXVECTOR3 rot,
		const CText::ALIGNMENT disp,
		const int nFont,
		const Color col) {
	if (!RNLib::Text()->CheckFontExists(nFont)) 
	{// �t�H���g�����݂��Ȃ����A�������I������
		return;
	}

	// ���P�[����ݒ肵�ă}���`�o�C�g�����ɑΉ�
	setlocale(LC_ALL, "");

	// char�^�̕������wchar_t�^�̕�����ɕϊ�
	size_t length = strlen(pString);
	wchar_t* wstr = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
	mbstowcs(wstr, pString, length + 1);

	CText::FontData font   = RNLib::Text()->GetFont(nFont);
	float       fWidth = RNLib::Texture()->GetWidth2D(font.nTexIdx) / font.nPtnWidth;
	float       fSpace = fWidth * fScaleX * font.fSpaceRate;

	int nStrLen = (int)wcslen(wstr);
	for (int nCntDigit = 0; nCntDigit < nStrLen; nCntDigit++) {
		if (pString[nCntDigit] == ' ') {
			continue;	// �J�E���g�̕������󔒂̎��A�܂�Ԃ�
		}
		
		D3DXVECTOR3 setPos = INITD3DXVECTOR3;	// �ݒ�ʒu
		
		// �\���`���ɉ������ݒ�ʒu�̐ݒ�
		switch (disp) {
		case CText::ALIGNMENT::CENTER:
			setPos.x += -((fSpace * nStrLen) * 0.5f) + (((float)nCntDigit + 0.5f) * fSpace);
			break;
		case CText::ALIGNMENT::LEFT:
			setPos.x += nCntDigit * fSpace;
			break;
		case CText::ALIGNMENT::RIGHT:
			setPos.x -= (fSpace * nStrLen) - nCntDigit * fSpace;
			break;
		}

		// �ʒu�ƌ������}�g���b�N�X�ϊ�
		D3DXMATRIX baseMtx = ConvPosRotToMatrix(pos, rot);
		D3DXMATRIX txtMtx  = ConvPosRotToMatrix(setPos, INITD3DXVECTOR3);

		// ��}�g���b�N�X�ƃe�L�X�g�}�g���b�N�X���|�����킹�A���ʃ}�g���b�N�X�����߂�
		D3DXMATRIX resultMtx = MultiplyMatrix(baseMtx, txtMtx);

		// �|���S��2D��ݒ�
		RNLib::Polygon2D()->Set(
			fScaleX,
			fScaleY,
			ConvMatrixToPos(resultMtx),
			ConvMatrixToRot(resultMtx),
			col,
			font.nTexIdx,
			(int)wstr[nCntDigit] - font.nStartCode,
			font.nPtnWidth,
			font.nPtnHeight);
	}

	// �������̉��
	free(wstr);
}