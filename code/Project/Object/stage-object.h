//========================================
// 
// �X�e�[�W�I�u�W�F�N�g�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
class CStageObject : public CObject {
public:
	//========== [[[ �萔��` ]]]
	static const float SIZE_OF_1_SQUARE;

	//========== [[[ �񋓌^��` ]]]
	enum class TYPE {
		NONE       = -1,
		BLOCK      = 0,
		TRAMPOLINE = 1,
		SPIKE	   = 2,
		MOVE_BLOCK = 3,
		METEOR	   = 4,
		PARTS      = 5,
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CStageObject();
	virtual ~CStageObject();
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	TYPE GetType(void) { return m_type; }
	void SetPos(const D3DXVECTOR3& pos) { m_pos = m_posOld = pos; }
	D3DXVECTOR3& GetPos(void) { return m_pos; }
	void SetRot(const D3DXVECTOR3& rot) { m_rot = rot; }
	D3DXVECTOR3& GetRot(void) { return m_rot; }
	float& GetWidth(void) { return m_width; }
	float& GetHeight(void) { return m_height; }

protected:
	//========== [[[ �ϐ��錾 ]]]
	TYPE        m_type;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_rot;
	float       m_width;
	float       m_height;
};