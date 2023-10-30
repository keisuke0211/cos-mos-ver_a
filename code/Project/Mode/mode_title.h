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
class CFontText;
class CWords;

//****************************************
// �N���X��`
//****************************************
// ���[�h(�^�C�g��)�N���X
class CMode_Title :public CMode {
public:
	// *** ��` ***
	static const int WORDS_MAX = 7;		// �����̍ő吔

	// *** �񋓌^ ***
	enum class STATE {
		NONE,
	};

	// �^�C�g�����[�h
	enum TITLE
	{
		TITLE_PLANET = 0,	// �f��
		TITLE_TITLE,		// �^�C�g��
		TITLE_OUTSET,		// ���o�I��
		TITLE_MENU_ANIME,	// ���j���[
		TITLE_MENU,			// ���j���[����
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
	// *** �񋓌^ ***

	// �e�N�X�`��
	enum TEX
	{
		TEX_BG = 0,		// �w�i
		TEX_PLANET00,	// �f��
		TEX_PLANET01,	// �f��
		TEX_ICON,		// �A�C�R��
		TEX_MAX
	};

	// *** �֐� ***
	/* �f���A�j�����[�V����		*/void PlanetAnime(void);
	/* �^�C�g���A�j���[�V����	*/void TitleAnime(void);
	/* ���j���[�A�j���[�V����	*/void MenuAnime(void);
	/* ���j���[����				*/void MenuCreate(void);
	/* ���j���[					*/void Menu(void);
	/* �X�e�[�W�I�𐶐�			*/void SelectCreate(void);
	/* �X�e�[�W�I��				*/void StageSelect(void);
	/* �e�L�X�g�폜				*/void TextClear(TITLE aTitle);

	// *** �ϐ� ***
	TITLE Title;
	D3DXVECTOR3 m_BgPos[TEX_MAX];
	D3DXVECTOR3 m_MenuPos[MENU_MAX];
	float m_PlanetAngle;
	int m_TexIdx[TEX_MAX];
	int m_nSelect;
	bool m_bMove[WORDS_MAX];
	bool m_bMenuAnime;
	CWords *m_Words[WORDS_MAX];
	CWords *m_WordsShadow[WORDS_MAX];
	CFontText *m_Menu[MENU_MAX];
	StageType *m_StageType;
};