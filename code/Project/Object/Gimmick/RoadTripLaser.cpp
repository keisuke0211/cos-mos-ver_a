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
static const D3DXVECTOR2  s_Size = D3DXVECTOR2(5.0f,50.0f);	// ����

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
	m_fGroundDis = fabsf(m_fGroundDis);

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

	//�I�u�W�F�N�g���擾
	CObject *obj = NULL;
	float fDis = m_fGroundDis;
	while (Manager::BlockMgr()->ListLoop(&obj)) {
		//�擾�����I�u�W�F�N�g���L���X�g
		CStageObject* stageObj = (CStageObject*)obj;

		TYPE type = stageObj->GetType();
		if (type == CStageObject::TYPE::MOVE_BLOCK || type == CStageObject::TYPE::BLOCK || type == CStageObject::TYPE::TRAMPOLINE)
		{// �z�肳�ꂽ��ނ̎�

			D3DXVECTOR3 stagepos = stageObj->GetPos();
			D3DXVECTOR2 stagesize = D3DXVECTOR2(stageObj->GetWidth(), stageObj->GetHeight());

			if (stagepos.x + (stagesize.x * 0.5f) >= m_pos.x - s_Size.x &&
				stagepos.x - (stagesize.x * 0.5f) <= m_pos.x + s_Size.x)
			{// �͈͓��ɂ���Ƃ�
				if (fDis >= m_pos.y - stagepos.y - stagesize.y * 0.5f)
				{// �������߂��Ƃ�
					fDis = m_pos.y - stagepos.y - stagesize.y * 0.5f;	// �����̍X�V
				}
			}
		}
	}
	
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

	// �u���b�N�̈ʒu�ݒ�
	m_pos += m_move;

	// �u���b�N
	RNLib::Model().Put(Block, m_rot, ModelIdx, false);

	// �r�[��
	RNLib::Polygon3D().Put(D3DXVECTOR3(m_pos.x, (Block.y - fDis * 0.5f),m_pos.z), m_rot, false)
		->SetSize(s_Size.x, fDis);
}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CRoadTripLaser::Draw(void) {


}