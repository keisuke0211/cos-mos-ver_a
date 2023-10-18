//========================================
// 
// ステージオブジェクトマネージャーの処理
// Author:KEISUKE OTONO
// Arrange:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"
#include "Block/block.h"
#include "Gimmick\Spike.h"
#include "Block/move-block.h"
#include "Gimmick/trampoline.h"
#include "Gimmick/meteor.h"
#include "Item/Parts.h"
#include "BackGround\Planet.h"
//****************************************
// クラス
//****************************************
class CStageObjectMgr : public CObjectMgr {
public:
	//========== [[[ 静的変数宣言 ]]]
	static const char* BLOCK_INFO_FILE;		// ブロック情報のファイルパス

	//========== [[[ 関数宣言 ]]]
	CStageObjectMgr();
	virtual~CStageObjectMgr();
	virtual void Update(void);	void Load(void);
	CBlock      *BlockCreate     (D3DXVECTOR3 pos);
	CSpike      *SpikeCreate	 (D3DXVECTOR3 pos);
	CTrampoline *TrampolineCreate(D3DXVECTOR3 pos);
	CMeteor     *MeteorCreate    (D3DXVECTOR3 pos, D3DXVECTOR3 move);
	CMoveBlock  *MoveBlockCreate (D3DXVECTOR3 pos, D3DXVECTOR3 move);
	CParts      *PartsCreate	 (D3DXVECTOR3 pos);
	CPlanet		*PlanetCreate	 (D3DXVECTOR3 pos,CPlanet::STAR_TYPE type);
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