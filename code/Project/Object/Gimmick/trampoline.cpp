//========================================
// 
// トランポリンの処理
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"
#include "../../main.h"
#include "../../../_RNLib/_Basis/Other/input.h"

#define MAX_COUNT (30)	//最大カウント数

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CTrampoline::CTrampoline(void) {
	Manager::BlockMgr()->AddList(this);

	//初期状態
	m_type = TYPE::TRAMPOLINE;
	m_width = SIZE_OF_1_SQUARE * 2.0f;
	m_height = SIZE_OF_1_SQUARE;
	m_state = STATE::NONE;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bLand = false;
	m_modelIdx[0] = RNLib::Model()->Load("data\\MODEL\\Spring_Middle.x");
	m_modelIdx[1] = RNLib::Model()->Load("data\\MODEL\\Spring_Up.x");
	m_modelIdx[2] = RNLib::Model()->Load("data\\MODEL\\Spring_Down.x");
	m_fJamp = 8.0f;
	m_nCnt = 1;
}

//========================================
// デストラクタ
//========================================
CTrampoline::~CTrampoline(void) {

}

//========================================
// 初期化処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Init(void) {

}

//========================================
// 終了処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Uninit(void) {

}

//========================================
// 更新処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Update(void) {

	if (RNLib::Input()->KeyTrigger(DIK_UPARROW))
	{
		m_nCnt = MAX_COUNT;
		m_state = STATE::UP_LAND;
	}
	if (RNLib::Input()->KeyTrigger(DIK_DOWNARROW))
	{
		m_nCnt = MAX_COUNT;
		m_state = STATE::DOWN_LAND;
	}

	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[0], false);

	if (m_nCnt > 0) {
		m_nCnt--;
		if(m_nCnt == 0)
			m_state = STATE::NONE;
	}

	if (m_state != STATE::NONE)
	{
		float fCountRate = Easing(EASE_IN, m_nCnt, MAX_COUNT);
		
		if (m_state == STATE::UP_LAND)
		{
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y - m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);
		}
		else if (m_state == STATE::DOWN_LAND)
		{
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y + m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);
		}
	}
	else if (m_state == STATE::NONE)
	{
		RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
		RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);
	}
}
//========================================
// 描画処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Draw(void) {


}