//========================================
// 
// �p�[�c�̏���
// Author:KOMURO HIROMU
// 
//========================================
#include "Parts.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampoline�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
static const D3DXVECTOR3 PARTS_ADDROT = { 0.0f,0.02f,0.0f };				// �p�[�c�̉�]�̈ړ���

//========================================
// �R���X�g���N�^
//========================================
CParts::CParts(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::PARTS;	// ��ނ̐ݒ�
							// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 3;
	m_height = SIZE_OF_1_SQUARE * 3;

	// �e���̏�����
	ModelIdx = RNLib::Model()->Load("data\\MODEL\\Block.x");
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fblink = 0.0f;
	m_nblinlAnim = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CParts::~CParts(void) {

}

//========================================
// ����������
// Author:KOMURO HIROMU
//========================================
void CParts::Init(void) {

}

//========================================
// �I������
// Author:KOMURO HIROMU
//========================================
void CParts::Uninit(void) {

}

//========================================
// �X�V����
// Author:KOMURO HIROMU
//========================================
void CParts::Update(void) {

	m_rot += PARTS_ADDROT;	// ��]�̈ړ��ʂ̑���
	float fBrightness = fabsf(m_rot.y) / (D3DX_PI * 0.5f);

	if (fBrightness >= 1.0f)
	{
		fBrightness = fBrightness - (fBrightness  - 1.0f);
	}

	if (fBrightness < 0)
	{
		fBrightness = fabsf(fBrightness);
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false)
		->SetCol(Color{ 0,(int)(255* fBrightness),255,255 })
		;
}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CParts::Draw(void) {


}