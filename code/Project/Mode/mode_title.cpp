//========================================
// 
// モード:タイトル処理
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_title.h"
#include "mode_game.h"
#include "../System/words/words.h"
#include "../System/words/font-text.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Titleクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Title::CMode_Title(void) {
	m_TexIdx = 0;
	m_nSelect = 0;

	m_StageType = NULL;;
}

//========================================
// デストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Title::~CMode_Title(void) {

}

//========================================
// 初期化処理
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Init(void) {
	CMode::Init();

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_Menu[nCnt] = {NULL};
	}
	Title = TITLE_OUTSET;
	m_nSelect = 0;

	m_TexIdx = RNLib::Texture()->Load("data\\TEXTURE\\BackGround\\title.jpg");

	// 遷移設定
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// カメラの視点/注視点を設定
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	// 背景色変更
	SetBGColor(Color{ 200,0,0,255 });


	FormFont pFont = {INITCOLOR,45.0f,1,1,-1,};
	FormShadow pShadow = { Color{0,0,0,255},true, D3DXVECTOR3(6.0f,6.0f,0.0f) ,D3DXVECTOR2(4.0f,4.0f) };

	m_Menu[0] = CFontText::Create(CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 600.0f, 0.0f),D3DXVECTOR2(1080.0f, 100.0f),
		" ",CFont::FONT_851GKKTT,&pFont);

	pFont = { INITCOLOR,70.0f,1,1,-1, };
	m_Menu[1] = CFontText::Create(CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(340.0f, 100.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		"COS/MOS", CFont::FONT_ROND_B, &pFont,false,&pShadow);

	pFont = { INITCOLOR,70.0f,5,10,-1 };// 45
	m_Menu[2] = CFontText::Create(CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 600.0f, 0.0f),D3DXVECTOR2(1080.0f, 100.0f),
		"ボタンを押して始めてね",CFont::FONT_ROND_B,&pFont, false);
}

//========================================
// 終了処理
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Uninit(void) {
	CMode::Uninit();

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			m_Menu[nCnt]->Uninit();
			m_Menu[nCnt] = NULL;
		}
	}
}

//========================================
// 更新処理
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Update(void) {
	CMode::Update();

	if (Title == TITLE_MENU)
		Menu();
	else if (Title == TITLE_SELECT)
		StageSelect();

	RNLib::Polygon2D()->Put(D3DXVECTOR3(RNLib::Window()->GetCenterPos().x, RNLib::Window()->GetCenterPos().y, -1.0f), 0.0f, false)
		->SetSize(1280.0f,720.0f)
		->SetCol(Color{255,255,255,255})
		->SetTex(m_TexIdx);

	if (RNLib::Input()->GetKeyTrigger(DIK_RETURN) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
	{
		switch (Title)
		{
		case TITLE_OUTSET:
		{
			// メニュー生成
			MenuCreate();
		}
		break;
		case TITLE_MENU:
		{
			switch (m_nSelect)
			{
			case MENU_GAME:
				Manager::StgEd()->FileLoad();
				SelectCreate();
				break;
			case MENU_SERRING:
				break;
			case MENU_END:
				//ゲームの終了
				PostQuitMessage(0);
				break;
			}
		}
		break;
		case TITLE_SELECT:
		{
			TextClear(TITLE_NEXT);
			CMode_Game::SetStage(m_nSelect);
			Manager::Transition(CMode::TYPE::GAME, CTransition::TYPE::NONE);

			delete[] m_StageType;
			m_StageType = NULL;
		}
		break;
		}
	}
}

//========================================
// 更新処理(状態)
// Author:KEISUKE OTONO
//========================================
void CMode_Title::ProcessState(const PROCESS process) {
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
// メニュー生成
// Author:KEISUKE OTONO
//========================================
void CMode_Title::MenuCreate(void)
{
	FormFont pFont = { INITCOLOR,55.0f,5,10,-1};// 45

	TextClear(TITLE_MENU);

	m_Menu[0] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 150.0f, 0.0f),D3DXVECTOR2(450.0f, 100.0f),// 360,100
		"ゲーム",CFont::FONT_ROND_B,&pFont);

	m_Menu[1] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 300.0f, 0.0f), D3DXVECTOR2(450.0f, 100.0f),
		"オプション", CFont::FONT_ROND_B, &pFont);

	m_Menu[2] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 450.0f, 0.0f), D3DXVECTOR2(450.0f, 100.0f),
		"ゲームをやめる", CFont::FONT_ROND_B, &pFont);
}

//========================================
// メニュー
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Menu(void)
{
	// 色
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			if (nCnt == m_nSelect)
			{
				m_Menu[nCnt]->SetBoxColor(Color{0,255,0,255});
			}
			else
			{
				m_Menu[nCnt]->SetBoxColor(INITCOLOR);
			}
		}
	}

	// -- メニュー選択 ---------------------------
	if (RNLib::Input()->GetKeyTrigger(DIK_W) || RNLib::Input()->GetKeyTrigger(DIK_UP) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::UP) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT,CInput::INPUT_ANGLE::UP))
	{
		m_nSelect--;
	}
	else if (RNLib::Input()->GetKeyTrigger(DIK_S) || RNLib::Input()->GetKeyTrigger(DIK_DOWN) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::DOWN) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::DOWN))
	{
		m_nSelect++;
	}

	// ループ制御
	IntLoopControl(&m_nSelect, MENU_MAX, 0);
}

//========================================
// ステージ選択の生成
// Author:KEISUKE OTONO
//========================================
void CMode_Title::SelectCreate(void)
{
	int nMax = Manager::StgEd()->GetStageMax();
	
	m_StageType = new StageType[nMax];

	for (int nCnt = 0; nCnt < nMax; nCnt++)
	{
		char *aTexFile = Manager::StgEd()->GetInfo()[nCnt].aTexFile;
		char *aStgName = Manager::StgEd()->GetInfo()[nCnt].aStageName;

		m_StageType[nCnt].nTex = RNLib::Texture()->Load(aTexFile);
		sprintf(m_StageType[nCnt].Text, aStgName);
	}

	TextClear(TITLE_SELECT);
	FormFont pFont = { INITCOLOR,65.0f,5,10,-1 };// 45
	m_Menu[0] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR2(360.0f, 100.0f),
		m_StageType[0].Text, CFont::FONT_ROND_B, &pFont);
}

//========================================
// ステージ選択
// Author:KEISUKE OTONO
//========================================
void CMode_Title::StageSelect(void)
{
	int nMax = Manager::StgEd()->GetStageMax();
	int nChoiceTex = RNLib::Texture()->Load("data\\TEXTURE\\Effect\\mark_smiley_000.png");
	int nNoChoiceTex = RNLib::Texture()->Load("data\\TEXTURE\\Effect\\eff_Circle_005.png");
	int nPrevTex = RNLib::Texture()->Load("data\\TEXTURE\\Effect\\eff_Arrow_01.png");
	int nNextTex = RNLib::Texture()->Load("data\\TEXTURE\\Effect\\eff_Arrow_00.png");

	int nTexIdx = 0;

	// ステージ画像
	RNLib::Polygon2D()->Put(D3DXVECTOR3(RNLib::Window()->GetCenterPos().x, RNLib::Window()->GetCenterPos().y - 120.0f, -1.0f), 0.0f, false)
		->SetSize(880.0f, 480.0f)
		->SetCol(Color{ 255,255,255,255 })
		->SetTex(m_StageType[m_nSelect].nTex);

	if (m_nSelect != 0)
	{
		RNLib::Polygon2D()->Put(D3DXVECTOR3(400.0f, 550.0f, 0.0), 0.0f, false)
			->SetSize(100.0f, 100.0f)
			->SetCol(Color{ 50,255,0,255 })
			->SetTex(nPrevTex);
	}
	if(m_nSelect != nMax - 1)
	RNLib::Polygon2D()->Put(D3DXVECTOR3(880.0f, 550.0f, 0.0), 0.0f, false)
		->SetSize(100.0f, 100.0f)
		->SetCol(Color{ 50,255,0,255 })
		->SetTex(nNextTex);

	// 選択アイコン
	for (int nCnt = 0; nCnt < nMax; nCnt++)
	{
		if (nCnt == m_nSelect)
		{
			nTexIdx = nChoiceTex;
		}
		else
		{
			nTexIdx = nNoChoiceTex;
		}
		D3DXVECTOR3 pos = D3DXVECTOR3(RNLib::Window()->GetCenterPos().x, 680,0.0f);
		pos.x += ((nMax * -0.5f) + nCnt + 0.5f) * 50;

		RNLib::Polygon2D()->Put(pos, 0.0f, false)
			->SetSize(40.0f, 40.0f)
			->SetCol(Color{ 255,255,255,255 })
			->SetTex(nTexIdx);
	}

	// -- メニュー選択 ---------------------------
	if (RNLib::Input()->GetKeyTrigger(DIK_A) || RNLib::Input()->GetKeyTrigger(DIK_LEFT) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::LEFT) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::LEFT))
	{
		m_nSelect--;
		IntLoopControl(&m_nSelect, nMax, 0);

		TextClear(TITLE_SELECT);
		FormFont pFont = { INITCOLOR,65.0f,5,10,-1 };
		m_Menu[0] = CFontText::Create(
			CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR2(360.0f, 100.0f),
			m_StageType[m_nSelect].Text, CFont::FONT_ROND_B, &pFont);
	}
	else if (RNLib::Input()->GetKeyTrigger(DIK_D) || RNLib::Input()->GetKeyTrigger(DIK_RIGHT) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::RIGHT) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::RIGHT))
	{
		m_nSelect++;
		IntLoopControl(&m_nSelect, nMax, 0);

		TextClear(TITLE_SELECT);
		FormFont pFont = { INITCOLOR,65.0f,5,10,-1 };
		m_Menu[0] = CFontText::Create(
			CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR2(360.0f, 100.0f),
			m_StageType[m_nSelect].Text, CFont::FONT_ROND_B, &pFont);
	}

	// ループ制御
	IntLoopControl(&m_nSelect, nMax, 0);
}

//========================================
// テキスト削除
// Author:KEISUKE OTONO
//========================================
void CMode_Title::TextClear(TITLE aTitle)
{
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			m_Menu[nCnt]->Uninit();
			m_Menu[nCnt] = NULL;
		}
	}

	Title = aTitle;
}