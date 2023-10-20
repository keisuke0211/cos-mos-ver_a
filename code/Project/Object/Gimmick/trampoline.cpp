//========================================
// 
// �g�����|�����̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"
#include "../../main.h"
#include "../../../_RNLib/_Basis/Other/input.h"
#include "../../Character/player.h"


#define MAX_COUNT (30)	//�ő�J�E���g��

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
	m_width = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE * 0.5f;
	m_state = STATE::NONE;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bLand = false;
	m_modelIdx[0] = RNLib::Model()->Load("data\\MODEL\\Spring_Middle.x");
	m_modelIdx[1] = RNLib::Model()->Load("data\\MODEL\\Spring_Up.x");
	m_modelIdx[2] = RNLib::Model()->Load("data\\MODEL\\Spring_Down.x");
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
	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[0], false);

	if (m_nCnt > 0) 
	{
		m_nCnt--;
		if(m_nCnt == 0)
			m_state = STATE::NONE;
	}

	if (m_state != STATE::NONE)
	{//�g�����|�������쓮���Ă���

		//�����v�Z
		float fCountRate = Easing(EASE_IN, m_nCnt, MAX_COUNT);
		
		if (m_state == STATE::UP_LAND)
		{
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y - m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);
		}
		else if (m_state == STATE::DOWN_LAND)
		{
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y + m_fJamp * fCountRate, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
			RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);
		}
	}
	else if (m_state == STATE::NONE)
	{//�g�����|�������쓮���Ă��Ȃ�
		RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
		RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);
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

	//**************************************
	//1p�g�����|���������蔻��
	//**************************************
	if (/*p1�����n�ŏ��*/
		p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width && p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
		&& p1->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height && p1->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height
		|| p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
		&& p1->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height && p1->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height)
	{//�y��͈͓̔��ɒ��n�œ�����
	
		if (p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
			&& p2->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height
			&& p2->side == CPlayer::WORLD_SIDE::BEHIND)
		{//2p������Ă��邩
			
			//�W�����v�ʂ��p��
			p2->move.y += p1->move.y * 2.5f;
			
			//�u���b�N�̗��ʒu�ɖ߂�
			p2->pos.y = m_pos.y - m_height * 2.0f;
		}
		if (p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
			&& p2->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height
			&& p2->side == CPlayer::WORLD_SIDE::FACE)
		{
			//�W�����v�ʂ��p��
			p2->move.y += p1->move.y * 2.5f;

			//�u���b�N�̗��ʒu�ɖ߂�
			p2->pos.y = m_pos.y + m_height * 2.0f;
		}

		if (m_state == STATE::NONE
			&& p1->side == CPlayer::WORLD_SIDE::FACE)
		{//�g�����|�������쓮���Ă��Ȃ�

			m_state = STATE::UP_LAND;
			m_nCnt = MAX_COUNT;
			p1->bJump = false;
		}
		else if (m_state == STATE::NONE
			&& p1->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			m_state = STATE::DOWN_LAND;
			m_nCnt = MAX_COUNT;
			p1->bJump = false;
		}

		//�ړ��ʁi�c�j������
		p1->move.y = 0.0f;

		if (p1->side == CPlayer::WORLD_SIDE::FACE)
		{
			//�u���b�N�̗��ʒu�ɖ߂�
			p1->pos.y = m_pos.y + m_height * 2.0f;
		}
		else if (p1->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			//�u���b�N�̗��ʒu�ɖ߂�
			p1->pos.y = m_pos.y - m_height * 2.0f;
		}
	}
	//**************************************
	//2p�g�����|���������蔻��
	//**************************************
	else if (/*p2�����n�ŏ��*/
		p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
		&& p2->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height && p2->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height
		|| p2->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width && p2->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
		&& p2->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height && p2->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height)
	{//�y��͈͓̔��ɒ��n�œ�����

		if (p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
			&& p1->pos.y - CPlayer::SIZE_HEIGHT <= m_pos.y + m_height
			&& p1->side == CPlayer::WORLD_SIDE::FACE)
		{//1p������Ă��邩

			//�W�����v�ʂ��p��
			p1->move.y = p2->move.y * 2.6875f;			

			//�u���b�N�̗��ʒu�ɖ߂�
			p1->pos.y = m_pos.y + m_height * 2.0f;
		}
		else if (p1->pos.x + CPlayer::SIZE_WIDTH >= m_pos.x - m_width&& p1->pos.x - CPlayer::SIZE_WIDTH <= m_pos.x + m_width
			&& p1->pos.y + CPlayer::SIZE_HEIGHT >= m_pos.y - m_height
			&& p1->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			//�W�����v�ʂ��p��
			p1->move.y = p2->move.y * 2.6875f;

			//�u���b�N�̗��ʒu�ɖ߂�
			p1->pos.y = m_pos.y - m_height * 2.0f;
		}

		if (m_state == STATE::NONE
			&& p2->side == CPlayer::WORLD_SIDE::FACE)
		{//�g�����|�������쓮���Ă��Ȃ�

			m_state = STATE::UP_LAND;
			m_nCnt = MAX_COUNT;
			p2->bJump = false;
		}
		else if (m_state == STATE::NONE
			&& p2->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			m_state = STATE::DOWN_LAND;
			m_nCnt = MAX_COUNT;
			p1->bJump = false;
		}

		//�ړ��ʁi�c�j������
		p2->move.y = 0.0f;

		if (p2->side == CPlayer::WORLD_SIDE::FACE)
		{
			//�u���b�N�̗��ʒu�ɖ߂�
			p2->pos.y = m_pos.y + m_height * 2.0f;
		}
		else if (p2->side == CPlayer::WORLD_SIDE::BEHIND)
		{
			//�u���b�N�̗��ʒu�ɖ߂�
			p2->pos.y = m_pos.y - m_height * 2.0f;
		}
	}
}