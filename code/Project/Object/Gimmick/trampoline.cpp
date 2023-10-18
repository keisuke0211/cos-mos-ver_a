//========================================
// 
// トランポリンの処理
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"
#include "../../main.h"
#include "../../../_RNLib/_Basis/Other/input.h"

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
	m_modelIdx[0] = RNLib::Model()->Load("data\\MODEL\\Block.x");
	m_modelIdx[1] = RNLib::Model()->Load("data\\MODEL\\SpringFloor.x");
	m_modelIdx[2] = RNLib::Model()->Load("data\\MODEL\\SpringFloor.x");
	m_nCnt = 1;
	m_fDifY = 0.0f;
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

	//位置記憶
	m_posOld = m_pos;

	if (RNLib::Input()->KeyTrigger(DIK_UPARROW))
	{
		m_state = STATE::UP_LAND;

		m_fDifY = 20.0f;

		m_nCnt = 30;
	}
	if (RNLib::Input()->KeyTrigger(DIK_DOWNARROW))
	{
		m_state = STATE::DOWN_LAND;

		m_fDifY = -20.0f;

		m_nCnt = 30;
	}

	D3DXMATRIX mtx = ConvPosRotToMatrix(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXMatrixScaling(&mtx, m_scale.x, m_scale.y, m_scale.z);
	RNLib::Model()->Put(mtx, m_modelIdx[0], false);

	D3DXMATRIX mtx1 = ConvPosRotToMatrix(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXMatrixScaling(&mtx1, m_scale.x/3, m_scale.y/3, m_scale.z/3);
	RNLib::Model()->Put(D3DXVECTOR3(0.0f, 10.0f + m_fDifY / m_nCnt, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);

	RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
	RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y + -20.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);

	if (m_nCnt > 1 && m_state != STATE::NONE)
	{
		m_nCnt--;
	}
	else if(m_nCnt < 30)
	{
		m_state = STATE::NONE;

		m_nCnt++;
	}
}

//========================================
// 描画処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Draw(void) {


}