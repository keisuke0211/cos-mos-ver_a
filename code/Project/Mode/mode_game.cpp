//========================================
// 
// ���[�h:�Q�[���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../main.h"
#include "../Character/player.h"
#include "../System/StageEditor.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Game�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

#define COLOR_UP   Color{45,212,140,255}
#define COLOR_DOWN Color{206,54,112,255}

CPlayer *CMode_Game::s_pPlayer = NULL;
CPlayer* CMode_Game::GetPlayer(void) { return s_pPlayer; }

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CMode_Game::CMode_Game(void) {

}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CMode_Game::~CMode_Game(void) {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Init(void) {
	CMode::Init();

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);

	Manager::BlockMgr()->Load();
	Manager::BlockMgr()->PlanetCreate(D3DXVECTOR3(00.0f, 00.0f, 300.0f), CPlanet::STAR_TYPE::BLUE);
	Manager::BlockMgr()->PlanetCreate(D3DXVECTOR3(-100.0f, -300.0f, 300.0f), CPlanet::STAR_TYPE::YELLOW);
	Manager::BlockMgr()->PlanetCreate(D3DXVECTOR3(200.0f, 300.0f, 300.0f),CPlanet::STAR_TYPE::RED);

	if (s_pPlayer == NULL)
		s_pPlayer = CPlayer::Create();

	// �Ǎ�
	/* �u���b�N	*/Manager::BlockMgr()->Load();
	/* �X�e�[�W	*/Manager::StgEd()->FileLoad();

	// �X�e�[�W����
	Manager::StgEd()->StageLoad(0);

	SetBGColor(COLOR_UP);
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Uninit(void) {
	CMode::Uninit();

	if (s_pPlayer != NULL)	{
		s_pPlayer->Uninit();
		delete s_pPlayer;
		s_pPlayer = NULL;
	}
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Update(void) {
	CMode::Update();

	if (s_pPlayer != NULL)
		s_pPlayer->Update();

	if (RNLib::Input()->KeyTrigger(DIK_RETURN))
		Manager::StgEd()->SwapStage(1);

	// �w�i(��)
	{
		float width = RNLib::Window()->GetWidth();
		float height = RNLib::Window()->GetHeight();
		RNLib::Polygon3D()->Put(D3DXVECTOR3(0.0f, -height*0.3f, 400.0f), INITD3DXVECTOR3)
			->SetLighting(false)
			->SetCol(COLOR_DOWN)
			->SetSize(width * 2.0f, height * 0.5f)
			->SetPriority(-2);
	}
}

//========================================
// �X�V����(���)
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::ProcessState(const PROCESS process) {
	switch ((STATE)m_state) {
		//----------------------------------------
		// ����
		//----------------------------------------
	case STATE::NONE: {
		switch (process) {
			// [[[ �������� ]]]
		case PROCESS::INIT: {

		}break;
			// [[[ �I������ ]]]
		case PROCESS::UNINIT: {

		}break;
			// [[[ �X�V���� ]]]
		case PROCESS::UPDATE: {

		}break;
		}
	}break;
	}
}