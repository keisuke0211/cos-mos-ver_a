//========================================
// 
// �e3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ dhadow3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//========================================
// ����������
//========================================
void CShadow3D::Init(void) {
	m_nTexIdx = RNLib::Texture()->Load("data\\Texture\\Effect\\shadow_00.png");
}

//========================================
// �ݒ菈��
//========================================
void CShadow3D::Set(D3DXVECTOR3 pos) {
	/*return;
	D3DXVECTOR3 setRot = D3DXVECTOR3(D3DX_PI*0.5f, 0.0f, 0.0f);
	pos.y = RNLib::ACTRPG3D()->Stage()->GetGroundModelHeight(pos, &setRot);
	pos += Find_RotVec(setRot);

	RNLib::Polygon3D()->Regist(
		16.0f, 
		16.0f,
		ConvPosRotToMatrix(pos, setRot),
		INITCOLOR,
		m_nTexIdx
		);*/
}