//========================================
// 
// �X�e�[�W�G�f�B�b�g�̓ǂݍ���
// Author:KEISUKE OTONO
// 
//========================================
#include "../manager.h"
#include "csv_file.h"
#include "../Object/stage-object.h"
#include "../Mode/mode_game.h"
#include "../Character/player.h"
#include "StageEditor.h"

//========================================
// �ÓI�ϐ�
//========================================
CStageEditor::StageType *CStageEditor::m_StageType = NULL;
int CStageEditor::m_nStageMax = 0;
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// �R���X�g���N�^
//========================================
CStageEditor::CStageEditor(void)
{
	m_StageType = NULL;
	m_nStageMax = 0;

	m_Info.nRow = 0;
	m_Info.nLine = 0;
	m_Info.nRowMax = 0;
	m_Info.nLineMax = 0;
	m_Info.nStageIdx = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CStageEditor::~CStageEditor()
{
	if (m_StageType != NULL)
	{
		delete m_StageType;
		m_StageType = NULL;
	}
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
			int nMax = -1;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMax);		// �ő吔

			if (nMax <= 0)
			{
				nMax = 0;
			}

			m_Info.nStageMax = nMax;
			m_StageType = new StageType[nMax];
			assert(m_StageType != NULL);

			m_nStageMax = nMax;	// �ő吔�̕ۑ�
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

	m_Info.nStageIdx = stage;
	bool bSet = true;
	bool bEnd = false;

	IntControl(&m_Info.nStageIdx, m_nStageMax, 0);

	// �ǂݍ���
	pFile->FileLood(m_StageType[m_Info.nStageIdx].aFileName, false, false, ',');

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
			if (bEnd) { break; }
			char *aDataSearch = NULL;	// �f�[�^�����p
			string sData = pFile->GetData(nRow, nLine);
			char* cstr = new char[sData.size() + 1]; // �������m��
			std::char_traits<char>::copy(cstr, sData.c_str(), sData.size() + 1);
			aDataSearch = cstr;
			

			if (!strcmp(aDataSearch, "End")) { bEnd = true;}
			else if (!strcmp(aDataSearch, "StageWidth"))
			{
				nLine += 4;
				int nWidth;
				
				ToData(nWidth, pFile, nRow, nLine);
				m_Info.nLine = 0;
				m_Info.nLineMax = nWidth;
			}
			else if (!strcmp(aDataSearch, "StageHeight"))
			{
				nLine += 4;
				int nHeight;

				ToData(nHeight, pFile, nRow, nLine);
				m_Info.nRow = 0;
				m_Info.nRowMax = nHeight;
			}
			else if (!strcmp(aDataSearch, "SetStage")) 
			{ 
				nRow++;
				// �X�e�[�W����
				while (1)
				{
					char *aDataSearch = NULL;	// �f�[�^�����p
					string sData = pFile->GetData(nRow, nLine);
					char* cstr = new char[sData.size() + 1]; // �������m��
					std::char_traits<char>::copy(cstr, sData.c_str(), sData.size() + 1);
					aDataSearch = cstr;

					if (!strcmp(aDataSearch, "EndStage")) {
						if (cstr != NULL){
							delete[] cstr;
							cstr = NULL;
						}
						break; 
					}
					else
					{
						for (m_Info.nLine = 0; m_Info.nLine < m_Info.nLineMax; m_Info.nLine++)
						{
							int nType = -1;
							ToData(nType, pFile, nRow, m_Info.nLine);
							SetStage(nType);
						}
						nRow++;
						m_Info.nRow++;
					}

					if (cstr != NULL)
					{
						delete[] cstr;
						cstr = NULL;
					}
				}
				
			}

			if (cstr != NULL)
			{
				delete[] cstr;
				cstr = NULL;
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax || bEnd)
		{
			break;
		}
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �X�e�[�W����
//========================================
void CStageEditor::SetStage(int nType)
{
	if (nType >= 0)
	{
		float fSizeX = CStageObject::SIZE_OF_1_SQUARE;
		float fSizeY = CStageObject::SIZE_OF_1_SQUARE;
		D3DXVECTOR3 pos = RNLib::Camera3D()->GetPosR();

		pos.x += ((m_Info.nLineMax * -0.5f) + m_Info.nLine + 0.5f) * fSizeX;
		pos.y -= ((m_Info.nRowMax * -0.5f) + m_Info.nRow + 0.5f) * fSizeY;

		pos.z = 0.0f/* + fRand() * 4.0f*/;

		// �z�u
		switch (nType)
		{
		case TYPE_BLOCK:
			Manager::BlockMgr()->BlockCreate(pos);
			break;
			break;
		case TYPE_TRAMPOLINE:
			pos.x += fSizeX / 2;
			Manager::BlockMgr()->TrampolineCreate(pos);
			break;
		case TYPE_SPIKE:
			Manager::BlockMgr()->SpikeCreate(pos);
			break;
		case TYPE_LIFT:
			Manager::BlockMgr()->MoveBlockCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),0.0f);
			break;
		case TYPE_Meteor:
			pos.x += fSizeX;
			pos.y -= fSizeY;
			Manager::BlockMgr()->MeteorCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case TYPE_FILL_BLOCK_11:
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_1x1);
			break;
		case TYPE_FILL_BLOCK_22:
			pos.x += fSizeX * 0.5f;
			pos.y -= fSizeY * 0.5f;
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_2x2);
			break;
		case TYPE_FILL_BLOCK_33:
			pos.x += fSizeX;
			pos.y -= fSizeY;
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_3x3);
			break;
		case TYPE_FILL_BLOCK_44:
			pos.x += fSizeX * 1.5f;
			pos.y -= fSizeY * 1.5f;
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_4x4);
			break;
		case TYPE_PLAYER_0:
			pos.y += fSizeY * 0.5f;
			CMode_Game::GetPlayer()->SetPos(0, pos);
			break;
		case TYPE_PLAYER_1:
			pos.y += -fSizeY * 0.5f;
			CMode_Game::GetPlayer()->SetPos(1, pos);
			break;
		case TYPE_PARTS:
			Manager::BlockMgr()->PartsCreate(pos);
			break;
		case TYPE_GOAL:
			pos.x += fSizeX;
			pos.y -= fSizeY;
			Manager::BlockMgr()->RocketCreate(pos);
			break;
		}
	}
}

//========================================
// �X�e�[�W�؂�ւ�
//========================================
void CStageEditor::SwapStage(int nStageIdx)
{
	if (m_Info.nStageIdx != nStageIdx)
	{
		Manager::BlockMgr()->ReleaseAll();

		if (nStageIdx < m_nStageMax)
		{
			StageLoad(nStageIdx);
		}
	}
}

//========================================
// �ϊ�
//========================================

// int
bool CStageEditor::ToData(int &val, CSVFILE *pFile, int nRow, int nLine)
{
	try
	{
		string sData = pFile->GetData(nRow, nLine);
		val = stoi(sData);
		return true;
	}
	catch (...)
	{
		return false;
	}
}