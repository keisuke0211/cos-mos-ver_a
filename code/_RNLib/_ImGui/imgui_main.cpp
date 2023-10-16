//========================================
// 
// ImGui�̃��C�������̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ imgui_main.cpp ]]]
//========================================
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "../RNlib.h"

//****************************************
// �}�N����`
//****************************************
// �t�H���g�̃p�X
#define FONT_PATH "data_R.N.App\\FONT\\meiryo.ttc"
// �t�H���g�̃T�C�Y
#define FONT_SIZE (14.0f)

//****************************************
// �O���[�o���ϐ��錾
//****************************************
static bool g_bImGuiSet = false;	// ImGui��ݒ肵�����t���O
static bool g_bWindowFocused = false;	// �E�B���h�E�Ƀt�H�[�J�X���������Ă��邩�t���O

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| [[[ ��{�ڑ� [[[ |--------------------
//============================================================

//========================================
// ImGuiInit�֐� - ImGui�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void ImGuiInit(HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();	// �f�o�C�X�̏��

	// DearImGui�R���e�L�X�g���Z�b�g�A�b�v
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// �L�[�{�[�h�̑����L����
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	// �Q�[���p�b�h�̑����L����
	io.Fonts->AddFontFromFileTTF(FONT_PATH, FONT_SIZE, nullptr, io.Fonts->GetGlyphRangesJapanese());

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);	// ���{��̃O���t�͈͂��擾
}

//========================================
// ImGuiUninit�֐� - ImGui�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void ImGuiUninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//========================================
// ImGuiInitFlag�֐� - ImGui�̃t���O���������� -
// Author:RIKU NISHIMURA
//========================================
void ImGuiInitFlag(void) {
	g_bImGuiSet      = false;
	g_bWindowFocused = false;
}

//========================================
// ImGuiDraw�֐� - ImGui�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void ImGuiDraw(void) {
	if (!g_bImGuiSet) 
	{// �ݒ肵�Ă��Ȃ����A
		return;
	}

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//============================================================
//--------------------| [[[ ��{�ڑ� [[[ |--------------------
//============================================================

//========================================
// ImGuiCreateStart�֐� - ImGui�̐����J�n���� -
// Author:RIKU NISHIMURA
//========================================
void ImGui_CreateStart(void)
{
	g_bImGuiSet = true;

	// ImGui�t���[�����J�n����
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

//========================================
// ImGuiCreateEnd�֐� - ImGui�̐����I������ -
// Author:RIKU NISHIMURA
//========================================
void ImGui_CreateEnd(void)
{
	// ImGui�t���[�����I������
	ImGui::EndFrame();
}

//========================================
// �E�B���h�E�ݒ菈��
// Author:RIKU NISHIMURA
//========================================
bool ImGui_SetWindow(const char* pName, const float fWidth, const float fHeight, const D3DXVECTOR3 pos) {
	// �E�B���h�E�̃T�C�Y�ύX
	if (RNLib::GetUseImGui()) {
		ImGui::SetNextWindowSize(ImVec2(fWidth * IMGUI_CORRECT_X, fHeight * IMGUI_CORRECT_Y), ImGuiCond_Once);
		ImGui::SetNextWindowPos (ImVec2(pos.x  * IMGUI_CORRECT_X, pos.y   * IMGUI_CORRECT_Y), ImGuiCond_Always);
	}
	else {
		ImGui::SetNextWindowSize(ImVec2(fWidth, fHeight), ImGuiCond_Once);
		ImGui::SetNextWindowPos (ImVec2(pos.x , pos.y  ), ImGuiCond_Always);
	}

	// �E�B���h�E���ݒ�
	ImGui::Begin(pName, nullptr, ImGuiWindowFlags_NoResize);

	// �t�H�[�J�X�擾
	g_bWindowFocused |= ImGui::IsWindowFocused();

	return true;
}

//========================================
// ImGui_EndWindow�֐� - ImGui�̃E�B���h�E�I������ -
// Author:RIKU NISHIMURA
//========================================
bool ImGui_EndWindow(void)
{
	ImGui::End();

	return true;
}

//========================================
// ImGui_SetHeader�֐� - ImGui�̃w�b�_�ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
bool ImGui_SetHeader(const char *pName)
{
	return ImGui::CollapsingHeader(pName, ImGuiTreeNodeFlags_DefaultOpen);
}

//========================================
// ImGui_GetWindowFocused�֐� - ImGui�̃E�B���h�E�Ƀt�H�[�J�X���������Ă��邩�擾 -
// Author:RIKU NISHIMURA
//========================================
bool ImGui_GetWindowFocused(void) 
{
	return g_bWindowFocused;
}