//========================================
// 
// 動くブロック処理 [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================
#include "../../manager.h"
#include "move-block.h"
#include "../../main.h"

#define ROT_MAG		(0.05f)	// 倍率
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
	m_Info.frefdef = 0.0f;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\Lift.x");
	nModelIdx = RNLib::Model()->Load("data\\MODEL\\Lift_Gear.x");
	m_nNumAll++;

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	m_Info.pos += m_Info.move;	// 移動量の増加
	if (m_Info.move.y != 0.0f)
	{
		m_rot.z += (m_Info.move.y + 1.0f) * ROT_MAG;
	}
	if (m_Info.move.x != 0.0f)
	{
		float f = m_Info.move.x;
		if (f < 0.0f)
			f -= 1.0f;
		else
			f += 1.0f;

		m_rot.z += f * ROT_MAG * -1;
	}

	// xの移動量の反転
	if (m_Info.posOld.x + m_Info.frefdef <= m_Info.pos.x || m_Info.posOld.x - m_Info.frefdef >= m_Info.pos.x)
	{
		m_Info.move.x *= -1;
	}
	// yの移動量の反転
	if (m_Info.posOld.y + m_Info.frefdef <= m_Info.pos.y || m_Info.posOld.y - m_Info.frefdef >= m_Info.pos.y)
	{
		m_Info.move.y *= -1;
	}

	RNLib::Model()->Put(m_Info.pos, m_Info.rot, m_Info.nModelIdx);
	RNLib::Model()->Put(m_Info.pos, m_rot, nModelIdx);
}

//========================================
// 描画
//========================================
void CMoveBlock::Draw(void)
{

}