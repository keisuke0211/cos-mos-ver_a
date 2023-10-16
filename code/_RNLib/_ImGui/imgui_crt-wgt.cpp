//========================================
// 
// ImGuiのウィジェット生成
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ imgui_crt-wgt.cpp ]]]
//========================================
#include "imgui.h"
#include "../RNlib.h"

//****************************************
// マクロ定義
//****************************************
// リストのデフォルトの高さ
#define DEFAULT_LIST_HEIGHT (80.0f)
// スクロールバーのデフォルトの幅
#define DEFAULT_SCROLLBAR_WIDTH (16.0f)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| Basic
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| [[[ General [[[ |---------------------
//============================================================

bool ImGui_crtWgt_button(const char *pLabelName) {
	return ImGui::Button(pLabelName);
}

void ImGui_crtWgt_checkBox(const char *pLabelName, bool *pCheck) {
	ImGui::Checkbox(pLabelName, pCheck);
}

void ImGui_crtWgt_holdToRepeat(const char *pLabelName, int *pData, const int nMin, const int nMax) {
	ImGui::Text(pLabelName);
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	
	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) {
		*pData -= 1;
	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) {
		*pData += 1;
	}

	ImGui::PopButtonRepeat();

	IntControl(pData, nMax, nMin);
}

//============================================================
//--------------------| [[[ Inputs [[[ |----------------------
//============================================================

void ImGui_crtWgt_inputText(const char* pLabelName, char* pText) {
	ImGui::InputText(pLabelName, pText, sizeof(char) * TXT_MAX);
}

void ImGui_crtWgt_inputInt(const char *pLabelName, int *pData, const int nMin, const int nMax) {
	ImGui::InputInt(pLabelName, pData);
	IntControl(pData, nMax, nMin);
}

void ImGui_crtWgt_inputInt_Float(const char* pLabelName, float* pData, const int nMin, const int nMax) {
	int nData = *pData;
	ImGui::InputInt(pLabelName, &nData);
	IntControl(&nData, nMax, nMin);
	*pData = nData;
}

void ImGui_crtWgt_inputFloat(const char *pLabelName, float *pData) {
	ImGui::InputFloat(pLabelName, pData);
}

void ImGui_crtWgt_inputFloat3(const char *pLabelName, float *pData1, float *pData2, float *pData3) {
	float *aData[3] = { pData1,pData2,pData3 };
	ImGui::InputFloat3(pLabelName, *aData);
}

void ImGui_crtWgt_inputRot(const char* pLabelName, float* pData1, float* pData2, float* pData3) {
	*pData1 /= D3DX_PI;
	*pData2 /= D3DX_PI;
	*pData3 /= D3DX_PI;
	ImGui_crtWgt_inputFloat3(pLabelName, pData1, pData2, pData3);
	*pData1 *= D3DX_PI;
	*pData2 *= D3DX_PI;
	*pData3 *= D3DX_PI;
}

//============================================================
//--------------------| [[[ Drags [[[ |-----------------------
//============================================================

void ImGui_crtWgt_dragFloat3(const char* pLabelName, float* pData1, float* pData2, float* pData3, float fMove) {
	float* aData[3] = { pData1,pData2,pData3 };
	ImGui::DragFloat3(pLabelName, *aData, fMove);
}

//============================================================
//--------------------| [[[ Sliders [[[ |---------------------
//============================================================

void ImGui_crtWgt_sliderInt(const char *pLabelName, int *pData, int nMin, int nMax) {
	ImGui::SliderInt(pLabelName, pData, nMin, nMax);
}

//============================================================
//--------------------| [[[ Selectors/Pickers [[[ |-----------
//============================================================

void ImGui_crtWgt_color(const char* pLabelName, Color* pCol) {
	float aCol[4];
	aCol[0] = (float)pCol->r / 255;
	aCol[1] = (float)pCol->g / 255;
	aCol[2] = (float)pCol->b / 255;
	aCol[3] = (float)pCol->a / 255;
	ImGui::ColorEdit3(pLabelName, aCol);
	pCol->r = (int)(aCol[0] * 255);
	pCol->g = (int)(aCol[1] * 255);
	pCol->b = (int)(aCol[2] * 255);
	pCol->a = (int)(aCol[3] * 255);
}

int ImGui_crtWgt_combo(const char *pLabelName, int *pSelect, const char *items[], int nItemCount) {
	ImGui::Combo(pLabelName, pSelect, items, nItemCount);
	return *pSelect;
}

int ImGui_crtWgt_combo_Float(const char* pLabelName, float* pSelect, const char* items[], int nItemCount) {
	int nSelect = *pSelect;
	ImGui::Combo(pLabelName, &nSelect, items, nItemCount);
	*pSelect = nSelect;
	return nSelect;
}

int ImGui_crtWgt_listBox(const char *pLabelName, int *pSelect, const char *items[], int nItemCount) {
	// リストの高さ
	float fListHeight = DEFAULT_LIST_HEIGHT;

	// スクロールバーのサイズを設定する
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, DEFAULT_SCROLLBAR_WIDTH);

	if (ImGui::BeginListBox(pLabelName, ImVec2(208.0f, fListHeight))) {
		for (int n = 0; n < nItemCount; n++) {
			const bool is_selected = (*pSelect == n);
			if (ImGui::Selectable(items[n], is_selected))
				*pSelect = n;

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}

	// スタイル変数をポップする
	ImGui::PopStyleVar();

	return *pSelect;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| Trees
//----------|---------------------------------------------------------------------
//================================================================================

bool ImGui_SetTreeNode(const char *pName) {
	return ImGui::TreeNode(pName);
}

bool ImGui_EndTreeNode(void) {
	ImGui::TreePop();

	return true;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| Text
//----------|---------------------------------------------------------------------
//================================================================================

void ImGui_crtWgt_text(const char *pText) {
	ImGui::Text(pText);
}

void ImGui_crtWgt_text_colored(const char* pText, const Color col) {
	ImVec4 setCol;
	setCol.x = (float)col.r / 255;
	setCol.y = (float)col.g / 255;
	setCol.z = (float)col.b / 255;
	setCol.w = (float)col.a / 255;
	ImGui::TextColored(setCol, pText);
}

void ImGui_crtWgt_separatorText(const char *pText) {
	ImGui::SeparatorText(pText);
}