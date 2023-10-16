//========================================
// 
// エフェクト3D(ポリゴン)のヘッダファイル
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
//// クラス定義
////****************************************
//// エフェクト3D(ポリゴン)クラス
//class CEff3D_Polygon : public CEff3D {
//public:
//	//========== [[[ 構造体宣言 ]]]
//	// 拡大
//	typedef struct Scaling_ {
//		int   nTime = 0;
//		float fScaleXStart = 0.0f;
//		float fScaleYStart = 0.0f;
//		float fScaleXEnd = 0.0f;
//		float fScaleYEnd = 0.0f;
//		EASE  ease = EASE_LINEAR;
//	}Scaling;
//	// フェードアウト
//	typedef struct FadeOut_ {
//		int   nTime = 0;
//		EASE  ease = EASE_LINEAR;
//	}FadeOut;
//	// 種類毎の情報
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
//	//========== [[[ 関数宣言 ]]]
//	CEff3D_Polygon();
//	~CEff3D_Polygon();
//	void Init(void);
//	void Uninit(void);
//	void Update(void);
//
//private:
//	//========== [[[ 変数宣言 ]]]
//	int   m_texIdx;
//	Color m_col;
//	float m_radius;
//	float m_addRadius;
//};
//
//#endif