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
		TITLE_SELECT,		// �X�e�[�W�I��
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

	// *** ���\���� ***

	// �X�e�[�W��ޏ��
	struct StageType
	{
		int nTex;				// �摜
		char Text[TXT_MAX];		// �X�e�[�W��
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
	/* ���j���[����			*/void MenuCreate(void);
	/* ���j���[				*/void Menu(void);
	/* �X�e�[�W�I�𐶐�		*/void SelectCreate(void);
	/* �X�e�[�W�I��			*/void StageSelect(void);
	/* �e�L�X�g�폜			*/void TextClear(TITLE aTitle);

	// *** �ϐ� ***
	TITLE Title;						// ���݂̃��[�h
	int m_TexIdx;
	int m_nSelect;
	CFontText *m_Menu[MENU_MAX];		// ���j���[�e�L�X�g
	CWords *m_Words[4];					// �^�C�g��
	StageType *m_StageType;
};