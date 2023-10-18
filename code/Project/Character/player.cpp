//================================================================================================
//
//�v���C���[����[player.cpp]
//Author:Hirasawa Shion
//
//================================================================================================
#include "../main.h"
#include "player.h"
#include "../../_RNLib/_Basis/Other/input.h"
#include "../../_RNLib/_Basis/Calculation/number.h"

//�X���b�v�C���^�[�o��
const int	CPlayer::SWAP_INTERVAL = 200;	//�X���b�v�C���^�[�o��
int			CPlayer::s_nSwapInterval = 0;	//�c��X���b�v�C���^�[�o��
const float CPlayer::UPPER_GROUND = 20.0f;	//��̐��E�̑���ʒu
const float CPlayer::DOWNER_GROUND = -20.0f;//���̐��E�̑���ʒu

const float CPlayer::MOVE_SPEED = 0.5f;		//�ړ���
const float CPlayer::MAX_MOVE_SPEED = 3.0f;	//�ő�ړ���

const float CPlayer::JUMP_POWER = 8.0f;		//��{�W�����v��
const float CPlayer::GRAVITY_POWER = -3.0f;	//��{�d�͉����x
const float CPlayer::GRAVITY_CORR = 0.1f;	//��{�d�͌W��

//=======================================
//�R���X�g���N�^
//=======================================
CPlayer::CPlayer()
{
	s_nSwapInterval = 0;	//�c��X���b�v�C���^�[�o��

	for each (Info &Player in m_aInfo)
	{
		//���N���A
		Player.pos = INITD3DXVECTOR3;
		Player.posOLd = INITD3DXVECTOR3;
		Player.rot = INITD3DXVECTOR3;
		Player.move = INITD3DXVECTOR3;
		Player.bJump = false;
		Player.fJumpPower = 0.0f;
		Player.fGravity = 0.0f;
		Player.fGravityCorr = 0.0f;
		Player.nModelIdx = DATANONE;
		Player.side = WORLD_SIDE::FACE;
	}
}

//=======================================
//�f�X�g���N�^
//=======================================
CPlayer::~CPlayer()
{

}

//=======================================
//��������
//=======================================
CPlayer *CPlayer::Create(void)
{
	//�v���C���[�C���X�^���X�̐���
	CPlayer *pPlayer = new CPlayer;

	//����������
	pPlayer->Init();

	//�v���C���[��Ԃ�
	return pPlayer;
}

//=======================================
//����������
//=======================================
HRESULT CPlayer::Init(void)
{
	//�P�o�������
	m_aInfo[0].nModelIdx = RNLib::Model()->Load("data\\MODEL\\1P.x");
	m_aInfo[0].pos = D3DXVECTOR3(50.0f, UPPER_GROUND, 0.0f);
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;
	m_aInfo[0].side = WORLD_SIDE::FACE;

	//�Q�o�������
	m_aInfo[1].nModelIdx = RNLib::Model()->Load("data\\MODEL\\2P.x");
	m_aInfo[1].pos = D3DXVECTOR3(-50.0f, DOWNER_GROUND, 0.0f);
	m_aInfo[1].fJumpPower = -JUMP_POWER;
	m_aInfo[1].fGravity = -GRAVITY_POWER;
	m_aInfo[1].fGravityCorr = GRAVITY_CORR;
	m_aInfo[1].side = WORLD_SIDE::BEHIND;

	//����������
	return S_OK;
}

//=======================================
//�I������
//=======================================
void CPlayer::Uninit(void)
{

}

//=======================================
//�O��ʒu�ݒ菈��
//=======================================
void CPlayer::SetPosOld(void)
{
	//�v���C���[�̑O��ʒu�X�V
	for each (Info &Player in m_aInfo)
	{
		Player.posOLd = Player.pos;
	}
}

//=======================================
//�X�V����
//=======================================
void CPlayer::Update(void)
{
	SetPosOld();

	//���쏈��
	ActionControl();

	//�X���b�v
	Swap();

	//�ړ�����
	Move();

	//�����蔻��܂Ƃ�
	WholeCollision();

	//�v���C���[�̈ʒu�X�V
	for each (Info &Player in m_aInfo)
	{
		RNLib::Model()->Put(Player.pos, Player.rot, Player.nModelIdx, false);
	}
}

//----------------------------
//�v���C���[���ݒ�
//----------------------------
void CPlayer::SetInfo(Info p1, Info p2)
{
	//�e�v���C���[���ݒ�
	m_aInfo[0] = p1;
	m_aInfo[1] = p2;
}

//----------------------------
//���쏈��
//----------------------------
void CPlayer::ActionControl(void)
{
	//�e�v���C���[�̃A�N�V�����L�[
	const int ACTION_KEY[NUM_PLAYER][3] = {
		{ DIK_W , DIK_D , DIK_A },	//�P�o�̑���L�[
		{ DIK_UPARROW, DIK_RIGHTARROW, DIK_LEFTARROW}//�Q�o�̑���L�[
	};

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		//�����Q��
		Info& rInfo = m_aInfo[nCntPlayer];

		//�W�����v���́i�󒆂���Ȃ��j
		if (!rInfo.bJump && RNLib::Input()->Trigger(ACTION_KEY[nCntPlayer][0], CInput::BUTTON_UP))
		{
			//�W�����v�ʑ��
			rInfo.move.y = rInfo.fJumpPower;

			//�W�����v����
			rInfo.bJump = true;
		}

		//�E�Ɉړ�
		if (RNLib::Input()->Press(ACTION_KEY[nCntPlayer][1], CInput::BUTTON_RIGHT))	rInfo.move.x += MOVE_SPEED;

		//���Ɉړ�
		if (RNLib::Input()->Press(ACTION_KEY[nCntPlayer][2], CInput::BUTTON_LEFT))	rInfo.move.x -= MOVE_SPEED;
	}
}

//############################
//�X���b�v����
//############################
void CPlayer::Swap(void)
{
	//�C���^�[�o��������Ό��������ďI��
	if (s_nSwapInterval > 0)
	{
		s_nSwapInterval--;
		return;
	}

	//���҂Ƃ��ɃX���b�v�{�^���������Ă���
	if (RNLib::Input()->KeyPress(DIK_S) && RNLib::Input()->KeyPress(DIK_DOWNARROW))
	{
		//�C���^�[�o���ݒ�
		s_nSwapInterval = SWAP_INTERVAL;

		for each (Info &Player in m_aInfo)
		{
			//�ʒu�E�d�͉����x�E�W�����v�ʁE���݂��鐢�E�𔽓]
			Player.pos.y *= -1.0f;
			Player.fGravity *= -1.0f;
			Player.fJumpPower *= -1.0f;
			Player.side = (WORLD_SIDE)(((int)Player.side + 1) % (int)WORLD_SIDE::MAX);
		}

		//�O��ʒu�X�V
		SetPosOld();
	}
}

//----------------------------
//�ړ�����
//----------------------------
void CPlayer::Move(void)
{
	//�v���C���[�̈ʒu�X�V
	for each (Info &Player in m_aInfo)
	{
		//��������
		Player.move.x += (0.0f - Player.move.x) * 0.1f;

		//�]�̈ړ��ʂ��C��
		FloatControl(&Player.move.x, MAX_MOVE_SPEED, -MAX_MOVE_SPEED);

		//�d�͏���
		Player.move.y += (Player.fGravity - Player.move.y) * Player.fGravityCorr;

		//�ړ��ʔ��f
		Player.pos += Player.move;

		//��̐��E�ɂ���
		if (Player.posOLd.y >= UPPER_GROUND &&
			Player.pos.y <= UPPER_GROUND)		//��̒n�ʂɂ߂荞��
		{
			Player.pos.y = UPPER_GROUND;//�n�ʂɖ߂�
			Player.move.y = 0.0f;		//�d�͂�����
			Player.bJump = false;		//�W�����v�\
		}

		//���̐��E�ɂ���
		else if (Player.posOLd.y <= DOWNER_GROUND &&
				 Player.pos.y >= DOWNER_GROUND)		//���̒n�ʂɂ߂荞��
		{
			Player.pos.y = DOWNER_GROUND;	//�n�ʂɖ߂�
			Player.move.y = 0.0f;			//�d�͂�����
			Player.bJump = false;			//�W�����v�\
		}
	}	
}

//----------------------------
//�����蔻��܂Ƃ�
//----------------------------
void CPlayer::WholeCollision(void)
{
	//�I�u�W�F�N�g�̃|�C���^���i�[
	CObject *obj = NULL;

	//�I�u�W�F�N�g���擾
	while (Manager::BlockMgr()->ListLoop(&obj)) {
		//�擾�����I�u�W�F�N�g���L���X�g
		CStageObject* stageObj = (CStageObject*)obj;
	
		for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++)
		{
			//��ނ��ƂɊ֐�����
			switch (stageObj->GetType())
			{
				case CStageObject::TYPE::BLOCK:		CollisionBlock(stageObj, (COLLI_VEC)nCntVec);	break;
				case CStageObject::TYPE::TRAMPOLINE:	break;
				case CStageObject::TYPE::MOVE_BLOCK:	break;
				case CStageObject::TYPE::METEOR:		break;
			}
		}
	}
}

//----------------------------
//�u���b�N�̓����蔻�菈��
//----------------------------
void CPlayer::CollisionBlock(CStageObject *pObj, COLLI_VEC value)
{
	//�u���b�N�̓����蔻����擾
	const D3DXVECTOR3 POS = pObj->GetPos();
	const float WIDTH = pObj->GetWidth();
	const float HEIGHT = pObj->GetHeight();

	//�u���b�N�̍ŏ��E�ő�ʒu
	const D3DXVECTOR2 MinPos = D3DXVECTOR2(POS.x - WIDTH, POS.y - HEIGHT);
	const D3DXVECTOR2 MaxPos = D3DXVECTOR2(POS.x + WIDTH, POS.y + HEIGHT);

	for each (Info &Player in m_aInfo)
	{
		//�w�x�N�g���̓����蔻��
		if (value == COLLI_VEC::X)
		{
			//�ŏ��ʒu��艺  or  �ő�ʒu����  �Ȃ�X�L�b�v
			if (MinPos.y > Player.pos.y || Player.pos.y > MaxPos.y) continue;

			//���̓����蔻��
			if (Player.posOLd.x <= MinPos.x &&
				Player.pos.x > MinPos.x)
			{
				Player.pos.x = MinPos.x;
				Player.move.x = 0.0f;
			}
			//�E�̓����蔻��
			else if(Player.posOLd.x >= MaxPos.x &&
					Player.pos.x < MaxPos.x)
			{
				Player.pos.x = MaxPos.x;
				Player.move.x = 0.0f;
			}
		}

		//�x�x�N�g���̓����蔻��
		else if (value == COLLI_VEC::Y)
		{
			//�ŏ��ʒu��荶  or  �ő�ʒu���E  �Ȃ�X�L�b�v
			if (MinPos.x > Player.pos.x || Player.pos.x > MaxPos.x) continue;

			//���̓����蔻��
			if (Player.posOLd.y <= MinPos.y &&
				Player.pos.y > MinPos.y)
			{
				Player.pos.y = MinPos.y;
				Player.move.y = 0.0f;

				//���̐��E�ɂ���Ȃ�W�����v�\
				if (Player.side == WORLD_SIDE::BEHIND)	Player.bJump = false;
			}
			//��̓����蔻��
			else if (Player.posOLd.y >= MaxPos.y &&
					 Player.pos.y < MaxPos.y)
			{
				Player.pos.y = MaxPos.y;
				Player.move.y = 0.0f;

				//�\�̐��E�ɂ���Ȃ�W�����v�\
				if (Player.side == WORLD_SIDE::FACE)	Player.bJump = false;
			}
		}
	}
}