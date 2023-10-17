//========================================
// 
// �g�����|�����̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#pragma once

#include "../stage-object.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h�̏��\����
class CTrampoline : public CStageObject {
public:

	//========== [[[ �񋓌^��` ]]]
	enum class STATE {
		NONE = 0,		//����Ă��Ȃ�
		UP_LAND,		//��ɒ��n
		DOWN_LAND,		//���ɒ��n
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CTrampoline();
	virtual        ~CTrampoline();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);
	void   SetState(STATE state) { m_state = state; }			//��ސݒ�
	STATE   GetState(void) { return m_state; }					//��ގ擾
	void   SetScale(D3DXVECTOR3 scale) { m_scale = scale; }	//�g�k�ݒ�

protected:
	
private:
	//========== [[[ �ϐ��錾 ]]]
	STATE m_state;			//���
	int m_modelIdx[3];		//���f���ԍ�
	D3DXVECTOR3 m_scale;	//�傫��
	bool		m_bLand;	//���n�����H
};
