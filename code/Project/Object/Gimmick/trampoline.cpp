//========================================
// 
// トランポリンの処理
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"
#include "../../main.h"
#include "../../../_RNLib/_Basis/Other/input.h"
#include "../../Character/player.h"


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
	m_width = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE * 0.5f;
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

	//土台モデル
	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[0], false);

	if (m_nCnt > 0) 
	{
		m_nCnt--;
		if(m_nCnt == 0)
			m_state = STATE::NONE;
	}

	if (m_state != STATE::NONE)
	{
		//割合計算
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
		//当たり判定
		Collision();

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
//========================================
// 当たり判定処理
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Collision(void) {

	//プレイヤー情報取得
	CPlayer::Info p1, p2;
	CPlayer *pPlayer = CMode_Game::GetPlayer();
	pPlayer->GetInfo(p1, p2);

	if (/*p1が着地で乗る*/
		p1.pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width && p1.pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
		&& p1.pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height)
	{//土台の範囲内に着地で入った

		m_state = STATE::UP_LAND;
		m_nCnt = MAX_COUNT;

		if (p2.pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p2.pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
			&& p2.pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height)
		{//2pが乗っているか

			//ジャンプ量を継承
			p2.move.y = p1.move.y * 2;

			p1.move.y = 0.0f;
		}

		p1.pos.y = p1.posOLd.y;

		pPlayer->SetInfo(p1, p2);
	}
	else if (/*p2が着地で乗る*/
		p2.pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p2.pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
		&& p2.pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height)
	{//土台の範囲内に着地で入った

		m_state = STATE::DOWN_LAND;
		m_nCnt = MAX_COUNT;

		if (p1.pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p1.pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
			&& p1.pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height)
		{//1pが乗っているか

			//ジャンプ量を継承
			p1.move.y = p2.move.y * 2;

			p1.move.y = 0.0f;
		}

		p2.pos.y = p2.posOLd.y;

		pPlayer->SetInfo(p1, p2);
	}
}