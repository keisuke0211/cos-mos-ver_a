//========================================
// 
// モード:ゲームの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../main.h"
#include "../Object/Block/block-manager.h"
#include "../Character/player.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Gameクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

CPlayer *CMode_Game::s_pPlayer = NULL;

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CMode_Game::CMode_Game(void) {

}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CMode_Game::~CMode_Game(void) {

}

//========================================
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Init(void) {
	CMode::Init();

	// カメラの視点/注視点を設定
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	Manager::BlockMgr()->Load();
	Manager::BlockMgr()->BlockCreate(0,D3DXVECTOR3(0.0f,0.0f,0.0f));
	Manager::BlockMgr()->TrampolineCreate(1,D3DXVECTOR3(40.0f, 0.0f, 0.0f));
	Manager::BlockMgr()->MeteorCreate(2, D3DXVECTOR3(80.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Manager::BlockMgr()->MoveBlockCreate(3, D3DXVECTOR3(80.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	if (s_pPlayer == NULL)
		s_pPlayer = CPlayer::Create();
}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Uninit(void) {
	CMode::Uninit();

	if (s_pPlayer != NULL)	{
		s_pPlayer->Uninit();
		delete s_pPlayer;
		s_pPlayer = NULL;
	}
}

//========================================
// 更新処理
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Update(void) {
	CMode::Update();

	if (s_pPlayer != NULL)
		s_pPlayer->Update();
}

//========================================
// 更新処理(状態)
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::ProcessState(const PROCESS process) {
	switch ((STATE)m_state) {
		//----------------------------------------
		// 無し
		//----------------------------------------
	case STATE::NONE: {
		switch (process) {
			// [[[ 初期処理 ]]]
		case PROCESS::INIT: {

		}break;
			// [[[ 終了処理 ]]]
		case PROCESS::UNINIT: {

		}break;
			// [[[ 更新処理 ]]]
		case PROCESS::UPDATE: {

		}break;
		}
	}break;
	}
}