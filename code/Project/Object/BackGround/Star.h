//========================================
// 
// 星の処理
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
class CStar : public CStageObject {
public:
	//========== [[[ 関数宣言 ]]]
	CStar();
	virtual        ~CStar();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);

	void	SetModelIdx(int idx)	 { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void	SetCol(Color col)		 { m_col = col; }
protected:

private:
	//========== [[[ 変数宣言 ]]]
	D3DXVECTOR3 m_posOld;		// 前の位置
	D3DXVECTOR3 m_move;			// 移動量
	Color m_col;				// 色
	int m_moveCounter;			// 移動量のカウンター
	int ModelIdx;
};
