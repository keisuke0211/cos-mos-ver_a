//========================================
// 
// �u���b�N�}�l�[�W���[
// Author:KEISUKE OTONO
// 
//========================================
// *** block-manager.h ***
//========================================
#include "block-manager.h"

//========================================
// �ÓI�ϐ�
//========================================
CBlockMgr::BlockType *CBlockMgr::m_pBlockType = NULL;
const char* CBlockMgr::BLOCK_INFO_FILE = "data\\GAMEDATA\\BLOCK\\BLOCK_DATA.txt";

//========================================
// �R���X�g���N�^
//========================================
CBlockMgr::CBlockMgr(void)
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CBlockMgr::~CBlockMgr()
{
	
}

//========================================
// ������
//========================================
void CBlockMgr::Init(void)
{
	CListMgr::Init();
}

//========================================
// �I��
//========================================
void CBlockMgr::Uninit(void)
{
	
}

//========================================
// �X�V
//========================================
void CBlockMgr::Update(void)
{
	CListMgr::Update();
}

//========================================
// �ǂݍ���
//========================================
void CBlockMgr::Load(void)
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

// �u���b�N
CBlock *CBlockMgr::BlockCreate(int type, D3DXVECTOR3 pos)
{
	CBlock *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CBlock;

	// ����������
	pObj->Init();
	pObj->SetModelIdx(m_pBlockType[type].nModelIdx);
	pObj->SetPos(pos);

	return pObj;
}

// �g�����|����
CTrampoline *CBlockMgr::TrampolineCreate(int type, D3DXVECTOR3 pos)
{
	CTrampoline *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CTrampoline;

	// ����������
	pObj->Init();
	pObj->SetModelIdx(m_pBlockType[type].nModelIdx);
	pObj->SetPos(pos);

	return pObj;
}

// �g�����|����
CMeteor *CBlockMgr::MeteorCreate(int type, D3DXVECTOR3 pos)
{
	CMeteor *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CMeteor;

	// ����������
	pObj->Init();
	pObj->SetModelIdx(m_pBlockType[type].nModelIdx);

	return pObj;
}
