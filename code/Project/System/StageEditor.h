//========================================
// 
// �X�e�[�W�G�f�B�b�g�̓ǂݍ���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

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

	// *** �֐��錾 ***
	CStageEditor();
	~CStageEditor();

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
		TYPE_PARTS = 98,
		TYPE_GOAL,
		TYPE_MAX
	};

	// *** �֐��錾 ***
	///* �X�e�[�W���� */void SetStage();

	// *** �ϐ��錾 ***
	static StageType *m_StageType;
	static int m_StageMax;
};
