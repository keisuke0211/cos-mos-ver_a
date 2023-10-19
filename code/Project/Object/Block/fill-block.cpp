//========================================
// 
// �u���b�N (���� ����)
// Author:KEISUKE OTONO
// 
//========================================
// *** fill-block.cpp ***
//========================================
#include "fill-block.h"
#include "../../main.h"

//========================================
// �R���X�g���N�^
//========================================
CFillBlock::CFillBlock(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::FILLBLOCK;
	m_width = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE;

	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\Block.x");
}

//========================================
// �f�X�g���N�^
//========================================
CFillBlock::~CFillBlock()
{

}

//========================================
// ������
//========================================
HRESULT CFillBlock::Init(void)
{
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;

	return S_OK;
}

//========================================
// �I��
//========================================
void CFillBlock::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CFillBlock::Update(void)
{
	// �ߋ��̈ʒu
	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_Info.nModelIdx, false);
}

//========================================
// �`��
//========================================
void CFillBlock::Draw(void)
{

}