//========================================
// 
// ギミックの処理
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CTrampoline::CTrampoline(void) {
	m_type = TYPE::NONE;
}

//========================================
// デストラクタ
//========================================
CTrampoline::~CTrampoline(void) {

}

//========================================
// 初期化処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Init(void) {

	ModelIdx = RNLib::Model()->Load("data\\MODEL\\Spring Floor.x");
}

//========================================
// 終了処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Uninit(void) {

}

//========================================
// 更新処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Update(void) {

	RNLib::Model()->Put(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ModelIdx, false);
}

//========================================
// 生成処理
//========================================
CTrampoline* CTrampoline::Create(void) {

	// 種類に応じてオブジェクト生成
	CTrampoline* pGimmick = NULL;

	//メモリ生成
	pGimmick = new CTrampoline;

	// 初期化処理
	pGimmick->Init();

	return pGimmick;
}

//========================================
// 描画処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Draw(void) {


}