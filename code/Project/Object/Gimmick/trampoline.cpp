//========================================
// 
// �g�����|�����̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#include "trampoline.h"
#include "../../main.h"
#include "../../../_RNLib/_Basis/Other/input.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampoline�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CTrampoline::CTrampoline(void) {
	Manager::BlockMgr()->AddList(this);

	//�������
	m_type = TYPE::TRAMPOLINE;
	m_width = SIZE_OF_1_SQUARE * 2.0f;
	m_height = SIZE_OF_1_SQUARE;
	m_state = STATE::NONE;
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_bLand = false;
	m_modelIdx[0] = RNLib::Model()->Load("data\\MODEL\\Block.x");
	m_modelIdx[1] = RNLib::Model()->Load("data\\MODEL\\SpringFloor.x");
	m_modelIdx[2] = m_modelIdx[1];
}

//========================================
// �f�X�g���N�^
//========================================
CTrampoline::~CTrampoline(void) {

}

//========================================
// ����������
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Init(void) {

}

//========================================
// �I������
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Uninit(void) {

}

//========================================
// �X�V����
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Update(void) {

	//�ʒu�L��
	m_posOld = m_pos;

	if (RNLib::Input()->KeyTrigger(DIK_UPARROW))
	{
		m_state = STATE::UP_LAND;
	}
	if (RNLib::Input()->KeyTrigger(DIK_DOWNARROW))
	{
		m_state = STATE::DOWN_LAND;
	}

	D3DXMATRIX mtx = ConvPosRotToMatrix(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXMatrixScaling(&mtx, m_scale.x, m_scale.y, m_scale.z);
	RNLib::Model()->Put(mtx, m_modelIdx[0], false)
		->SetModel(2);

	SetScale(m_scale);


	RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[1], false);
	RNLib::Model()->Put(D3DXVECTOR3(m_pos.x, m_pos.y + -20.0f, m_pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_modelIdx[2], false);


}

//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Draw(void) {


}