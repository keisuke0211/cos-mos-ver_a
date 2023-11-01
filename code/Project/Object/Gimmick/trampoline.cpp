//========================================
// 
// �g�����|�����̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"
#include "../../main.h"
#include "../../../_RNLib/Basis/input.h"
#include "../../Character/player.h"


#define MAX_COUNT		(12)	//�ő�J�E���g��
#define PLAYER_FLAME	(12)	//�v���C���[�̍������B�J�E���g
#define RADIUS_WIDTH	(0.5f)	//�����a
#define RADIUS_HEIGHT	(0.5f)	//�c���a
#define CORRECT_WIDTH	(8.0f)	//�����␳
#define CORRECT_HEIGHT	(6.0f)	//�����␳

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampoline�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CTrampoline::CTrampoline(void) {
	Manager::BlockMgr()->AddList(this);

	//�������
	m_type = TYPE::TRAMPOLINE;
	m_width = SIZE_OF_1_SQUARE * 2;
	m_height = SIZE_OF_1_SQUARE;
	m_state = STATE::NONE;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bLand = false;
	m_modelIdx[0] = RNLib::Model().Load("data\\MODEL\\Spring_Body.x");
	m_modelIdx[1] = RNLib::Model().Load("data\\MODEL\\Spring_Footing.x");
	m_modelIdx[2] = RNLib::Model().Load("data\\MODEL\\Spring_Spring.x");
	m_modelIdx[3] = RNLib::Model().Load("data\\MODEL\\Spring_Eye.x");
	m_fJamp = 8.0f;
	m_nCnt = 1;
}

//========================================
// �f�X�g���N�^
//========================================
CTrampoline::~CTrampoline(void) {

}

//========================================
// ����������
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Init(void) {

}

//========================================
// �I������
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Uninit(void) {

}

//========================================
// �X�V����
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Update(void) {

	//�y�䃂�f��
	RNLib::Model().Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[0], false)
		->SetCol(m_color)
		->SetOutLine(true);

	//�ڋʃ��f��
	RNLib::Model().Put(D3DXVECTOR3(m_pos.x + CORRECT_WIDTH, m_pos.y, m_pos.z - CORRECT_HEIGHT), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[3], false)
		->SetCol(m_color)
		->SetOutLine(true);
	RNLib::Model().Put(D3DXVECTOR3(m_pos.x - CORRECT_WIDTH, m_pos.y, m_pos.z - CORRECT_HEIGHT), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[3], false)
		->SetCol(m_color)
		->SetOutLine(true);

	if (m_nCnt > 0) 
	{
		m_nCnt--;
		if(m_nCnt == 0)
			m_state = STATE::NONE;
	}

	if (m_state != STATE::NONE)
	{//�g�����|�������쓮���Ă���

		//�����v�Z
		float fCountRate = CEase::Easing(CEase::TYPE::IN_SINE, m_nCnt, MAX_COUNT);
		
		if (m_state == STATE::UP_LAND)
		{
			//�L�m�R
			RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y + CORRECT_HEIGHT, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false)
				->SetOutLine(true);
			RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y - CORRECT_HEIGHT - m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), m_modelIdx[1], false)
				->SetOutLine(true);

			//�΂�
			RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y - m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), m_modelIdx[2], false)
				->SetOutLine(true);
		}
		else if (m_state == STATE::DOWN_LAND)
		{
			//�L�m�R
			RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y + CORRECT_HEIGHT + m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false)
				->SetOutLine(true);
			RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y - CORRECT_HEIGHT, m_pos.z), D3DXVECTOR3(0.0f, 0.0f,D3DX_PI), m_modelIdx[1], false)
				->SetOutLine(true);

			//�΂�
			RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y + m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false)
				->SetOutLine(true);
		}
	}
	else if (m_state == STATE::NONE)
	{//�g�����|�������쓮���Ă��Ȃ�
		RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y + CORRECT_HEIGHT, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false)
			->SetOutLine(true);
		RNLib::Model().Put(D3DXVECTOR3(m_pos.x, m_pos.y - CORRECT_HEIGHT, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, D3DX_PI), m_modelIdx[1], false)
			->SetOutLine(true);
	}

	//�����蔻��
	Collision();
}
//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Draw(void) {

}
//========================================
// �����蔻�菈��
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Collision(void) {

	//�v���C���[���擾
	CPlayer::Info *p1, *p2;
	CPlayer *pPlayer = CMode_Game::GetPlayer();
	if (pPlayer == NULL)
		return;
	pPlayer->GetInfo(p1, p2);

	float width, height;

	width = m_width * RADIUS_WIDTH;
	height = m_height * RADIUS_HEIGHT;

	//**************************************
	//1p�g�����|���������蔻��
	//**************************************
	if (p1->bGround == false
		&& p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - width && p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + width
		&& p1->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height && p1->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height)
	{//�y��͈͓̔��ɒ��n�œ�����

		if (p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - width&& p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + width
			&& p2->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - height
			&& p2->side == CPlayer::WORLD_SIDE::BEHIND)
		{//2p������Ă��邩

			CPlayer::SetSwapInterval();

			//�W�����v�ʂ��p��
			p2->move.y = -(p1->fMaxHeight / PLAYER_FLAME);
			p2->fOrientHeight = -p1->fMaxHeight;
			p2->bTrampolineJump = true;

			p2->bGround = false;
		}
		else if (p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - width&& p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + width
			&& p2->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + height
			&& p2->side == CPlayer::WORLD_SIDE::FACE)
		{
			CPlayer::SetSwapInterval();

			//�W�����v�ʂ��p��
			p2->move.y = -(p1->fMaxHeight / PLAYER_FLAME);
			p2->fOrientHeight = -p1->fMaxHeight;
			p2->bTrampolineJump = true;

			p2->bGround = false;
		}

		if (m_state == STATE::NONE
			&& p1->side == CPlayer::WORLD_SIDE::FACE)
		{//�g�����|�������쓮���Ă��Ȃ�

			m_state = STATE::UP_LAND;
			m_nCnt = MAX_COUNT;
		}
		else if (m_state == STATE::NONE
			&& p1->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			m_state = STATE::DOWN_LAND;
			m_nCnt = MAX_COUNT;
		}
	}
	//**************************************
	//2p�g�����|���������蔻��
	//**************************************
	else if (p2->bGround == false
		&& p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - width&& p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + width
		&& p2->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height && p2->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height)
	{//�y��͈͓̔��ɒ��n�œ�����

		if (p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - width&& p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + width
			&& p1->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + height
			&& p1->side == CPlayer::WORLD_SIDE::FACE)
		{//1p������Ă��邩

			CPlayer::SetSwapInterval();

			//�W�����v�ʂ��p��
			p1->move.y = -(p2->fMaxHeight / PLAYER_FLAME);
			p1->fOrientHeight = -p2->fMaxHeight;
			p1->bTrampolineJump = true;

			p1->bGround = false;
		}
		else if (p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - width&& p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + width
			&& p1->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - height
			&& p1->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			CPlayer::SetSwapInterval();

			//�W�����v�ʂ��p��
			p1->move.y = -(p2->fMaxHeight / PLAYER_FLAME);
			p1->fOrientHeight = -p2->fMaxHeight;
			p1->bTrampolineJump = true;

			p1->bGround = false;
		}

		if (m_state == STATE::NONE
			&& p2->side == CPlayer::WORLD_SIDE::FACE)
		{//�g�����|�������쓮���Ă��Ȃ�

			m_state = STATE::UP_LAND;
			m_nCnt = MAX_COUNT;
		}
		else if (m_state == STATE::NONE
			&& p2->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			m_state = STATE::DOWN_LAND;
			m_nCnt = MAX_COUNT;
		}
	}
}