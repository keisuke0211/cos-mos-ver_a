//========================================
// 
// マトリックス関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ matrix.h ]]]
//========================================
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "../../RNmain.h"

//****************************************
// マクロ定義
//****************************************
// D3DXMATRIX型の初期値
#define INITD3DXMATRIX D3DXMATRIX(1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f)

//****************************************
// プロトタイプ宣言
//****************************************
// 位置と向きをマトリックスに変換して返す
D3DXMATRIX ConvPosRotToMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// マトリックスを掛け合わせる
D3DXMATRIX MultiplyMatrix(D3DXMATRIX mtxParent, D3DXMATRIX mtxChild);
// マトリックスの位置成分を分解して返す
D3DXVECTOR3 ConvMatrixToPos(D3DXMATRIX mtx);
// マトリックスの向き成分を分解して返す
D3DXVECTOR3 ConvMatrixToRot(D3DXMATRIX mtx);
// マトリックスに向きを設定
void SetMatrixRot(D3DXMATRIX *pMtx, D3DXVECTOR3 rot);
// マトリックスに拡大倍率を設定
void SetMatrixScale(D3DXMATRIX* pMtx, float fScale);

float FindMatrixScaleX(const D3DXMATRIX& mtx);
float FindMatrixScaleY(const D3DXMATRIX& mtx);
float FindMatrixScaleZ(const D3DXMATRIX& mtx);

#endif