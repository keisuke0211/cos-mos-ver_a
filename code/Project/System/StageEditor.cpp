//========================================
// 
// ステージエディットの読み込み
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
// 静的変数
//========================================
CStageEditor::StageType *CStageEditor::m_StageType = NULL;
int CStageEditor::m_StageMax = 0;
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// コンストラクタ
//========================================
CStageEditor::CStageEditor(void)
{
	m_StageType = NULL;
	m_StageMax = 0;

	m_Info.nRow = 0;
	m_Info.nLine = 0;
	m_Info.nRowMax = 0;
	m_Info.nLineMax = 0;
}

//========================================
// デストラクタ
//========================================
CStageEditor::~CStageEditor()
{
	delete m_StageType;
	m_StageType = NULL;
}

//========================================
// ファイル読み込み
//========================================
void CStageEditor::FileLoad(void)
{
	int nCntStage = 0;
	char aDataSearch[TXT_MAX];	// データ検索用

	// ファイルの読み込み
	FILE *pFile = fopen(STAGE_INFO_FILE, "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return;
	}

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "END"))
		{// 読み込みを終了
			fclose(pFile);
			break;
		}
		if (aDataSearch[0] == '#')
		{// 折り返す
			continue;
		}

		if (!strcmp(aDataSearch, "NUM_STAGE"))
		{
			int nMaxType = -1;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMaxType);		// 最大数

			if (nMaxType <= 0)
			{
				nMaxType = 0;
			}

			m_StageType = new StageType[nMaxType];
			assert(m_StageType != NULL);

			m_StageMax = nMaxType;	// 最大数の保存
		}
		else if (!strcmp(aDataSearch, "STAGE"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_StageType[nCntStage].aFileName[0]);	// ファイル名

			nCntStage++;
		}
	}
}

//========================================
// ステージ読み込み
//========================================
void CStageEditor::StageLoad(int stage)
{
	CSVFILE *pFile = new CSVFILE;

	int nStage = stage;
	bool bSet = true;
	bool bEnd = false;

	IntControl(&nStage, m_StageMax, 0);

	// 読み込み
	pFile->FileLood(m_StageType[nStage].aFileName, false, false, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// 各データに代入
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 配置情報の生成
		int nType = -1;				// 種類

		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			char *aDataSearch;	// データ検索用
			ToData(aDataSearch, pFile, nRow, nLine);

			if (!strcmp(aDataSearch, "StageWidth"))
			{
				nLine += 4;
				int nWidth;
				
				ToData(nWidth, pFile, nRow, nLine);
				m_Info.nLineMax = nWidth;
			}
			else if (!strcmp(aDataSearch, "StageHeight"))
			{
				nLine += 4;
				int nHeight;

				ToData(nHeight, pFile, nRow, nLine);
				m_Info.nRowMax = nHeight;
			}
			else if (!strcmp(aDataSearch, "SetStage")) 
			{ 
				// ステージ生成
				while (1)
				{
					char *aDataSearch;	// データ検索用
					ToData(aDataSearch, pFile, nRow, nLine);

					if (!strcmp(aDataSearch, "EndStage")) { break; }
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
				}
				
			}
			
			if (!strcmp(aDataSearch, "End")) { bEnd = true; }
		}

		// 最大数に達したら返す
		if (nRow == nRowMax)
		{
			bEnd = true;
		}
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}

//========================================
// ステージ生成
//========================================
void CStageEditor::SetStage(int nType)
{
	if (nType >= 0)
	{
		int nSizeX = CStageObject::SIZE_OF_1_SQUARE;
		int nSizeY = CStageObject::SIZE_OF_1_SQUARE;
		D3DXVECTOR3 pos = RNLib::Camera3D()->GetPosR();

		pos.x += ((m_Info.nLineMax * -0.5f) + m_Info.nLine + 0.5f) * nSizeX;
		pos.y -= ((m_Info.nRowMax * -0.5f) + m_Info.nRow + 0.5f) * nSizeY;

		pos.z = 0.0f/* + fRand() * 4.0f*/;

		// 配置
		switch (nType)
		{
		case TYPE_BLOCK:
			Manager::BlockMgr()->BlockCreate(pos);
			break;
		case TYPE_TRAMPOLINE:
			pos.x += nSizeX / 2;
			Manager::BlockMgr()->TrampolineCreate(pos);
			break;
		case TYPE_SPIKE:
			Manager::BlockMgr()->SpikeCreate(pos);
			break;
		case TYPE_LIFT:
			Manager::BlockMgr()->MoveBlockCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case TYPE_Meteor:
			Manager::BlockMgr()->MeteorCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case TYPE_PLAYER_0:
			pos.y += 10.0f;
			CMode_Game::GetPlayer()->SetPos(0, pos);
			break;
		case TYPE_PLAYER_1:
			pos.y += -10.0f;
			CMode_Game::GetPlayer()->SetPos(1, pos);
			break;
		case TYPE_PARTS:
			Manager::BlockMgr()->PartsCreate(pos);
			break;
		case TYPE_GOAL:
			break;
		}
	}
}

//========================================
// 変換
//========================================

// char型
bool CStageEditor::ToData(char* &val, CSVFILE *pFile, int nRow, int nLine)
{
	try
	{
		string sData = pFile->GetData(nRow, nLine);
		char* cstr = new char[sData.size() + 1]; // メモリ確保

		char_traits<char>::copy(cstr, sData.c_str(), sData.size() + 1);

		val = cstr;
		return true;
	}
	catch (...)
	{
		return false;
	}
}

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