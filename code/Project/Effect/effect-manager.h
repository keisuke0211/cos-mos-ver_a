//========================================
// 
// エフェクトマネージャーの処理
// Author:RYUKI FUJIWARA
//
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"
#include "effect.h"

//****************************************
// クラス
//****************************************
class CEffectMgr : public CObjectMgr {
public:
	//========== [[[ 関数宣言 ]]]
	CEffectMgr();
	virtual~CEffectMgr();
	virtual void Update(void);

	CEffect *EffectCreate(int nTex, D3DXVECTOR3 pos );

private:

	// *** 構造体 ***

	// *** 静的変数 ***

	// *** 変数 ***
};
