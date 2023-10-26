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
static const int s_PlanetMaxSummon = 8;		// 出現する位置の最大数
static const int s_StarMaxSummon = 10;		// 出現する位置の最大数
static const D3DXVECTOR3 s_PlanetSummonPos[s_PlanetMaxSummon] = {	// 惑星の出現する位置
	D3DXVECTOR3(-300.0f, 300.0f, 300.0f),
	D3DXVECTOR3(0.0f,	 200.0f, 300.0f),
	D3DXVECTOR3(200.0f,  300.0f, 300.0f),
	D3DXVECTOR3(-100.0f, 100.0f,   300.0f),
	D3DXVECTOR3(100.0f,	 100.0f,   300.0f),
	D3DXVECTOR3(-300.0f, -200.0f,300.0f),
	D3DXVECTOR3(0.0f,	 -200.0f,300.0f),
	D3DXVECTOR3(100.0f,  -300.0f,300.0f),
};
static const D3DXVECTOR3 s_StarSummonPos[s_StarMaxSummon] = {	// 星の出現する位置
	D3DXVECTOR3(-300.0f, 300.0f, 500.0f),
	D3DXVECTOR3(0.0f,	 200.0f, 500.0f),
	D3DXVECTOR3(200.0f,  300.0f, 500.0f),
	D3DXVECTOR3(-100.0f, 100.0f, 500.0f),
	D3DXVECTOR3(100.0f,	 100.0f, 500.0f),
	D3DXVECTOR3(-300.0f, 200.0f,500.0f),
	D3DXVECTOR3(0.0f,	 -200.0f,500.0f),
	D3DXVECTOR3(-400.0f, -300.0f,500.0f),
	D3DXVECTOR3(400.0f,  -100.0f ,500.0f),
	D3DXVECTOR3(500.0f,  0.0f ,500.0f),
};
CPlayer *CMode_Game::s_pPlayer = NULL;
CPlayer* CMode_Game::GetPlayer(void) { return s_pPlayer; }
int CMode_Game::m_nStageIdx = 0;

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
	Manager::BlockMgr()->ShiningWaveCreate();
	Manager::BlockMgr()->RoadTripLaserCreate(D3DXVECTOR3(250.0f, -10.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), 50.0f);

	BackGroundPut(Color{ 100,100,100,255 }, Color{ 100,100,100,255 });

	if (s_pPlayer == NULL)
		s_pPlayer = CPlayer::Create();

	// 読込
	/* ブロック	*/Manager::BlockMgr()->Load();

	// ステージ生成
	Manager::StgEd()->StageLoad(m_nStageIdx);

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
		Manager::StgEd()->SwapStage(2);

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

	D3DXVECTOR3 Planpos,Starpos,rot;
	Color col;
	CPlanet::STAR_TYPE type;

	for (int nCntPut = 0; nCntPut < s_PlanetMaxSummon; nCntPut++)
	{
		// 惑星の設定
		Planpos = s_PlanetSummonPos[nCntPut];	// 出現する位置の設定
		Planpos += D3DXVECTOR3(rand() % 100 - 100, rand() % 100 - 100, rand() % 150 - 50);	// 位置の設定

		type = (CPlanet::STAR_TYPE)(rand() % (int)CPlanet::STAR_TYPE::MAX);	// 種類の設定
		col = Color{ mincol.r + rand() % addcol.r,mincol.g + rand() % addcol.g,mincol.b + rand() % addcol.b,255 };	// 色の設定
		rot = D3DXVECTOR3(rand() % 6 - 3, rand() % 6 - 3, rand() % 6 - 3);	// 向きの設定
		//Manager::BlockMgr()->PlanetCreate(Planpos, rot, type, col);	// 惑星の生成
	}

	for (int nCntPut = 0; nCntPut < s_StarMaxSummon; nCntPut++)
	{
		// 星の設定
		Starpos = s_StarSummonPos[nCntPut];	// 出現する位置の設定
		Starpos += D3DXVECTOR3(rand() % 50 - 50, rand() % 50 - 50, 0.0f);	// 位置の設定

		//Manager::BlockMgr()->StarCreate(Starpos, INITD3DXVECTOR3);	// 星の生成
	}
}
