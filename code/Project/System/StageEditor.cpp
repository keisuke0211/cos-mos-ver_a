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
CStageEditor::StageColor CStageEditor::m_StageColor = {NULL};
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// コンストラクタ
//========================================
CStageEditor::CStageEditor(void)
{
	if (m_StageType != NULL)
	{
		delete[] m_StageType;
		m_StageType = NULL;
	}

	m_StageType = NULL;
	m_StageColor.Block = INITCOLOR;
	m_StageColor.FillBlock = INITCOLOR;
	m_StageColor.Lift = INITCOLOR;
	m_StageColor.Meteor = INITCOLOR;
	m_StageColor.Spike = INITCOLOR;
	m_StageColor.Trampoline = INITCOLOR;

	m_Info.nRow = 0;
	m_Info.nLine = 0;
	m_Info.nRowMax = 0;
	m_Info.nLineMax = 0;
	m_Info.nStageIdx = 0;
	m_Info.nStageMax = 0;
}

//========================================
// デストラクタ
//========================================
CStageEditor::~CStageEditor()
{
	if (m_StageType != NULL)
	{
		delete[] m_StageType;
		m_StageType = NULL;
	}
}

//========================================
// 終了処理
// Author:KEISUKE OTONO
//========================================
void CStageEditor::Uninit(void)
{
	if (m_StageType != NULL)
	{
		delete[] m_StageType;
		m_StageType = NULL;
	}
}

//========================================
// ファイル読み込み
// Author:KEISUKE OTONO
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
			int nMax = -1;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMax);		// 最大数

			if (nMax <= 0)
			{
				nMax = 0;
			}

			m_Info.nStageMax = nMax;
			m_StageType = new StageType[nMax];
			assert(m_StageType != NULL);

			m_Info.nStageMax = nMax;	// 最大数の保存
		}
		else if (!strcmp(aDataSearch, "STAGE"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_StageType[nCntStage].aFileName[0]);	// ファイル名
			fscanf(pFile, "%s", &m_StageType[nCntStage].aTexFile[0]);	// ステージ画像
			fscanf(pFile, "%s", &m_StageType[nCntStage].aStageName[0]);	// ステージ名

			nCntStage++;
		}
	}
}

//========================================
// ステージ読み込み
// Author:KEISUKE OTONO
//========================================
void CStageEditor::StageLoad(int stage)
{
	//プレイヤー初期化
	CMode_Game::GetPlayer()->Init();

	CSVFILE *pFile = new CSVFILE;

	m_Info.nStageIdx = stage;
	bool bSet = true;
	bool bEnd = false;

	IntControl(&m_Info.nStageIdx, m_Info.nStageMax, 0);

	// 読み込み
	pFile->FileLood(m_StageType[m_Info.nStageIdx].aFileName, false, false, ',');

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
			if (bEnd) { break; }
			char *aDataSearch = NULL;	// データ検索用
			string sData = pFile->GetData(nRow, nLine);
			char* cstr = new char[sData.size() + 1]; // メモリ確保
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
			else if (!strcmp(aDataSearch, "SetColor"))
			{
				while (1)
				{
					nLine = 0;
					nRow++;
					char *aDataSearch = NULL;	// データ検索用
					string sData = pFile->GetData(nRow, nLine);
					char* cstr = new char[sData.size() + 1]; // メモリ確保
					std::char_traits<char>::copy(cstr, sData.c_str(), sData.size() + 1);
					aDataSearch = cstr;

					if (!strcmp(aDataSearch, "EndColor")) {
						if (cstr != NULL) {
							delete[] cstr;
							cstr = NULL;
						}
						break;
					}
					else if (!strcmp(aDataSearch, "Block"))
					{
						nLine += 4;
						ToData(m_StageColor.Block.r, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Block.g, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Block.b, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Block.a, pFile, nRow, nLine); nLine++;
					}
					else if (!strcmp(aDataSearch, "Trampoline"))
					{
						nLine += 4;
						ToData(m_StageColor.Trampoline.r, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Trampoline.g, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Trampoline.b, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Trampoline.a, pFile, nRow, nLine); nLine++;
					}
					else if (!strcmp(aDataSearch, "Spike"))
					{
						nLine += 4;
						ToData(m_StageColor.Spike.r, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Spike.g, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Spike.b, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Spike.a, pFile, nRow, nLine); nLine++;
					}
					else if (!strcmp(aDataSearch, "Lift"))
					{
						nLine += 4;
						ToData(m_StageColor.Lift.r, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Lift.g, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Lift.b, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Lift.a, pFile, nRow, nLine); nLine++;
					}
					else if (!strcmp(aDataSearch, "Meteor"))
					{
						nLine += 4;
						ToData(m_StageColor.Meteor.r, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Meteor.g, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Meteor.b, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.Meteor.a, pFile, nRow, nLine); nLine++;
					}
					else if (!strcmp(aDataSearch, "FillBlock"))
					{
						nLine += 4;
						ToData(m_StageColor.FillBlock.r, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.FillBlock.g, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.FillBlock.b, pFile, nRow, nLine); nLine++;
						ToData(m_StageColor.FillBlock.a, pFile, nRow, nLine); nLine++;
					}

					if (cstr != NULL)
					{
						delete[] cstr;
						cstr = NULL;
					}
				}
			}
			else if (!strcmp(aDataSearch, "SetStage"))
			{
				nRow++;
				// ステージ生成
				while (1)
				{
					char *aDataSearch = NULL;	// データ検索用
					string sData = pFile->GetData(nRow, nLine);
					char* cstr = new char[sData.size() + 1]; // メモリ確保
					std::char_traits<char>::copy(cstr, sData.c_str(), sData.size() + 1);
					aDataSearch = cstr;

					if (!strcmp(aDataSearch, "EndStage")) {
						if (cstr != NULL) {
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

		// 最大数に達したら返す
		if (nRow == nRowMax || bEnd)
		{
			break;
		}
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}

//========================================
// ステージ生成
// Author:KEISUKE OTONO
//========================================
void CStageEditor::SetStage(int nType)
{
	if (nType >= 0)
	{
		float fSizeX = CStageObject::SIZE_OF_1_SQUARE;
		float fSizeY = CStageObject::SIZE_OF_1_SQUARE;
		D3DXVECTOR3 pos = RNLib::Camera3D().GetPosR();

		pos.x += ((m_Info.nLineMax * -0.5f) + m_Info.nLine + 0.5f) * fSizeX;
		pos.y -= ((m_Info.nRowMax * -0.5f) + m_Info.nRow + 0.5f) * fSizeY;

		pos.z = 0.0f/* + fRand() * 4.0f*/;

		// 配置
		switch (nType)
		{
		case TYPE_BLOCK:
			Manager::BlockMgr()->BlockCreate(pos,m_StageColor.Block);
			break;
		case TYPE_TRAMPOLINE:
			pos.x += fSizeX / 2;
			Manager::BlockMgr()->TrampolineCreate(pos, m_StageColor.Trampoline);
			break;
		case TYPE_SPIKE:
			Manager::BlockMgr()->SpikeCreate(pos, m_StageColor.Spike);
			break;
		case TYPE_LIFT:
			Manager::BlockMgr()->MoveBlockCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),0.0f, m_StageColor.Lift);
			break;
		case TYPE_Meteor:
			pos.x += fSizeX;
			pos.y -= fSizeY;
			Manager::BlockMgr()->MeteorCreate(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_StageColor.Meteor);
			break;
		case TYPE_FILL_BLOCK_11:
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_1x1, m_StageColor.FillBlock);
			break;
		case TYPE_FILL_BLOCK_22:
			pos.x += fSizeX * 0.5f;
			pos.y -= fSizeY * 0.5f;
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_2x2, m_StageColor.FillBlock);
			break;
		case TYPE_FILL_BLOCK_33:
			pos.x += fSizeX;
			pos.y -= fSizeY;
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_3x3, m_StageColor.FillBlock);
			break;
		case TYPE_FILL_BLOCK_44:
			pos.x += fSizeX * 1.5f;
			pos.y -= fSizeY * 1.5f;
			Manager::BlockMgr()->FillBlockCreate(pos, CFillBlock::FILL_TYPE::FILL_4x4, m_StageColor.FillBlock);
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
// ステージ切り替え
// Author:KEISUKE OTONO
//========================================
void CStageEditor::SwapStage(int nStageIdx)
{
	if (m_Info.nStageIdx != nStageIdx)
	{
		Manager::BlockMgr()->ReleaseAll();

		if (nStageIdx < m_Info.nStageMax)
		{
			StageLoad(nStageIdx);
		}
	}
}

//========================================
// 変換
// Author:KEISUKE OTONO
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