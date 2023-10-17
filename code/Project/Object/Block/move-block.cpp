//========================================
// 
// �����u���b�N���� [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================

#include "move-block.h"

//========================================
// �ÓI�ϐ�
//========================================
int CMoveBlock::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CMoveBlock::CMoveBlock(void)
{
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\Lift.x");
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CMoveBlock::~CMoveBlock()
{
	m_nNumAll--;
}

//========================================
// ������
//========================================
HRESULT CMoveBlock::Init(void)
{

	return S_OK;
}

//========================================
// �I��
//========================================
void CMoveBlock::Uninit(void)
{
	
}

//========================================
// �X�V
//========================================
void CMoveBlock::Update(void)
{
	m_Info.pos.x += 0.1f;
	m_Info.nCntMove++;

	RNLib::Model()->Put(m_Info.pos, m_Info.rot, m_Info.nModelIdx, false);
}

//========================================
// �`��
//========================================
void CMoveBlock::Draw(void)
{

}

//========================================
// ����
//========================================
CMoveBlock *CMoveBlock::Create(void)
{
	CMoveBlock *pMoveBlock = NULL;

	if (pMoveBlock != NULL){ return pMoveBlock; }
	pMoveBlock = new CMoveBlock;

	// ����������
	pMoveBlock->Init();

	return pMoveBlock;
}