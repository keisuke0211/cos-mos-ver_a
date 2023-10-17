//========================================
// 
// �}�l�[�W���[����
// Author:RIKU NISHIMURA
// 
//========================================
#include "main.h"

//****************************************
// ���O���
//****************************************
namespace {
	//========== [[[ �ϐ��錾 ]]]
	CMode*      m_modeObj;
	CMode::TYPE m_reserveModeType;
	CBlockMgr   m_blockMgr;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| Manager�̊֐�
//----------|---------------------------------------------------------------------
//================================================================================
CBlockMgr* Manager::BlockMgr(void) { return &m_blockMgr; }

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void Manager::Init(CMode::TYPE mode) {

	// ���[�h�ݒ�
	SetMode(mode);
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void Manager::Uninit(void) {

	// ���[�h�I�u�W�F�N�g���
	RNLib::Memory()->Release(&m_modeObj);
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void Manager::Update(void) {

	m_blockMgr.Update();

	// �\�񂳂�Ă��鎞�A�J�ڂ����[�h�ݒ�҂��Ȃ烂�[�h��ݒ肷��
	if (m_reserveModeType != CMode::TYPE::NONE) {
		if (RNLib::Transition()->GetState() == CTransition::STATE::WAIT_SET_MODE) {
			SetMode(m_reserveModeType);
		}
	}

	// ���[�h�I�u�W�F�N�g���݂鎞�A�X�V����
	if (m_modeObj != NULL) {
		m_modeObj->Update();
		m_modeObj->ProcessState(PROCESS::UPDATE);
	}
}

//========================================
// �ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
void Manager::Load(void) {
	
}

//========================================
// �������ݏ���
// Author:RIKU NISHIMURA
//========================================
void Manager::Save(void) {
	
}

//========================================
// ���[�h�̐ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void Manager::SetMode(CMode::TYPE newMode) {

	// �V�[�����I��
	RNLib::UninitScene();
	
	// ���[�h�I�u�W�F�N�g�̏I������
	if (m_modeObj != NULL) {
		m_modeObj->Uninit();
		RNLib::Memory()->Release(&m_modeObj);
	}

	// ���[�h�I�u�W�F�N�g��V���ɐ���
	m_modeObj = CMode::Create(newMode);
	
	// �\�񃂁[�h�𖳂��ɂ���
	m_reserveModeType = CMode::TYPE::NONE;
}

//========================================
// ���[�h�̎擾����
// Author:RIKU NISHIMURA
//========================================
CMode::TYPE Manager::GetMode(void) {

	if (m_modeObj != NULL)
		return m_modeObj->GetType();

	return CMode::TYPE::NONE;
}

//========================================
// �J�ڏ���
// Author:RIKU NISHIMURA
//========================================
void Manager::Transition(CMode::TYPE newMode, CTransition::TYPE transType) {

	// ���[�h��\�񂷂�
	m_reserveModeType = newMode;

	// �J�ڐݒ�
	RNLib::Transition()->Set(CTransition::STATE::CLOSE, transType);
}