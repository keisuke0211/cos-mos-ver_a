//========================================
// 
// �g�����|�����̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#include "goalgate.h"
#include "../../main.h"
#include "../../../_RNLib/Basis/input.h"
#include "../../Character/player.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CGoalGate�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CGoalGate::CGoalGate(void) {
	Manager::BlockMgr()->AddList(this);

	//�������
	m_type = TYPE::GOALGATE;
	m_width = SIZE_OF_1_SQUARE;
	m_height = SIZE_OF_1_SQUARE * 2.0f;
	m_bGoal = false;
	m_TexIdx[0] = RNLib::Texture().Load("data\\TEXTURE\\Effect\\eff_Star_000.png");
	m_TexIdx[1] = RNLib::Texture().Load("data\\TEXTURE\\Effect\\eff_Smoke_001.png");
}

//========================================
// �f�X�g���N�^
//========================================
CGoalGate::~CGoalGate(void) {

}

//========================================
// ����������
// Author:RYUKI FUJIWARA
//========================================
void CGoalGate::Init(void) {

}

//========================================
// �I������
// Author:RYUKI FUJIWARA
//========================================
void CGoalGate::Uninit(void) {

}

//========================================
// �X�V����
// Author:RYUKI FUJIWARA
//========================================
void CGoalGate::Update(void) {

	// �S�[���|���S��
	RNLib::Polygon3D().Put(m_pos, INITD3DXVECTOR3)
		->SetTex(m_TexIdx[0])
		->SetBillboard(true);

	Manager::EffectMgr()->ParticleCreate(m_TexIdx[1],m_pos, INIT_EFFECT_SCALE, INITCOLOR);
}
//========================================
// �`�揈��
// Author:RYUKI FUJIWARA
//========================================
void CGoalGate::Draw(void) 
{

}