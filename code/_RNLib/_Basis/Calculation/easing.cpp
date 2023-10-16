//========================================
// 
// �C�[�W���O�����̂܂Ƃ܂�
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ chunk.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================
// �J�E���g�ɉ��������l��ԏ���
float Easing(const EASE ease, const int nCount, const int nCountMax) {
	float fCount = nCount;	// ���������߂�ו��������ɒu��������
	float fRate  = 0.0f;

	switch (ease) {
		//----- ���� -----
	case EASE_LINEAR:
		fRate = fCount / nCountMax;

		break;
		//----- ���X�ɉ��� -----(�m)
	case EASE_IN:
		fCount /= nCountMax;
		fRate = fCount * fCount;

		break;
		//----- ���X�Ɍ��� -----(���m)
	case EASE_OUT:
		fCount /= nCountMax;
		fRate = -fCount * (fCount - 2.0f);

		break;
		//----- �������Č��� -----(�m�����m)
	case EASE_INOUT:
		fCount /= nCountMax / 2.0f;
		if (fCount < 1) {
			fRate = 0.5f * fCount * fCount;
		}
		else {
			fCount = fCount - 1.0f;
			fRate = -0.5f * (fCount * (fCount - 2.0f) - 1.0f);
		}
		break;
	}

	if (fRate > 1.0f) {
		fRate = 1.0f;
	}

	return fRate;
}