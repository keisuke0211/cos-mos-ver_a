//========================================
// 
// �p�[�c�̏���
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include"../stage-object.h"
//****************************************
// �N���X��`
//****************************************
// �p�[�c�̏��\����
class CParts : public CStageObject {
public:
	//========== [[[ �֐��錾 ]]]
	CParts();
	virtual        ~CParts();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

protected:

private:
	//========== [[[ �ϐ��錾 ]]]
	float m_fblink;		// �_��
	int	  m_nblinlAnim;	// �_�ŃA�j���[�V����

	int ModelIdx;
}; 
