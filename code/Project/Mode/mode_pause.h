//========================================
// 
// ���[�h:�|�[�Y�̏���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h(���U���g)�N���X
class CMode_Pause :public CMode {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE,
	};

	//========== [[[ �֐��錾 ]]]
	CMode_Pause();
	~CMode_Pause();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

	// -- �ݒ� --------------------------------------------
	/* �|�[�Y */static void SetPause(bool bPause) { m_bPause = bPause; }

	// -- �擾 --------------------------------------------
	/* �|�[�Y	*/static bool IsPause(void) { return m_bPause; }

private:
	static bool m_bPause;

};