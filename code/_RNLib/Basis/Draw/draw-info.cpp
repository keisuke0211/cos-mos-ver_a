//========================================
// 
// 基底用描画情報クラスの定義
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 基底用描画情報クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CDrawInfoBase::CDrawInfoBase() {

	m_type     = TYPE::NONE;
	m_priority = 0;
}

//========================================
// デストラクタ
//========================================
CDrawInfoBase::~CDrawInfoBase() {

}