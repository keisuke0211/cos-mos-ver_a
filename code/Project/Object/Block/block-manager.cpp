//========================================
// 
// ブロックマネージャー
// Author:KEISUKE OTONO
// 
//========================================
// *** block-manager.h ***
//========================================
#include "block-manager.h"

//========================================
// 静的変数
//========================================
CBlockMgr::BlockType *CBlockMgr::m_pBlockType = NULL;
const char* CBlockMgr::BLOCK_INFO_FILE = "data\\GAMEDATA\\BLOCK\\BLOCK_DATA.txt";

//========================================
// コンストラクタ
//========================================
CBlockMgr::CBlockMgr(void)
{
	
}

//========================================
// デストラクタ
//========================================
CBlockMgr::~CBlockMgr()
{
	
}

//========================================
// 初期化
//========================================
void CBlockMgr::Init(void)
{
	CListMgr::Init();
}

//========================================
// 終了
//========================================
void CBlockMgr::Uninit(void)
{
	
}

//========================================
// 更新
//========================================
void CBlockMgr::Update(void)
{
	CListMgr::Update();
}

//========================================
// 読み込み
//========================================
void CBlockMgr::Load(void)
{
	int nCntModel = 0;
	char aDataSearch[TXT_MAX];	// データ検索用

	// ファイルの読み込み
	FILE *pFile = fopen(BLOCK_INFO_FILE, "r");

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

		if (!strcmp(aDataSearch, "NUM_MODEL"))
		{
			int nMaxType = -1;

			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%d", &nMaxType);		// 最大数
			m_pBlockType = new BlockType[nMaxType];
			assert(m_pBlockType != NULL);
		}
		else if (!strcmp(aDataSearch, "MODEL"))
		{
			fscanf(pFile, "%s", &aDataSearch[0]);
			fscanf(pFile, "%s", &m_pBlockType[nCntModel].aFileName[0]);	// ファイル名

			m_pBlockType[nCntModel].nModelIdx = RNLib::Model()->Load(m_pBlockType[nCntModel].aFileName);	// モデル番号
			nCntModel++;
		}
	}
}

//========================================
// 各生成
//========================================

// ブロック
CBlock *CBlockMgr::BlockCreate(int type, D3DXVECTOR3 pos)
{
	CBlock *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CBlock;

	// 初期化処理
	pObj->Init();
	pObj->SetModelIdx(m_pBlockType[type].nModelIdx);
	pObj->SetPos(pos);

	return pObj;
}

// トランポリン
CTrampoline *CBlockMgr::TrampolineCreate(int type, D3DXVECTOR3 pos)
{
	CTrampoline *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CTrampoline;

	// 初期化処理
	pObj->Init();
	pObj->SetModelIdx(m_pBlockType[type].nModelIdx);
	pObj->SetPos(pos);

	return pObj;
}

// トランポリン
CMeteor *CBlockMgr::MeteorCreate(int type, D3DXVECTOR3 pos)
{
	CMeteor *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CMeteor;

	// 初期化処理
	pObj->Init();
	pObj->SetModelIdx(m_pBlockType[type].nModelIdx);

	return pObj;
}
