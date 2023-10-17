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

	static const char* STAGE_INFO_FILE;		// �X�e�[�W���̃t�@�C���p�X

public:

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
	/* �X�e�[�W�Ǎ�	*/void StageLoad(const char *pFileName);

private:
	// *** �ϐ��錾 ***
	static StageType *m_StageType;
};
