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
	void   SetScale(D3DXVECTOR3 scale) { m_scale = scale; }		//�g�k�ݒ�

	STATE  GetState(void) { return m_state; }					//��ގ擾

	

protected:
	
private:

	//========== [[[ �֐��錾 ]]]
	void   Collision(void);	//�����蔻�菈��

	//========== [[[ �ϐ��錾 ]]]
	STATE m_state;			//���
	int m_modelIdx[2];		//���f���ԍ�
	D3DXVECTOR3 m_scale;	//�傫��
	bool		m_bLand;	//���n�����H
	float		m_fJamp;	//����
	int			m_nCnt;		//�J�E���g
};
