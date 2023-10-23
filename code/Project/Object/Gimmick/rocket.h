//========================================
// 
// ロケット
// Author:KEISUKE OTONO
// 
//========================================
// *** rocket.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// クラス
//****************************************
class CRocket : public CStageObject {
public:
	//========== [[[ 列挙型定義 ]]]
	enum class ANIME_STATE {
		NONE = -1,// 何もなし
		FLY,	  // 飛ぶ
		MAX,
	};
	// 共通情報
	struct Info
	{
		D3DXVECTOR3 move;		// 移動量
		D3DXCOLOR col;			// 頂点カラー
		ANIME_STATE Animstate;	// アニメーションの状態
		short nModelIdx;		// モデル番号
		int	nFlyAnimeCounter;	// 飛行アニメーションカウンター
	};

	// *** 関数 ***
	CRocket();
	~CRocket();

	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);

	// -- 設定 ---------------------------------------------
	/* 色			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* モデル番号	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }
	/* アニメーションの状態の設定*/void SetState(const ANIME_STATE state) { m_Info.Animstate = state; }
	// -- 所得 ---------------------------------------------
	/* 色		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** 変数 ***
	Info m_Info;		// 共通情報

};