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
const int	CPlayer::SWAP_INTERVAL = 0;
bool		CPlayer::s_bSwap = false;		//�X���b�v�������ǂ���
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
	s_bSwap = false;		//�X���b�v�������ǂ���
	s_nSwapInterval = 0;	//�c��X���b�v�C���^�[�o��

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		//���N���A
		m_aInfo[nCntPlayer].pos = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].posOLd = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].rot = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].move = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].bJump = false;
		m_aInfo[nCntPlayer].fJumpPower = 0.0f;
		m_aInfo[nCntPlayer].fGravity = 0.0f;
		m_aInfo[nCntPlayer].fGravityCorr = 0.0f;
		m_aInfo[nCntPlayer].nModelIdx = DATANONE;
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
	m_aInfo[0].nModelIdx = RNLib::Model()->Load("data\\MODEL\\1P.x");
	m_aInfo[0].pos = D3DXVECTOR3(50.0f, UPPER_GROUND, 0.0f);
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;

	m_aInfo[1].nModelIdx = RNLib::Model()->Load("data\\MODEL\\2P.x");
	m_aInfo[1].pos = D3DXVECTOR3(-50.0f, DOWNER_GROUND, 0.0f);
	m_aInfo[1].fJumpPower = -JUMP_POWER;
	m_aInfo[1].fGravity = -GRAVITY_POWER;
	m_aInfo[1].fGravityCorr = GRAVITY_CORR;

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
	//�P�o�̏����Q��
	Info& rInfo = m_aInfo[0];

	//�W�����v���́i�󒆂���Ȃ��j
	if (!rInfo.bJump && RNLib::Input()->Trigger(DIK_W, CInput::BUTTON_UP))
	{
		//�W�����v�ʑ��
		rInfo.move.y = rInfo.fJumpPower;

		//�W�����v����
		rInfo.bJump = true;
	}

	//�E�Ɉړ�
	if (RNLib::Input()->Press(DIK_D, CInput::BUTTON_UP))
	{
		rInfo.move.x += MOVE_SPEED;
	}

	//���Ɉړ�
	if (RNLib::Input()->Press(DIK_A, CInput::BUTTON_UP))	rInfo.move.x -= MOVE_SPEED;
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
			}
			//��̓����蔻��
			else if (Player.posOLd.y >= MaxPos.y &&
					 Player.pos.y < MaxPos.y)
			{
				Player.pos.y = MaxPos.y;
				Player.move.y = 0.0f;
			}
		}
	}
}