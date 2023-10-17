//========================================
// 
// 動くブロック処理 [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================

#ifndef _MOVEBLOCK_H_
#define _MOVEBLOCK_H_

#include "../../../_RNLib/RNlib.h"

//========================================
// クラス
//========================================
class CMoveBlock : public CObject
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
	void SetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	void SetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	void SetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* モデル番号	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	//取得
	D3DXVECTOR3 GetPos(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRot(void) { return m_Info.rot; }
	D3DXCOLOR GetColor(void) { return m_Info.col; }
	D3DXVECTOR3 GetSize(void) { return m_Info.size; }

private:

	//静的変数
	static int m_nNumAll;		// 総数

	//変数
	Info m_Info;		// 共通情報

};
#endif