//========================================
// 
// ���C������
// Author:RIKU NISHIMURA
// 
//========================================
#include "main.h"

//========================================
// WinMain�֐�
// Author:RIKU NISHIMURA
//========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow) {
	int nEndCode = 0;

	while (RNLib::MainLoop(
			&nEndCode,
			hInstance,
			"DigBug",	// �N���X��
			"DigBug",	// �E�B���h�E��
			1280,	// ��
			720,	// ����
			false,	// ImGui�g�p
			2.0f	// �𑜓x�{��
			)) {

		switch (RNLib::GetSignal()) {
		case RNLib::SIGNAL::INIT:
			Manager::Init(CMode::TYPE::GAME);
			break;
		case RNLib::SIGNAL::UNINIT:
			Manager::Uninit();
			break;
		case RNLib::SIGNAL::UPDATE:
			Manager::Update();
			break;
		case RNLib::SIGNAL::LOAD:
			Manager::Load();
			break;
		case RNLib::SIGNAL::SAVE:
			Manager::Save();
			break;
		}
	}

	return nEndCode;
}
