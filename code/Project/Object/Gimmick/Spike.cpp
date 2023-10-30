//========================================
// 
// ��
// Author:KEISUKE OTONO
// 
//========================================
// *** spike.h ***
//========================================
#include "Spike.h"
#include "../../main.h"

//========================================
// �R���X�g���N�^
//========================================
CSpike::CSpike(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::SPIKE;
	m_width = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE * 0.5f;

	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nModelIdx = RNLib::Model().Load("data\\MODEL\\Spike.x");
}

//========================================
// �f�X�g���N�^
//========================================
CSpike::~CSpike()
{
	
}

//========================================
// ������
//========================================
HRESULT CSpike::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;

	return S_OK;
}

//========================================
// �I��
//========================================
void CSpike::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CSpike::Update(void)
{
	// �ߋ��̈ʒu
	RNLib::Model().Put(m_pos, m_rot, m_Info.nModelIdx, false)
		->SetOutLine(true);
}

//========================================
// �`��
//========================================
void CSpike::Draw(void)
{

}