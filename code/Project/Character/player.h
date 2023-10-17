//================================================================================================
//
//�v���C���[����[player.h]
//Author:Hirasawa Shion
//
//================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//�v���C���[�N���X
class CPlayer
{
public:
	//�v���C���[���
	struct Info
	{
		D3DXVECTOR3 pos;			//�ʒu
		D3DXVECTOR3 rot;			//����
		D3DXVECTOR3 move;			//�ړ���
		bool		bJump;			//�W�����v
		float		fJumpPower;		//�W�����v��
		float		fGravity;		//�d��
		float		fGravityCorr;	//�d�͌W��
		int			nModelIdx;		//���f���ԍ�
	};

	static const int SWAP_INTERVAL;	//�X���b�v�C���^�[�o��
	static const int NUM_PLAYER = 2;//�v���C���[�̐�

	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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

private:
	static bool	s_bSwap;		//�X���b�v�������ǂ���
	static int	s_nSwapInterval;//�c��X���b�v�C���^�[�o��

	Info m_aInfo[NUM_PLAYER];	//�e�v���C���[�̏��
};

#endif