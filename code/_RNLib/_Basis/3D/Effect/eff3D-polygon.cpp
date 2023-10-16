//========================================
// 
// �G�t�F�N�g3D(�|���S��)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ eff3D-polygon.h ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CEff3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CEff3D_Polygon::CEff3D_Polygon() {
	m_type          = POLYGON_TYPE::NONE;
	m_fMoveForce    = 0.0f;
	m_col           = INITCOLOR;
	m_fScale        = 1.0f;
	m_nPtn          = 0;
	m_nPtnSwapCount = 0;
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CEff3D_Polygon::~CEff3D_Polygon() {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Polygon::Init(void) {
	CEff3D::Init();
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Polygon::Uninit(void) {
	CEff3D::Uninit();
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Polygon::Update(void) {
	// �K�v�ȏ����擾(�v�Z)
	TypeInfo typeInfo   = RNLib::Eff3DMng()->GetTypeInfo_Polygon(m_type);
	int      nLifeCount = 0;
	float    fLifeRate  = 1.0f; {
		if (typeInfo.nLife >= 0) {
			nLifeCount = typeInfo.nLife - m_nLife;
			float fLifeRate = (float)nLifeCount / typeInfo.nLife;
		}
	}

	//----------------------------------------
	// �e�N�X�`���؂�ւ�
	//----------------------------------------
	if (typeInfo.nPtnSwapTime != DATANONE) {
		if (m_nPtnSwapCount % typeInfo.nPtnSwapTime == 0) {
			m_nPtnSwapCount = 0;
			m_nPtn = (m_nPtn + 1) % (typeInfo.nPtnX * typeInfo.nPtnY);
		}
	}

	//----------------------------------------
	// �ʒu�X�V
	//----------------------------------------
	// �ړ�������
	if (m_fMoveForce > 0.0f) {
		m_pos += Find_RotVec(m_rot) * m_fMoveForce * ((float)m_nLife / m_nLifeMax);
	}

	// �d�͂�������
	if (typeInfo.bGravity) {
		float fRate = (float)m_nLife / m_nLifeMax;
		m_pos.y -= (1.0f - fRate) * CEff3D::GRAVITY_FORCE;
	}

	//----------------------------------------
	// �g��k��
	//----------------------------------------
	float fScaleX = 1.0f;
	float fScaleY = 1.0f;
	{
		// �I���X�P�[�����O
		bool bScalingEnd = false;
		if (typeInfo.pScalingEnd != NULL) {
			int nEndLine = typeInfo.nLife - typeInfo.pScalingEnd->nTime;
			if (nLifeCount >= nEndLine) {
				bScalingEnd = true;
				ScaleChange(nLifeCount - nEndLine, typeInfo, *typeInfo.pScalingEnd, fScaleX, fScaleY);
			}
		}

		// �J�n�X�P�[�����O
		if (typeInfo.pScalingStart != NULL && !bScalingEnd) {
			if (nLifeCount < typeInfo.pScalingStart->nTime) {
				ScaleChange(nLifeCount, typeInfo, *typeInfo.pScalingStart, fScaleX, fScaleY);
			}
			else {
				fScaleX = typeInfo.pScalingStart->fScaleXEnd;
				fScaleY = typeInfo.pScalingStart->fScaleYEnd;
			}
		}
	}

	//----------------------------------------
	// �t�F�[�h
	//----------------------------------------
	float fAlpha = 1.0f;
	{
		// �t�F�[�h�A�E�g
		bool bOut = false;
		if (typeInfo.pFadeOut != NULL) {
			int nOutLine = typeInfo.nLife - typeInfo.pFadeOut->nTime;
			if (nLifeCount > nOutLine) {
				bOut = true;
				fAlpha -= Easing(typeInfo.pFadeOut->ease, nLifeCount - nOutLine, typeInfo.pFadeOut->nTime);
			}
		}
	}

	Color setCol = m_col;
	setCol.a *= fAlpha;

	RNLib::Polygon3D()->Put(ConvPosRotToMatrix(m_pos, m_rot))
		->SetCol(setCol)
		->SetSize_TexBaseScale(fScaleX * m_fScale, fScaleY * m_fScale)
		->SetTex(typeInfo.nTexIdx, m_nPtn, typeInfo.nPtnX, typeInfo.nPtnY)
		->SetZTest(typeInfo.bZTest)
		->SetLighting(typeInfo.bLighting)
		->SetBillboard(typeInfo.bBillboard);

	m_nPtnSwapCount++;

	CEff3D::Update();	// ���N���X�X�V����
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CEff3D_Polygon::ScaleChange(const int nCount, TypeInfo& typeInfo, Scaling& scaling, float& fScaleX, float& fScaleY) {
	float fRate    = Easing(typeInfo.pScalingStart->ease, nCount, typeInfo.pScalingStart->nTime);
	float fRateOpp = 1.0f - fRate;
	fScaleX = (typeInfo.pScalingStart->fScaleXStart * fRateOpp) + (typeInfo.pScalingStart->fScaleXEnd * fRate);
	fScaleY = (typeInfo.pScalingStart->fScaleYStart * fRateOpp) + (typeInfo.pScalingStart->fScaleYEnd * fRate);
}