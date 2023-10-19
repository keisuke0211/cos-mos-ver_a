//========================================
// 
// ロケット
// Author:KEISUKE OTONO
// 
//========================================
// *** rocket.cpp ***
//========================================
#include "rocket.h"
#include "../../main.h"

//========================================
// コンストラクタ
//========================================
CRocket::CRocket(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BLOCK;
	m_width = SIZE_OF_1_SQUARE*3;
	m_height = SIZE_OF_1_SQUARE*3;

	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\rocket.x");
}

//========================================
// デストラクタ
//========================================
CRocket::~CRocket()
{

}

//========================================
// 初期化
//========================================
HRESULT CRocket::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;

	return S_OK;
}

//========================================
// 終了
//========================================
void CRocket::Uninit(void)
{

}

//========================================
// 更新
//========================================
void CRocket::Update(void)
{
	// 過去の位置
	RNLib::Model()->Put(m_pos, m_rot, m_Info.nModelIdx, false);
}

//========================================
// 描画
//========================================
void CRocket::Draw(void)
{

}