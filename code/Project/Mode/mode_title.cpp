//========================================
// 
// ���[�h:�^�C�g������
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_title.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Title�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Title::CMode_Title(void) {
	m_TexIdx = 0;
}

//========================================
// �f�X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Title::~CMode_Title(void) {

}

//========================================
// ����������
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Init(void) {
	CMode::Init();

	m_TexIdx = RNLib::Texture()->Load("data\\TEXTURE\\BackGround\\title.jpg");

	// �J�ڐݒ�
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);

	// �w�i�F�ύX
	SetBGColor(Color{ 200,0,0,255 });
}

//========================================
// �I������
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Uninit(void) {
	CMode::Uninit();

}

//========================================
// �X�V����
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Update(void) {
	CMode::Update();

	RNLib::Polygon2D()->Put(D3DXVECTOR3(RNLib::Window()->GetCenterPos().x, RNLib::Window()->GetCenterPos().y, -1.0f), 0.0f, false)
		->SetSize(1280.0f,720.0f)
		->SetCol(Color{255,255,255,255})
		->SetTex(m_TexIdx);

	if (RNLib::Input()->GetKeyTrigger(DIK_SPACE) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		Manager::Transition(CMode::TYPE::GAME, CTransition::TYPE::NONE);
}

//========================================
// �X�V����(���)
// Author:KEISUKE OTONO
//========================================
void CMode_Title::ProcessState(const PROCESS process) {
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