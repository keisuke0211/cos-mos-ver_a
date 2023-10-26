//========================================
// 
// ���[�h:�Q�[���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../main.h"
#include "../Character/player.h"
#include "../System/StageEditor.h"
#include "../System/words/font-text.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Game�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================
#define COLOR_UP   Color{45,212,140,255}
#define COLOR_DOWN Color{206,54,112,255}
static const int s_PlanetMaxSummon = 8;		// �o������ʒu�̍ő吔
static const int s_StarMaxSummon = 10;		// �o������ʒu�̍ő吔
static const D3DXVECTOR3 s_PlanetSummonPos[s_PlanetMaxSummon] = {	// �f���̏o������ʒu
	D3DXVECTOR3(-300.0f, 300.0f, 300.0f),
	D3DXVECTOR3(0.0f,	 200.0f, 300.0f),
	D3DXVECTOR3(200.0f,  300.0f, 300.0f),
	D3DXVECTOR3(-100.0f, 100.0f,   300.0f),
	D3DXVECTOR3(100.0f,	 100.0f,   300.0f),
	D3DXVECTOR3(-300.0f, -200.0f,300.0f),
	D3DXVECTOR3(0.0f,	 -200.0f,300.0f),
	D3DXVECTOR3(100.0f,  -300.0f,300.0f),
};
static const D3DXVECTOR3 s_StarSummonPos[s_StarMaxSummon] = {	// ���̏o������ʒu
	D3DXVECTOR3(-300.0f, 300.0f, 500.0f),
	D3DXVECTOR3(0.0f,	 200.0f, 500.0f),
	D3DXVECTOR3(200.0f,  300.0f, 500.0f),
	D3DXVECTOR3(-100.0f, 100.0f, 500.0f),
	D3DXVECTOR3(100.0f,	 100.0f, 500.0f),
	D3DXVECTOR3(-300.0f, 200.0f,500.0f),
	D3DXVECTOR3(0.0f,	 -200.0f,500.0f),
	D3DXVECTOR3(-400.0f, -300.0f,500.0f),
	D3DXVECTOR3(400.0f,  -100.0f ,500.0f),
	D3DXVECTOR3(500.0f,  0.0f ,500.0f),
};
CPlayer *CMode_Game::s_pPlayer = NULL;
CPlayer* CMode_Game::GetPlayer(void) { return s_pPlayer; }
int CMode_Game::m_nStageIdx = 0;

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

	// �J�ڐݒ�
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// �J�����̎��_/�����_��ݒ�
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ��Ԑݒ�
	SetState((int)STATE::NONE);

	Manager::BlockMgr()->Load();
	Manager::BlockMgr()->MoveBlockCreate(D3DXVECTOR3(-250.0f, -10.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), 50.0f);
	Manager::BlockMgr()->ShiningWaveCreate();
	Manager::BlockMgr()->RoadTripLaserCreate(D3DXVECTOR3(250.0f, -10.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), 50.0f);

	BackGroundPut(Color{ 100,100,100,255 }, Color{ 100,100,100,255 });

	if (s_pPlayer == NULL)
		s_pPlayer = CPlayer::Create();

	// �Ǎ�
	/* �u���b�N	*/Manager::BlockMgr()->Load();

	// �X�e�[�W����
	Manager::StgEd()->StageLoad(m_nStageIdx);

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

	Manager::BlockMgr()->ReleaseAll();
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CMode_Game::Update(void) {
	CMode::Update();

	if (m_state != (int)STATE::PAUSE)
	{
		if (RNLib::Input()->GetKeyTrigger(DIK_P))
		{
			SetState((int)STATE::PAUSE);
		}

		if (s_pPlayer != NULL)
			s_pPlayer->Update();
	}

	if (RNLib::Input()->GetKeyTrigger(DIK_SPACE) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		Manager::Transition(CMode::TYPE::RESULT, CTransition::TYPE::FADE);

	// �w�i(��)
	{
		float width = RNLib::Window()->GetWidth();
		float height = RNLib::Window()->GetHeight();
		RNLib::Polygon3D()->Put(D3DXVECTOR3(0.0f, -height*0.25f, 400.0f), INITD3DXVECTOR3)
			->SetLighting(false)
			->SetCol(COLOR_DOWN)
			->SetSize(width * 2.0f, height * 0.5f)
			->SetPriority(-2)
			->SetZTest(false);
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
	case STATE::PAUSE: {
		switch (process) {
			// [[[ �������� ]]]
		case PROCESS::INIT: {
			PauseCreate();
		}break;
			// [[[ �I������ ]]]
		case PROCESS::UNINIT: {
			for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
			{
				if (m_Menu[nCnt] != NULL)
				{
					m_Menu[nCnt]->Uninit();
					m_Menu[nCnt] = NULL;
				}
			}
		}break;
			// [[[ �X�V���� ]]]
		case PROCESS::UPDATE: {
			PauseMenu();
			PauseSelect();
		}break;
		}
	}break;
	}
}

//========================================
// �w�i�̐�������
// Author:KOMURO HIROMU
//========================================
void CMode_Game::BackGroundPut(Color mincol, Color addcol) {

	D3DXVECTOR3 Planpos,Starpos,rot;
	Color col;
	CPlanet::STAR_TYPE type;

	for (int nCntPut = 0; nCntPut < s_PlanetMaxSummon; nCntPut++)
	{
		// �f���̐ݒ�
		Planpos = s_PlanetSummonPos[nCntPut];	// �o������ʒu�̐ݒ�
		Planpos += D3DXVECTOR3(rand() % 100 - 100, rand() % 100 - 100, rand() % 150 - 50);	// �ʒu�̐ݒ�

		type = (CPlanet::STAR_TYPE)(rand() % (int)CPlanet::STAR_TYPE::MAX);	// ��ނ̐ݒ�
		col = Color{ mincol.r + rand() % addcol.r,mincol.g + rand() % addcol.g,mincol.b + rand() % addcol.b,255 };	// �F�̐ݒ�
		rot = D3DXVECTOR3(rand() % 6 - 3, rand() % 6 - 3, rand() % 6 - 3);	// �����̐ݒ�
		//Manager::BlockMgr()->PlanetCreate(Planpos, rot, type, col);	// �f���̐���
	}

	for (int nCntPut = 0; nCntPut < s_StarMaxSummon; nCntPut++)
	{
		// ���̐ݒ�
		Starpos = s_StarSummonPos[nCntPut];	// �o������ʒu�̐ݒ�
		Starpos += D3DXVECTOR3(rand() % 50 - 50, rand() % 50 - 50, 0.0f);	// �ʒu�̐ݒ�

		//Manager::BlockMgr()->StarCreate(Starpos, INITD3DXVECTOR3);	// ���̐���
	}
}

//========================================
// �|�[�Y�����̏���
// Author:KEISUKE OTONO
//========================================
void CMode_Game::PauseCreate(void)
{
	FormFont pFont = { INITCOLOR,45.0f,1,1,-1, };

	m_Menu[0] = CFontText::Create(CFontText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 200.0f, 0.0f), D3DXVECTOR2(460.0f, 100.0f),
		"������", CFont::FONT_ROND_B, &pFont);

	m_Menu[1] = CFontText::Create(CFontText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 350.0f, 0.0f), D3DXVECTOR2(460.0f, 100.0f),
		"���X�^�[�g", CFont::FONT_ROND_B, &pFont);

	m_Menu[2] = CFontText::Create(CFontText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 500.0f, 0.0f), D3DXVECTOR2(460.0f, 100.0f),
		"�^�C�g����ʂɖ߂�", CFont::FONT_ROND_B, &pFont);
}

//========================================
// �|�[�Y���j���[�̏���
// Author:KEISUKE OTONO
//========================================
void CMode_Game::PauseMenu(void)
{
	// �F
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			if (nCnt == m_nSelect)
			{
				m_Menu[nCnt]->SetBoxColor(Color{ 0,255,0,255 });
			}
			else
			{
				m_Menu[nCnt]->SetBoxColor(INITCOLOR);
			}
		}
	}

	// -- ���j���[�I�� ---------------------------
	if (RNLib::Input()->GetKeyTrigger(DIK_W) || RNLib::Input()->GetKeyTrigger(DIK_UP) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::UP) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::UP))
	{
		m_nSelect--;
	}
	else if (RNLib::Input()->GetKeyTrigger(DIK_S) || RNLib::Input()->GetKeyTrigger(DIK_DOWN) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::DOWN) || RNLib::Input()->GetStickAngleTrigger(CInput::STICK::LEFT, CInput::INPUT_ANGLE::DOWN))
	{
		m_nSelect++;
	}

	// ���[�v����
	IntLoopControl(&m_nSelect, MENU_MAX, 0);
}

//========================================
// �|�[�Y�I���̏���
// Author:KEISUKE OTONO
//========================================
void CMode_Game::PauseSelect(void)
{
	if ((RNLib::Input()->GetKeyTrigger(DIK_RETURN) || RNLib::Input()->GetButtonTrigger(CInput::BUTTON::A)) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
	{
		switch (m_nSelect)
		{
		case MENU_RESUME:
			SetState((int)STATE::NONE);
			break;
		case MENU_RESET:
			Manager::Transition(CMode::TYPE::GAME, CTransition::TYPE::FADE);
			break;
		case MENU_TITLE:
			Manager::Transition(CMode::TYPE::TITLE, CTransition::TYPE::FADE);
			break;
		}

		ProcessState(PROCESS::UNINIT);
	}
}