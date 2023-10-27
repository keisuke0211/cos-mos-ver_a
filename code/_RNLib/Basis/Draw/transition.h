//========================================
// 
// �J�ڂ̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ transition.h ]]]
//========================================
#ifndef _TRANSITION_H_
#define _TRANSITION_H_

//****************************************
// �N���X��`
//****************************************
// �J�ڃN���X
class CTransition {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE, OPEN, OPEN_WAIT, CLOSE, WAIT_SET_MODE,
	};
	enum class TYPE {
		NONE,
		FADE,
	};

	//========== [[[ �֐��錾 ]]]
	CTransition();
	~CTransition();
	void Update(void);
	void Set(STATE state, TYPE type);
	STATE GetState(void) { return m_state; }

private:
	//========== [[[ �ϐ��錾 ]]]
	STATE m_state;
	int   m_nStateCtr;
	TYPE  m_type;
};

#endif