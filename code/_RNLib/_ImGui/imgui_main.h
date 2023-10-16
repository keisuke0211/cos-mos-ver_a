//========================================
// 
// ImGui�̃��C�������̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ imgui_main.h ]]]
//========================================
#ifndef _IMGUI_MAIN_H_
#define _IMGUI_MAIN_H_

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== [[[ ��{�ڑ� ]]]
// ImGui�̏���������
void ImGuiInit(HWND hWnd);
// ImGui�̏I������
void ImGuiUninit(void);
// ImGui�̃t���O����������
void ImGuiInitFlag(void);
// ImGui�̕`�揈��
void ImGuiDraw(void);
//========== [[[ �����֘A ]]]
// ImGui�̐����J�n����
void ImGui_CreateStart(void);
// ImGui�̐����I������
void ImGui_CreateEnd(void);
// ImGui�̃E�B���h�E�ݒ菈��
bool ImGui_SetWindow(const char* pName, const float fWidth, const float fHeight, const D3DXVECTOR3 pos);
// ImGui�̃E�B���h�E�I������
bool ImGui_EndWindow(void);
// ImGui�̃w�b�_�ݒ菈��
bool ImGui_SetHeader(const char *pName);
//========== [[[ �擾 ]]]
// ImGui�̃E�B���h�E�Ƀt�H�[�J�X���������Ă��邩�擾
bool ImGui_GetWindowFocused(void);

#endif