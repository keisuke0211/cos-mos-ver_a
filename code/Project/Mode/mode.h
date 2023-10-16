//========================================
// 
// ���[�h�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h�̏��\����
class CMode {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class TYPE{
		NONE = -1,
		GAME,
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	               CMode        ();
	virtual        ~CMode       ();
	virtual void   Init         (void);
	virtual void   Uninit       (void);
	virtual void   Update       (void);
	virtual void   ProcessState (const PROCESS process) = 0;
	        void   SetType      (TYPE type) { m_type = type; }
	        TYPE   GetType      (void)      { return m_type; }
	static  CMode* Create       (TYPE type);

protected:
	//========== [[[ �֐��錾 ]]]
	void SetState (const int nState);

	//========== [[[ �ϐ��錾 ]]]
	int m_state;
	int m_stateCtr;

private:
	//========== [[[ �ϐ��錾 ]]]
	TYPE m_type;
};