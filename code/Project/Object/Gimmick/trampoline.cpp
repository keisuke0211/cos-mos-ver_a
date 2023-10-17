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
CStageEditor::CStageEditor(void) {
	Manager::BlockMgr()->AddList(this);

	//�������
	m_type = TYPE::NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

//========================================
// �f�X�g���N�^
//========================================
CStageEditor::~CStageEditor(void) {

}

//========================================
// ����������
// Author:RYUKI FUJIWARA
//========================================
void CStageEditor::Init(void) {

}

//========================================
// �I������
// Author:RYUKI FUJIWARA
//========================================
void CStageEditor::Uninit(void) {

}

//========================================
// �X�V����
// Author:RYUKI FUJIWARA
//========================================
void CStageEditor::Update(void) {

	D3DXMATRIX mtx = ConvPosRotToMatrix(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	D3DXMatrixScaling(&mtx, m_scale.x, m_scale.y, m_scale.z);
	RNLib::Model()->Put(mtx, m_modelIdx, false);

	if (RNLib::Input()->KeyPress(DIK_UPARROW))
	{
		m_scale.y += 0.1f;
	}
	if (RNLib::Input()->KeyPress(DIK_DOWNARROW))
	{
		m_scale.y -= 0.1f;
	}

	SetScale(m_scale);
}

//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CStageEditor::Draw(void) {


}