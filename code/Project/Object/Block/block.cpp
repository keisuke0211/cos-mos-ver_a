//========================================
// 
// ブロック処理
// Author:KEISUKE OTONO
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "../../main.h"

//========================================
// 静的変数
//========================================
int CBlock::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CBlock::CBlock(void)
{
	Manager::BlockMgr()->AddList(this);
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nModelIdx = 0;
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
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;

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
	// 過去の位置
	m_Info.posOld = m_Info.pos;

	RNLib::Model()->Put(m_Info.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Info.nModelIdx, false);
}

//========================================
// 描画
//========================================
void CBlock::Draw(void)
{

}

//========================================
// 読み込み
//========================================
void CBlock::Load(void)
{

}