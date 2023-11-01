//========================================
// 
// ���[�h:�Q�[���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �O���錾
//****************************************
class CPlayer;
class CFontText;

//****************************************
// �N���X��`
//****************************************
// ���[�h(�Q�[��)�N���X
class CMode_Game :public CMode {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE,
		PAUSE,
	};

	// ���j���[
	enum MENU
	{
		MENU_RESUME = 0,// ������
		MENU_RESET,		// ��蒼��
		MENU_TITLE,		// �^�C�g���ɖ߂�
		MENU_MAX
	};

	//========== [[[ �֐��錾 ]]]
	      CMode_Game    ();
	      ~CMode_Game   ();
	void  Init          (void);
	void  Uninit        (void);
	void  Update        (void);
	void  ProcessState  (const PROCESS process);

	void BackGroundPut  (Color mincol, Color addcol);
	static CPlayer* GetPlayer(void);

	// -- �ݒ� -------------------------------------------------------------------
	static void SetStage(int Idx) { m_nStageIdx = Idx; }
	static void SetBgColor(Color color, int Idx) { m_BgColor[Idx] = color; }

	// -- �擾 -------------------------------------------------------------------
	static int GetStage(void) { return m_nStageIdx; }

private:

	//========== [[[ �֐��錾 ]]]
	void PauseCreate(void);
	void PauseSelect(void);
	void PauseMenu(void);

	//========== [[[ �ϐ��錾 ]]]
	static CPlayer *s_pPlayer;
	static int m_nStageIdx;
	int m_nSelect;
	CFontText *m_Menu[MENU_MAX];

	static Color m_BgColor[2];
};