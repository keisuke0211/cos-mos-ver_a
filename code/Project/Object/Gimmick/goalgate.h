//========================================
// 
// �S�[���Q�[�g�̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#pragma once

#include "../stage-object.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h�̏��\����
class CGoalGate : public CStageObject {
public:

	//========== [[[ �֐��錾 ]]]
	CGoalGate();
	virtual        ~CGoalGate();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	//�ݒ�
	void   SetGoal(bool bGoal) { m_bGoal = bGoal; }				//�S�[��

	//�擾
	bool   GetGoal(void) { return m_bGoal; }					//�S�[��

protected:

private:

	//========== [[[ �ϐ��錾 ]]]
	int m_TexIdx[2];		//���f���ԍ�
	bool m_bGoal;			//�S�[��������
};
