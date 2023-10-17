//========================================
// 
// 覐΂̏���
// Author:KOMURO HIROMU
// 
//========================================
#include "meteor.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampoline�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
D3DXVECTOR3 static const METEOR_ADDROT = { 0.1f,0.2f,0.1f };	// 覐΂̉�]�̈ړ���
D3DXVECTOR3 static const METEOR_UNINIT_MINPOS = { -1000.0f,-1000.0f,0.0f };	// �ŏ��̈ʒu
D3DXVECTOR3 static const METEOR_UNINIT_MAXPOS = { 1000.0f,1000.0f,0.0f };	// �ő�̈ʒu
//========================================
// �R���X�g���N�^
//========================================
CMeteor::CMeteor(void) {
	Manager::BlockMgr()->AddList(this);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================
// �f�X�g���N�^
//========================================
CMeteor::~CMeteor(void) {

}

//========================================
// ����������
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Init(void) {

}

//========================================
// �I������
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Uninit(void) {

}

//========================================
// �X�V����
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Update(void) {

	// �ړ��ʂ̒ǉ�
	m_pos += m_move;
	// �����̈ړ��ʂ̒ǉ�
	m_rot += METEOR_ADDROT;

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false);

	if (m_pos.x >= METEOR_UNINIT_MAXPOS.x || m_pos.y >= METEOR_UNINIT_MAXPOS.y || m_pos.x <= METEOR_UNINIT_MINPOS.x || m_pos.y <= METEOR_UNINIT_MINPOS.y)
	{

	}
}

//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Draw(void) {


}