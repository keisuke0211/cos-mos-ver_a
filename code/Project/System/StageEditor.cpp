//========================================
// 
// ステージエディットの読み込み
// Author:KEISUKE OTONO
// 
//========================================
#include "../manager.h"
#include "csv_file.h"
#include "../Object/stage-object.h"
#include "StageEditor.h"

//========================================
// 静的変数
//========================================
CStageEditor::StageType *CStageEditor::m_StageType = NULL;
int CStageEditor::m_StageMax = 0;
const float CStageEditor::SIZE_SPACE = 23.0f;
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// コンストラクタ
//========================================
CStageEditor::CStageEditor(void)
{
	m_StageType = NULL;
	m_StageMax = 0;
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
			string sData = pFile->GetData(nRow, nLine);

			char *aDataSearch;	// データ検索用

			/*pFile->ToValue(aDataSearch, sData);*/
			/*if (!strcmp(aDataSearch, "SetStage")) { bSet = true; }
			if (!strcmp(aDataSearch, "EndStage")) { bSet = false; }
			if (!strcmp(aDataSearch, "End")) { bEnd = true; }*/

			// ステージ生成
			if (bSet)
			{
				pFile->ToValue(nType, sData);

				if (nType >= 0)
				{
					D3DXVECTOR3 pos = RNLib::Camera3D()->GetPosR();

					pos.x += ((nLineMax * -0.5f) + nLine + 0.5f) * SIZE_SPACE;
					pos.y += ((nRowMax * -0.5f) + nRow + 0.5f) * SIZE_SPACE;

					pos.z = 0.0f/* + fRand() * 4.0f*/;

					// 配置
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