//========================================
// 
// ブロック処理
// Author:KEISUKE OTONO
// 
//========================================
// *** block.h ***
//========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../main.h"

//****************************************
// クラス
//****************************************
class CBlock
{
public:

	// 共通情報
	struct Info
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 位置(過去)
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3	size;		// サイズ
		D3DXCOLOR col;			// 頂点カラー
		int nType;				// 種類
		int nID;				// ID
	};

private:

	// *** 関数 ***
	CBlock();
	~CBlock();

	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* 読み込み	*/static void Load(void);
	/* 生成		*/static CBlock *Create(void);

	// -- 設定 ---------------------------------------------
	/* 位置		*/void SetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* 向き		*/void SetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* 色		*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* 大きさ	*/void SetSize(const D3DXVECTOR3 size) { m_Info.size = size; }

	// -- 所得 ---------------------------------------------
	/* 位置		*/D3DXVECTOR3 GetPos(void) { return m_Info.pos; }
	/* 向き		*/D3DXVECTOR3 GetRot(void) { return m_Info.rot; }
	/* 色		*/D3DXCOLOR GetColor(void) { return m_Info.col; }
	/* 大きさ	*/D3DXVECTOR3 GetSize(void) { return m_Info.size; }

	// *** 静的変数 ***
	static int m_nNumAll;		// 総数

	// *** 変数 ***
	Info m_Info;		// 共通情報

};
#endif