//================================================================================================
//
//�v���C���[����[player.h]
//Author:Hirasawa Shion
//
//================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�O���錾
class CStageObject;
class CMoveBlock;
class CParts;
class CRocket;

//�v���C���[�N���X
class CPlayer
{
public:
	//�\���ǂ���̐��E�ɑ��݂��邩
	enum class WORLD_SIDE	{
		FACE = 0,	//�\
		BEHIND,		//��
		MAX,
	};

	//�����蔻��̏��ԗ�
	enum class COLLI_VEC {
		X = 0,	//�]�x�N�g��
		Y,		//�x�x�N�g��
		MAX
	};

	//�����蔻�肪����������
	enum class COLLI_ROT {
		NONE = 0,	//�����Ȃ�
		OVER,		//��
		UNDER,		//��
		LEFT,		//��
		RIGHT,		//�E
		UNKNOWN,	//�������Ă��邯�Ǖ�����������Ȃ��i�������鑤�������Ă���\���A��
		MAX
	};

	//�v���C���[���
	struct Info
	{
		D3DXVECTOR3 StartPos;		//�J�n�ʒu

		D3DXVECTOR3 pos;			//�ʒu
		D3DXVECTOR3 posOLd;			//�O��ʒu
		D3DXVECTOR3 rot;			//����
		D3DXVECTOR3 move;			//�ړ���
		bool		bGround;		//�n�ʂɐڂ��Ă��邩
		bool		bJump;			//�W�����v
		bool		bRide;			//���P�b�g�ɏ���Ă��邩�ǂ���
		float		fJumpPower;		//�W�����v��
		float		fGravity;		//�d��
		float		fGravityCorr;	//�d�͌W��
		int			nModelIdx;		//���f���ԍ�
		WORLD_SIDE  side;			//�ǂ���̐��E�ɑ��݂��邩
	};

	static const float SIZE_WIDTH;	//����
	static const float SIZE_HEIGHT;	//����

	static const int SWAP_INTERVAL;	//�X���b�v�C���^�[�o��
	static const int NUM_PLAYER = 2;//�v���C���[�̐�

	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//----------------------------
	//�v���C���[����
	//�v���C���[�̃|�C���^��Ԃ��܂�
	//----------------------------
	static CPlayer *Create(void);

	//----------------------------
	//�v���C���[���ݒ�
	//�w�肳�ꂽ�ԍ��̃v���C���[����ݒ肵�܂��B
	//----------------------------
	void SetInfo(const Info info, const int nNum);

	//----------------------------
	//�v���C���[���ݒ�
	//�e�v���C���[�̈ʒu���Ȃǂ������ɓn���Ă��������B
	//�\���́uInfo�v�Ɋւ��Ă�player.h�̃N���X�錾���m�F���Ă��������B
	//----------------------------
	void SetInfo(Info p1, Info p2);

	//----------------------------
	//�v���C���[�ʒu���ݒ�
	//�w�肵���v���C���[�̈ʒu���������ɓn���Ă��������B
	//----------------------------
	void SetPos(const int nNum, D3DXVECTOR3 pos) { m_aInfo[nNum].StartPos = m_aInfo[nNum].pos = pos; }

	//----------------------------
	//�v���C���[���擾
	//�e�����Ƀv���C���[���̃A�h���X��n���܂�
	//----------------------------
	void GetInfo(Info*& pP1, Info*& pP2) { pP1 = &m_aInfo[0]; pP2 = &m_aInfo[1]; }

	//----------------------------
	//�v���C���[���擾
	//�w�肳�ꂽ�ԍ��̃v���C���[���̃A�h���X��Ԃ��܂�
	//----------------------------
	Info *GetInfo(int nNum) { return &m_aInfo[nNum]; }

	//----------------------------
	//�v���C���[���擾
	//�w�肳�ꂽ���E�ɂ���v���C���[�̏���Ԃ��܂�
	//----------------------------
	Info *GetInfo(WORLD_SIDE side);

	//----------------------------
	//�X���b�v�C���^�[�o����ݒ�
	//���ɃC���^�[�o��������ΐݒ肵�Ȃ�
	//----------------------------
	static void SetSwapInterval(void) { s_nSwapInterval = s_nSwapInterval == 0 ? SWAP_INTERVAL : s_nSwapInterval; }

private:
	static int	s_nSwapInterval;//�c��X���b�v�C���^�[�o��

	static const float MOVE_SPEED;		//�ړ���
	static const float MAX_MOVE_SPEED;	//�ő�ړ���

	static const float JUMP_POWER;		//��{�W�����v��
	static const float GRAVITY_POWER;	//��{�d�͉����x
	static const float GRAVITY_CORR;	//��{�d�͌W��

	static int	s_nNumGetParts;	//�擾�����p�[�c�̐�
	static bool	s_bRideRocket;	//���P�b�g�ɏ��邩�ǂ���

	void SetPosOld(void);
	void ActionControl(void);
	void Move(COLLI_VEC vec);
	void Swap(void);
	void Death(D3DXVECTOR3 *pDeathPos);//���񂾏ꏊ�������Ɏw��i���S�p�[�e�B�N���Ȃǂ�`�悷��̂Ɏg�p����

	void WholeCollision(void);

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
	COLLI_ROT IsBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float fWidth, float fHeight, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetPosOld, float TargetWidth, float TargetHeight, COLLI_VEC value);

	void FixPos_OVER(float *pPosY, float fMaxPosY, float *pMoveY);	//�ォ��̓����蔻��ɂ��ʒu�E�ړ��ʏC��
	void FixPos_UNDER(float *pPosY, float fMinPosY, float *pMoveY);//������̓����蔻��ɂ��ʒu�E�ړ��ʏC��
	void FixPos_LEFT(float *pPosX, float fMinPosX, float *pMoveX);	//������̓����蔻��ɂ��ʒu�E�ړ��ʏC��
	void FixPos_RIGHT(float *pPosX, float fMaxPosX, float *pMoveX);//�E����̓����蔻��ɂ��ʒu�E�ړ��ʏC��

	void CollisionBlock(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot);
	void CollisionTrampoline(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot);
	void CollisionSpike(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot);
	void CollisionMoveBlock(Info *pInfo, CMoveBlock *pMoveBlock,D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot);
	void CollisionParts(Info *pInfo, CParts *pParts);
	void CollisionRocket(Info *pInfo, CRocket *pRocket);

	//���X�V�����i�X�V�����̍Ō�Ɉʒu���Ȃǂ�ݒ肷��
	void UpdateInfo(void);

	Info m_aInfo[NUM_PLAYER];	//�e�v���C���[�̏��
};

#endif