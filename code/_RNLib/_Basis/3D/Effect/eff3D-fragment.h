//========================================
// 
// エフェクト3D(欠片)のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ eff3D-polygon.h ]]]
//========================================
#ifndef _EFF3D_FRAGMENT_H_
#define _EFF3D_FRAGMENT_H_

#include "effect3D.h"
#include "../../../RNmain.h"

//****************************************
// クラス定義
//****************************************
// エフェクト3D(欠片)クラス
class CEff3D_Fragment : public CEff3D {
public:
	//========== [[[ 関数宣言 ]]]
	CEff3D_Fragment();
	~CEff3D_Fragment();
	void Init(void);
	void Uninit(void);
	void Update(void);
	// 設定取得
	void SetModelIdx(int nModelIdx)     { if (this != NULL)m_nModelIdx = nModelIdx; }
	void SetMove    (D3DXVECTOR3 move)  { m_move = move; }
	void SetSpin    (D3DXVECTOR3 spin)  { m_spin = spin; }
	void SetScale   (float fScale)      { m_fScale = fScale; }
	void SetTex     (int nTex)          { m_nTex = nTex; }
	void SetCol     (Color col)         { m_col = col; }
	static int GetTypeModel(FRAGMENT_TYPE type) { return m_aTypeModel[(int)type]; }

private:
	//========== [[[ 変数宣言 ]]]
	static int    m_aTypeModel[(int)FRAGMENT_TYPE::MAX];
	int           m_nModelIdx;
	D3DXVECTOR3   m_move;
	D3DXVECTOR3   m_spin;
	float         m_fScale;
	int           m_nTex;
	Color         m_col;
};

#endif