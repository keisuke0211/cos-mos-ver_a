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
D3DXVECTOR3 static const METEOR_ADDROT = { 0.10f,0.02f,0.01f };				// 覐΂̉�]�̈ړ���
D3DXVECTOR3 static const METEOR_UNINIT_MINPOS = { -150.0f,-150.0f,0.0f };	// �ŏ��̈ʒu
D3DXVECTOR3 static const METEOR_UNINIT_MAXPOS = { 150.0f,150.0f,0.0f };		// �ő�̈ʒu
float			static const METEOR_BLINK_MAX = { 5.0f };					// �_�ŃA�j���[�V�����̍ő吔
float			static const METEOR_BLINK_MIN = { 0.5f };					// �_�ł̍ŏ���
float			static const METEOR_BLINK_ADJ = { 10.0f };					// �_�ŃA�j���[�V�����̒���
//========================================
// �R���X�g���N�^
//========================================
CMeteor::CMeteor(void) {
	Manager::BlockMgr()->AddList(this);
	
	// �e���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fblink = 0.0f;
	m_nblinlAnim = 0;
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


	m_pos += m_move;			// �ړ��ʂ̒ǉ�
	m_rot += METEOR_ADDROT;		// �����̈ړ��ʂ̒ǉ�

	// �_�ŃA�j���[�V�����̌v�Z
	m_fblink = (m_nblinlAnim % (int)METEOR_BLINK_MAX);
	m_fblink = (m_fblink / (float)METEOR_BLINK_ADJ);
	m_fblink =  m_fblink + METEOR_BLINK_MIN;

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false)
		->SetOutLine(true)
		->SetBrightnessOfEmissive(m_fblink)
		;

	m_nblinlAnim++;	// �_�ŃA�j���[�V�����̑���

	if (m_pos.x >= METEOR_UNINIT_MAXPOS.x || m_pos.y >= METEOR_UNINIT_MAXPOS.y || m_pos.x <= METEOR_UNINIT_MINPOS.x || m_pos.y <= METEOR_UNINIT_MINPOS.y)
	{
		// �폜
		Delete();
	}
}

//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CMeteor::Draw(void) {


}