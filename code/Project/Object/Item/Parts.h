//========================================
// 
// パーツの処理
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include"../stage-object.h"
//****************************************
// クラス定義
//****************************************
// パーツの情報構造体
class CParts : public CStageObject {
public:
	//========== [[[ 関数宣言 ]]]
	CParts();
	virtual        ~CParts();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

protected:

private:
	//========== [[[ 変数宣言 ]]]
	float m_fblink;		// 点滅
	int	  m_nblinlAnim;	// 点滅アニメーション

	int ModelIdx;
}; 
