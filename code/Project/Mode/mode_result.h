//========================================
// 
// ���[�h:���U���g�̏���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h(���U���g)�N���X
class CMode_Result :public CMode {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE,
	};

	//========== [[[ �֐��錾 ]]]
	CMode_Result();
	~CMode_Result();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

private:

};