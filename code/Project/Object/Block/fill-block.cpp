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

//�p�X�ǂݍ���
static const char* s_Path[4] = {
	"data\\MODEL\\fill-block_1x1.x",
	"data\\MODEL\\fill-block_2x2.x",
	"data\\MODEL\\fill-block_3x3.x",
	"data\\MODEL\\fill-block_4x4.x",
};

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
HRESULT CFillBlock::Init(FILL_TYPE type)
{
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;

	//���f���ԍ��ǂݍ���
	m_Info.nModelIdx = RNLib::Model()->Load(s_Path[(int)type]);

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
	RNLib::Model()->Put(m_pos, D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), m_Info.nModelIdx, false);
}



//========================================
// �`��
//========================================
void CFillBlock::Draw(void)
{

}