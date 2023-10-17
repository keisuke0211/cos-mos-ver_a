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
// Author:RIKU NISHIMURA
//========================================
void CTransition::Update(void) {
#if 0
	//===== [[[ ローカル関数宣言 ]]]
	struct LocalFunc {
		static void FillScreen(void) {
			RNLib::Polygon2D()->SetVtxPos(
				D3DXVECTOR3(0.0f                       , 0.0f                        , 0.0f),
				D3DXVECTOR3(RNLib::Window()->GetWidth(), 0.0f                        , 0.0f),
				D3DXVECTOR3(0.0f                       , RNLib::Window()->GetHeight(), 0.0f),
				D3DXVECTOR3(RNLib::Window()->GetWidth(), RNLib::Window()->GetHeight(), 0.0f),
				COLOR_BLACK);
		}
	};

	if (m_state == STATE::NONE) {
		return;
	}
	else if (m_state == STATE::WAIT_SET_MODE) {
		LocalFunc::FillScreen();
		return;
	}
	else if (m_state == STATE::OPEN_WAIT) {
		if (++m_nStateCtr >= WAIT_TIME) {
			m_nStateCtr = 0;
			m_state = STATE::OPEN;
		}
		LocalFunc::FillScreen();
		return;
	}
	else if (++m_nStateCtr >= TIME) {
		if (m_state == STATE::CLOSE) {
			m_state = STATE::WAIT_SET_MODE;
			LocalFunc::FillScreen();
		}
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

	// [    ]
	// □●□
	// [    ]
	
	float fSetScale      = fRate * HOLE_SCALE_MAX;
	int   nTexIdx        = RNLib::Visual()->GetTextureIdx(CVisual::TEXTURE::TRANSITION_HOLE);
	float fTexWidthHalf  = RNLib::Texture()->GetWidth2D (nTexIdx) * fSetScale * 0.5f;
	float fTexHeightHalf = RNLib::Texture()->GetHeight2D(nTexIdx) * fSetScale * 0.5f;
	float fLeftX         = RNLib::Window()->GetCenterX() - fTexWidthHalf;
	float fRightX        = RNLib::Window()->GetCenterX() + fTexWidthHalf;
	float fTopY          = RNLib::Window()->GetCenterY() - fTexHeightHalf;
	float fBottomY       = RNLib::Window()->GetCenterY() + fTexHeightHalf;
	float fScreenWidth   = RNLib::Window()->GetWidth();
	float fScreenHeight  = RNLib::Window()->GetHeight();

	{// [[[ 中央の穴 ]]]
		RNLib::Polygon2D()->Set(
			fSetScale, fSetScale,
			RNLib::Window()->GetCenterPos(),
			INITD3DXVECTOR3,
			COLOR_BLACK,
			nTexIdx);
	}
	// [[[ 上 ]]]
	RNLib::Polygon2D()->SetVtx(
		D3DXVECTOR3(0.0f        , 0.0f , 0.0f),
		D3DXVECTOR3(fScreenWidth, 0.0f , 0.0f),
		D3DXVECTOR3(0.0f        , fTopY, 0.0f),
		D3DXVECTOR3(fScreenWidth, fTopY, 0.0f),
		COLOR_BLACK);
	// [[[ 下 ]]]
	RNLib::Polygon2D()->SetVtx(
		D3DXVECTOR3(0.0f        , fBottomY    , 0.0f),
		D3DXVECTOR3(fScreenWidth, fBottomY    , 0.0f),
		D3DXVECTOR3(0.0f        , fScreenWidth, 0.0f),
		D3DXVECTOR3(fScreenWidth, fScreenWidth, 0.0f),
		COLOR_BLACK);
	// [[[ 左 ]]]
	RNLib::Polygon2D()->SetVtx(
		D3DXVECTOR3(0.0f  , fTopY   , 0.0f),
		D3DXVECTOR3(fLeftX, fTopY   , 0.0f),
		D3DXVECTOR3(0.0f  , fBottomY, 0.0f),
		D3DXVECTOR3(fLeftX, fBottomY, 0.0f),
		COLOR_BLACK);
	// [[[ 下 ]]]
	RNLib::Polygon2D()->SetVtx(
		D3DXVECTOR3(fRightX     , fTopY   , 0.0f),
		D3DXVECTOR3(fScreenWidth, fTopY   , 0.0f),
		D3DXVECTOR3(fRightX     , fBottomY, 0.0f),
		D3DXVECTOR3(fScreenWidth, fBottomY, 0.0f),
		COLOR_BLACK);
#endif
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