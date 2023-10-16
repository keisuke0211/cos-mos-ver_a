//========================================
// 
// �M�~�b�N�̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h�̏��\����
class CTrampoline : public CList {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class TYPE {
		NONE = 0,	//����Ă��Ȃ�
		GETON,		//����Ă���
		LAND,		//���n����
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CTrampoline();
	virtual        ~CTrampoline();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);
	void   SetType(TYPE type) { m_type = type; }
	void	SetModelIdx(int idx) { ModelIdx = idx; }
	TYPE   GetType(void) { return m_type; }

protected:
	
private:
	//========== [[[ �ϐ��錾 ]]]
	TYPE m_type;
	int ModelIdx;
};
