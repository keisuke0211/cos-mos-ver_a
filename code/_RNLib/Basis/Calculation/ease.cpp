//========================================
// 
// ��Ԋ֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]��ԃN���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// [�ÓI]��ԏ���(����)
//========================================
float CEase::Easing(const TYPE& ease, const int& base, const int& max) {

	return Easing(ease, (float)base, (float)max);
}

//========================================
// [�ÓI]��ԏ���(��������)
//========================================
float CEase::Easing(const TYPE& type, const float& base, const float& max) {

	// ����
	float rate(0.0f);

	switch (type) {
		// [[[ ���� ]]]
	case TYPE::LINEAR: {
		rate = base / max;
	}break;
		// [[[ ���X�ɉ��� ]]]
	case TYPE::IN_SINE: {
		rate = base / max;
		rate *= rate;
	}break;
		// [[[ ���X�Ɍ��� ]]]
	case TYPE::OUT_SINE: {
		rate = base / max;
		rate = -rate * (rate - 2.0f);
	}break;
		// [[[ �������Č��� ]]]
	case TYPE::INOUT_SINE: {
		rate = base / (max / 2.0f);

		if (rate < 1.0f) {
			rate = 0.5f * rate * rate;
		}
		else {
			rate = rate - 1.0f;
			rate = -0.5f * (rate * (rate - 2.0f) - 1.0f);
		}
	}break;
	}


	return rate;
}