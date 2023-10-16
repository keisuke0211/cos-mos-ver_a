//========================================
// 
// ブロックマネージャー
// Author:KEISUKE OTONO
// 
//========================================
// *** block-manager.h ***
//========================================
#include "block-manager.h"

//========================================
// コンストラクタ
//========================================
CBlockMgr::CBlockMgr(void)
{
	
}

//========================================
// デストラクタ
//========================================
CBlockMgr::~CBlockMgr()
{
	
}

//========================================
// 初期化
//========================================
void CBlockMgr::Init(void)
{
	CListMgr::Init();
}

//========================================
// 終了
//========================================
void CBlockMgr::Uninit(void)
{
	
}

//========================================
// 更新
//========================================
void CBlockMgr::Update(void)
{
	CListMgr::Update();
}

//========================================
// 生成
//========================================
CBlock *CBlockMgr::Create(D3DXVECTOR3 pos)
{
	CBlock *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CBlock;

	// 初期化処理
	pObj->Init();
	pObj->SetPos(pos);

	return pObj;
}

CTrampoline *CBlockMgr::TCreate(D3DXVECTOR3 pos)
{
	CTrampoline *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CTrampoline;

	// 初期化処理
	pObj->Init();

	return pObj;
}
