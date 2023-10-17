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

//****************************************
// �N���X
//****************************************
class CBlockMgr : public CListMgr {

	static const char* BLOCK_INFO_FILE;		// �u���b�N���̃t�@�C���p�X

public:

	// *** �֐� ***
	CBlockMgr();
	virtual~CBlockMgr();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	void Load(void);

	// -- ���� ---------------------------------------------
	/* �u���b�N		*/CBlock *BlockCreate(int type,D3DXVECTOR3 pos);
	/* �g�����|����	*/CTrampoline *TrampolineCreate(int type, D3DXVECTOR3 pos);

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