//========================================
// 
// 動くブロック処理 [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================

#ifndef _MOVEBLOCK_H_
#define _MOVEBLOCK_H_

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//========================================
// クラス
//========================================
class CMoveBlock : public CStageObject
{
public:

	// 共通情報
	struct Info
	{
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3	size;		// サイズ
		D3DXCOLOR col;			// 頂点カラー
		int nCntMove;			// 移動カウント
		int nType;				// 種類
		int nID;				// ID
		int nModelIdx;
	};


	//関数
	CMoveBlock();
	~CMoveBlock();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//設定
	void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	void SetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	//取得
	D3DXCOLOR GetColor(void) { return m_Info.col; }
	D3DXVECTOR3 GetSize(void) { return m_Info.size; }

private:

	//静的変数
	static int m_nNumAll;		// 総数

	//変数
	Info m_Info;		// 共通情報

};
#endif