//========================================
// 
// �f���̏���
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

static const char* s_modelPaths[(int)CPlanet::STAR_TYPE::MAX] = {
	"data\\MODEL\\Blue_Star.x",
	"data\\MODEL\\Red_Star.x",
	"data\\MODEL\\Comet_Star.x",
	"data\\MODEL\\Yellow_Star.x",
	"data\\MODEL\\Saturn_Star.x",
};

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
	ModelIdx = RNLib::Model()->Load(s_modelPaths[(int)m_Star_type]);

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

	m_pos += m_move;

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false);
}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CPlanet::Draw(void) {


}