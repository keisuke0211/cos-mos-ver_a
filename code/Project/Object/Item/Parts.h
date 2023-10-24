//========================================
// 
// �p�[�c�̏���
// Author:KOMURO HIROMU�@Hirasawa Shion
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

	//---------------------------
	//�`�� ON/OFF ��Ԃ��擾
	//---------------------------
	bool	GetDisp(void) { return m_bDisp; }

	//---------------------------
	//�擾������`�� ON/OFF ��؂�ւ�
	//---------------------------
	void	DispSwitch(bool bGet) { m_bDisp = bGet; }

private:
	//========== [[[ �ϐ��錾 ]]]

	int ModelIdx;
	bool m_bDisp;	//�擾�������ǂ���
}; 
