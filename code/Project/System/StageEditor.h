//========================================
// 
// �X�e�[�W�G�f�B�b�g�̓ǂݍ���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once
using namespace std;

//****************************************
// �O���錾
//****************************************
class CSVFILE;

//****************************************
// �N���X��`
//****************************************
class CStageEditor {

public:

	// �萔
	static const char* STAGE_INFO_FILE;		// �X�e�[�W���̃t�@�C���p�X

	// *** ���\���� ***

	// �X�e�[�W��ޏ��
	struct StageType
	{
		char	aFileName[0xff];	// �t�@�C���p�X
		char	aTexFile[0xff];		// �e�N�X�`���p�X
		char	aStageName[0xff];	// �X�e�[�W��

	};

	// �X�e�[�W���
	struct StageInfo
	{
		int nRow;		// �s��
		int nLine;		// ��
		int nRowMax;	// �s���̍ő�
		int nLineMax;	// �񐔂̍ő�
		int nStageIdx;	// ���݂̃X�e�[�W�ԍ�
		int nStageMax;	// �X�e�[�W�̍ő�l
	};

	// �F
	struct StageColor
	{
		Color Block;
		Color Trampoline;
		Color Spike;
		Color Lift;
		Color Meteor;
		Color FillBlock;
	};

	// *** �֐��錾 ***
	CStageEditor();
	~CStageEditor();

	/* �X�e�[�W�؂�ւ�	*/void SwapStage(int nStageIdx);

	// -- �擾 ---------------------------------------------
	/* �ő�l			*/int GetStageMax(void) { return m_Info.nStageMax; }
	/* ���݂̃X�e�[�W	*/int GetStageIdx(void) { return m_Info.nStageIdx; }
	/* �X�e�[�W���		*/StageType *GetType(void) { return m_StageType; }
	/* �ϊ�				*/bool ToData(int &val, CSVFILE *pFile, int nRow, int nLine);

	// -- �Ǎ� ---------------------------------------------
	/* �t�@�C���p�X	*/void FileLoad(void);
	/* �X�e�[�W�Ǎ�	*/void StageLoad(int stage);

private:

	// *** �񋓌^ ***
	enum Type
	{
		TYPE_BLOCK = 0,				// �u���b�N
		TYPE_TRAMPOLINE,			// �g�����|����
		TYPE_SPIKE,					// ��
		TYPE_LIFT,					// ���t�g
		TYPE_Meteor,				// 覐�
		TYPE_FILL_BLOCK_11 = 20,	// �u���b�N(���� ��) 1 * 1
		TYPE_FILL_BLOCK_22 = 21,	// �u���b�N(���� ��) 2 * 2
		TYPE_FILL_BLOCK_33 = 22,	// �u���b�N(���� ��) 3 * 3
		TYPE_FILL_BLOCK_44 = 23,	// �u���b�N(���� ��) 4 * 4
		TYPE_PLAYER_0 = 90,			// �v���C���[2
		TYPE_PLAYER_1,				// �v���C���[1
		TYPE_PARTS = 98,			// �p�[�c
		TYPE_GOAL,					// �S�[��
		TYPE_MAX
	};

	// *** �֐��錾 ***
	/* �X�e�[�W���� */void SetStage(int nType);

	// *** �ϐ��錾 ***
	static StageType *m_StageType;		// �X�e�[�W���
	static StageColor m_StageColor;		// �F���
	StageInfo m_Info;					// �X�e�[�W���
};
