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
		bool		bJump;			//�W�����v
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

private:
	static int	s_nSwapInterval;//�c��X���b�v�C���^�[�o��

	static const float MOVE_SPEED;		//�ړ���
	static const float MAX_MOVE_SPEED;	//�ő�ړ���

	static const float JUMP_POWER;		//��{�W�����v��
	static const float GRAVITY_POWER;	//��{�d�͉����x
	static const float GRAVITY_CORR;	//��{�d�͌W��

	void SetPosOld(void);
	void ActionControl(void);
	void Move(COLLI_VEC vec);
	void Swap(void);
	void Death(D3DXVECTOR3 *pDeathPos);//���񂾏ꏊ�������Ɏw��i���S�p�[�e�B�N���Ȃǂ�`�悷��̂Ɏg�p����

	void WholeCollision(void);
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
	COLLI_ROT IsBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float fWidth, float fHeight, D3DXVECTOR3 TargetMinPos, D3DXVECTOR3 TargetMaxPos, COLLI_VEC value);

	void CollisionBlock(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot);
	void CollisionSpike(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot);

	Info m_aInfo[NUM_PLAYER];	//�e�v���C���[�̏��
};

#endif