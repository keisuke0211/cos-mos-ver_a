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
static const D3DXVECTOR3 METEOR_ADDROT = { 0.10f,0.02f,0.01f };				// 覐΂̉�]�̈ړ���
static const D3DXVECTOR3 METEOR_UNINIT_MINPOS = { -150.0f,-150.0f,0.0f };	// �ŏ��̈ʒu
static const D3DXVECTOR3 METEOR_UNINIT_MAXPOS = { 150.0f,150.0f,0.0f };		// �ő�̈ʒu
static const int METEOR_BLINK_MAX = 10;						// �_�ŃA�j���[�V�����̍ő吔
static const float METEOR_BLINK_MIN = 0.0f;					// �_�ł̍ŏ���
static const float METEOR_BLINK_ADJ = 0.01f;				// �_�ŃA�j���[�V�����̒���
//========================================
// �R���X�g���N�^
//========================================
CMeteor::CMeteor(void) {
	Manager::BlockMgr()->AddList(this);
	
	m_type = TYPE::METEOR;	// ��ނ̐ݒ�
	// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 3;
	m_height = SIZE_OF_1_SQUARE * 3;

	// �e���̏�����
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

	int nBlink;

	m_rot += METEOR_ADDROT;		// �����̈ړ��ʂ̒ǉ�
	m_pos += m_move;			// �ړ��ʂ̒ǉ�

	// �_�ŃA�j���[�V�����̌v�Z
	if (m_nblinlAnim <= METEOR_BLINK_MAX * 2)
	{
		m_nblinlAnim = m_nblinlAnim % (METEOR_BLINK_MAX + 1);
		m_fblink -= METEOR_BLINK_MAX % -m_nblinlAnim;
	}
	else
	{
		m_nblinlAnim = 0;
	}
	

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