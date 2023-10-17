//========================================
// 
// �G�t�F�N�g3D�}�l�[�W���[�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ effect3D_manager.h ]]]
//========================================
#ifndef _EFFECT3D_MANAGER_H_
#define _EFFECT3D_MANAGER_H_

#include "effect3D.h"
#include "eff3D-polygon.h"
#include "../../Mechanical/object-manager.h"

//****************************************
// �N���X��`
//****************************************
// �G�t�F�N�g3D�}�l�[�W���[�N���X
class CEff3DMng : public CObjectMgr {
public:
	//========== [[[ �֐��錾 ]]]
	CEff3DMng();
	~CEff3DMng();
	void Update(void);
	void Load(void);
	CEff3D_Polygon*          Create_Polygon     (CEff3D::POLYGON_TYPE  type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CEff3D::POWER power, Color col);
	CEff3D_Polygon::TypeInfo GetTypeInfo_Polygon(CEff3D::POLYGON_TYPE  type) { return m_aTypePolygon[(int)type]; }
	CEff3D_Fragment*         Create_Fragment    (CEff3D::FRAGMENT_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CEff3D::POWER power, Color col, int nTexIdx);

private:
	//========== [[[ �ϐ��錾 ]]]
	CEff3D_Polygon::TypeInfo m_aTypePolygon[(int)CEff3D_Polygon::POLYGON_TYPE::MAX];
};

#endif