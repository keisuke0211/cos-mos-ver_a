//========================================
// 
// ステージエディットの読み込み
// Author:KEISUKE OTONO
// 
//========================================
#include "../manager.h"
#include "StageEditor.h"

//========================================
// 静的変数
//========================================
CStageEditor::StageType *CStageEditor::m_StageType = NULL;
const char* CStageEditor::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE\\STAGE_FILE.txt";

//========================================
// コンストラクタ
//========================================
CStageEditor::CStageEditor(void)
{
	m_StageType = NULL;
}

//========================================
// デストラクタ
//========================================
CStageEditor::~CStageEditor()
{

}

//========================================
// 初期化
//========================================
HRESULT CStageEditor::Init(void)
{
	m_StageType = NULL;
	return S_OK;
}

//========================================
// 終了
//========================================
void CStageEditor::Uninit(void)
{
	delete m_StageType;
	m_StageType = NULL;
}

//========================================
// 更新
//========================================
void CStageEditor::Update(void)
{
	
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
			m_StageType = new StageType[nMaxType];
			assert(m_StageType != NULL);
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
void CStageEditor::StageLoad(const char *pFileName)
{

}