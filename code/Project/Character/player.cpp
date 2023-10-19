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
const int	CPlayer::SWAP_INTERVAL = 30;	//�X���b�v�C���^�[�o��
int			CPlayer::s_nSwapInterval = 0;	//�c��X���b�v�C���^�[�o��

const float CPlayer::SIZE_WIDTH  = 8.0f;	//����
const float CPlayer::SIZE_HEIGHT = 8.0f;	//����

const float CPlayer::MOVE_SPEED = 0.5f;		//�ړ���
const float CPlayer::MAX_MOVE_SPEED = 2.7f;	//�ő�ړ���

const float CPlayer::JUMP_POWER = 12.0f;		//��{�W�����v��
const float CPlayer::GRAVITY_POWER = -8.0f;	//��{�d�͉����x
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
		Player = FormatInfo();
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
	m_aInfo[0].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;
	m_aInfo[0].side = WORLD_SIDE::FACE;

	//�Q�o�������
	m_aInfo[1].nModelIdx = RNLib::Model()->Load("data\\MODEL\\2P.x");
	m_aInfo[1].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
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
//�O��ʒu�X�V����
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
	//�O��ʒu�X�V
	SetPosOld();

	//���쏈��
	ActionControl();

	//�X���b�v
	Swap();

	//�����蔻��܂Ƃ�
	WholeCollision();

	//�v���C���[�̈ʒu�X�V
	for each (Info &Player in m_aInfo)
	{
		RNLib::Model()->Put(Player.pos, Player.rot, Player.nModelIdx, false)
			->SetOutLine(true);
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
	const int ACTION_KEY[NUM_PLAYER][4] = {
		{ DIK_W, DIK_S, DIK_D , DIK_A },	//�P�o�̑���L�[
		{ DIK_UPARROW, DIK_DOWNARROW, DIK_RIGHTARROW, DIK_LEFTARROW}//�Q�o�̑���L�[
	};

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		//�����Q��
		Info& Player = m_aInfo[nCntPlayer];

		//�W�����v���́i�󒆂���Ȃ��j
		if (!Player.bJump && RNLib::Input()->Trigger(ACTION_KEY[nCntPlayer][(int)Player.side], (int)CInput::BUTTON::UP))
		{
			//�W�����v�ʑ��
			Player.move.y = Player.fJumpPower;

			//�W�����v����
			Player.bJump = true;
		}

		//�E�Ɉړ�
		if (RNLib::Input()->Press(ACTION_KEY[nCntPlayer][2], (int)CInput::BUTTON::RIGHT))
			Player.move.x += MOVE_SPEED;

		//���Ɉړ�
		if (RNLib::Input()->Press(ACTION_KEY[nCntPlayer][3], (int)CInput::BUTTON::LEFT))
			Player.move.x -= MOVE_SPEED;
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

	//�e�v���C���[�̃A�N�V�����L�[
	const int ACTION_KEY[NUM_PLAYER][2] = {
		{ DIK_S, DIK_W},	//�P�o�̑���L�[
		{ DIK_DOWNARROW, DIK_UPARROW }//�Q�o�̑���L�[
	};

	//���҂Ƃ��ɃX���b�v�{�^���������Ă���
	if (RNLib::Input()->KeyPress(ACTION_KEY[0][(int)m_aInfo[0].side]) && RNLib::Input()->KeyPress(ACTION_KEY[1][(int)m_aInfo[1].side]))
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
void CPlayer::Move(COLLI_VEC vec)
{
	//�v���C���[�̈ʒu�X�V
	for each (Info &Player in m_aInfo)
	{
		//�ړ��ʔ��f
		switch (vec)
		{
			case COLLI_VEC::X:
				//��������
				Player.move.x += (0.0f - Player.move.x) * 0.1f;

				//�]�̈ړ��ʂ��C��
				FloatControl(&Player.move.x, MAX_MOVE_SPEED, -MAX_MOVE_SPEED);

				//�ʒu�X�V
				Player.pos.x += Player.move.x;
				break;

				//�d�͏���
			case COLLI_VEC::Y:
				Player.move.y += (Player.fGravity - Player.move.y) * Player.fGravityCorr;

				//�ʒu�X�V
				Player.pos.y += Player.move.y;
				break;
		}
	}
}

//----------------------------
//�����蔻��܂Ƃ�
//----------------------------
void CPlayer::WholeCollision(void)
{
	for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++) {

		//�ړ�����
		Move((COLLI_VEC)nCntVec);

		//�I�u�W�F�N�g�̃|�C���^���i�[
		CObject *obj = NULL;

		//�I�u�W�F�N�g���擾
		while (Manager::BlockMgr()->ListLoop(&obj)) {
			//�擾�����I�u�W�F�N�g���L���X�g
			CStageObject* stageObj = (CStageObject*)obj;

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
	const float WIDTH = pObj->GetWidth() * 0.5f;
	const float HEIGHT = pObj->GetHeight() * 0.5f;

	//�u���b�N�̍ŏ��E�ő�ʒu
	const D3DXVECTOR2 MinPos = D3DXVECTOR2(POS.x - WIDTH, POS.y - HEIGHT);
	const D3DXVECTOR2 MaxPos = D3DXVECTOR2(POS.x + WIDTH, POS.y + HEIGHT);

	for each (Info &Player in m_aInfo)
	{
		if (value == COLLI_VEC::X)
		{//�w�x�N�g���̓����蔻��
			if (MinPos.y < Player.pos.y + SIZE_HEIGHT && Player.pos.y - SIZE_HEIGHT < MaxPos.y)
			{// �㉺�ŏd�Ȃ��Ă���
				//���̓����蔻��
				if (Player.posOLd.x + SIZE_WIDTH <= MinPos.x &&
					Player.pos.x + SIZE_WIDTH> MinPos.x)
				{
					Player.pos.x = MinPos.x - SIZE_WIDTH;
					Player.move.x = 0.0f;
				}
				//�E�̓����蔻��
				else if (Player.posOLd.x - SIZE_WIDTH >= MaxPos.x &&
						 Player.pos.x - SIZE_WIDTH < MaxPos.x)
				{
					Player.pos.x = MaxPos.x + SIZE_WIDTH;
					Player.move.x = 0.0f;
				}
			}
		}
		else if (value == COLLI_VEC::Y)
		{//�x�x�N�g���̓����蔻��
			if (MinPos.x < Player.pos.x + SIZE_WIDTH  && Player.pos.x - SIZE_WIDTH < MaxPos.x)
			{// ���E�ŏd�Ȃ��Ă���
				//���̓����蔻��
				if (Player.posOLd.y + SIZE_HEIGHT <= MinPos.y &&
					Player.pos.y + SIZE_HEIGHT > MinPos.y)
				{
					Player.pos.y = MinPos.y - SIZE_HEIGHT;
					Player.move.y = 0.0f;

					//���̐��E�ɂ���Ȃ�W�����v�\
					if (Player.side == WORLD_SIDE::BEHIND)	Player.bJump = false;
				}
				//��̓����蔻��
				else if (Player.posOLd.y - SIZE_HEIGHT >= MaxPos.y &&
						 Player.pos.y - SIZE_HEIGHT < MaxPos.y)
				{
					Player.pos.y = MaxPos.y + SIZE_HEIGHT;
					Player.move.y = 0.0f;

					//�\�̐��E�ɂ���Ȃ�W�����v�\
					if (Player.side == WORLD_SIDE::FACE)	Player.bJump = false;
				}
			}
		}
	}
}

//----------------------------
//�v���C���[���ݒ�
//�w�肳�ꂽ�ԍ��̃v���C���[����ݒ肵�܂��B
//----------------------------
void CPlayer::SetInfo(const Info info, const int nNum)
{
	if (0 <= nNum || nNum < NUM_PLAYER)
	{
		//�����
		m_aInfo[nNum] = info;
	}
}

//----------------------------
//�v���C���[���̏���������
//�v���C���[����������Ԃɂ��܂��B
//----------------------------
CPlayer::Info CPlayer::FormatInfo(void)
{
	return{
		INITD3DXVECTOR3,	//�ʒu
		INITD3DXVECTOR3,	//�O��ʒu
		INITD3DXVECTOR3,	//����
		INITD3DXVECTOR3,	//�ړ���
		false,				//�W�����v
		JUMP_POWER,			//�W�����v��
		GRAVITY_POWER,		//�d��
		GRAVITY_CORR ,		//�d�͌W��
		DATANONE,			//���f���ԍ�
		WORLD_SIDE::FACE,	//�ǂ���̐��E�ɑ��݂��邩
	};
}