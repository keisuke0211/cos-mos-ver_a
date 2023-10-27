//========================================
// 
// �f���̏���
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include"../stage-object.h"
//****************************************
// �N���X��`
//****************************************
// �f���̏��\����
class CPlanet : public CStageObject {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class STAR_TYPE {
		SATURN,
		SATURNx2,
		SATURNx4,
		SATURNx8,
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CPlanet();
	virtual        ~CPlanet();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx)	 { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void	SetCol(Color col)		 { m_col = col; }
	void    SetType(STAR_TYPE type) { m_Star_type = type; }
protected:

private:
	//========== [[[ �ϐ��錾 ]]]
	D3DXVECTOR3 m_posOld;		// �O�̈ʒu
	D3DXVECTOR3 m_posInit;		// �����̈ʒu
	D3DXVECTOR3 m_move;			// �ړ���
	Color m_col;				// �F
	STAR_TYPE m_Star_type;		// ���
	int m_moveCounter;			// �ړ��ʂ̃J�E���^�[
	int ModelIdx;
};
