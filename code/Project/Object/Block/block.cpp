//========================================
// 
// �u���b�N����
// Author:KEISUKE OTONO
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "../../main.h"

//========================================
// �ÓI�ϐ�
//========================================
int CBlock::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type   = TYPE::BLOCK;
	m_width  = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE;

	m_Info.move = INITD3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nModelIdx = RNLib::Model().Load("data\\MODEL\\Block.x");
	m_Info.nID = m_nNumAll;
}

//========================================
// �f�X�g���N�^
//========================================
CBlock::~CBlock()
{

}

//========================================
// ������
//========================================
HRESULT CBlock::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.nType = 0;

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlock::Uninit(void)
{
	
}

//========================================
// �X�V
//========================================
void CBlock::Update(void)
{
	// �ߋ��̈ʒu
	RNLib::Model().Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Info.nModelIdx, false)
		->SetCol(m_color);
}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{

}