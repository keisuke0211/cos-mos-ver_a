//========================================
// 
// �X�e�[�W�I�u�W�F�N�g�}�l�[�W���[�̏���
// Author:KEISUKE OTONO
// Arrange:RIKU NISHIMURA
// 
//========================================
#include "../main.h"

//========================================
// �ÓI�ϐ�
//========================================
CStageObjectMgr::BlockType *CStageObjectMgr::m_pBlockType = NULL;
const char* CStageObjectMgr::BLOCK_INFO_FILE = "data\\GAMEDATA\\BLOCK\\BLOCK_DATA.txt";

//========================================
// �R���X�g���N�^
//========================================
CStageObjectMgr::CStageObjectMgr(void)
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CStageObjectMgr::~CStageObjectMgr()
{
	delete m_pBlockType;
	m_pBlockType = NULL;
}

//========================================
// �X�V
//========================================
void CStageObjectMgr::Update(void)
{
	
}

//========================================
// �ǂݍ���
//========================================
void CStageObjectMgr::Load(void)
{
	int nCntModel = 0;
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(BLOCK_INFO_FILE, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_MODEL"))
		{
			int nMaxType = -1;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMaxType);		// �ő吔
			m_pBlockType = new BlockType[nMaxType];
			assert(m_pBlockType != NULL);
		}
		else if (!strcmp(aDataSearch, "MODEL"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_pBlockType[nCntModel].aFileName[0]);	// �t�@�C����

			m_pBlockType[nCntModel].nModelIdx = RNLib::Model()->Load(m_pBlockType[nCntModel].aFileName);	// ���f���ԍ�
			nCntModel++;
		}
	}
}

//========================================
// �e����
//========================================

//========================================
// �u���b�N
//========================================
CBlock *CStageObjectMgr::BlockCreate(D3DXVECTOR3 pos)
{
	CBlock *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CBlock;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);

	return pObj;
}

//========================================
// �u���b�N(����@��)
//========================================
CFillBlock *CStageObjectMgr::FillBlockCreate(D3DXVECTOR3 pos,CFillBlock::FILL_TYPE type)
{
	//�v���C���[�C���X�^���X�̐���
	CFillBlock *pObj = new CFillBlock;

	//����������
	pObj->Init(type);

	pObj->SetPos(pos);

	//�v���C���[��Ԃ�
	return pObj;
}

//========================================
// ��
//========================================
CSpike *CStageObjectMgr::SpikeCreate(D3DXVECTOR3 pos)
{
	CSpike *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CSpike;

	// ����������
	pObj->Init();

	if (pos.y <= 0) {
		pObj->SetRot(D3DXVECTOR3(0.0f,0.0f, 3.24f));
		pos.y += CStageObject::SIZE_OF_1_SQUARE * 0.25f;
	}
	else {
		pos.y -= CStageObject::SIZE_OF_1_SQUARE * 0.25f;
	}

	pObj->SetPos(pos);
	
	return pObj;
}

//========================================
// �g�����|����
//========================================
CTrampoline *CStageObjectMgr::TrampolineCreate(D3DXVECTOR3 pos)
{
	CTrampoline *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CTrampoline;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);

	return pObj;
}

//========================================
// 覐�
//========================================
CMeteor *CStageObjectMgr::MeteorCreate(D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	CMeteor *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CMeteor;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);
	pObj->SetMove(move);

	return pObj;
}

//========================================
// �ړ���
//========================================
CMoveBlock *CStageObjectMgr::MoveBlockCreate(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRefdef)
{
	CMoveBlock *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CMoveBlock;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);
	pObj->SetMove(move);
	pObj->SetRefdef(fRefdef);

	return pObj;
}

//========================================
// �p�[�c
//========================================
CParts *CStageObjectMgr::PartsCreate(D3DXVECTOR3 pos)
{
	CParts *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CParts;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);

	return pObj;
}

//========================================
// ���P�b�g
//========================================
CRocket *CStageObjectMgr::RocketCreate(D3DXVECTOR3 pos)
{
	CRocket *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CRocket;

	// ����������
	pObj->Init();
	pObj->SetPos(pos);

	if (pos.y <= 0)
	{
		pObj->SetRot(D3DXVECTOR3(0.0f, 0.0f, 3.24f));
	}

	return pObj;
}

//========================================
// �f��
//========================================
CPlanet *CStageObjectMgr::PlanetCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CPlanet::STAR_TYPE type, Color col)
{
	CPlanet *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CPlanet;

	// ����������
	pObj->SetType(type);
	pObj->SetPos(pos);
	pObj->SetCol(col);
	pObj->SetRot(rot);
	pObj->Init();
	

	return pObj;
}

//========================================
// ��
//========================================
CStar *CStageObjectMgr::StarCreate(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CStar *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CStar;

	// ����������
	pObj->SetPos(pos);
	pObj->SetRot(rot);
	pObj->Init();


	return pObj;
}
//========================================
// �g�ł�
//========================================
CShiningWave *CStageObjectMgr::ShiningWaveCreate(void)
{
	CShiningWave *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CShiningWave;

	// ����������
	pObj->Init();


	return pObj;
}
//========================================
// �ړ���
//========================================
CRoadTripLaser *CStageObjectMgr::RoadTripLaserCreate(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRefdef)
{
	CRoadTripLaser *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CRoadTripLaser;

	// ����������
	pObj->SetPos(pos);
	pObj->SetMove(move);
	pObj->SetRefdef(fRefdef);
	pObj->Init();
	

	return pObj;
}