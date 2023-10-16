//========================================
// 
// エフェクト3D(ポリゴン)のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ eff3D-polygon.h ]]]
//========================================
#ifndef _EFF3D_POLYGON_H_
#define _EFF3D_POLYGON_H_

#include "effect3D.h"
#include "../../../RNmain.h"

//****************************************
// クラス定義
//****************************************
// エフェクト3D(ポリゴン)クラス
class CEff3D_Polygon : public CEff3D {
public:
	//========== [[[ 構造体宣言 ]]]
	// 拡大
	typedef struct Scaling_ {
		int   nTime        = 0;
		float fScaleXStart = 0.0f;
		float fScaleYStart = 0.0f;
		float fScaleXEnd   = 0.0f;
		float fScaleYEnd   = 0.0f;
		EASE  ease         = EASE_LINEAR;
	}Scaling;
	// フェードアウト
	typedef struct FadeOut_ {
		int   nTime  = 0;
		EASE  ease   = EASE_LINEAR;
	}FadeOut;
	// 種類毎の情報
	typedef struct TypeInfo_ {
		int      nLife         = 0;
		int      nTexIdx       = DATANONE;
		int      nPtnX         = 1;
		int      nPtnY         = 1;
		int      nPtnSwapTime  = DATANONE;
		bool     bZTest        = true;
		bool     bLighting     = false;
		bool     bBillboard    = false;
		Scaling* pScalingStart = NULL;
		Scaling* pScalingEnd   = NULL;
		FadeOut* pFadeOut      = NULL;
		bool     bGravity      = false;
	}TypeInfo;

	//========== [[[ 関数宣言 ]]]
	CEff3D_Polygon();
	~CEff3D_Polygon();
	void Init(void);
	void Uninit(void);
	void Update(void);
	// 設定
	CEff3D_Polygon* SetMoveForce(float fMoveForce) {
		m_fMoveForce = fMoveForce;
		return this;
	}
	CEff3D_Polygon* SetCol(Color col) {
		m_col = col; 
		return this;
	}
	CEff3D_Polygon* SetScale(float fScale) {
		m_fScale = fScale;
		return this;
	}
	CEff3D_Polygon* SetType(POLYGON_TYPE type) {
		m_type = type; 
		return this;
	}

private:
	//========== [[[ 関数宣言 ]]]
	void ScaleChange(const int nCount, TypeInfo& typeInfo, Scaling& scaling, float& fScaleX, float& fScaleY);

	//========== [[[ 変数宣言 ]]]
	POLYGON_TYPE m_type;
	float        m_fMoveForce;
	Color        m_col;
	float        m_fScale;
	int          m_nPtn;
	int          m_nPtnSwapCount;
};

#endif