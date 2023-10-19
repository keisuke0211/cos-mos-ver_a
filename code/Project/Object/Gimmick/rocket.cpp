//========================================
// 
// ���P�b�g
// Author:KEISUKE OTONO
// 
//========================================
// *** rocket.cpp ***
//========================================
#include "rocket.h"
#include "../../main.h"

//========================================
// �R���X�g���N�^
//========================================
CRocket::CRocket(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BLOCK;
	m_width = SIZE_OF_1_SQUARE*3;
	m_height = SIZE_OF_1_SQUARE*3;

	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nModelIdx = RNLib::Model()->Load("data\\MODEL\\rocket.x");
}

//========================================
// �f�X�g���N�^
//========================================
CRocket::~CRocket()
{

}

//========================================
// ������
//========================================
HRESULT CRocket::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;

	return S_OK;
}

//========================================
// �I��
//========================================
void CRocket::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CRocket::Update(void)
{
	// �ߋ��̈ʒu
	RNLib::Model()->Put(m_pos, m_rot, m_Info.nModelIdx, false);
}

//========================================
// �`��
//========================================
void CRocket::Draw(void)
{

}