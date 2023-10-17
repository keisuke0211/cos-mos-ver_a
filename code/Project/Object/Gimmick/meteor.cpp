//========================================
// 
// 隕石の処理
// Author:KOMURO HIROMU
// 
//========================================
#include "meteor.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================
D3DXVECTOR3 static const METEOR_ADDROT = { 0.1f,0.2f,0.1f };	// 隕石の回転の移動量
D3DXVECTOR3 static const METEOR_UNINIT_MINPOS = { -1000.0f,-1000.0f,0.0f };	// 最小の位置
D3DXVECTOR3 static const METEOR_UNINIT_MAXPOS = { 1000.0f,1000.0f,0.0f };	// 最大の位置
//========================================
// コンストラクタ
//========================================
CMeteor::CMeteor(void) {
	Manager::BlockMgr()->AddList(this);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================
// デストラクタ
//========================================
CMeteor::~CMeteor(void) {

}

//========================================
// 初期化処理
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Init(void) {

}

//========================================
// 終了処理
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Uninit(void) {

}

//========================================
// 更新処理
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Update(void) {

	// 移動量の追加
	m_pos += m_move;
	// 向きの移動量の追加
	m_rot += METEOR_ADDROT;

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false);

	if (m_pos.x >= METEOR_UNINIT_MAXPOS.x || m_pos.y >= METEOR_UNINIT_MAXPOS.y || m_pos.x <= METEOR_UNINIT_MINPOS.x || m_pos.y <= METEOR_UNINIT_MINPOS.y)
	{

	}
}

//========================================
// 描画処理
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Draw(void) {


}