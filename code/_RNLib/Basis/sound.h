//========================================
// 
// �T�E���h�̃w�b�_�t�@�C��
// Author :AKIRA TANAKA
// Arrange:RIKU NISHIMURA
// 
//========================================
// [[[ sound.h ]]]
//========================================
#ifndef _SOUND_H_
#define _SOUND_H_

//****************************************
// �N���X��`
//****************************************
// �T�E���h�N���X
class CSound {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class CATEGORY{
		BGM,
		SE,
		MAX,
	};

	typedef enum {
		SPACE_NONE,
		SPACE_3D,
		SPACE_MAX,
	}SPACE;

	typedef enum {
		DISTANCE_NONE,
		DISTANCE_5M,
		DISTANCE_25M,
		DISTANCE_50M,
		DISTANCE_100M,
		DISTANCE_MAX,
	}DISTANCE;

	typedef enum {
		// BGM
		BGM_DIGBUG,			// �f�B�O�o�O
		BGM_DIGBUG_BOSS,	// �f�B�O�o�O(�{�X)
		// �V�X�e��SE
		SE_MENU_SELECT,		// ���j���[�I��
		SE_MENU_DECIDE,		// ���j���[����
		SE_MENU_BACK,		// ���j���[��߂�
		SE_SCORE_COUNT,		// �X�R�A�J�E���g
		SE_GOLD_COUNT,		// �S�[���h�J�E���g
		SE_ITEM_GET,		// �A�C�e���擾
		SE_GAMECLEAR,		// �Q�[���N���A
		SE_GAMEOVER,		// �Q�[���I�[�o�[
		SE_TAKE_AIM,		// �_��������
		// �퓬SE
		SE_BLOW_DAMAGE_LOW,		// �Ō��_���[�W(��)
		SE_BLOW_DAMAGE_MID,		// �Ō��_���[�W(��)
		SE_BLOW_DAMAGE_HIGH,	// �Ō��_���[�W(��)
		SE_SLASH_DAMAGE_LOW,	// �a���_���[�W(��)
		SE_SLASH_DAMAGE_MID,	// �a���_���[�W(��)
		SE_SLASH_DAMAGE_HIGH,	// �a���_���[�W(��)
		SE_SPC_DAMAGE_LOW,		// ����_���[�W(��)
		SE_SPC_DAMAGE_MID,		// ����_���[�W(��)
		SE_ELEM_DAMAGE_FIRE,	// �Α����_���[�W
		SE_ELEM_DAMAGE_WATER,	// �������_���[�W
		SE_ELEM_DAMAGE_ICE,		// �X�����_���[�W
		SE_ELEM_DAMAGE_WIND,	// �������_���[�W
		SE_ELEM_DAMAGE_ELEC,	// �������_���[�W
		SE_ELEM_DAMAGE_SOIL,	// �n�����_���[�W
		SE_ELEM_DAMAGE_DARK,	// �ő����_���[�W
		SE_ELEM_DAMAGE_LIGHT,	// �������_���[�W
		SE_IMPACT_MID,			// �Ռ�(��)
		SE_BREATH_LOW,			// �u���X(��)
		SE_BREATH_MID,			// �u���X(��)
		SE_BREATH_HIGH,			// �u���X(��)
		SE_BREATH_SHOT,			// �u���X�V���b�g
		// ��SE
		SE_LANDING_GRASS,	// ���n(��)
		SE_LANDING_SOIL,	// ���n(�y)
		SE_LANDING_STONE,	// ���n(��)
		SE_LANDING_SAND,	// ���n(��)
		SE_LANDING_IMPACT,	// ���n�̏Ռ�
		SE_EARTHQUAKE,		// �n�k
		SE_BREAK_SOIL,		// �j��(�y)
		SE_BREAK_STONE,		// �j��(��)
		SE_EXPLOSION_MID,	// ����(��)
		SE_SWING_LOW,		// �U��(��)
		SE_SWING_MID,		// �U��(��)
		SE_SWING_HIGH,		// �U��(��)
		SE_METAL_STRIKE,	// �����Փ�
		SE_MOTOR,			// ���[�^�[
		MAX,
	}TYPE;

	//========== [[[ �\���̒�` ]]]
	typedef struct Data_ {
		char     aFileName[TXT_MAX];
		int      nCntLoop;
		float    fVolume;
		CATEGORY category;
	}Data;

	typedef struct State_ {
		bool        bPlay = false;
		SPACE       space = SPACE_NONE;
		D3DXVECTOR3 pos   = INITD3DXVECTOR3;
		DISTANCE    dist  = DISTANCE_NONE;
	}State;

	//========== [[[ �֐��錾 ]]]
	CSound();
	~CSound();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(void);
	int  Play(int nSoundIdx, SPACE space = SPACE_NONE, D3DXVECTOR3 pos = INITD3DXVECTOR3, DISTANCE dist = DISTANCE_NONE);
	int  Stop(int nID);				// (�����x���w��)
	void Stop(TYPE type);			// (����ގw��)
	void Stop(CATEGORY category);	// (���J�e�S���[�w��)
	void Stop(void);				// (���S��)
	void SetPos(int nID, D3DXVECTOR3 pos);
	void SetMic3DPos(D3DXVECTOR3 pos) { m_mic3DPos = pos; }
	void SetSettingVolume(CATEGORY category);
	void TypeVolumeChange(CATEGORY category, float fVolume);

private:
	//========== [[[ �萔��` ]]]
	static const int PLAY_MAX = 32;

	//========== [[[ �֐��錾 ]]]
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//========== [[[ �ϐ��錾 ]]]
	Data  m_aData[MAX];
	float m_aCategoryVolume[(int)CATEGORY::MAX];	// ���ޖ��̉���
	float m_aSettingVolume [(int)CATEGORY::MAX];	// ���ޖ��̐ݒ�̉���
	State m_aState[MAX][PLAY_MAX];

	D3DXVECTOR3 m_mic3DPos;

	IXAudio2*               m_pXAudio2;	// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;
	IXAudio2SourceVoice*    m_apSourceVoice[MAX][PLAY_MAX];
	BYTE* m_apDataAudio[MAX];	// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[MAX];	// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
