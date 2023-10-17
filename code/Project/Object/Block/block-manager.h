//========================================
// 
// �u���b�N����
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
// �N���X
//****************************************
class CBlockMgr : public CObjectMgr {

	static const char* BLOCK_INFO_FILE;		// �u���b�N���̃t�@�C���p�X

public:

	// *** �֐� ***
	CBlockMgr();
	virtual~CBlockMgr();
	virtual void Update(void);
	void Load(void);

	// -- ���� ---------------------------------------------
	/* �u���b�N		*/CBlock *BlockCreate(int type,D3DXVECTOR3 pos);
	/* �g�����|����	*/CTrampoline *TrampolineCreate(int type, D3DXVECTOR3 pos);
	/* 覐�			*/CMeteor *MeteorCreate(int type, D3DXVECTOR3 pos,D3DXVECTOR3 move);
	/* �ړ���		*/CMoveBlock *MoveBlockCreate(int type, D3DXVECTOR3 pos, D3DXVECTOR3 move);
private:

	// *** �\���� ***

	// ��ޏ��
	struct BlockType
	{
		char			aFileName[0xff];	// X�t�@�C���̃p�X
		int				nModelIdx;			// ���f���ԍ�
	};

	// *** �ÓI�ϐ� ***
	static int *m_nMaxType;

	// *** �ϐ� ***
	static BlockType *m_pBlockType;	// ��ޏ��
};

#endif