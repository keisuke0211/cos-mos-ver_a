//========================================
// 
// 遷移の処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ transition.cpp ]]]
//========================================
#include "../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
#define TIME           (30)
#define WAIT_TIME      (10)
#define HOLE_SCALE_MAX (6.0f)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTransitionクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CTransition::CTransition() {
	m_state     = STATE::NONE;
	m_nStateCtr = 0;
	m_type      = TYPE::NONE;
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CTransition::~CTransition() {

}

//========================================
// 更新処理
//========================================
void CTransition::Update(void) {

	//===== [[[ ローカル関数宣言 ]]]
	struct LocalFunc {
		//========================================
		// 画面埋め
		//========================================
		static void FillScreen(const float& fRate) {
			RNLib::Polygon2D()->Put(RNLib::Window()->GetCenterPos(), 0.0f)
				->SetCol(Color{0,0,0,(int)(255 * fRate)})
				->SetSize(RNLib::Window()->GetWidth(), RNLib::Window()->GetHeight());
		}
	};

	// [[[ 状態:無し ]]]
	if (m_state == STATE::NONE)
		return;

	// [[[ 状態:モード設定待ち ]]]
	if (m_state == STATE::WAIT_SET_MODE) {
		LocalFunc::FillScreen(1.0f);
		return;
	}

	// [[[ 状態:開き待ち ]]]
	if (m_state == STATE::OPEN_WAIT) {
		if (++m_nStateCtr >= WAIT_TIME) {
			m_nStateCtr = 0;
			m_state = STATE::OPEN;	// 開く
		}
		LocalFunc::FillScreen(1.0f);
		return;
	}

	// [[[ 状態:開くor閉じる ]]]
	if (++m_nStateCtr >= TIME) 
	{// 状態が終わった
		// 閉じ終わった
		if (m_state == STATE::CLOSE) {
			m_state = STATE::WAIT_SET_MODE;
			LocalFunc::FillScreen(1.0f);
		}
		// 開き終わった
		else {
			m_state = STATE::NONE;
		}
		return;
	}

	float fRate = (float)m_nStateCtr / TIME;
	if (m_state == STATE::CLOSE) {
		fRate = 1.0f - fRate;
	}
	float fRateOpp = 1.0f - fRate;

	LocalFunc::FillScreen(fRateOpp);
}

//========================================
// 設定処理
// Author:RIKU NISHIMURA
//========================================
void CTransition::Set(STATE state, TYPE type) {
	if (state == STATE::OPEN)
		m_state = STATE::OPEN_WAIT;
	else
		m_state = state;
	m_type      = type;
	m_nStateCtr = 0;
}