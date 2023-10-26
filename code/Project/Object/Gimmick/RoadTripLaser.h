//========================================
// 
// �������郌�[�U�[�̏���
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
class CRoadTripLaser : public CStageObject {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class ROT {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CRoadTripLaser();
	virtual        ~CRoadTripLaser();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void	SetCol(Color col) { m_col = col; }
	void	SetMove(const D3DXVECTOR3 move) { m_move = move; }
	void	SetRefdef(const float refdef) { m_frefdef = refdef; }
protected:

private:
	//========== [[[ �ϐ��錾 ]]]
	D3DXMATRIX mtx;				// �}�g���b�N�X
	D3DXVECTOR3 m_posOld;		// �O�̈ʒu
	D3DXVECTOR3 m_refPos;		// �ʒu(�ߋ�)
	D3DXVECTOR3 m_move;			// �ړ���
	Color m_col;				// �F
	float m_frefdef;			// ���˂��鋗��
	float m_fGroundDis;			// �n�ʂ܂ł̋���
	int ModelIdx;
};
