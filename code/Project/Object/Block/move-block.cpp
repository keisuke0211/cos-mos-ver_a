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
	m_type = TYPE::MOVE_BLOCK;

	Manager::BlockMgr()->AddList(this);

	m_width  = SIZE_OF_1_SQUARE * 2;
	m_height = SIZE_OF_1_SQUARE;

	m_Info.move = INITD3DXVECTOR3;
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
	

	m_pos.x += 1.0f;

	RNLib::Model()->Put(m_pos, m_rot, m_Info.nModelIdx);
}

//========================================
// 描画
//========================================
void CMoveBlock::Draw(void)
{

}