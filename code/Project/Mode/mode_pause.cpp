//========================================
// 
// ���[�h:�|�[�Y����
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_pause.h"

//========================================
// �ÓI�ϐ�
//========================================
bool CMode_Pause::m_bPause = false;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Result�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================


//========================================
// �R���X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Pause::CMode_Pause(void) {

}

//========================================
// �f�X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Pause::~CMode_Pause(void) {

}

//========================================
// ����������
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::Init(void) {
	CMode::Init();

	// �J�ڐݒ�
	RNLib::Transition()->Set(CTransition::STATE::NONE, CTransition::TYPE::NONE);

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);

	// �w�i�F�ύX
	SetBGColor(Color{ 0,200,0,255 });
}

//========================================
// �I������
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::Uninit(void) {
	CMode::Uninit();

}

//========================================
// �X�V����
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::Update(void) {
	CMode::Update();

	m_bPause = true;
	if (m_bPause)
	{
		if (RNLib::Input()->GetKeyTrigger(DIK_P) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		{
			Manager::UninitMode();

			m_bPause = false;
		}
	}

}

//========================================
// �X�V����(���)
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::ProcessState(const PROCESS process) {
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
			return;
		}break;
		}
	}break;
	}
}
