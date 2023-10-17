//========================================
// 
// 動くブロック処理 [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================

#include "move-block.h"

//========================================
// 静的変数
//========================================
int CMoveBlock::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CMoveBlock::CMoveBlock(void)
{
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\Lift.x");
	m_nNumAll++;
}

//========================================
// デストラクタ
//========================================
CMoveBlock::~CMoveBlock()
{
	m_nNumAll--;
}

//========================================
// 初期化
//========================================
HRESULT CMoveBlock::Init(void)
{

	return S_OK;
}

//========================================
// 終了
//========================================
void CMoveBlock::Uninit(void)
{
	
}

//========================================
// 更新
//========================================
void CMoveBlock::Update(void)
{
	m_Info.pos.x += 0.1f;
	m_Info.nCntMove++;

	RNLib::Model()->Put(m_Info.pos, m_Info.rot, m_Info.nModelIdx, false);
}

//========================================
// 描画
//========================================
void CMoveBlock::Draw(void)
{

}

//========================================
// 生成
//========================================
CMoveBlock *CMoveBlock::Create(void)
{
	CMoveBlock *pMoveBlock = NULL;

	if (pMoveBlock != NULL){ return pMoveBlock; }
	pMoveBlock = new CMoveBlock;

	// 初期化処理
	pMoveBlock->Init();

	return pMoveBlock;
}