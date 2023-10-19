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
	Color m_col;				// �F
	D3DXVECTOR3 m_move;			// �ړ���
	STAR_TYPE m_Star_type;		// ���
	int ModelIdx;
};
