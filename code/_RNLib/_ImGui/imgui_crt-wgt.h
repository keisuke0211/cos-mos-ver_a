//========================================
// 
// ImGuiのウィジェット生成のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ imgui_crt-wgt_basic.h ]]]
//========================================
#ifndef _IMGUI_CRTWGT_BASIC_H_
#define _IMGUI_CRTWGT_BASIC_H_

//****************************************
// プロトタイプ宣言
//****************************************
//======================// [[[ ]]] Basic [[[ ]]]
//======================// [[[ General ]]]
/* button               */bool ImGui_crtWgt_button(const char* pLabelName);
/* checkbox             */void ImGui_crtWgt_checkBox(const char* pLabelName, bool* pCheck);
/* radio                */
/* click                */
/* hold to repeat       */void ImGui_crtWgt_holdToRepeat(const char* pLabelName, int* pData, const int nMin = INT_MIN, const int nMax = INT_MAX);
/* tool tips            */
//======================// [[[ Inputs ]]]
/* input text           */void ImGui_crtWgt_inputText(const char* pLabelName, char* pText);	// ※文字数 < TXT_MAX
/* input text (w/ hint) */
/* input int            */void ImGui_crtWgt_inputInt(const char* pLabelName, int *pData, const int nMin = INT_MIN, const int nMax = INT_MAX);
/* input int (float)    */void ImGui_crtWgt_inputInt_Float(const char* pLabelName, float* pData, const int nMin = INT_MIN, const int nMax = INT_MAX);
/* input float          */void ImGui_crtWgt_inputFloat(const char* pLabelName, float *pData);
/* input double         */
/* input scientifc      */
/* input float3         */void ImGui_crtWgt_inputFloat3(const char* pLabelName, float *pData1, float *pData2, float *pData3);
/* input rot            */void ImGui_crtWgt_inputRot(const char* pLabelName, float* pData1, float* pData2, float* pData3);
//======================// [[[ Drags ]]]
/* drag int             */
/* drag int 0..100      */
/* drag float           */
/* drag float3          */void ImGui_crtWgt_dragFloat3(const char* pLabelName, float* pData1, float* pData2, float* pData3, float fMove = 0.1f);
/* drag small float     */
//======================// [[[ Sliders ]]]
/* slider int           */void ImGui_crtWgt_sliderInt(const char *pLabelName, int *pData, int nMin, int nMax);
/* slider float         */
/* slider float(log)    */
/* slider angle         */
/* slider enum          */
//======================// [[[ Selectors/Pickers ]]]
/* color 1              */void ImGui_crtWgt_color(const char* pLabelName, Color* pCol);
/* color 2              */
/* combo                */int ImGui_crtWgt_combo(const char* pLabelName, int* pSelect, const char* items[], int nItemCount);
/* combo (float)        */int ImGui_crtWgt_combo_Float(const char* pLabelName, float* pSelect, const char* items[], int nItemCount);
/* list box             */int ImGui_crtWgt_listBox(const char* pLabelName, int* pSelect, const char* items[], int nItemCount);
//======================// [[[ ]]] Trees [[[ ]]]
/* tree node set        */bool ImGui_SetTreeNode(const char* pName);
/* tree node end        */bool ImGui_EndTreeNode(void);
//======================// [[[ ]]] Text [[[ ]]]
/* text                 */void ImGui_crtWgt_text(const char* pText);
/* text (Colored)       */void ImGui_crtWgt_text_colored(const char* pText, const Color col);
/* separator text       */void ImGui_crtWgt_separatorText(const char* pText);
//======================//

//****************************************
// 生成サンプル
//****************************************
#if 0
{
	//==================== Basic

	//========== General

	// button
	if (ImGui_crtWgt_button(u8" "))
	{

	}

	// combo
	static int nSelect = 0;
	char *items[] = { u8" ", u8" " };
	ImGui_crtWgt_combo(u8" ", &nSelect, items, ARRAY_SIZE(items));

	// list box
	static int nSelect = 0;
	const char *items[] = { u8" ", u8" " };
	ImGui_crtWgt_listBox(u8" ", &nSelect, items, ARRAY_SIZE(items));

	//==================== Text

	// Text
	ImGui_crtWgt_text(u8" ");
}
#endif

#endif