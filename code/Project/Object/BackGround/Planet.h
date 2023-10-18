//========================================
// 
// 惑星の処理
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include"../stage-object.h"
//****************************************
// クラス定義
//****************************************
// 惑星の情報構造体
class CPlanet : public CStageObject {
public:
	//========== [[[ 関数宣言 ]]]
	CPlanet();
	virtual        ~CPlanet();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

protected:

private:
	//========== [[[ 変数宣言 ]]]
	D3DXVECTOR3 m_move;	// 移動量

	int ModelIdx;
};
