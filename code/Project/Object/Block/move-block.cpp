//========================================
// 
// 動くブロック処理 [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================
#include "../../manager.h"
#include "move-block.h"
#include "../../main.h"

//========================================
// 静的変数
//========================================
int CMoveBlock::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CMoveBlock::CMoveBlock(void)
{
	Manager::BlockMgr()->AddList(this);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	//m_Info.pos.y -= 1.0f;
	//m_Info.nCntMove++;

	RNLib::Model()->Put(m_Info.pos, m_Info.rot, m_Info.nModelIdx);
}

//========================================
// 描画
//========================================
void CMoveBlock::Draw(void)
{

}