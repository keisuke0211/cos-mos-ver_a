//========================================
// 
// �G�t�F�N�g3D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ effect3D.h ]]]
//========================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

#include "../../Mechanical/object.h"

//****************************************
// �N���X��`
//****************************************
// �G�t�F�N�g3D�N���X
class CEff3D : public CObject {
public:
	//========== [[[ �萔��` ]]]
	static const float GRAVITY_FORCE;

	//========== [[[ �񋓌^��` ]]]
	enum class POWER {
		NONE,
		LOW,
		MID,
		HIGH,
		MAX,
	};

	// ���
	enum class TYPE {
		NONE,
		POLYGON,
		FRAGMENT,
		MAX,
	};
	enum class POLYGON_TYPE {
		NONE,
		// UI
		CALLOUT_TAKEAIM,
		CALLOUT_SILENCE,
		// ��Ԉُ�
		SLEEP,
		// �O�������
		RING,
		LIGHT_M,
		SMOKE_M,
		SMOKE_L,
		LIQUID_S,
		LIQUID_M,
		FRAME_M,
		LAVABALL_XS,
		SPARK_ORANGE,
		EXPLOSION_DESTROY_M,
		MAX,
	};
	enum class FRAGMENT_TYPE {
		NONE,
		S,
		M,
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CEff3D();
	virtual ~CEff3D();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	// �ݒ�擾
	void SetPos (D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot (D3DXVECTOR3 rot) { m_rot = rot; }
	void SetLife(int nLife)       { m_nLife = m_nLifeMax = nLife; }

protected:
	//========== [[[ �ϐ��錾 ]]]
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int         m_nLife;
	int         m_nLifeMax;
};

#endif