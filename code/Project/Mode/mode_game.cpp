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
static const float DISTANCE = 100.0f;	// ����

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

	BackGroundPut();

	if (s_pPlayer == NULL)
		s_pPlayer = CPlayer::Create();

	// �Ǎ�
	/* �u���b�N	*/Manager::BlockMgr()->Load();
	/* �X�e�[�W	*/Manager::StgEd()->FileLoad();

	// �X�e�[�W����
	Manager::StgEd()->StageLoad(0);

	SetBGColor(Color{255,119,183,255});
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

//========================================
// �w�i�̐�������
// Author:KOMURO HIROMU
//========================================
void CMode_Game::BackGroundPut(void){

	D3DXVECTOR3 *posOld[10] = {};
	D3DXVECTOR3 pos;
	CPlanet::STAR_TYPE *typeOld[(int)CPlanet::STAR_TYPE::MAX] = {};
	CPlanet::STAR_TYPE type;


	for (int nCntPut = 0; nCntPut < 10; nCntPut++)
	{
		bool bpos = false;
		bool btype = false;
		while (bpos != true)
		{
			pos = D3DXVECTOR3(rand() % 400 - 200, rand() % 400 - 200, 100);	// �ʒu�̐ݒ�

			if (nCntPut == 0)
			{
				bpos = true;
				posOld[nCntPut] = &pos;	// ���
			}
			for (int nCntpos = 0; nCntpos < nCntPut; nCntpos++)
			{
				if (posOld[nCntpos] != NULL)
				{
					if (posOld[nCntpos]->x - DISTANCE >= pos.x + DISTANCE &&
						posOld[nCntpos]->x + DISTANCE <= pos.x - DISTANCE &&
						posOld[nCntpos]->y - DISTANCE >= pos.y + DISTANCE &&
						posOld[nCntpos]->y + DISTANCE >= pos.y - DISTANCE)
					{
						bpos = false;
					}
					else
					{
						bpos = true;
						posOld[nCntPut] = &pos;	// ���
					}
				}
			}
		}
		type = (CPlanet::STAR_TYPE)(rand() % (int)CPlanet::STAR_TYPE::MAX);	// ��ނ̐ݒ�

		Manager::BlockMgr()->PlanetCreate(pos, type);	// �f���̐���
	
	}
}
