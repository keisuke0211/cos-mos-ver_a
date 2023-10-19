//========================================
// 
// モード:ゲームの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../main.h"
#include "../Character/player.h"
#include "../System/StageEditor.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Gameクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================
static const float DISTANCE = 100.0f;	// 距離

#define COLOR_UP   Color{45,212,140,255}
#define COLOR_DOWN Color{206,54,112,255}

CPlayer *CMode_Game::s_pPlayer = NULL;
CPlayer* CMode_Game::GetPlayer(void) { return s_pPlayer; }

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
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	Manager::BlockMgr()->Load();

	//BackGroundPut();

	if (s_pPlayer == NULL)
		s_pPlayer = CPlayer::Create();

	// 読込
	/* ブロック	*/Manager::BlockMgr()->Load();
	/* ステージ	*/Manager::StgEd()->FileLoad();

	// ステージ生成
	Manager::StgEd()->StageLoad(0);

	SetBGColor(COLOR_UP);
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

	Manager::BlockMgr()->ReleaseAll();
}

//========================================
// 更新処理
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Update(void) {
	CMode::Update();

	if (s_pPlayer != NULL)
		s_pPlayer->Update();

	if (RNLib::Input()->KeyTrigger(DIK_RETURN))
		Manager::StgEd()->SwapStage(1);

	if (RNLib::Input()->KeyTrigger(DIK_SPACE))
		Manager::Transition(CMode::TYPE::RESULT, CTransition::TYPE::HOLE);

	// 背景(仮)
	{
		float width = RNLib::Window()->GetWidth();
		float height = RNLib::Window()->GetHeight();
		RNLib::Polygon3D()->Put(D3DXVECTOR3(0.0f, -height*0.3f, 400.0f), INITD3DXVECTOR3)
			->SetLighting(false)
			->SetCol(COLOR_DOWN)
			->SetSize(width * 2.0f, height * 0.5f)
			->SetPriority(-2);
	}
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

//========================================
// 背景の生成処理
// Author:KOMURO HIROMU
//========================================
void CMode_Game::BackGroundPut(void){

	D3DXVECTOR3 *posOld[10] = {};
	D3DXVECTOR3 pos;
	CPlanet::STAR_TYPE *typeOld[(int)CPlanet::STAR_TYPE::MAX] = {};
	CPlanet::STAR_TYPE type;


	for (int nCntPut = 0; nCntPut < 10; nCntPut++)
	{
		bool bpos = false;
		bool btype = false;
		while (bpos != true)
		{
			pos = D3DXVECTOR3(rand() % 400 - 200, rand() % 400 - 200, 100);	// 位置の設定

			if (nCntPut == 0)
			{
				bpos = true;
				posOld[nCntPut] = &pos;	// 代入
			}
			for (int nCntpos = 0; nCntpos < nCntPut; nCntpos++)
			{
				if (posOld[nCntpos] != NULL)
				{
					if (posOld[nCntpos]->x - DISTANCE >= pos.x + DISTANCE &&
						posOld[nCntpos]->x + DISTANCE <= pos.x - DISTANCE &&
						posOld[nCntpos]->y - DISTANCE >= pos.y + DISTANCE &&
						posOld[nCntpos]->y + DISTANCE >= pos.y - DISTANCE)
					{
						bpos = false;
					}
					else
					{
						bpos = true;
						posOld[nCntPut] = &pos;	// 代入
					}
				}
			}
		}
		type = (CPlanet::STAR_TYPE)(rand() % (int)CPlanet::STAR_TYPE::MAX);	// 種類の設定

		Manager::BlockMgr()->PlanetCreate(pos, type);	// 惑星の生成
	
	}
}
