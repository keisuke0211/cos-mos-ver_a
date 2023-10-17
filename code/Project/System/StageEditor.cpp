//========================================
// 
// �X�e�[�W�G�f�B�b�g�̓ǂݍ���
// Author:KEISUKE OTONO
// 
//========================================
#include "../manager.h"
#include "StageEditor.h"

//========================================
// �ÓI�ϐ�
//========================================
CStageEditor::StageType *CStageEditor::m_StageType = NULL;
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// �R���X�g���N�^
//========================================
CStageEditor::CStageEditor(void)
{
	m_StageType = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CStageEditor::~CStageEditor()
{

}

//========================================
// ������
//========================================
HRESULT CStageEditor::Init(void)
{
	m_StageType = NULL;
	return S_OK;
}

//========================================
// �I��
//========================================
void CStageEditor::Uninit(void)
{
	delete m_StageType;
	m_StageType = NULL;
}

//========================================
// �X�V
//========================================
void CStageEditor::Update(void)
{
	
}

//========================================
// �t�@�C���ǂݍ���
//========================================
void CStageEditor::FileLoad(void)
{
	int nCntStage = 0;
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(STAGE_INFO_FILE, "r");

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

		if (!strcmp(aDataSearch, "NUM_STAGE"))
		{
			int nMaxType = -1;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMaxType);		// �ő吔
			m_StageType = new StageType[nMaxType];
			assert(m_StageType != NULL);
		}
		else if (!strcmp(aDataSearch, "STAGE"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_StageType[nCntStage].aFileName[0]);	// �t�@�C����

			nCntStage++;
		}
	}
}

//========================================
// �X�e�[�W�ǂݍ���
//========================================
void CStageEditor::StageLoad(const char *pFileName)
{

}