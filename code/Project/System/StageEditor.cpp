//========================================
// 
// �X�e�[�W�G�f�B�b�g�̓ǂݍ���
// Author:KEISUKE OTONO
// 
//========================================
#include "../manager.h"
#include "csv_file.h"
#include "../Object/stage-object.h"
#include "StageEditor.h"

//========================================
// �ÓI�ϐ�
//========================================
CStageEditor::StageType *CStageEditor::m_StageType = NULL;
int CStageEditor::m_StageMax = 0;
const float CStageEditor::SIZE_SPACE = 23.0f;
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// �R���X�g���N�^
//========================================
CStageEditor::CStageEditor(void)
{
	m_StageType = NULL;
	m_StageMax = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CStageEditor::~CStageEditor()
{
	delete m_StageType;
	m_StageType = NULL;
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

			if (nMaxType <= 0)
			{
				nMaxType = 0;
			}

			m_StageType = new StageType[nMaxType];
			assert(m_StageType != NULL);

			m_StageMax = nMaxType;	// �ő吔�̕ۑ�
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
void CStageEditor::StageLoad(int stage)
{
	CSVFILE *pFile = new CSVFILE;

	int nStage = stage;
	bool bSet = true;
	bool bEnd = false;

	IntControl(&nStage, m_StageMax, 0);

	// �ǂݍ���
	pFile->FileLood(m_StageType[nStage].aFileName, false, false, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType = -1;				// ���

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			char *aDataSearch;	// �f�[�^�����p

			/*pFile->ToValue(aDataSearch, sData);*/
			/*if (!strcmp(aDataSearch, "SetStage")) { bSet = true; }
			if (!strcmp(aDataSearch, "EndStage")) { bSet = false; }
			if (!strcmp(aDataSearch, "End")) { bEnd = true; }*/

			// �X�e�[�W����
			if (bSet)
			{
				pFile->ToValue(nType, sData);

				if (nType >= 0)
				{
					D3DXVECTOR3 pos = RNLib::Camera3D()->GetPosR();

					pos.x += ((nLineMax * -0.5f) + nLine + 0.5f) * SIZE_SPACE;
					pos.y += ((nRowMax * -0.5f) + nRow + 0.5f) * SIZE_SPACE;

					pos.z = 0.0f/* + fRand() * 4.0f*/;

					// �z�u
					switch (nType)
					{
					case TYPE_BLOCK:
						Manager::BlockMgr()->BlockCreate(pos);
						break;
					case TYPE_TRAMPOLINE:
						Manager::BlockMgr()->TrampolineCreate(pos);
						break;
					case TYPE_THORN:

						break;
					case TYPE_LIFT:
						Manager::BlockMgr()->MoveBlockCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						break;
					case TYPE_Meteor:
						Manager::BlockMgr()->MeteorCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
						break;
					}
				}
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax)
		{
			bEnd = true;
		}
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}