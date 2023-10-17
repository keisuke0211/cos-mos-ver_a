//========================================
// 
// ステージオブジェクトの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "stage-object.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| ステージオブジェクトクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

const float CStageObject::SIZE_OF_1_SQUARE = 160.0f;

//========================================
// コンストラクタ
//========================================
CStageObject::CStageObject() {

	m_type   = TYPE::NONE;
	m_pos    = INITD3DXVECTOR3;
	m_posOld = INITD3DXVECTOR3;
	m_rot    = INITD3DXVECTOR3;
	m_width  = 0.0f;
	m_height = 0.0f;
}

//========================================
// デストラクタ
//========================================
CStageObject::~CStageObject() {

}