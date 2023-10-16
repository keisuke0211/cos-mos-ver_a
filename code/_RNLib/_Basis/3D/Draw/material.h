//========================================
// 
// マテリアル関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ material.h ]]]
//========================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

//****************************************
// プロトタイプ宣言
//****************************************
/* マテリアルの設定 */void SetMaterial(LPDIRECT3DDEVICE9 pDevice, D3DMATERIAL9 *pMat, Color col, bool bLighting = false);

#endif