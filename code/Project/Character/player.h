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

	//�v���C���[���
	struct Info
	{
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
	//�e�v���C���[�̈ʒu���Ȃǂ������ɓn���Ă��������B
	//�\���́uInfo�v�Ɋւ��Ă�player.h�̃N���X�錾���m�F���Ă��������B
	//----------------------------
	void SetInfo(Info p1, Info p2);

	// �ʒu�ݒ�
	void SetPos(int idx, D3DXVECTOR3 pos) { m_aInfo[idx].pos = pos; }

	//----------------------------
	//�v���C���[���擾
	//�֐����ĂԑO��Info�\���̂��l���錾���A
	//���ԂɈ����ɓ���Ă��������B
	//�����͎Q�ƌ^�Ȃ̂ŁA�����ɓ���邾���ŏ�񂪑������܂��B
	//----------------------------
	void GetInfo(Info& rP1, Info& rP2) { rP1 = m_aInfo[0]; rP2 = m_aInfo[1]; }
	
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

	void WholeCollision(void);
	void CollisionBlock(CStageObject *pObj, COLLI_VEC value);

	Info m_aInfo[NUM_PLAYER];	//�e�v���C���[�̏��
};

#endif