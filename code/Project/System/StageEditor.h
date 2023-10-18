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
	};

	// �X�e�[�W���
	struct StageInfo
	{
		int nRow;		// �s��
		int nLine;		// ��
		int nRowMax;	// �s���̍ő�
		int nLineMax;	// �񐔂̍ő�
	};

	// *** �֐��錾 ***
	CStageEditor();
	~CStageEditor();

	// -- �擾 ---------------------------------------------
	/* �ϊ� */bool ToData(char* &val, CSVFILE *pFile, int nRow, int nLine);
	/* �ϊ� */bool ToData(int &val, CSVFILE *pFile, int nRow, int nLine);

	// -- �Ǎ� ---------------------------------------------
	/* �t�@�C���p�X	*/void FileLoad(void);
	/* �X�e�[�W�Ǎ�	*/void StageLoad(int stage);

private:

	// *** �񋓌^ ***
	enum Type
	{
		TYPE_BLOCK = 0,		// ��
		TYPE_TRAMPOLINE,	// �g�����|����
		TYPE_SPIKE,			// ��
		TYPE_LIFT,			// ���t�g
		TYPE_Meteor,		// 覐�
		TYPE_PLAYER_0 = 90,	// �v���C���[2
		TYPE_PLAYER_1,		// �v���C���[1
		TYPE_PARTS = 98,	// �p�[�c
		TYPE_GOAL,			// �S�[��
		TYPE_MAX
	};

	// *** �֐��錾 ***
	/* �X�e�[�W���� */void SetStage(int nType);

	// *** �ϐ��錾 ***
	static StageType *m_StageType;	// �X�e�[�W���
	static int m_StageMax;			// �X�e�[�W�̍ő�l
	StageInfo m_Info;				// �X�e�[�W���
};
