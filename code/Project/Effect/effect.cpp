//========================================
// 
// ブロック処理
// Author:KEISUKE OTONO
// 
//========================================
// *** block.cpp ***
//========================================
#include "effect.h"
#include "../main.h"

//========================================
// 静的変数
//========================================
int CEffect::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CEffect::CEffect(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_nNumAll++;
}

//========================================
// デストラクタ
//========================================
CEffect::~CEffect()
{
	m_nNumAll--;
}

//========================================
// 初期化
//========================================
HRESULT CEffect::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;

	return S_OK;
}

//========================================
// 終了
//========================================
void CEffect::Uninit(void)
{

}

//========================================
// 更新
//========================================
void CEffect::Update(void)
{
	// 過去の位置
	RNLib::Polygon3D()->Put(INITD3DXVECTOR3, INITD3DXVECTOR3)
		->SetTex(1)
		->SetBillboard(true);
}

//========================================
// 描画
//========================================
void CEffect::Draw(void)
{

}