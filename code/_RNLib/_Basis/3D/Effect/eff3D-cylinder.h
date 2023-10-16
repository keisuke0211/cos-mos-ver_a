//========================================
// 
// �G�t�F�N�g3D(�|���S��)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ eff3D-polygon.h ]]]
//========================================
//#ifndef _EFF3D_POLYGON_H_
//#define _EFF3D_POLYGON_H_
//
//#include "effect3D.h"
//#include "../../../RNmain.h"
//
////****************************************
//// �N���X��`
////****************************************
//// �G�t�F�N�g3D(�|���S��)�N���X
//class CEff3D_Polygon : public CEff3D {
//public:
//	//========== [[[ �\���̐錾 ]]]
//	// �g��
//	typedef struct Scaling_ {
//		int   nTime = 0;
//		float fScaleXStart = 0.0f;
//		float fScaleYStart = 0.0f;
//		float fScaleXEnd = 0.0f;
//		float fScaleYEnd = 0.0f;
//		EASE  ease = EASE_LINEAR;
//	}Scaling;
//	// �t�F�[�h�A�E�g
//	typedef struct FadeOut_ {
//		int   nTime = 0;
//		EASE  ease = EASE_LINEAR;
//	}FadeOut;
//	// ��ޖ��̏��
//	typedef struct TypeInfo_ {
//		int      nLife = 0;
//		int      nTexIdx = DATANONE;
//		int      nPtnX = 1;
//		int      nPtnY = 1;
//		int      nPtnSwapTime = DATANONE;
//		bool     bZTest = true;
//		bool     bLighting = false;
//		bool     bBillboard = false;
//		Scaling* pScalingStart = NULL;
//		Scaling* pScalingEnd = NULL;
//		FadeOut* pFadeOut = NULL;
//		bool     bGravity = false;
//	}TypeInfo;
//
//	//========== [[[ �֐��錾 ]]]
//	CEff3D_Polygon();
//	~CEff3D_Polygon();
//	void Init(void);
//	void Uninit(void);
//	void Update(void);
//
//private:
//	//========== [[[ �ϐ��錾 ]]]
//	int   m_texIdx;
//	Color m_col;
//	float m_radius;
//	float m_addRadius;
//};
//
//#endif