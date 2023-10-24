//========================================
// 
// モード:タイトルの処理
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// 前方宣言
//****************************************
class CWords;
class CFontText;

//****************************************
// クラス定義
//****************************************
// モード(タイトル)クラス
class CMode_Title :public CMode {
public:
	// *** 列挙型 ***
	enum class STATE {
		NONE,
	};

	// タイトルモード
	enum TITLE
	{
		TITLE_OUTSET = 0,	// タイトル
		TITLE_MENU,			// メニュー
		TITLE_SELECT,		// ステージ選択
		TITLE_NEXT,			// 次の画面に移動 
		TITLE_MAX
	};

	// メニュー
	enum MENU
	{
		MENU_GAME = 0,	// ゲーム
		MENU_SERRING,	// 設定
		MENU_END,		// 終了
		MENU_MAX
	};

	// *** 関数 ***
	CMode_Title();
	~CMode_Title();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

private:
	// *** 関数 ***
	/* メニュー生成			*/void MenuCreate(void);
	/* メニュー				*/void Menu(void);
	/* ステージ選択生成		*/void SelectCreate(void);
	/* ステージ選択			*/void StageSelect(void);
	/* テキスト削除			*/void TextClear(TITLE aTitle);

	// *** 変数 ***
	TITLE Title;						// 現在のモード
	int m_TexIdx;
	int m_nSelect;
	CFontText *m_Menu[MENU_MAX];		// メニューテキスト
	CWords *m_Words[4];					// タイトル
	int m_nStageTex[3];					// 仮ステージ画像
};