//========================================
// 
// ���[�h:�^�C�g���̏���
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h(�^�C�g��)�N���X
class CMode_Title :public CMode {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE,
	};

	//========== [[[ �֐��錾 ]]]
	CMode_Title();
	~CMode_Title();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

private:

};