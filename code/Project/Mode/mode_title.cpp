//========================================
// 
// モード:タイトル処理
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_title.h"
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
	m_nSelectMenu = 0;
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
	m_nSelectMenu = 0;

	m_TexIdx = RNLib::Texture()->Load("data\\TEXTURE\\BackGround\\title.jpg");

	// 遷移設定
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// カメラの視点/注視点を設定
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	// 背景色変更
	SetBGColor(Color{ 200,0,0,255 });


	FormFont pFont = {INITCOLOR,45.0f,1,1,-1};
	m_Menu[0] = CFontText::Create(CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 600.0f, 0.0f),D3DXVECTOR2(1080.0f, 100.0f),
		" ",CFont::FONT_851GKKTT,&pFont);

	pFont = { INITCOLOR,45.0f,5,10,-1 };
	m_Menu[1] = CFontText::Create(CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 600.0f, 0.0f),D3DXVECTOR2(1080.0f, 100.0f),
		"ENTERを押して始めてね!!",CFont::FONT_851GKKTT,&pFont, false);
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
	{
		// メニュー
		Menu();
	}

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
			switch (m_nSelectMenu)
			{
			case MENU_GAME:
				TextClear(TITLE_NEXT);
				Manager::Transition(CMode::TYPE::GAME, CTransition::TYPE::NONE);
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
	FormFont pFont = { INITCOLOR,45.0f,5,10,-1};

	TextClear(TITLE_MENU);

	m_Menu[0] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(640.0f, 150.0f, 0.0f),D3DXVECTOR2(360.0f, 100.0f),
		"ゲーム",CFont::FONT_851GKKTT,&pFont);

	m_Menu[1] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 300.0f, 0.0f), D3DXVECTOR2(360.0f, 100.0f),
		"設定", CFont::FONT_851GKKTT, &pFont);

	m_Menu[2] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 450.0f, 0.0f), D3DXVECTOR2(360.0f, 100.0f),
		"ゲームをやめる", CFont::FONT_851GKKTT, &pFont);
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
			if (nCnt == m_nSelectMenu)
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
		m_nSelectMenu--;
	}
	else if (RNLib::Input()->GetKeyTrigger(DIK_S) || RNLib::Input()->GetKeyTrigger(DIK_DOWN) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::DOWN) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::DOWN))
	{
		m_nSelectMenu++;
	}

	// ループ制御
	IntLoopControl(&m_nSelectMenu, MENU_MAX, 0);
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