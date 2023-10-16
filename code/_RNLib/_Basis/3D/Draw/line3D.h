//========================================
// 
// ライン3D関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ line3D.h ]]]
//========================================
#ifndef _LINE3D_H_
#define _LINE3D_H_

#include "../../Other/color.h"

//****************************************
// クラス定義
//****************************************
// ライン3Dクラス
class CLine3D {
public:
	//========= [[[ 関数宣言 ]]]
	CLine3D();
	~CLine3D();
	void Init(void);
	void Uninit(void);
	void Draw(bool bZTest);
	void Set         (D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, Color col = INITCOLOR, bool bZTest = true);
	void Set_Circle  (D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col = INITCOLOR, bool bZTest = true);
	void Set_Sphere  (D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col = INITCOLOR, bool bZTest = true);
	void Set_Cube    (D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, Color col = INITCOLOR, bool bZTest = true);
	void Set_Cylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, Color col = INITCOLOR, bool bZTest = true);
	void SetReset(void);

private:
	//========= [[[ 構造体定義 ]]]
	// 描画設定情報構造体
	typedef struct DrawSet_ {
		bool bZTest = false;	// Zテストフラグ
	}DrawSet;

	//========= [[[ 変数宣言 ]]]
	DrawSet* m_pDrawSet;	// 描画設定情報
	int      m_nDrawSetNum;	// 描画設定数
	LPDIRECT3DVERTEXBUFFER9* m_ppVtxBuff;	// 頂点バッファへのダブルポインタ
};

#endif