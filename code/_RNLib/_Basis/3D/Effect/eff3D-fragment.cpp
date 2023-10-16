//========================================
// 
// �G�t�F�N�g3D(����)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ eff3D-polygon.h ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// �萔��`
//****************************************
int CEff3D_Fragment::m_aTypeModel[(int)FRAGMENT_TYPE::MAX];

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CEff3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CEff3D_Fragment::CEff3D_Fragment(void) {
	m_nModelIdx = DATANONE;
	m_move      = INITD3DXVECTOR3;
	m_spin      = INITD3DXVECTOR3;
	m_fScale    = 1.0f;			
	m_col       = INITCOLOR;		
	m_nTex      = DATANONE;		
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CEff3D_Fragment::~CEff3D_Fragment(void) {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Fragment::Init(void) {
	for (int nCntType = 0; nCntType < (int)FRAGMENT_TYPE::MAX; nCntType++) {
		switch ((FRAGMENT_TYPE)nCntType) {
		case FRAGMENT_TYPE::S:m_aTypeModel[nCntType] = RNLib::Visual()->GetModelIdx(CVisual::MODEL::CLOD_S); break;
		case FRAGMENT_TYPE::M:m_aTypeModel[nCntType] = RNLib::Visual()->GetModelIdx(CVisual::MODEL::CLOD_M); break;
		default:
			m_aTypeModel[nCntType] = DATANONE;
			break;
		}
	}
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Fragment::Uninit(void) {
	CEff3D::Uninit();
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Fragment::Update(void) {
	float fRate = (float)m_nLife / m_nLifeMax;

	m_pos += m_move * fRate;
	m_rot += m_spin * fRate;
	m_pos.y -= (1.0f - fRate) * CEff3D::GRAVITY_FORCE;

	D3DXMATRIX mtx = ConvPosRotToMatrix(m_pos, m_rot);
	SetMatrixScale(&mtx, m_fScale);

	RNLib::Model()->Put(mtx, m_nModelIdx)
		->SetCol(m_col)
		->SetTex(m_nTex)
		->SetLighting(true)
		->SetOutLine(true);

	CEff3D::Update();
}