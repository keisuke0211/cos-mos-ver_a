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
bool CMode_Title::s_bStageSelect = false;

//========================================
// コンストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Title::CMode_Title(void) {

	for (int nCnt = 0; nCnt < TEX_MAX; nCnt++)
	{
		m_BgPos[nCnt] = INITD3DXVECTOR3;
		m_TexIdx[nCnt] = 0;
	}

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_MenuPos[nCnt] = INITD3DXVECTOR3;
	}

	m_nSelect = 0;
	m_PlanetAngle = 0.0f;
	m_nSelect = 0;
	m_nOldSelect = 0;
	m_StageType = NULL;
	m_bMenuAnime = false;
}

//========================================
// デストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Title::~CMode_Title(void) {

	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			m_Words[nCnt]->Uninit();
			m_Words[nCnt] = NULL;
		}
		if (m_WordsShadow[nCnt] != NULL)
		{
			m_WordsShadow[nCnt]->Uninit();
			m_WordsShadow[nCnt] = NULL;
		}
	}

	if (m_StageType != NULL)
	{
		delete[] m_StageType;
		m_StageType = NULL;
	}
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
	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		m_bMove[nCnt] = false;
		m_Words[nCnt] = NULL;
		m_WordsShadow[nCnt] = NULL;
	}

	if (s_bStageSelect)
	{
		SelectCreate();
		s_bStageSelect = false;
	}
	else
	{
		Title = TITLE_PLANET;
	}


	m_bMenuAnime = false;

	// テクスチャ
	m_BgPos[0] = D3DXVECTOR3(RNLib::Window().GetCenterPos().x, RNLib::Window().GetCenterPos().y, -1.0f);
	m_BgPos[1] = D3DXVECTOR3(RNLib::Window().GetCenterPos().x, 1460.0f, 0.0f);
	m_BgPos[2] = D3DXVECTOR3(RNLib::Window().GetCenterPos().x, 1460.0f, 0.0f);
	m_BgPos[3] = D3DXVECTOR3(50, 140.0f, 0.0f);
	m_nSelect = 0;

	// メニュー
	m_MenuPos[0] = D3DXVECTOR3(280.0f, 150.0f, 1.0f);
	m_MenuPos[1] = D3DXVECTOR3(280.0f, 300.0f, 1.0f);
	m_MenuPos[2] = D3DXVECTOR3(280.0f, 450.0f, 1.0f);

	m_TexIdx[0] = RNLib::Texture().Load("data\\TEXTURE\\BackGround\\title.jpg");
	m_TexIdx[1] = RNLib::Texture().Load("data\\TEXTURE\\BackGround\\planet.png");
	m_TexIdx[2] = RNLib::Texture().Load("data\\TEXTURE\\BackGround\\planet.png");
	m_TexIdx[3] = RNLib::Texture().Load("data\\TEXTURE\\Effect\\mark_smiley_000.png");

	// 遷移設定
	RNLib::Transition().Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// カメラの視点/注視点を設定
	RNLib::Camera3D().SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	// 背景色変更
	SetBGColor(Color{ 200,0,0,255 });
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

	// 各モードの処理
	if (Title == TITLE_PLANET)
		PlanetAnime();
	else if (Title == TITLE_TITLE)
		TitleAnime();
	else if (Title == TITLE_MENU_ANIME)
		MenuAnime();
	else if (Title == TITLE_MENU)
		Menu();
	else if (Title == TITLE_SELECT)
		StageSelect();

	RNLib::Polygon2D().Put(m_BgPos[0], 0.0f, false)
		->SetSize(1280.0f, 720.0f)
		->SetCol(Color{ 255,255,255,255 })
		->SetTex(m_TexIdx[0]);

	if (Title == TITLE_OUTSET || Title == TITLE_MENU)
	{
		if(Title == TITLE_OUTSET)
			m_PlanetAngle += -0.01f;
		else if (Title == TITLE_MENU)
			m_PlanetAngle += -0.005f;

		FloatLoopControl(&m_PlanetAngle, D3DX_PI, -D3DX_PI);
	}

	if (Title <= TITLE_MENU)
	{
		RNLib::Polygon2D().Put(m_BgPos[1], m_PlanetAngle, false)
			->SetSize(1300.0f, 1300.0f)
			->SetCol(Color{ 255,255,255,255 })
			->SetTex(m_TexIdx[1]);

		RNLib::Polygon2D().Put(m_BgPos[2], m_PlanetAngle, false)
			->SetSize(600.0f, 600.0f)
			->SetCol(Color{ 255,255,255,255 })
			->SetTex(m_TexIdx[2]);
	}

	if ((RNLib::Input().GetKeyTrigger(DIK_RETURN) || RNLib::Input().GetButtonTrigger(CInput::BUTTON::A)) && RNLib::Transition().GetState() == CTransition::STATE::NONE)
	{
		switch (Title)
		{
		case TITLE_OUTSET:
		{
			TextClear(TITLE_MENU_ANIME);
		}
		break;
		case TITLE_MENU:
		{
			switch (m_nSelect)
			{
			case MENU_GAME:
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
			Manager::Transition(CMode::TYPE::GAME, CTransition::TYPE::FADE);

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
// 惑星アニメーション
// Author:KEISUKE OTONO
//========================================
void CMode_Title::PlanetAnime(void)
{
	if (m_BgPos[1].y >= 1060.0f)
	{
		D3DXVECTOR3 move = INITD3DXVECTOR3;

		move.y = -15.0f;

		m_BgPos[1] += move;
		if (m_BgPos[1].y <= 1060.0f)
		{
			move.y = 0.0f;
			m_BgPos[1].y = 1060;
			Title = TITLE_TITLE;

			{
				m_WordsShadow[0] = CWords::Create("Ｃ", D3DXVECTOR3(786.0f, -52.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.0f,0.0f,0.0f,1.0f));
				m_WordsShadow[1] = CWords::Create("Ｏ", D3DXVECTOR3(946.0f, -52.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				m_WordsShadow[2] = CWords::Create("Ｓ", D3DXVECTOR3(1096.0f, -52.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				m_WordsShadow[3] = CWords::Create("／", D3DXVECTOR3(1246.0f, -54.0f, 0.0f), D3DXVECTOR3(100.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.8f, 0.2f, 0.4f, 1.0f));
				m_WordsShadow[4] = CWords::Create("Ｍ", D3DXVECTOR3(1406.0f, -52.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				m_WordsShadow[5] = CWords::Create("Ｏ", D3DXVECTOR3(1566.0f, -52.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				m_WordsShadow[6] = CWords::Create("Ｓ", D3DXVECTOR3(1706.0f, -52.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			}
			{
				m_Words[0] = CWords::Create("Ｃ", D3DXVECTOR3(780.0f, -60.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.2f, 0.8f, 0.5f, 1.0f));
				m_Words[1] = CWords::Create("Ｏ", D3DXVECTOR3(940.0f, -60.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.2f, 0.8f, 0.5f, 1.0f));
				m_Words[2] = CWords::Create("Ｓ", D3DXVECTOR3(1090.0f, -60.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.2f, 0.8f, 0.5f, 1.0f));
				m_Words[3] = CWords::Create("／", D3DXVECTOR3(1234.0f, -66.0f, 0.0f), D3DXVECTOR3(100.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.2f, 0.8f, 0.5f, 1.0f));
				m_Words[4] = CWords::Create("Ｍ", D3DXVECTOR3(1400.0f, -60.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.8f, 0.2f, 0.4f, 1.0f));
				m_Words[5] = CWords::Create("Ｏ", D3DXVECTOR3(1560.0f, -60.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.8f, 0.2f, 0.4f, 1.0f));
				m_Words[6] = CWords::Create("Ｓ", D3DXVECTOR3(1700.0f, -60.0f, 0.0f), D3DXVECTOR3(125.0f, 125.0f, 0.0f), CFont::FONT_ROND_B, D3DXCOLOR(0.8f, 0.2f, 0.4f, 1.0f));
			}
			m_bMove[0] = true;
		}
	}
}

//========================================
// タイトルアニメーション
// Author:KEISUKE OTONO
//========================================
void CMode_Title::TitleAnime(void)
{
	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_Words[nCnt]->GetPos();

			if (pos.y <= 210.0f && m_bMove[nCnt])
			{
				D3DXVECTOR3 move;

				move.y = 15.0f;

				m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
				m_WordsShadow[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));

				if (pos.y >= 200.0f)
				{
					move.y = 0.0f;
					pos.y = 200;

					m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
					m_WordsShadow[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));

					if (nCnt == WORDS_MAX - 1)
					{
						FormFont pFont = { D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),70.0f,5,10,-1, };// 45
						FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),true, D3DXVECTOR3(6.0f,6.0f,0.0f) ,D3DXVECTOR2(4.0f,4.0f) };

						m_Menu[0] = CFontText::Create(CFontText::BOX_NORMAL_RECT,D3DXVECTOR3(230.0f, 600.0f, 0.0f),D3DXVECTOR2(0.0f, 0.0f),
							"ボタンを押して始めてね",CFont::FONT_ROND_B,&pFont, false,&pShadow);

						Title = TITLE_OUTSET;
					}

				}
				else if (pos.y >= 20 && nCnt != WORDS_MAX - 1 && !m_bMove[nCnt + 1])
				{
					m_bMove[nCnt + 1] = true;
				}
			}
		}
	}
}

//========================================
// メニュー演出
// Author:KEISUKE OTONO
//========================================
void CMode_Title::MenuAnime(void)
{
	if (!m_bMenuAnime)
	{
		for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
		{
			if (m_Words[nCnt] != NULL)
			{
				D3DXVECTOR3 pos = m_Words[nCnt]->GetPos();

				if (pos.y >= -60.0f && m_bMove[nCnt])
				{
					D3DXVECTOR3 move;

					move.y = -15.0f;

					m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
					m_WordsShadow[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
				}
			}
		}

		if (m_BgPos[1].y <= 1460.0f)
		{
			D3DXVECTOR3 move = INITD3DXVECTOR3;
			move.y = 25.0f;

			m_BgPos[1] += move;
			if (m_BgPos[1].y >= 1460.0f)
			{
				move.y = 0.0f;
				m_BgPos[1].y = 1460;
				m_bMenuAnime = true;

				m_BgPos[1] = D3DXVECTOR3(-640.0f, 600.0f, 0.0f);
				m_BgPos[2] = D3DXVECTOR3(1240.0f, -200.0f, 0.0f);
			}
		}
	}
	else if (m_bMenuAnime)
	{
		if (m_BgPos[1].x <= 120.0f)
		{
			D3DXVECTOR3 move = INITD3DXVECTOR3;
			move.x = 40.0f;

			m_BgPos[1] += move;

			if (m_BgPos[1].x >= 120.0f)
			{
				move.x = 0.0f;
				m_BgPos[1].x = 120.0f;

				MenuCreate();
			}
		}
		if (m_BgPos[2].y <= 0)
		{
			D3DXVECTOR3 move01 = INITD3DXVECTOR3;
			move01.y = 10.0f;

			m_BgPos[2] += move01;

			if (m_BgPos[2].y >= 0.0f)
			{
				move01.y = 0.0f;
				m_BgPos[2].y = 0.0f;
			}
		}
	}
}

//========================================
// メニュー生成
// Author:KEISUKE OTONO
//========================================
void CMode_Title::MenuCreate(void)
{
	FormFont pFont = { D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),45.0f,5,10,-1};// 45
	FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), true, D3DXVECTOR3(4.0f,4.0f,0.0f), D3DXVECTOR2(4.0f,4.0f) };

	TextClear(TITLE_MENU);

	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			m_Words[nCnt]->Uninit();
			m_Words[nCnt] = NULL;
		}
		if (m_WordsShadow[nCnt] != NULL)
		{
			m_WordsShadow[nCnt]->Uninit();
			m_WordsShadow[nCnt] = NULL;
		}
	}

	m_Menu[0] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, m_MenuPos[0],D3DXVECTOR2(360.0f, 80.0f),// 360,100
		"ゲーム",CFont::FONT_ROND_B,&pFont,false,&pShadow);

	m_Menu[1] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, m_MenuPos[1], D3DXVECTOR2(360.0f, 80.0f),
		"オプション", CFont::FONT_ROND_B, &pFont,false,&pShadow);

	m_Menu[2] = CFontText::Create(
		CFontText::BOX_NORMAL_RECT, m_MenuPos[2], D3DXVECTOR2(360.0f, 80.0f),
		"ゲームをやめる", CFont::FONT_ROND_B, &pFont,false,&pShadow);
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
				m_Menu[nCnt]->SetTexBox(true);
				m_Menu[nCnt]->SetTextColor(D3DXCOLOR(240,255,0,255));
			}
			else
			{
				m_Menu[nCnt]->SetTexBox(false);
				m_Menu[nCnt]->SetTextColor(INITD3DCOLOR);
			}
		}
	}

	// -- メニュー選択 ---------------------------
	if (RNLib::Input().GetKeyTrigger(DIK_W) || RNLib::Input().GetKeyTrigger(DIK_UP) || RNLib::Input().GetButtonTrigger(CInput::BUTTON::UP) || RNLib::Input().GetStickAngleTrigger(CInput::STICK::LEFT,CInput::INPUT_ANGLE::UP))
	{
		m_nSelect--;
	}
	else if (RNLib::Input().GetKeyTrigger(DIK_S) || RNLib::Input().GetKeyTrigger(DIK_DOWN) || RNLib::Input().GetButtonTrigger(CInput::BUTTON::DOWN) || RNLib::Input().GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::DOWN))
	{
		m_nSelect++;
	}

	// ループ制御
	IntLoopControl(&m_nSelect, MENU_MAX, 0);

	m_BgPos[3].y = m_MenuPos[m_nSelect].y;

	RNLib::Polygon2D().Put(m_BgPos[3], 0.0f, false)
		->SetSize(50.0f, 50.0f)
		->SetCol(Color{ 255,255,255,255 })
		->SetTex(m_TexIdx[3]);
}

//========================================
// ステージ選択の生成
// Author:KEISUKE OTONO
//========================================
void CMode_Title::SelectCreate(void)
{
	Manager::StgEd()->FileLoad();
	int nMax = Manager::StgEd()->GetStageMax();

	m_StageType = new StageType[nMax];

	for (int nCnt = 0; nCnt < nMax; nCnt++)
	{
		char *aTexFile = Manager::StgEd()->GetType()[nCnt].aTexFile;
		char *aStgName = Manager::StgEd()->GetType()[nCnt].aStageName;

		m_StageType[nCnt].nTex = RNLib::Texture().Load(aTexFile);
		sprintf(m_StageType[nCnt].Text, aStgName);
	}

	TextClear(TITLE_SELECT);
	FormFont pFont = { D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),65.0f,5,10,-1 };// 45
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
	int nChoiceTex = RNLib::Texture().Load("data\\TEXTURE\\Effect\\mark_smiley_000.png");
	int nNoChoiceTex = RNLib::Texture().Load("data\\TEXTURE\\Effect\\eff_Circle_005.png");
	int nPrevTex = RNLib::Texture().Load("data\\TEXTURE\\Effect\\eff_Arrow_01.png");
	int nNextTex = RNLib::Texture().Load("data\\TEXTURE\\Effect\\eff_Arrow_00.png");

	int nTexIdx = 0;

	// ステージ画像
	RNLib::Polygon2D().Put(D3DXVECTOR3(RNLib::Window().GetCenterPos().x, RNLib::Window().GetCenterPos().y - 120.0f, -1.0f), 0.0f, false)
		->SetSize(880.0f, 480.0f)
		->SetCol(Color{ 255,255,255,255 })
		->SetTex(m_StageType[m_nSelect].nTex);

	if (m_nSelect != 0)
	{
		RNLib::Polygon2D().Put(D3DXVECTOR3(400.0f, 550.0f, 0.0), 0.0f, false)
			->SetSize(100.0f, 100.0f)
			->SetCol(Color{ 50,255,0,255 })
			->SetTex(nPrevTex);
	}
	if(m_nSelect != nMax - 1)
	RNLib::Polygon2D().Put(D3DXVECTOR3(880.0f, 550.0f, 0.0), 0.0f, false)
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
		D3DXVECTOR3 pos = D3DXVECTOR3(RNLib::Window().GetCenterPos().x, 680,1.0f);
		pos.x += ((nMax * -0.5f) + nCnt + 0.5f) * 50;

		RNLib::Polygon2D().Put(pos, 0.0f, false)
			->SetSize(40.0f, 40.0f)
			->SetCol(Color{ 255,255,255,255 })
			->SetTex(nTexIdx);
	}

	bool bInput = false;
	// -- メニュー選択 ---------------------------
	if (RNLib::Input().GetKeyTrigger(DIK_A) || RNLib::Input().GetKeyTrigger(DIK_LEFT) || RNLib::Input().GetButtonTrigger(CInput::BUTTON::LEFT) || RNLib::Input().GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::LEFT))
	{
		m_nSelect--;
		bInput = true;
	}
	else if (RNLib::Input().GetKeyTrigger(DIK_D) || RNLib::Input().GetKeyTrigger(DIK_RIGHT) || RNLib::Input().GetButtonTrigger(CInput::BUTTON::RIGHT) || RNLib::Input().GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::RIGHT))
	{
		m_nSelect++;
		bInput = true;
	}

	if (bInput)
	{
		IntControl(&m_nSelect, nMax - 1, 0);

		if (m_nSelect != m_nOldSelect)
		{
			m_nOldSelect = m_nSelect;

			TextClear(TITLE_SELECT);
			FormFont pFont = { D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),65.0f,5,10,-1 };
			m_Menu[0] = CFontText::Create(
				CFontText::BOX_NORMAL_RECT, D3DXVECTOR3(640.0f, 550.0f, 0.0f), D3DXVECTOR2(360.0f, 100.0f),
				m_StageType[m_nSelect].Text, CFont::FONT_ROND_B, &pFont);
		}
	}

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