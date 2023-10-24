//========================================
// 
// ���̏���
// Author:KOMURO HIROMU
// 
//========================================
#include "Star.h"
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
CStar::CStar(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// ��ނ̐ݒ�
								// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// �e���̏�����
	m_rot = INITD3DXVECTOR3;
	m_move = INITD3DXVECTOR3;
	m_col = Color{ 255,255,255,255 };
	m_rot = INITD3DXVECTOR3;
	m_moveCounter = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CStar::~CStar(void) {

}

//========================================
// ����������
// Author:KOMURO HIROMU
//========================================
void CStar::Init(void) {
	//ModelIdx = RNLib::Model()->Load(s_modelPaths[(int)m_Star_type]);
	//RNLib::Texture()->Load();
	m_posOld = m_pos;
}

//========================================
// �I������
// Author:KOMURO HIROMU
//========================================
void CStar::Uninit(void) {

}

//========================================
// �X�V����
// Author:KOMURO HIROMU
//========================================
void CStar::Update(void) {
	
	RNLib::Polygon3D()->Put(m_pos, m_rot, false)
		->SetSize(100.0f,100.0f);
}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CStar::Draw(void) {


}