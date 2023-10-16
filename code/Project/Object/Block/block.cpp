//========================================
// 
// �u���b�N����
// Author:KEISUKE OTONO
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"

//========================================
// �ÓI�ϐ�
//========================================
int CBlock::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(void)
{
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CBlock::~CBlock()
{
	m_nNumAll--;
}

//========================================
// ������
//========================================
HRESULT CBlock::Init(void)
{

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlock::Uninit(void)
{
	/*CObjectX::Uninit();*/
}

//========================================
// �X�V
//========================================
void CBlock::Update(void)
{

}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{

}

//========================================
// ����
//========================================
CBlock *CBlock::Create(void)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL){ return pBlock; }
	pBlock = new CBlock;

	// ����������
	pBlock->Init();

	return pBlock;
}