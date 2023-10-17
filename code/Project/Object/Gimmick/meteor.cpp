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
D3DXVECTOR3 static const METEOR_ADDROT = { 0.10f,0.02f,0.01f };				// 隕石の回転の移動量
D3DXVECTOR3 static const METEOR_UNINIT_MINPOS = { -150.0f,-150.0f,0.0f };	// 最小の位置
D3DXVECTOR3 static const METEOR_UNINIT_MAXPOS = { 150.0f,150.0f,0.0f };		// 最大の位置
float			static const METEOR_BLINK_MAX = { 5.0f };					// 点滅アニメーションの最大数
float			static const METEOR_BLINK_MIN = { 0.5f };					// 点滅の最小数
float			static const METEOR_BLINK_ADJ = { 10.0f };					// 点滅アニメーションの調整
//========================================
// コンストラクタ
//========================================
CMeteor::CMeteor(void) {
	Manager::BlockMgr()->AddList(this);
	
	// 各情報の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fblink = 0.0f;
	m_nblinlAnim = 0;
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


	m_pos += m_move;			// 移動量の追加
	m_rot += METEOR_ADDROT;		// 向きの移動量の追加

	// 点滅アニメーションの計算
	m_fblink = (m_nblinlAnim % (int)METEOR_BLINK_MAX);
	m_fblink = (m_fblink / (float)METEOR_BLINK_ADJ);
	m_fblink =  m_fblink + METEOR_BLINK_MIN;

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false)
		->SetOutLine(true)
		->SetBrightnessOfEmissive(m_fblink)
		;

	m_nblinlAnim++;	// 点滅アニメーションの増加

	if (m_pos.x >= METEOR_UNINIT_MAXPOS.x || m_pos.y >= METEOR_UNINIT_MAXPOS.y || m_pos.x <= METEOR_UNINIT_MINPOS.x || m_pos.y <= METEOR_UNINIT_MINPOS.y)
	{
		// 削除
		Delete();
	}
}

//========================================
// 描画処理
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Draw(void) {


}