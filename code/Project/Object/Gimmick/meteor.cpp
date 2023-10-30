//========================================
// 
// 覐΂̏���
// Author:KOMURO HIROMU  Hirasawa Shion
// 
//========================================
#include "meteor.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampoline�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
const D3DXVECTOR3 CMeteor::METEOR_ADDROT = { 0.10f,0.02f,0.01f };    // 覐΂̉�]�̈ړ���
const D3DXVECTOR3 CMeteor::METEOR_MINPOS = { -150.0f,-150.0f,0.0f }; // �ŏ��̈ʒu
const D3DXVECTOR3 CMeteor::METEOR_MAXPOS = { 150.0f,150.0f,0.0f };   // �ő�̈ʒu
const int		  CMeteor::METEOR_ANIME_MAG = 2;                     // �_�ŃA�j���[�V�����̔{��
const int		  CMeteor::METEOR_BLINK_MAX = 10 * METEOR_ANIME_MAG; // �_�ŃA�j���[�V�����̍ő吔
const float		  CMeteor::METEOR_BLINK_MIN = 0.0f;                  // �_�ł̍ŏ���
const float		  CMeteor::METEOR_BLINK_ADJ = 0.01f;                 // �_�ŃA�j���[�V�����̒���

//========================================
// �R���X�g���N�^
//========================================
CMeteor::CMeteor(void) {
	Manager::BlockMgr()->AddList(this);
	
	// ��ނ̐ݒ�
	m_type = TYPE::METEOR;

	// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 3;
	m_height = SIZE_OF_1_SQUARE * 3;

	// �e���̏�����
	ModelIdx = RNLib::Model().Load("data\\MODEL\\Meteorite.x");
	m_pos = INITD3DXVECTOR3;
	m_rot = INITD3DXVECTOR3;
	m_move = INITD3DXVECTOR3;
	m_fBlink = 0.0f;
	m_nBlinkAnim = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CMeteor::~CMeteor(void) {

}

//========================================
// ����������
// Author:KOMURO HIROMU
//========================================
void CMeteor::Init(void) {

}

//========================================
// �I������
// Author:KOMURO HIROMU
//========================================
void CMeteor::Uninit(void) {

}

//========================================
// �X�V����
// Author:KOMURO HIROMU
//========================================
void CMeteor::Update(void) {

	m_rot += METEOR_ADDROT;	// �����̈ړ��ʂ̒ǉ�
	m_pos += m_move;		// �ړ��ʂ̒ǉ�

	//�_�ŃA�j���[�V��������
	BlinkAnimation();

	//���f���z�u
	RNLib::Model().Put(m_pos, m_rot, ModelIdx, false)->SetOutLine(true)
		->SetBrightnessOfEmissive(m_fBlink)->SetCol(m_color);

	// �Ƃ肠������ʊO�ŏ�������
	if (m_pos.x >= METEOR_MAXPOS.x || m_pos.y >= METEOR_MAXPOS.y || m_pos.x <= METEOR_MINPOS.x || m_pos.y <= METEOR_MINPOS.y)
	{
		// �폜
		Delete();
	}
}

//========================================
//�_�ŃA�j���[�V��������
// Author:KOMURO HIROMU  Hirasawa Shion
//========================================
void CMeteor::BlinkAnimation(void)
{
	// �_�ŃA�j���[�V�����̑���
	m_nBlinkAnim++;	

	// �_�ŃA�j���[�V�����̌v�Z
	if (m_nBlinkAnim < METEOR_BLINK_MAX * METEOR_ANIME_MAG)
	{
		m_fBlink -= METEOR_BLINK_MAX - m_nBlinkAnim;
		m_fBlink = m_fBlink / (10 * METEOR_ANIME_MAG);

		if (m_fBlink < 0.0f)
		{
			m_fBlink = fabsf(m_fBlink);
		}
	}
	else
	{
		m_nBlinkAnim = 0;
	}
}