//========================================
// 
// フォグの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ fog.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CFogクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CFog::CFog() {
	m_col        = INITCOLOR;
	m_fDistStart = 0.0f;
	m_fDistEnd   = 0.0f;
	m_bUse       = false;
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CFog::~CFog() {

}

//========================================
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void CFog::Init(void) {
	RNLib::Window()->GetD3DDevice()->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	RNLib::Window()->GetD3DDevice()->SetRenderState(D3DRS_FOGCOLOR, ColorToD3DCOLOR(INITCOLOR));
}

//========================================
// 設定
// Author:RIKU NISHIMURA
//========================================
void CFog::SetCol(Color col) {
	m_col = col;
	RNLib::Window()->GetD3DDevice()->SetRenderState(D3DRS_FOGCOLOR, ColorToD3DCOLOR(col));
	SetBGColor(col);
}
void CFog::SetDistStart(float fDistStart) {
	m_fDistStart = fDistStart;
	RNLib::Window()->GetD3DDevice()->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fDistStart));
}
void CFog::SetDistEnd(float fDistEnd) {
	m_fDistEnd = fDistEnd;
	RNLib::Window()->GetD3DDevice()->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fDistEnd));
}

//========================================
// 有効無効設定
// Author:RIKU NISHIMURA
//========================================
void CFog::Enable(bool bEnable) {
	if (!m_bUse)
		return;
	RNLib::Window()->GetD3DDevice()->SetRenderState(D3DRS_FOGENABLE, bEnable);
}