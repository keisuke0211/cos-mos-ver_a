//========================================
// 
// �����u���b�N���� [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================
#include "../../manager.h"
#include "move-block.h"
#include "../../main.h"

//========================================
// �ÓI�ϐ�
//========================================
int CMoveBlock::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CMoveBlock::CMoveBlock(void)
{
	m_type = TYPE::MOVE_BLOCK;

	Manager::BlockMgr()->AddList(this);

	m_width  = SIZE_OF_1_SQUARE * 2;
	m_height = SIZE_OF_1_SQUARE;

	m_Info.move = INITD3DXVECTOR3;
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
	

	m_pos.x += 1.0f;

	RNLib::Model()->Put(m_pos, m_rot, m_Info.nModelIdx);
}

//========================================
// �`��
//========================================
void CMoveBlock::Draw(void)
{

}