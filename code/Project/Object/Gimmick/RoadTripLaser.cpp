//========================================
// 
// �������郌�[�U�[�̏���
// Author:KOMURO HIROMU
// 
//========================================
#include "RoadTripLaser.h"
#include "../../main.h"
//================================================================================
//----------|---------------------------------------------------------------------
//==========| CRoadTripLaser�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
static const D3DXVECTOR2  s_Size = D3DXVECTOR2(10.0f,50.0f);	// ����

//========================================
// �R���X�g���N�^
//========================================
CRoadTripLaser::CRoadTripLaser(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// ��ނ̐ݒ�
								// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// �e���̏�����
	m_pos = INITD3DXVECTOR3;
	m_refPos = INITD3DXVECTOR3;
	m_frefdef = 0.0f;
	m_fGroundDis = 0.0f;
}

//========================================
// �f�X�g���N�^
//========================================
CRoadTripLaser::~CRoadTripLaser(void) {

}

//========================================
// ����������
// Author:KOMURO HIROMU
//========================================
void CRoadTripLaser::Init(void) {
	ModelIdx = RNLib::Model().Load("data\\MODEL\\Lift.x");
	//RNLib::Texture().Load();

	m_refPos = m_pos;
	m_fGroundDis = m_pos.y - 0.0f;
}

//========================================
// �I������
// Author:KOMURO HIROMU
//========================================
void CRoadTripLaser::Uninit(void) {

}

//========================================
// �X�V����
// Author:KOMURO HIROMU
//========================================
void CRoadTripLaser::Update(void) {

	D3DXVECTOR3 Block = m_pos;	// �ʒu
	// �u���b�N�̈ʒu�ݒ�
	Block.y += s_Size.y;


	// x�̈ړ��ʂ̔��]
	if (m_refPos.x + m_frefdef <= m_pos.x || m_refPos.x - m_frefdef >= m_pos.x)
	{
		m_move.x *= -1;
	}
	// y�̈ړ��ʂ̔��]
	if (m_refPos.y + m_frefdef <= m_pos.y || m_refPos.y - m_frefdef >= m_pos.y)
	{
		m_move.y *= -1;
	}

	m_pos += m_move;

	RNLib::Model().Put(Block, m_rot, ModelIdx, false);

	RNLib::Polygon3D().Put(D3DXVECTOR3(m_pos.x, m_pos.y + Block.y,m_pos.z), m_rot, false)
		->SetSize(s_Size.x, s_Size.y);

}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CRoadTripLaser::Draw(void) {


}