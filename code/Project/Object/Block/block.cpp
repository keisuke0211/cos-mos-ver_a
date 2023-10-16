//========================================
// 
// ブロック処理
// Author:KEISUKE OTONO
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"

//========================================
// 静的変数
//========================================
int CBlock::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CBlock::CBlock(void)
{
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_nNumAll++;
}

//========================================
// デストラクタ
//========================================
CBlock::~CBlock()
{
	m_nNumAll--;
}

//========================================
// 初期化
//========================================
HRESULT CBlock::Init(void)
{

	return S_OK;
}

//========================================
// 終了
//========================================
void CBlock::Uninit(void)
{
	/*CObjectX::Uninit();*/
}

//========================================
// 更新
//========================================
void CBlock::Update(void)
{

}

//========================================
// 描画
//========================================
void CBlock::Draw(void)
{

}

//========================================
// 生成
//========================================
CBlock *CBlock::Create(void)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL){ return pBlock; }
	pBlock = new CBlock;

	// 初期化処理
	pBlock->Init();

	return pBlock;
}