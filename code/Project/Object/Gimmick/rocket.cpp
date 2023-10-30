//========================================
// 
// ���P�b�g
// Author:KEISUKE OTONO
// 
//========================================
// *** rocket.cpp ***
//========================================
#include "rocket.h"
#include "../../main.h"

const int s_AnimeMax = 120;			// �A�j���[�V�����̍ő吔
const int s_RideAnimeMax = 20;		// ��荞�݃A�j���[�V�����̍ő吔
const float s_RideAnimeMag = 1.7f;	// ��荞�݃A�j���[�V�����̑傫���̔{��
const float s_RotAdd = 0.02f;		// �����̑�����
const int s_RotAnimeMax = 4;		// �����݃A�j���[�V�����̍ő� 
const float s_MoveMag = 1.05f;		// �ړ��ʂ̔{��
const float s_MoveAdd = 0.01f;		// �ړ��ʂ̑�����
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
	m_Info.Maxscale = Scale3D(1.0f, 1.0f, 1.0f);
	m_Info.nFlyAnimeCounter = 0;
	m_Info.Animstate = CRocket::ANIME_STATE::RIDE;
	m_Info.nRideAnimeCounter = 0;
	m_Info.nModelIdx = RNLib::Model().Load("data\\MODEL\\rocket.x");
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
	int nCounter;
	switch (m_Info.Animstate)
	{
	case CRocket::ANIME_STATE::NONE:

		break;
	case CRocket::ANIME_STATE::RIDE:
		m_Info.nRideAnimeCounter++;
		
		if (m_Info.nRideAnimeCounter <= s_RideAnimeMax)
		{
			m_Info.scale = Scale3D(1.0f + (float)m_Info.nRideAnimeCounter / (s_RideAnimeMax * s_RideAnimeMag), 1.0f + (float)m_Info.nRideAnimeCounter / (s_RideAnimeMax * s_RideAnimeMag), 1.0f + (float)m_Info.nRideAnimeCounter / (s_RideAnimeMax * s_RideAnimeMag));
		}
		else if (m_Info.nRideAnimeCounter <= s_RideAnimeMax * 2)
		{
			if (m_Info.nRideAnimeCounter == s_RideAnimeMax + 1)
			{
				m_Info.Maxscale = m_Info.scale;
			}
			m_Info.scale = Scale3D(m_Info.Maxscale.x - (float)(m_Info.nRideAnimeCounter - s_RideAnimeMax) / (s_RideAnimeMax * s_RideAnimeMag), m_Info.Maxscale.y - (float)(m_Info.nRideAnimeCounter - s_RideAnimeMax) / (s_RideAnimeMax * s_RideAnimeMag), m_Info.Maxscale.z - (float)(m_Info.nRideAnimeCounter - s_RideAnimeMax) / (s_RideAnimeMax * s_RideAnimeMag));
		}
		else if (m_Info.nRideAnimeCounter <= s_RideAnimeMax * 3)
		{
			m_Info.Animstate = CRocket::ANIME_STATE::FLY;
			m_Info.nRideAnimeCounter = 0;
		}
		break;
	case CRocket::ANIME_STATE::FLY:
		m_Info.nFlyAnimeCounter++;
		nCounter = m_Info.nFlyAnimeCounter % s_RotAnimeMax;
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
								// �ߋ��̈ʒu
		break;

	}

	RNLib::Model().Put(m_pos, m_rot, m_Info.scale, m_Info.nModelIdx, false)
		->SetOutLine(true);

}

//========================================
// �`��
//========================================
void CRocket::Draw(void)
{

}