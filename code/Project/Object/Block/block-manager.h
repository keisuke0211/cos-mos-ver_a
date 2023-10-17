//========================================
// 
// ブロック処理
// Author:KEISUKE OTONO
// 
//========================================
// *** block.h ***
//========================================
#ifndef _BLOCK_MANAGER_H_
#define _BLOCK_MANAGER_H_

#include "../../../_RNLib/RNlib.h"
#include "block.h"
#include "../Gimmick/trampoline.h"
#include "../Gimmick/meteor.h"
#include "move-block.h"

//****************************************
// クラス
//****************************************
class CBlockMgr : public CObjectMgr {

	static const char* BLOCK_INFO_FILE;		// ブロック情報のファイルパス

public:

	// *** 関数 ***
	CBlockMgr();
	virtual~CBlockMgr();
	virtual void Update(void);
	void Load(void);

	// -- 生成 ---------------------------------------------
	/* ブロック		*/CBlock *BlockCreate(int type,D3DXVECTOR3 pos);
	/* トランポリン	*/CTrampoline *TrampolineCreate(int type, D3DXVECTOR3 pos);
	/* 隕石			*/CMeteor *MeteorCreate(int type, D3DXVECTOR3 pos,D3DXVECTOR3 move);
	/* 移動床		*/CMoveBlock *MoveBlockCreate(int type, D3DXVECTOR3 pos, D3DXVECTOR3 move);
private:

	// *** 構造体 ***

	// 種類情報
	struct BlockType
	{
		char			aFileName[0xff];	// Xファイルのパス
		int				nModelIdx;			// モデル番号
	};

	// *** 静的変数 ***
	static int *m_nMaxType;

	// *** 変数 ***
	static BlockType *m_pBlockType;	// 種類情報
};

#endif