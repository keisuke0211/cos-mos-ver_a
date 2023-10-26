//========================================
// 
// ���[�h�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "mode.h"
#include "mode_logo.h"
#include "mode_pause.h"
#include "mode_title.h"
#include "mode_game.h"
#include "mode_result.h"
#include "../../_RNLib/RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CMode::CMode(void) {
	m_type     = TYPE::NONE;
	m_state    = 0;
	m_stateCtr = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CMode::~CMode(void) {

}

//========================================
// ����������
//========================================
void CMode::Init(void) {

}

//========================================
// �I������
//========================================
void CMode::Uninit(void) {
	
}

//========================================
// �X�V����
//========================================
void CMode::Update(void) {

}

//========================================
// ��������
//========================================
CMode* CMode::Create(TYPE type) {

	// ��ނɉ����ăI�u�W�F�N�g����
	CMode* pMode = NULL;
	switch (type) {
	case TYPE::LOGO:pMode = new CMode_Logo; break;
	case TYPE::PAUSE:pMode = new CMode_Pause; break;
	case TYPE::TITLE:pMode = new CMode_Title; break;
	case TYPE::GAME:pMode = new CMode_Game; break;
	case TYPE::RESULT:pMode = new CMode_Result; break;
	default:
		assert(false);
		break;
	}

	// ��ސݒ�
	pMode->SetType(type);
	
	// ����������
	pMode->Init();

	return pMode;
}

//========================================
// ��Ԑݒ菈��
//========================================
void CMode::SetState(int nState) {

	// ��ԏI������
	ProcessState(PROCESS::UNINIT);

	// ��Ԃ�ݒ肵�A�J�E���^�[������
	m_state = nState;
	m_stateCtr = 0;
	
	// ��ԏ�������
	ProcessState(PROCESS::INIT);
}