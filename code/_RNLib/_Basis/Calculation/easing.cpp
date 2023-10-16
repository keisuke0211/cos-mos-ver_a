//========================================
// 
// イージング処理のまとまり
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ chunk.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================
// カウントに応じた数値補間処理
float Easing(const EASE ease, const int nCount, const int nCountMax) {
	float fCount = nCount;	// 割合を求める為浮動小数に置き換える
	float fRate  = 0.0f;

	switch (ease) {
		//----- 等速 -----
	case EASE_LINEAR:
		fRate = fCount / nCountMax;

		break;
		//----- 徐々に加速 -----(ノ)
	case EASE_IN:
		fCount /= nCountMax;
		fRate = fCount * fCount;

		break;
		//----- 徐々に減速 -----(反ノ)
	case EASE_OUT:
		fCount /= nCountMax;
		fRate = -fCount * (fCount - 2.0f);

		break;
		//----- 加速して減速 -----(ノ→反ノ)
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