//========================================
// 
// ���[�h:���S
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_logo.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Logo�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �ÓI�ϐ�
//========================================
int CMode_Logo::m_TexLogo = 0;

//========================================
// �R���X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Logo::CMode_Logo(void) {
	m_TexLogo = 0;
	m_nStateCtr = TIME;
	m_state = STATE::NONE;
}

//========================================
// �f�X�g���N�^
// Author:KEISUKE OTONO
//========================================
CMode_Logo::~CMode_Logo(void) {

}

//========================================
// ����������
// Author:KEISUKE OTONO
//========================================
void CMode_Logo::Init(void) {
	CMode::Init();

	m_TexLogo = RNLib::Texture()->Load("data\\TEXTURE\\BackGround\\TeamLogo.PNG");

	// ��Ԑݒ�
	SetState((int)STATE::NONE);
	// �J�ڐݒ�
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);

	m_state = STATE::OPEN_WAIT;
}

//========================================
// �I������
// Author:KEISUKE OTONO
//========================================
void CMode_Logo::Uninit(void) {
	CMode::Uninit();

}

//========================================
// �X�V����
// Author:KEISUKE OTONO
//========================================
void CMode_Logo::Update(void) {
	CMode::Update();

	//===== [[[ ���[�J���֐��錾 ]]]
	struct LocalFunc {
		static void FillScreen(const float& fRate) {
			RNLib::Polygon2D()->Put(RNLib::Window()->GetCenterPos(), 0.0f)
				->SetCol(Color{ 255,255,255,(int)(255 * fRate) })
				->SetSize(RNLib::Window()->GetWidth(), RNLib::Window()->GetHeight())
				->SetTex(m_TexLogo);
		}
	};

	if (m_state == STATE::NONE)
	{
		return;
	}
	else if (m_state == STATE::OPEN_WAIT) {
		if (++m_nStateCtr >= WAIT_TIME) {
			m_nStateCtr = TIME;
			m_state = STATE::OPEN;
		}
		LocalFunc::FillScreen(0.0f);
		return;
	}
	else if (m_state == STATE::CLOSE_WAIT)
	{
		if (++m_nStateCtr >= WAIT_TIME) {
			m_nStateCtr = 0;

			m_state = STATE::CLOSE;
		}
		LocalFunc::FillScreen(1.0f);
		return;
	}
	else if (m_state == STATE::OPEN)
	{
		if (--m_nStateCtr <= 0)
		{
			m_state = STATE::CLOSE_WAIT;
			m_stateCtr = WAIT_TIME;
		}
	}
	else if (m_state == STATE::CLOSE)
	{
		if (++m_nStateCtr >= TIME)
		{
			if (RNLib::Transition()->GetState() == CTransition::STATE::NONE)
			{
				Manager::Transition(CMode::TYPE::TITLE, CTransition::TYPE::NONE);
				m_state = STATE::NONE;
			}
		}
	}

	float fRate = (float)m_nStateCtr / TIME;
	float fRateOpp = 1.0 - fRate;

	LocalFunc::FillScreen(fRateOpp);

}

//========================================
// �X�V����(���)
// Author:KEISUKE OTONO
//========================================
void CMode_Logo::ProcessState(const PROCESS process) {
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