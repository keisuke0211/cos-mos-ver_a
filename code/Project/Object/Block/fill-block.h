//========================================
// 
// ブロック(判定 無し)
// Author:KEISUKE OTONO
// 
//========================================
// *** fill-block.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// クラス
//****************************************
class CFillBlock : public CStageObject {
public:

	// 共通情報
	struct Info
	{
		D3DXCOLOR col;			// 頂点カラー
		int nType;				// 種類
		short nModelIdx;		// モデル番号
	};

	// *** 関数 ***
	CFillBlock();
	~CFillBlock();

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

	// *** 変数 ***
	Info m_Info;		// 共通情報

};