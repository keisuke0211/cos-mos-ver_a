//========================================
// 
// ImGuiのメイン処理のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ imgui_main.h ]]]
//========================================
#ifndef _IMGUI_MAIN_H_
#define _IMGUI_MAIN_H_

//****************************************
// プロトタイプ宣言
//****************************************
//========== [[[ 基本接続 ]]]
// ImGuiの初期化処理
void ImGuiInit(HWND hWnd);
// ImGuiの終了処理
void ImGuiUninit(void);
// ImGuiのフラグ初期化処理
void ImGuiInitFlag(void);
// ImGuiの描画処理
void ImGuiDraw(void);
//========== [[[ 生成関連 ]]]
// ImGuiの生成開始処理
void ImGui_CreateStart(void);
// ImGuiの生成終了処理
void ImGui_CreateEnd(void);
// ImGuiのウィンドウ設定処理
bool ImGui_SetWindow(const char* pName, const float fWidth, const float fHeight, const D3DXVECTOR3 pos);
// ImGuiのウィンドウ終了処理
bool ImGui_EndWindow(void);
// ImGuiのヘッダ設定処理
bool ImGui_SetHeader(const char *pName);
//========== [[[ 取得 ]]]
// ImGuiのウィンドウにフォーカスが当たっているか取得
bool ImGui_GetWindowFocused(void);

#endif