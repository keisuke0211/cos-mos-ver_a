//========================================
// 
// 惑星の処理
// Author:KOMURO HIROMU
// 
//========================================
#include "Planet.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CPlanet::CPlanet(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// 種類の設定
								// 大きさの設定
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// 各情報の初期化
	ModelIdx = RNLib::Model()->Load("data\\MODEL\\comet_star.x");
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//========================================
// デストラクタ
//========================================
CPlanet::~CPlanet(void) {

}

//========================================
// 初期化処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Init(void) {

}

//========================================
// 終了処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Uninit(void) {

}

//========================================
// 更新処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Update(void) {

	m_pos += m_move;

	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), ModelIdx, false);
}

//========================================
// 描画処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Draw(void) {


}