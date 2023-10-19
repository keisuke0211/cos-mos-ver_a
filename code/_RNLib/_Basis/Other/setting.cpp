//========================================
// 
// 設定の処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ setting.cpp ]]]
//========================================
// RNlib
#include "../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
// 設定の情報のデータファイルの相対パス
#define SETTING_DATA_PATH_PATH "data\\SAVEDATA\\setting.bin"
// 音量の表示倍率
#define VOLUME_DISPLAY_DIAMETER (5)
// 画面モードの切り替えにかかる時間
#define WINDOW_MODE_CHANGE_TIME (20)

//****************************************
// 列挙型定義
//****************************************
// 設定メニュー
typedef enum
{
	SETTING_MENU_BGM_VOLUME,	// BGM音量
	SETTING_MENU_SE_VOLUME,		// SE音量
	SETTING_MENU_SCREEN_MODE,	// 画面モード
	SETTING_MENU_VIBRATION,		// 振動
	SETTING_MENU_OK,			// 了解
	SETTING_MENU_MAX,
}SETTING_MENU;

//****************************************
// プロトタイプ宣言
//****************************************
//========== [[[ 設定 ]]]
// 設定メニューのテキストを設定
void SetSettingMenuText(void);

//****************************************
// グローバル変数宣言
//****************************************
// 画面モード切り替えカウンター
int g_nCounterScreenModeChange = -1;
bool g_bSettingNow;	// 設定中フラグ

// 設定の情報
Setting g_setting = {// 初期設定
	VOLUME_STAGE / 2,
	VOLUME_STAGE / 2,
	true,
};

//****************************************
// グローバル定数宣言
//****************************************
// 画面モードの表示形式
const char g_aScreenModeText[2][TXT_MAX] = {
	"FULL: OFF ",
	"FULL: ON  ",
};
// 振動の表示形式
const char g_aVibrationText[2][TXT_MAX] = {
	"VIB : OFF ",
	"VIB : ON  ",
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| [[[ 設定 [[[ |------------------------
//============================================================
//========================================
// SetSettingMenuText関数 - 設定メニューのテキストを設定 -
//========================================
void SetSettingMenuText(void)
{
	
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| [[[ 基本接続 [[[ |--------------------
//============================================================
//========================================
// InitSetting関数 - 設定の初期化処理 -
//========================================
void InitSetting(void)
{
	g_bSettingNow = false;	// 設定中フラグを初期化
}

//========================================
// UninitSetting関数 - 設定の終了処理 -
//========================================
void UninitSetting(void)
{

}

//========================================
// UpdateSetting関数 - 設定の更新処理 -
//========================================
void UpdateSetting(void)
{
	if (g_nCounterScreenModeChange >= 0)
	{// 画面モード切り替えカウンターが0以上の時、
		// 画面モード切り替えカウンターを減算
		g_nCounterScreenModeChange--;

		if (g_nCounterScreenModeChange == 0)
		{// 画面モード切り替えカウンターが0の時、
			// ウインドウのモードを切り替える
			RNLib::Window()->SetFullScreen(g_setting.bFullScreen);
		}
	}

	if (RNLib::Input()->GetKeyTrigger(DIK_F11) && !RNLib::GetUseImGui())
	{// F11キーが入力された時、
		// 全画面フラグを切り替える
		g_setting.bFullScreen ^= 1;

		// 画面モード切り替えカウンターを設定
		g_nCounterScreenModeChange = WINDOW_MODE_CHANGE_TIME;
	}
}

//========================================
// UpdateSettingMenu関数 - 設定メニューの更新処理 -
//========================================
void UpdateSettingMenu(void)
{
	// 設定メニューのテキストを設定
	SetSettingMenuText();
}

//============================================================
//--------------------| [[[ 入出力 [[[ |----------------------
//============================================================
//========================================
// LoadSetting関数 - 設定の読み込み処理 -
//========================================
void LoadSetting(void) {

}

//========================================
// SaveSetting関数 - 設定の書き込み処理 -
//========================================
void SaveSetting(void) {
	
}

//============================================================
//--------------------| [[[ 取得 [[[ |------------------------
//============================================================
//========================================
// GetSetting関数 - 設定の情報を取得 -
//========================================
Setting *GetSetting(void) {
	return &g_setting;
}

//========================================
// GetSettingNow関数 - 設定中フラグを取得 -
//========================================
bool *GetSettingNow(void) {
	return &g_bSettingNow;
}

//============================================================
//--------------------| [[[ 設定 [[[ |------------------------
//============================================================
//========================================
// SetSettingMenu関数 - 設定メニューの設定処理 -
//========================================
void SetSettingMenu(void) {
	// 設定中フラグを真にする
	g_bSettingNow = true;
}