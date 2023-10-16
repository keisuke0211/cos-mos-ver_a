//========================================
// 
// コリジョン3Dのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// クラス定義
//****************************************
// モデルセットアップクラス
class CCollision3D {
public:
	//========== [[[ 列挙型定義 ]]]
	// 形
	typedef enum {
		FORM_SPHERE,	// 球
		FORM_CUBE,		// 立方体
		FORM_CYLINDER,	// 筒
		FORM_MAX,
	}FORM;

	//========== [[[ 構造体定義 ]]]
	// 部品情報構造体
	typedef struct Parts_ {
		FORM        form    = (FORM)0;			// 形
		float       fWidth  = 0.0f;				// 幅
		float       fHeight = 0.0f;				// 高さ
		float       fDepth  = 0.0f;				// 奥行き
		int         nParent = DATANONE;			// 親
		D3DXVECTOR3 pos     = INITD3DXVECTOR3;	// 位置
		D3DXVECTOR3 rot     = INITD3DXVECTOR3;	// 向き
	}Parts;
	// データ構造体
	typedef struct Data_{
		Parts* pParts    = NULL;	// 部品情報
		int    nPartsNum = 0;		// 部品数
	}Data;

	//========== [[[ 関数宣言 ]]]
	static void LoadData(Data* pData);
	static void SaveData(Data* pData);
};