//========================================
// 
// ���[�h:�Q�[���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Game�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CMode_Game::CMode_Game(void) {

}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CMode_Game::~CMode_Game(void) {

}

int g_modelIdx = -1;

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Init(void) {
	CMode::Init();

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);

	g_modelIdx = RNLib::Model()->Load("data\\_RNData\\Model\\Effect\\Clod_M\\Body.x");
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Uninit(void) {
	CMode::Uninit();
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Update(void) {
	CMode::Update();
}

//========================================
// �X�V����(���)
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::ProcessState(const PROCESS process) {
	switch ((STATE)m_state) {
		//----------------------------------------
		// ����
		//----------------------------------------
	case STATE::NONE: {
		switch (process) {
			// [[[ �������� ]]]
		case PROCESS::INIT: {

		}break;
			// [[[ �I������ ]]]
		case PROCESS::UNINIT: {

		}break;
			// [[[ �X�V���� ]]]
		case PROCESS::UPDATE: {

		}break;
		}
	}break;
	}
}