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
//==========| CParts�N���X�̃����o�ϐ�
//----------|---------------------------------------------------------------------
//================================================================================
int					CParts::s_nNumAll = 0;	
const D3DXVECTOR3	CParts::PARTS_ADDROT = { 0.0f,0.02f,0.0f };

//========================================
// �R���X�g���N�^
//========================================
CParts::CParts(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::PARTS;	// ��ނ̐ݒ�
							// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 2;
	m_height = SIZE_OF_1_SQUARE * 2;
	m_bDisp = true;

	// �e���̏�����
	ModelIdx = RNLib::Model().Load("data\\MODEL\\Rocket_Engine_break.x");
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	s_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CParts::~CParts(void) {

	s_nNumAll--;
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
// Author:KOMURO HIROMU (Hirasawa Shion)
//========================================
void CParts::Update(void) {
	
	if (!m_bDisp) return;

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

	RNLib::Model().Put(m_pos, m_rot, ModelIdx, false)
		->SetCol(Color{ (int)(255 * fBrightness),(int)(255 * fBrightness),(int)(255 * fBrightness),255 })
		->SetOutLine(true);

	int ParTex = RNLib::Texture().Load("data\\TEXTURE\\Effect\\eff_Hit_002.png");

	Manager::EffectMgr()->EffectCreate(ParTex,m_pos,INIT_EFFECT_SCALE, INITCOLOR);
}

//---------------------------
// �擾������`�� ON/OFF ��؂�ւ�
// Author�FHirasawa Shion
//---------------------------
void CParts::DispSwitch(bool bGet)
{
	//�`��؂�ւ�
	m_bDisp = bGet;
}