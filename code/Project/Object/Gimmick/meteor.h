//========================================
// 
// 隕石の処理
// Author:KOMURO HIROMU
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"

//****************************************
// クラス定義
//****************************************
// メテオの情報構造体
class CMeteor : public CList {
public:
	//========== [[[ 関数宣言 ]]]
	CMeteor();
	virtual        ~CMeteor();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);
	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void	SetMove(D3DXVECTOR3 move) { m_move = move; }

protected:

private:
	//========== [[[ 変数宣言 ]]]
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_rot;	// 向き
	D3DXVECTOR3 m_move;	// 移動量
	int ModelIdx;
};
