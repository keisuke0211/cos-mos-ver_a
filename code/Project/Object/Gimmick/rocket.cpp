//========================================
// 
// ���P�b�g
// Author:KOMURO HIROMU
// 
//========================================
// *** rocket.cpp ***
//========================================
#include "rocket.h"
#include "../../main.h"
#include"../../Character/player.h"

const int   CRocket::s_AnimeMax = 120;		// ���������A�j���[�V�����̍ő吔
const int   CRocket::s_RideAnimeMax = 25;	// ��荞�݃A�j���[�V�����̍ő吔
const float CRocket::s_RideAnimeMag = 1.3f;	// �傫��1.0����ɂ���������Z�����傫��	
const float CRocket::s_RideAnimeShrink = 20;// ��荞�݃A�j���[�V�����̏k�ޔ{��
const float CRocket::s_RotAdd = 0.02f;		// �����̑�����
const int   CRocket::s_RotAnimeMax = 4;		// �����݃A�j���[�V�����̍ő� 
const float CRocket::s_MoveMag = 1.05f;		// �ړ��ʂ̔{��
const float CRocket::s_MoveAdd = 0.01f;		// �ړ��ʂ̑�����
const int   CRocket::s_FadeModeCountMax = 120;	// �t�F�[�h�̃��[�h�̃J�E���g�ő�

//========================================
// �R���X�g���N�^
//========================================
CRocket::CRocket(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::ROCKET;
	m_width = SIZE_OF_1_SQUARE*3;
	m_height = SIZE_OF_1_SQUARE*3;

	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.scale = Scale3D(1.0f,1.0f,1.0f);
	m_Info.nFlyAnimeCounter = 0;
	m_Info.SmallSpeed = 0.0f;
	m_Info.fScaleMag = 1.0f;
	m_Info.Animstate = CRocket::ANIME_STATE::NONE;
	m_Info.nRideAnimeCounter = 0;
	m_Info.nCountPlayer = 0;
	m_Info.nModelIdx = RNLib::Model().Load("data\\MODEL\\Rocket_Body.x");
}

//========================================
// �f�X�g���N�^
//========================================
CRocket::~CRocket()
{

}

//========================================
// ������
//========================================
HRESULT CRocket::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	if (m_pos.y < 0)
	{// ���̐��E�ɂ���Ƃ����]������
		m_rot.z -= D3DX_PI;
	}
	return S_OK;
}

//========================================
// �I��
//========================================
void CRocket::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CRocket::Update(void)
{
	//���A�j���[�V�����Ɉړ�
	if (RNLib::Input().GetKeyPress(DIK_R))
	{
		m_Info.Animstate = CRocket::ANIME_STATE::RIDE;
		Ride();
	}

	switch (m_Info.Animstate)
	{
	case CRocket::ANIME_STATE::NONE:
		break;
	case CRocket::ANIME_STATE::RIDE:
		UpdateState_Ride();		// ��яo��������Ԃ̍X�V
		break;
	case CRocket::ANIME_STATE::FLY:
		UpdateState_Fly();		// ��яo��������Ԃ̍X�V
		break;

	}

	RNLib::Model().Put(m_pos, m_rot, m_Info.scale * m_Info.fScaleMag, m_Info.nModelIdx, false);

}
//========================================
// ����ԍX�V
//========================================
void CRocket::UpdateState_Ride(void)
{
	m_Info.nRideAnimeCounter++;	// �A�j���[�V�����̑���

	if (m_Info.nRideAnimeCounter <= 1)
	{// �傫������
	}
	else if (m_Info.nRideAnimeCounter <= s_RideAnimeMax)
	{// ����������
		m_Info.fScaleMag -= m_Info.SmallSpeed;	// �X�P�[���{���̌��Z
		if (m_Info.fScaleMag <= 1.0f)
		{
			m_Info.fScaleMag = 1.0f;
		}
	}
	else if (m_Info.nRideAnimeCounter <= (s_RideAnimeMax + s_RideAnimeShrink) * 4)
	{// �A�j���[�V�����̈ڍs
		m_Info.Animstate = CRocket::ANIME_STATE::NONE;	// �Ȃ��ɕύX	
		m_Info.nRideAnimeCounter = 0;					// ���A�j���[�V�����J�E���^�[��������
	}
}
//========================================
// ��ԏ�ԍX�V
//========================================
void CRocket::UpdateState_Fly(void)
{
	int nCounter;

	m_Info.nFlyAnimeCounter++;	// �A�j���[�V�����̑���
	nCounter = m_Info.nFlyAnimeCounter % s_RotAnimeMax;	// �����̌v�Z

	// ���[�h�̐؂�ւ�	
	if (m_Info.nFlyAnimeCounter >= s_FadeModeCountMax)
	{
		Manager::StgEd()->SwapStage(Manager::StgEd()->GetStageIdx() + 1);
	}

	// ���������������
	if (nCounter >= s_RotAnimeMax * 0.5f)
	{
		m_rot.z += s_RotAdd;
	}
	else
	{
		m_rot.z -= s_RotAdd;
	}

	if (m_Info.nFlyAnimeCounter >= s_AnimeMax)
	{
		m_Info.move.y *= s_MoveMag;	// �ړ��ʂɔ{����������

		if (m_pos.y >= 0)
		{// ��̐��E�ɂ���Ƃ�
			m_Info.move.y += s_MoveAdd;
		}
		else
		{// ���̐��E�ɂ���Ƃ�
			m_Info.move.y -= s_MoveAdd;
		}
	}

	
	m_pos += m_Info.move;	// �ʒu�Ɉړ��ʂ̑���
}
//========================================
// �`��
//========================================
void CRocket::Draw(void)
{

}
//========================================
// ����Ă���
//========================================
void CRocket::Ride(void)
{
	m_Info.nCountPlayer++;											// �v���C���[�̏�����l���̑���
	m_Info.fScaleMag = s_RideAnimeMag;								// �X�P�[���{���̐ݒ�
	m_Info.SmallSpeed = (m_Info.fScaleMag - 1.0f) / s_RideAnimeMax;	// �������Ȃ鑬�x�̐ݒ�

	m_Info.Animstate = ANIME_STATE::RIDE;		// ����ԂɈڍs
	if (m_Info.nCountPlayer == CPlayer::NUM_PLAYER)
	{// �v���C���[���S���������
		m_Info.Animstate = ANIME_STATE::FLY;	// ��ԏ�ԂɈڍs
	}
}