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
#define COLOR_UP   Color{45,212,140,255}
#define COLOR_DOWN Color{206,54,112,255}
static const int s_MaxSummon = 8;		// 出現する位置の最大数
static const D3DXVECTOR3 s_SummonPos[s_MaxSummon] = {	// 出現する位置
	D3DXVECTOR3(-300.0f, 300.0f, 300.0f),
	D3DXVECTOR3(0.0f,	 200.0f, 300.0f),
	D3DXVECTOR3(200.0f,  300.0f, 300.0f),
	D3DXVECTOR3(-100.0f, 100.0f,   300.0f),
	D3DXVECTOR3(100.0f,	 100.0f,   300.0f),
	D3DXVECTOR3(-300.0f, -200.0f,300.0f),
	D3DXVECTOR3(0.0f,	 -200.0f,300.0f),
	D3DXVECTOR3(100.0f,  -300.0f,300.0f),
};

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

	// 遷移設定
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// カメラの視点/注視点を設定
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	Manager::BlockMgr()->Load();
	Manager::BlockMgr()->MoveBlockCreate(D3DXVECTOR3(-250.0f, -10.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), 50.0f);

	BackGroundPut(Color{ 100,100,100,255 }, Color{ 100,100,100,255 });

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

	if (RNLib::Input()->GetKeyTrigger(DIK_RETURN))
		Manager::StgEd()->SwapStage(1);

	if (RNLib::Input()->GetKeyTrigger(DIK_SPACE) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		Manager::Transition(CMode::TYPE::RESULT, CTransition::TYPE::FADE);

	// 背景(仮)
	{
		float width = RNLib::Window()->GetWidth();
		float height = RNLib::Window()->GetHeight();
		RNLib::Polygon3D()->Put(D3DXVECTOR3(0.0f, -height*0.25f, 400.0f), INITD3DXVECTOR3)
			->SetLighting(false)
			->SetCol(COLOR_DOWN)
			->SetSize(width * 2.0f, height * 0.5f)
			->SetPriority(-2)
			->SetZTest(false);
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
void CMode_Game::BackGroundPut(Color mincol, Color addcol) {

	D3DXVECTOR3 pos,rot;
	Color col;
	CPlanet::STAR_TYPE type;

	for (int nCntPut = 0; nCntPut < s_MaxSummon; nCntPut++)
	{
		pos = s_SummonPos[nCntPut];	// 出現する位置の設定
		pos += D3DXVECTOR3(rand() % 100 - 100, rand() % 100 - 100, rand() % 150 - 50);	// 位置の設定

		type = (CPlanet::STAR_TYPE)(rand() % (int)CPlanet::STAR_TYPE::MAX);	// 種類の設定
		col = Color{mincol.r + rand() % addcol.r,mincol.g + rand() % addcol.g,mincol.b + rand() % addcol.b,255 };	// 色の設定
		rot = D3DXVECTOR3(rand() % 6 - 3, rand() % 6 - 3, rand() % 6 - 3);	// 向きの設定

		Manager::BlockMgr()->PlanetCreate(pos,rot, type, col);	// 惑星の生成
	}
}
