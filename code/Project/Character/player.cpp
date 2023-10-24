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
#include "../Object/Block/move-block.h"
#include "../Object/Gimmick/meteor.h"
#include "../Object/Gimmick/trampoline.h"

//�X���b�v�C���^�[�o��
const int	CPlayer::SWAP_INTERVAL = 30;	//�X���b�v�C���^�[�o��
int			CPlayer::s_nSwapInterval = 0;	//�c��X���b�v�C���^�[�o��

const float CPlayer::SIZE_WIDTH  = 8.0f;	//����
const float CPlayer::SIZE_HEIGHT = 8.0f;	//����

const float CPlayer::MOVE_SPEED = 0.5f;		//�ړ���
const float CPlayer::MAX_MOVE_SPEED = 2.7f;	//�ő�ړ���

const float CPlayer::JUMP_POWER = 3.0f;	//��{�W�����v��
const float CPlayer::GRAVITY_POWER = -3.0f;	//��{�d�͉����x
const float CPlayer::GRAVITY_CORR = 0.01f;	//��{�d�͌W��

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
		Player.bGround = false;				//�n�ʂɐڂ��Ă��邩
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

	//���X�V
	UpdateInfo();
}

//----------------------------
//���X�V����
//----------------------------
void CPlayer::UpdateInfo(void)
{
	for each (Info &Player in m_aInfo)
	{
		//�ʒu�ݒ�
		RNLib::Model()->Put(Player.pos, Player.rot, Player.nModelIdx, false)
			->SetOutLine(true);

		//�X���b�v��̃}�[�N��`�悷��ʒu
		D3DXVECTOR3 MarkPos = Player.pos;
		MarkPos.y *= -1.0f;

		RNLib::Polygon3D()->Put(MarkPos, INITD3DXVECTOR3)
			->SetSize(20.0f, 20.0f)
			->SetBillboard(true);
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
			Player.bGround = false;				//�n�ʂ��痣�ꂽ
			Player.move.y = Player.fJumpPower;	//�W�����v�ʑ��
			Player.bJump = true;				//�W�����v����
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
	m_aInfo[0].bGround = m_aInfo[1].bGround = false;

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
				//�v���C���[�̋߂��ɃI�u�W�F�N�g�����邩����
				{
					const D3DXVECTOR3 PosDiff = POS - Player.pos;
					const float fLength = D3DXVec3Length(&PosDiff);

					const float fWIDTH_SUM = WIDTH + SIZE_WIDTH;
					const float fHEIGHT_SUM = HEIGHT + SIZE_WIDTH;

					float flength = sqrtf(fWIDTH_SUM * fWIDTH_SUM + fHEIGHT_SUM * fHEIGHT_SUM);

					if (fLength > sqrtf(fWIDTH_SUM * fWIDTH_SUM + fHEIGHT_SUM * fHEIGHT_SUM)) continue;
				}

				//��ގ擾
				const CStageObject::TYPE type = stageObj->GetType();

				//�O��ʒu
				D3DXVECTOR3 PosOld = POS;

				//�ړ�����I�u�W�F�N�g�́A�O��ʒu����ʂɐݒ�
				switch (type)
				{
					//�ړ���
					case CStageObject::TYPE::MOVE_BLOCK:
					{
						CMoveBlock *pBlock = (CMoveBlock *)stageObj;
						PosOld = pBlock->GetPosOld();
					}
						break;

						//覐�
					case CStageObject::TYPE::METEOR:
					{
						CMeteor *pMeteor = (CMeteor *)stageObj;
						//PosOld = pMeteor->GetPosOld();
					}
						break;
				}

				//���������������i�[
				const COLLI_ROT ColliRot = IsBoxCollider(Player.pos, Player.posOLd, SIZE_WIDTH, SIZE_HEIGHT, POS, PosOld, WIDTH, HEIGHT, vec);

				//�������Ă��Ȃ���΃X�L�b�v
				if (ColliRot == COLLI_ROT::NONE) continue;

				//��ނ��ƂɊ֐�����
				switch (type)
				{
					case CStageObject::TYPE::BLOCK:			CollisionBlock(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::FILLBLOCK:		break;
					case CStageObject::TYPE::TRAMPOLINE:	CollisionTrampoline(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::SPIKE:			CollisionSpike(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::MOVE_BLOCK:	CollisionMoveBlock(&Player, (CMoveBlock *)stageObj, MinPos, MaxPos, ColliRot);	break;
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

#if 0
	//�v���C���[�̈ʒu�X�V
	for(int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		RNLib::Text2D()->Put(D3DXVECTOR2(20.0f, 20.0f + 25.0f * nCnt), 0.0f, CreateText("%dP��Y���W�F%f", nCnt, m_aInfo[nCnt].pos.y), CText::ALIGNMENT::LEFT, 0);
	}

	RNLib::Text2D()->Put(D3DXVECTOR2(20.0f, 80.0f), 0.0f, CreateText("FPS�F%d", RNLib::GetFPSCount()), CText::ALIGNMENT::LEFT, 0);
#endif

	////�v���C���[�̈ʒu�X�V
	//for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	//{
	//	RNLib::Text3D()->Put(D3DXVECTOR3(20.0f, 20.0f + 25.0f * nCnt, 0.0f), INITD3DXVECTOR3, CreateText("%dP��Y���W�F%f", nCnt, m_aInfo[nCnt].pos.y), CText::ALIGNMENT::LEFT, 0);
	//}

	//RNLib::Text3D()->Put(D3DXVECTOR3(20.0f, 80.0f, 0.0f), INITD3DXVECTOR3, CreateText("FPS�F%d", RNLib::GetFPSCount()), CText::ALIGNMENT::LEFT, 0);

}

//----------------------------
//�ォ��̓����蔻��ɂ��ʒu�C��
//----------------------------
void CPlayer::FixPos_OVER(float *pPosY, float fMaxPosY, float *pMoveY)
{
	//�ʒu�E�ړ��ʏC��
	*pPosY = fMaxPosY + SIZE_HEIGHT;
	*pMoveY = 0.0f;
}

//----------------------------
//������̓����蔻��ɂ��ʒu�C��
//----------------------------
void CPlayer::FixPos_UNDER(float *pPosY, float fMinPosY, float *pMoveY)
{
	//�ʒu�E�ړ��ʏC��
	*pPosY = fMinPosY - SIZE_HEIGHT;
	*pMoveY = 0.0f;
}

//----------------------------
//������̓����蔻��ɂ��ʒu�C��
//----------------------------
void CPlayer::FixPos_LEFT(float *pPosX, float fMinPosX, float *pMoveX)
{
	//�ʒu�E�ړ��ʏC��
	*pPosX = fMinPosX - SIZE_WIDTH;
	*pMoveX = 0.0f;
}

//----------------------------
//�E����̓����蔻��ɂ��ʒu�C��
//----------------------------
void CPlayer::FixPos_RIGHT(float *pPosX, float fMaxPosX, float *pMoveX)
{
	//�ʒu�E�ړ��ʏC��
	*pPosX = fMaxPosX + SIZE_WIDTH;
	*pMoveX = 0.0f;
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
			FixPos_OVER(&pInfo->pos.y, MaxPos.y, &pInfo->move.y);

			//�\�̐��E�̃v���C���[
			if (pInfo->side == WORLD_SIDE::FACE) {
				pInfo->bGround = true;	//�n�ʂɐڂ��Ă���
				pInfo->bJump = false;	//�W�����v�\
			}
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::UNDER:
			//�ʒu�E�ړ��ʏC��
			FixPos_UNDER(&pInfo->pos.y, MinPos.y, &pInfo->move.y);

			//���̐��E�̃v���C���[�Ȃ�W�����v�\
			if (pInfo->side == WORLD_SIDE::BEHIND) {
				pInfo->bGround = true;	//�n�ʂɐڂ��Ă���
				pInfo->bJump = false;	//�W�����v�\
			}
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::LEFT:
			//�ʒu�E�ړ��ʏC��
			FixPos_LEFT(&pInfo->pos.x, MinPos.x, &pInfo->move.x);
			break;

			//*********************************
			//�E�ɓ�������
			//*********************************
		case COLLI_ROT::RIGHT:
			//�ʒu�E�ړ��ʏC��
			FixPos_RIGHT(&pInfo->pos.x, MaxPos.x, &pInfo->move.x);
			break;
	}
}

//----------------------------
//�g�����|�����̓����蔻�菈��
//----------------------------
void CPlayer::CollisionTrampoline(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	//���������������Ƃɏ�����؂�ւ�
	switch (ColliRot)
	{
		//*********************************
		//��ɓ�������
		//*********************************
		case COLLI_ROT::OVER:
			//�ʒu�E�ړ��ʏC��
			FixPos_OVER(&pInfo->pos.y, MaxPos.y, &pInfo->move.y);

			//�\�̐��E�̃v���C���[
			if (pInfo->side == WORLD_SIDE::FACE) {
				pInfo->bGround = true;	//�n�ʂɐڂ��Ă���
				pInfo->bJump = false;	//�W�����v�\
			}
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::UNDER:
			//�ʒu�E�ړ��ʏC��
			FixPos_UNDER(&pInfo->pos.y, MinPos.y, &pInfo->move.y);

			//���̐��E�̃v���C���[�Ȃ�W�����v�\
			if (pInfo->side == WORLD_SIDE::BEHIND) {
				pInfo->bGround = true;	//�n�ʂɐڂ��Ă���
				pInfo->bJump = false;	//�W�����v�\
			}
			break;
	}
}

//----------------------------
//�g�Q�̓����蔻�菈��
//----------------------------
void CPlayer::CollisionSpike(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	//���������������Ƃɏ�����؂�ւ�
	switch (ColliRot)
	{
		//*********************************
		//�㉺�ǂ��炩�ɓ�������
		//*********************************
		case COLLI_ROT::OVER:
		case COLLI_ROT::UNDER:
			//���S����
			Death(NULL);
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::LEFT:
			//�ʒu�E�ړ��ʏC��
			FixPos_LEFT(&pInfo->pos.x, MinPos.x, &pInfo->move.x);
			break;

			//*********************************
			//�E�ɓ�������
			//*********************************
		case COLLI_ROT::RIGHT:
			//�ʒu�E�ړ��ʏC��
			FixPos_RIGHT(&pInfo->pos.x, MaxPos.x, &pInfo->move.x);
			break;
	}
}

//----------------------------
//�ړ����̓����蔻�菈��
//----------------------------
void CPlayer::CollisionMoveBlock(Info *pInfo, CMoveBlock *pMoveBlock, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	switch (ColliRot)
	{
			//*********************************
			//��ɓ�������
			//*********************************
		case COLLI_ROT::OVER:
			//�ʒu�E�ړ��ʏC��
			FixPos_OVER(&pInfo->pos.y, MaxPos.y, &pInfo->move.y);

			//�\�̐��E�̃v���C���[�̏ꍇ
			if (pInfo->side == WORLD_SIDE::FACE)
			{
				pInfo->pos += pMoveBlock->GetMove();
				pInfo->bGround = true;	//�n�ʂɐڂ��Ă���
				pInfo->bJump = false;	//�W�����v�\
			}
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::UNDER:
			//�ʒu�E�ړ��ʏC��
			FixPos_UNDER(&pInfo->pos.y, MinPos.y, &pInfo->move.y);

			//���̐��E�̃v���C���[�Ȃ�W�����v�\
			if (pInfo->side == WORLD_SIDE::BEHIND)
			{
				pInfo->pos += pMoveBlock->GetMove();
				pInfo->bGround = true;	//�n�ʂɐڂ��Ă���
				pInfo->bJump = false;	//�W�����v�\
			}
			break;

			//*********************************
			//���ɓ�������
			//*********************************
		case COLLI_ROT::LEFT:
			//�ʒu�E�ړ��ʏC��
			FixPos_LEFT(&pInfo->pos.x, MinPos.x, &pInfo->move.x);
			break;

			//*********************************
			//�E�ɓ�������
			//*********************************
		case COLLI_ROT::RIGHT:
			//�ʒu�E�ړ��ʏC��
			FixPos_RIGHT(&pInfo->pos.x, MaxPos.x, &pInfo->move.x);
			break;

		case COLLI_ROT::UNKNOWN:
			/*
			//�ړ��� -> �v���C���[�ւ̓����蔻�菈�������s
			const D3DXVECTOR3 BlockPos = pMoveBlock->GetPos();
			const D3DXVECTOR3 BlockPosOld = pMoveBlock->GetPosOld();
			const float fWidth = pMoveBlock->GetWidth() * 0.5f;
			const float fHeight = pMoveBlock->GetHeight() * 0.5f;
			const D3DXVECTOR3 PlayerMinPos = D3DXVECTOR3(pInfo->pos.x - SIZE_WIDTH, pInfo->pos.y - SIZE_HEIGHT, 0.0f);
			const D3DXVECTOR3 PlayerMaxPos = D3DXVECTOR3(pInfo->pos.x + SIZE_WIDTH, pInfo->pos.y + SIZE_HEIGHT, 0.0f);

			//�ړ�������̓����蔻��
			for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++)
			{
				//�v���C���[�̂ǂ̕����ɓ������Ă��邩
				COLLI_ROT ColliRot_Player = IsBoxCollider(BlockPos, BlockPosOld, fWidth, fHeight, PlayerMinPos, PlayerMaxPos, (COLLI_VEC)nCntVec);

				//����ł�������Ȃ��Ȃ�A�X�L�b�v
				if (ColliRot_Player == COLLI_ROT::NONE || ColliRot_Player == COLLI_ROT::UNKNOWN) continue;

				//�������������i�㉺�E���E�j�𔽓]����
				{
					//��������������int�^�ɕϊ� - 1
					const int nRot = (int)ColliRot_Player;

					ColliRot_Player = (COLLI_ROT)(nRot - 1 + 2 * (nRot % 2));
				}

				//������x�����蔻��
				CollisionMoveBlock(pInfo, pMoveBlock, MinPos, MaxPos, ColliRot_Player);
			}
			*/
			break;
	}
}

//========================
//�Ώە��̒��ɂ߂荞��ł��邩�ǂ�������
//------------------------
// �����P	pos			�F���݈ʒu
// �����Q	posOld		�F�O��ʒu
// �����R	fWidth		�F��
// �����S	fHeight		�F����
// �����T	TargetPos	�F�Ώۂ̌��݈ʒu
// �����U	TargetPosOld�F�Ώۂ̑O��ʒu�i�I�u�W�F�N�g��PosOld�ϐ��������Ȃ�A���݈ʒu��������OK
// �����V	TargetWidth	�F�Ώۂ̕�
// �����W	TargetHeight�F�Ώۂ̍���
// �����X	value		�F�x�N�g��
// �Ԃ�l	�Ώە��ɂ߂肱��ł��������Ԃ��iNONE�Ȃ瓖�����Ă��Ȃ�
//========================
CPlayer::COLLI_ROT CPlayer::IsBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float fWidth, float fHeight, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetPosOld, float TargetWidth, float TargetHeight, COLLI_VEC value)
{
	//�����̌��݂̍ŏ��E�ő�ʒu
	const D3DXVECTOR2 MinPos = D3DXVECTOR2(pos.x - fWidth, pos.y - fHeight);
	const D3DXVECTOR2 MaxPos = D3DXVECTOR2(pos.x + fWidth, pos.y + fHeight);

	//�Ώۂ̌��݂̍ŏ��E�ő�ʒu
	const D3DXVECTOR2 TARGET_MinPos = D3DXVECTOR2(TargetPos.x - fWidth, TargetPos.y - fHeight);
	const D3DXVECTOR2 TARGET_MaxPos = D3DXVECTOR2(TargetPos.x + fWidth, TargetPos.y + fHeight);

	//�߂荞��ł��邩����
	if (MinPos.x < TARGET_MaxPos.x && TARGET_MinPos.x < MaxPos.x &&
		MinPos.y < TARGET_MaxPos.y && TARGET_MinPos.y < MaxPos.y)
	{
		//�����̉ߋ��̍ŏ��E�ő�ʒu
		const D3DXVECTOR2 OLD_MINPOS = D3DXVECTOR2(posOld.x - fWidth, posOld.y - fHeight);
		const D3DXVECTOR2 OLD_MAXPOS = D3DXVECTOR2(posOld.x + fWidth, posOld.y + fHeight);

		//�Ώۂ̑O��̍ŏ��E�ő�ʒu
		const D3DXVECTOR2 TARGET_MinPosOld = D3DXVECTOR2(TargetPosOld.x - fWidth, TargetPosOld.y - fHeight);
		const D3DXVECTOR2 TARGET_MaxPosOld = D3DXVECTOR2(TargetPosOld.x + fWidth, TargetPosOld.y + fHeight);

		//�Փ˃x�N�g���ŏ�������
		switch (value)
		{
			case COLLI_VEC::X:
				//�O��͍�����߂荞��ł��Ȃ��i���͂߂荞��
				if (OLD_MAXPOS.x <= TARGET_MinPosOld.x)			return COLLI_ROT::LEFT;

				//�O��͉E����߂荞��ł��Ȃ��i���͂߂荞��
				else if (OLD_MINPOS.x >= TARGET_MaxPosOld.x)	return COLLI_ROT::RIGHT;
				break;

			case COLLI_VEC::Y:
				//�O��͏ォ��߂荞��ł��Ȃ��i���͂߂荞��
				if (OLD_MINPOS.y >= TARGET_MaxPosOld.y)			return COLLI_ROT::OVER;

				//�O��͉�����߂荞��ł��Ȃ��i���͂߂荞��
				else if (OLD_MAXPOS.y <= TARGET_MinPosOld.y)	return COLLI_ROT::UNDER;
				break;
		}

		//��������������������Ȃ�
		return COLLI_ROT::UNKNOWN;
	}

	//������Ȃ�����
	return COLLI_ROT::NONE;
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