//========================================
// 
// ���[�h:���U���g����
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_result.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Result�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Result::CMode_Result(void) {

}

//========================================
// �f�X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Result::~CMode_Result(void) {

}

//========================================
// ����������
// Author:KEISUKE OTONO
//========================================
void CMode_Result::Init(void) {
	CMode::Init();

	// �J�ڐݒ�
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);
}

//========================================
// �I������
// Author:KEISUKE OTONO
//========================================
void CMode_Result::Uninit(void) {
	CMode::Uninit();

}

//========================================
// �X�V����
// Author:KEISUKE OTONO
//========================================
void CMode_Result::Update(void) {
	CMode::Update();

	RNLib::Polygon2D()->Put(D3DXVECTOR3(640.0f, 360.0f, -1.0f), 0.0f, false)
		->SetSize(1280.0f, 720.0f)
		->SetCol(Color{ 0,200,0,255 });

	if (RNLib::Input()->GetKeyTrigger(DIK_SPACE) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		Manager::Transition(CMode::TYPE::TITLE, CTransition::TYPE::FADE);

}

//========================================
// �X�V����(���)
// Author:KEISUKE OTONO
//========================================
void CMode_Result::ProcessState(const PROCESS process) {
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