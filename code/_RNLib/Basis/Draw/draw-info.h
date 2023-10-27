//========================================
// 
// ���p�`����N���X�̒�`
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//----------------------------------------
// �N���X��`
//----------------------------------------
// ���p�`����N���X
class CDrawInfoBase {
public:
	//===== [[[ �񋓌^��` ]]
	// ���
	enum class TYPE {
		NONE,
		POLYGON2D,
		POLYGON3D,
		MODEL,
	};

	//===== [[[ �֐��錾 ]]]
	CDrawInfoBase();
	virtual ~CDrawInfoBase();
	virtual void Draw(LPDIRECT3DDEVICE9& device, const D3DXMATRIX& viewMtx) = 0;

	//===== [[[ �ϐ���` ]]]
	TYPE  m_type;
	short m_priority;
};
