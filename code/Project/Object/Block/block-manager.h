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

//****************************************
// クラス
//****************************************
class CBlockMgr : public CListMgr {
public:

	// *** 関数 ***
	CBlockMgr();
	virtual~CBlockMgr();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	
	CBlock *Create(D3DXVECTOR3 pos);
	CTrampoline *TCreate(D3DXVECTOR3 pos);

};

#endif