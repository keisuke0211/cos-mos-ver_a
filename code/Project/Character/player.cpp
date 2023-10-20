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

const float CPlayer::JUMP_POWER = 11.0f;		//��{�W�����v��
const float CPlayer::GRAVITY_POWER = -11.0f;	//��{�d�͉����x
const float CPlayer::GRAVITY_CORR = 0.06f;	//��{�d�͌W��

//=======================================
//�R���X�g���N�^
//=======================================
CPlayer::CPlayer()
{
	s_nSwapInterval = 0;	//�c��X���b�v�C���^�[�o��

	for each(Info &Player in m_aInfo)
	{
		Player.StartPos = INITD3DXVECTOR3;	//�J�n�ʒu
		Player.pos = INITD3DXVECTOR3;		//�ʒu
		Player.posOLd = INITD3DXVECTOR3;	//�O��ʒu
		Player.rot = INITD3DXVECTOR3;		//����
		Player.move = INITD3DXVECTOR3;		//�ړ���
		Player.bJump = false;				//�W�����v
		Player.fJumpPower = 0.0f;			//�W�����v��
		Player.fGravity = 0.0f;				//�d��
		Player.fGravityCorr = 0.0f;			//�d�͌W��
		Player.nModelIdx = DATANONE;		//���f���ԍ�
		Player.side = WORLD_SIDE::FACE;		//�ǂ���̐��E�ɑ��݂��邩
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

	//�������ݒ�
	Death(NULL);

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
		if (!Player.bJump && RNLib::Input()->GetTrigger(ACTION_KEY[nCntPlayer][(int)Player.side], CInput::BUTTON::UP))
		{
			//�W�����v�ʑ��
			Player.move.y = Player.fJumpPower;

			//�W�����v����
			Player.bJump = true;
		}

		//�E�Ɉړ�
		if (RNLib::Input()->GetPress(ACTION_KEY[nCntPlayer][2], CInput::BUTTON::RIGHT))
			Player.move.x += MOVE_SPEED;

		//���Ɉړ�
		if (RNLib::Input()->GetPress(ACTION_KEY[nCntPlayer][3], CInput::BUTTON::LEFT))
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
	if (RNLib::Input()->GetKeyPress(ACTION_KEY[0][(int)m_aInfo[0].side]) && RNLib::Input()->GetKeyPress(ACTION_KEY[1][(int)m_aInfo[1].side]))
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
//���S����
//----------------------------
void CPlayer::Death(D3DXVECTOR3 *pDeathPos)
{
	//�P�o�������
	m_aInfo[0].pos = m_aInfo[0].StartPos;
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;
	m_aInfo[0].side = WORLD_SIDE::FACE;

	//�Q�o�������
	m_aInfo[1].pos = m_aInfo[1].StartPos;
	m_aInfo[1].fJumpPower = -JUMP_POWER;
	m_aInfo[1].fGravity = -GRAVITY_POWER;
	m_aInfo[1].fGravityCorr = GRAVITY_CORR;
	m_aInfo[1].side = WORLD_SIDE::BEHIND;
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
	//��U���v���C���[�Ƃ��ɃW�����v�s��
	m_aInfo[0].bJump = m_aInfo[1].bJump = true;

	for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++) {

		//�Փ˃x�N�g�����L���X�g
		const COLLI_VEC vec = (COLLI_VEC)nCntVec;

		//�ړ�����
		Move(vec);

		//�I�u�W�F�N�g�̃|�C���^���i�[
		CObject *obj = NULL;

		//�I�u�W�F�N�g���擾
		while (Manager::BlockMgr()->ListLoop(&obj)) {
			//�擾�����I�u�W�F�N�g���L���X�g
			CStageObject* stageObj = (CStageObject*)obj;

			//�I�u�W�F�N�g�̓����蔻����擾
			const D3DXVECTOR3 POS = stageObj->GetPos();
			const float WIDTH = stageObj->GetWidth() * 0.5f;
			const float HEIGHT = stageObj->GetHeight() * 0.5f;

			//�I�u�W�F�N�g�̍ŏ��E�ő�ʒu
			const D3DXVECTOR3 MinPos = D3DXVECTOR3(POS.x - WIDTH, POS.y - HEIGHT, 0.0f);
			const D3DXVECTOR3 MaxPos = D3DXVECTOR3(POS.x + WIDTH, POS.y + HEIGHT, 0.0f);

			for each(Info& Player in m_aInfo)
			{
				//���������������i�[
				const COLLI_ROT ColliRot = IsBoxCollider(Player.pos, Player.posOLd, SIZE_WIDTH, SIZE_HEIGHT, MinPos, MaxPos, vec);

				//�������Ă��Ȃ���΃X�L�b�v
				if (ColliRot == COLLI_ROT::NONE) continue;

				//��ގ擾
				const CStageObject::TYPE type = stageObj->GetType();

				//��ނ��ƂɊ֐�����
				switch (type)
				{
					case CStageObject::TYPE::BLOCK:			CollisionBlock(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::FILLBLOCK:		break;
					case CStageObject::TYPE::TRAMPOLINE:	break;
					case CStageObject::TYPE::SPIKE:			CollisionSpike();	break;
					case CStageObject::TYPE::MOVE_BLOCK:	break;
					case CStageObject::TYPE::METEOR:		break;
					case CStageObject::TYPE::PARTS:			break;
				}

				//������Α����̃I�u�W�F�N�g�ɓ������Ă���
				if (type == CStageObject::TYPE::SPIKE ||
					type == CStageObject::TYPE::METEOR)
				{
					break;
				}
			}
		}
	}
}

//----------------------------
//�u���b�N�̓����蔻�菈��
//----------------------------
void CPlayer::CollisionBlock(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	//���������������Ƃɏ�����؂�ւ�
	switch (ColliRot)
	{
			//*********************************
			//��ɓ�������
			//*********************************
		case COLLI_ROT::OVER:
			//�ʒu�E�ړ��ʏC��
			pInfo->pos.y = MaxPos.y + SIZE_HEIGHT;
			pInfo->move.y = 0.0f;

			//�\�̐��E�̃v���C���[�Ȃ�W�����v�\
			if (pInfo->side == WORLD_SIDE::FACE) pInfo->bJump = false;
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::UNDER:
			//�ʒu�E�ړ��ʏC��
			pInfo->pos.y = MinPos.y - SIZE_HEIGHT;
			pInfo->move.y = 0.0f;

			//���̐��E�̃v���C���[�Ȃ�W�����v�\
			if (pInfo->side == WORLD_SIDE::BEHIND) pInfo->bJump = false;
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::LEFT:
			//�ʒu�E�ړ��ʏC��
			pInfo->pos.x = MinPos.x - SIZE_WIDTH;
			pInfo->move.x = 0.0f;
			break;

			//*********************************
			//�E�ɓ�������
			//*********************************
		case COLLI_ROT::RIGHT:
			//�ʒu�E�ړ��ʏC��
			pInfo->pos.x = MaxPos.x + SIZE_WIDTH;
			pInfo->move.x = 0.0f;
			break;
	}
}

//----------------------------
//�g�Q�̓����蔻�菈��
//----------------------------
void CPlayer::CollisionSpike(void)
{
	//���S����
	Death(NULL);
}

//========================
//�Ώە��̒��ɂ߂荞��ł��邩�ǂ�������
//------------------------
// �����P	pos				�F���݈ʒu
// �����Q	posOld			�F�O��ʒu
// �����R	fWidth			�F��
// �����S	fHeight			�F����
// �����T	TargetMinPos	�F�Ώە��̍ŏ��ʒu
// �����U	TargetMaxPos	�F�Ώە��̍ő�ʒu
// �Ԃ�l	�Ώە��ɂ߂肱��ł��������Ԃ��iNONE�Ȃ瓖�����Ă��Ȃ�
//========================
CPlayer::COLLI_ROT CPlayer::IsBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float fWidth, float fHeight, D3DXVECTOR3 TargetMinPos, D3DXVECTOR3 TargetMaxPos, COLLI_VEC value)
{
	//������������
	COLLI_ROT ColliRot = COLLI_ROT::NONE;

	//�����̌��݂̍ŏ��E�ő�ʒu
	const D3DXVECTOR2 MINPOS = D3DXVECTOR2(pos.x - fWidth, pos.y - fHeight);
	const D3DXVECTOR2 MAXPOS = D3DXVECTOR2(pos.x + fWidth, pos.y + fHeight);

	//�߂荞��ł��邩����
	if (MINPOS.x < TargetMaxPos.x && TargetMinPos.x < MAXPOS.x &&
		MINPOS.y < TargetMaxPos.y && TargetMinPos.y < MAXPOS.y)
	{
		//�����̉ߋ��̍ŏ��E�ő�ʒu
		const D3DXVECTOR2 OLD_MINPOS = D3DXVECTOR2(posOld.x - fWidth, posOld.y - fHeight);
		const D3DXVECTOR2 OLD_MAXPOS = D3DXVECTOR2(posOld.x + fWidth, posOld.y + fHeight);

		//�Փ˃x�N�g���ŏ�������
		switch (value)
		{
			case COLLI_VEC::X:
				//�O��͍�����߂荞��ł��Ȃ��i���͂߂荞��
				if (OLD_MAXPOS.x <= TargetMinPos.x)		ColliRot = COLLI_ROT::LEFT;

				//�O��͉E����߂荞��ł��Ȃ��i���͂߂荞��
				else if (OLD_MINPOS.x >= TargetMaxPos.x)		ColliRot = COLLI_ROT::RIGHT;
				break;

			case COLLI_VEC::Y:
				//�O��͏ォ��߂荞��ł��Ȃ��i���͂߂荞��
				if (OLD_MINPOS.y >= TargetMaxPos.y)		ColliRot = COLLI_ROT::OVER;

				//�O��͉�����߂荞��ł��Ȃ��i���͂߂荞��
				else if (OLD_MAXPOS.y <= TargetMinPos.y)		ColliRot = COLLI_ROT::UNDER;
				break;
		}
	}

	//��������������Ԃ�
	return ColliRot;
}

//----------------------------
//�v���C���[���ݒ�
//�w�肳�ꂽ�ԍ��̃v���C���[����ݒ肵�܂��B
//----------------------------
void CPlayer::SetInfo(const Info info, const int nNum)
{
	if (0 <= nNum && nNum < NUM_PLAYER)
	{
		//�e�v���C���[���ݒ�
		m_aInfo[nNum] = info;
		m_aInfo[nNum].StartPos = info.pos;
	}
}

//----------------------------
//�v���C���[���ݒ�
//----------------------------
void CPlayer::SetInfo(Info p1, Info p2)
{
	//�e�v���C���[���ݒ�
	m_aInfo[0] = p1;	m_aInfo[0].StartPos = p1.pos;
	m_aInfo[1] = p2;	m_aInfo[1].StartPos = p2.pos;
}

//----------------------------
//�v���C���[���擾
//�w�肳�ꂽ���E�ɂ���v���C���[�̏���Ԃ��܂�
//----------------------------
CPlayer::Info *CPlayer::GetInfo(WORLD_SIDE side)
{
	//�P�o�̂��鐢�E�ƍ��v������P�o����Ԃ�
	if (m_aInfo[0].side == side) return &m_aInfo[0];

	//�Ⴄ�Ȃ�Q�o����Ԃ�
	else return &m_aInfo[1];
}