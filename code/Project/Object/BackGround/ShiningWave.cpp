//========================================
// 
// �g�ł��̏���
// Author:KOMURO HIROMU
// 
//========================================
#include "ShiningWave.h"
#include "../../main.h"
//================================================================================
//----------|---------------------------------------------------------------------
//==========| CShiningWave�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
static const 	int		 s_nNumShining = 30;	// ���̑���
static const D3DXVECTOR3 s_ShiningSummonPos =	// ���̏o������ʒu
D3DXVECTOR3(-120.0f, 120.0f, 200.0f);

//========================================
// �R���X�g���N�^
//========================================
CShiningWave::CShiningWave(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// ��ނ̐ݒ�
								// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// �e���̏�����
}

//========================================
// �f�X�g���N�^
//========================================
CShiningWave::~CShiningWave(void) {

}

//========================================
// ����������
// Author:KOMURO HIROMU
//========================================
void CShiningWave::Init(void) {
	//ModelIdx = RNLib::Model().Load(s_modelPaths[(int)m_Star_type]);
	//RNLib::Texture().Load();

	
}

//========================================
// �I������
// Author:KOMURO HIROMU
//========================================
void CShiningWave::Uninit(void) {

}

//========================================
// �X�V����
// Author:KOMURO HIROMU
//========================================
void CShiningWave::Update(void) {
	int nShining;    

	/*for (int nCntShin = 0; nCntShin < s_nNumShining; nCntShin++)
	{
		nShining = nCntShin % 12;
		RNLib::Polygon3D().Put(D3DXVECTOR3(s_ShiningSummonPos.x + (20.0f * nShining), s_ShiningSummonPos.x + (20.0f * nShining), m_pos.z), m_rot, false)
			->SetLighting(false)
			->SetSize(10.0f, 10.0f);
	}*/
}

//========================================
// �`�揈��
// Author:KOMURO HIROMU
//========================================
void CShiningWave::Draw(void) {


}