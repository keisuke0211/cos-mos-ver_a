//========================================
// 
// 覐΂̏���
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���e�I�̏��\����
class CMeteor : public CList {
public:
	//========== [[[ �֐��錾 ]]]
	CMeteor();
	virtual        ~CMeteor();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);
	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
protected:

private:
	//========== [[[ �ϐ��錾 ]]]
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	int ModelIdx;
};
