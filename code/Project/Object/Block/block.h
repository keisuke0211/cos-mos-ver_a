//========================================
// 
// ブロック処理
// Author:KEISUKE OTONO
// 
//========================================
// *** block.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// クラス
//****************************************
class CBlock : public CStageObject {
public:

	// 共通情報
	struct Info
	{
		D3DXVECTOR3 move;		// 移動量
		D3DXCOLOR col;			// 頂点カラー
		int nType;				// 種類
		int nModelIdx;			// モデル番号
		int nID;				// ID
	};

	// *** 関数 ***
	CBlock();
	~CBlock();

	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);

	// -- 設定 ---------------------------------------------
	/* 色			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* モデル番号	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	// -- 所得 ---------------------------------------------
	/* 色		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** 静的変数 ***
	static int m_nNumAll;		// 総数

	short m_modelIdx;

	// *** 変数 ***
	Info m_Info;		// 共通情報

};