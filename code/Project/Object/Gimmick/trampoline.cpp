//========================================
// 
// �M�~�b�N�̏���
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
	m_type = TYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
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

	
	D3DXMATRIX mtx = ConvPosRotToMatrix(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXMatrixScaling(&mtx, m_scale.x, m_scale.y, m_scale.z);
	RNLib::Model()->Put(mtx, m_modelIdx, false);

	if (RNLib::Input()->KeyTrigger(DIK_UPARROW))
	{

	}
}

//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CTrampoline::Draw(void) {


}