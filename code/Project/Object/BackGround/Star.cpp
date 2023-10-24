//========================================
// 
// ���̏���
// Author:KOMURO HIROMU
// 
//========================================
#include "Planet.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampoline�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
static const int s_maxAnimeCounter = 120;		// �A�j���[�V�����̃J�E���^�[�ő�
static const D3DXVECTOR3 s_moveRot = D3DXVECTOR3(0.0005f, 0.0005f, 0.0f);
static const float s_PosOver = 100.0f;	

//========================================
// �R���X�g���N�^
//========================================
CPlanet::CPlanet(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// ��ނ̐ݒ�
								// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// �e���̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = Color{ 255,255,255,255 };
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveCounter = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CPlanet::~CPlanet(void) {

}

//========================================
// ����������
// Author:KOMURO HIROMU
//========================================
void CPlanet::Init(void) {
	//ModelIdx = RNLib::Model()->Load(s_modelPaths[(int)m_Star_type]);

	m_posOld = m_pos;
}

//========================================
// �I������
// Author:KOMURO HIROMU
//========================================
void CPlanet::Uninit(void) {

}

//========================================
// �X�V����
// Author:KOMURO HIROMU
//========================================
void CPlanet::Update(void) {

	m_moveCounter++;	// �J�E���^�[��i�߂�


	if (m_moveCounter % s_maxAnimeCounter == 0)
	{
		m_move = vecRand() * 0.05f;
		m_move.z = 0.0f;
	}

	// �ړ��ʂ��ʒu�ɑ���
	m_pos += m_move;
	m_rot += s_moveRot;

	if (m_posOld.x + s_PosOver <= m_pos.x || m_posOld.x - s_PosOver >= m_pos.x)
	{
		m_move *= -1;
	}
	
	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false)
		->SetCol(m_col);
		
}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CPlanet::Draw(void) {


}