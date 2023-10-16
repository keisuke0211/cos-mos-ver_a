//========================================
// 
// �u���b�N�}�l�[�W���[
// Author:KEISUKE OTONO
// 
//========================================
// *** block-manager.h ***
//========================================
#include "block-manager.h"

//========================================
// �R���X�g���N�^
//========================================
CBlockMgr::CBlockMgr(void)
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CBlockMgr::~CBlockMgr()
{
	
}

//========================================
// ������
//========================================
void CBlockMgr::Init(void)
{
	CListMgr::Init();
}

//========================================
// �I��
//========================================
void CBlockMgr::Uninit(void)
{
	
}

//========================================
// �X�V
//========================================
void CBlockMgr::Update(void)
{
	CListMgr::Update();
}

//========================================
// ����
//========================================
CBlock *CBlockMgr::Create(D3DXVECTOR3 pos)
{
	CBlock *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CBlock;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);

	return pObj;
}

CTrampoline *CBlockMgr::TCreate(D3DXVECTOR3 pos)
{
	CTrampoline *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CTrampoline;

	// ����������
	pObj->Init();

	return pObj;
}
