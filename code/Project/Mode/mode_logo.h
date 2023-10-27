//========================================
// 
// ���[�h:���S�̏���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h(���S)�N���X
class CMode_Logo :public CMode {
public:

	// ***** ��` *****
	static const int WAIT_TIME = 60;	// �ҋ@����
	static const int TIME = 60;			// ���ڎ���

	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE,
		OPEN,
		OPEN_WAIT,
		CLOSE_WAIT,
		CLOSE,
	};

	//========== [[[ �֐��錾 ]]]
	CMode_Logo();
	~CMode_Logo();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

private:
	static int m_TexLogo;
	int m_nStateCtr;
	STATE m_state;

};