//========================================
// 
// ���[�h:�^�C�g���̏���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �O���錾
//****************************************
class CWords;
class CFontText;

//****************************************
// �N���X��`
//****************************************
// ���[�h(�^�C�g��)�N���X
class CMode_Title :public CMode {
public:
	// *** �񋓌^ ***
	enum class STATE {
		NONE,
	};

	// �^�C�g�����[�h
	enum TITLE
	{
		TITLE_OUTSET = 0,	// �^�C�g��
		TITLE_MENU,			// ���j���[
		TITLE_NEXT,			// ���̉�ʂɈړ� 
		TITLE_MAX
	};

	// ���j���[
	enum MENU
	{
		MENU_GAME = 0,	// �Q�[��
		MENU_SERRING,	// �ݒ�
		MENU_END,		// �I��
		MENU_MAX
	};

	// *** �֐� ***
	CMode_Title();
	~CMode_Title();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

private:
	// *** �֐� ***
	/* ���j���[���� */void MenuCreate(void);
	/* ���j���[		*/void Menu(void);
	/* �e�L�X�g�폜 */void TextClear(TITLE aTitle);

	// *** �ϐ� ***
	TITLE Title;						// ���݂̃��[�h
	int m_TexIdx;
	int m_nSelectMenu;
	CFontText *m_Menu[MENU_MAX];		// ���j���[�e�L�X�g
	CWords *m_Words[4];					// �^�C�g��
};