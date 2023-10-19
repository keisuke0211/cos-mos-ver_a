//========================================
// 
// ブロック (判定 無し)
// Author:KEISUKE OTONO
// 
//========================================
// *** fill-block.cpp ***
//========================================
#include "fill-block.h"
#include "../../main.h"

//========================================
// コンストラクタ
//========================================
CFillBlock::CFillBlock(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::FILLBLOCK;
	m_width = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE;

	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\Block.x");
}

//========================================
// デストラクタ
//========================================
CFillBlock::~CFillBlock()
{

}

//========================================
// 初期化
//========================================
HRESULT CFillBlock::Init(void)
{
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;

	return S_OK;
}

//========================================
// 終了
//========================================
void CFillBlock::Uninit(void)
{

}

//========================================
// 更新
//========================================
void CFillBlock::Update(void)
{
	// 過去の位置
	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Info.nModelIdx, false);
}

//========================================
// 描画
//========================================
void CFillBlock::Draw(void)
{

}