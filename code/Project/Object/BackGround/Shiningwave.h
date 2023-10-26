//========================================
// 
// �g�ł��̏���
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include"../stage-object.h"
//****************************************
// �N���X��`
//****************************************
// �g�ł��̏��\����
class CShiningWave : public CStageObject {
public:
	//========== [[[ �֐��錾 ]]]
	CShiningWave();
	virtual        ~CShiningWave();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void	SetCol(Color col) { m_col = col; }
protected:

private:
	//========== [[[ �ϐ��錾 ]]]
	D3DXMATRIX mtx;				// �}�g���b�N�X
	D3DXVECTOR3 m_posOld;		// �O�̈ʒu
	D3DXVECTOR3 m_move;			// �ړ���
	Color m_col;				// �F
	int m_moveCounter;			// �ړ��ʂ̃J�E���^�[
	int ModelIdx;
};