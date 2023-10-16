//========================================
// 
// モデルセットアップ関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//****************************************
// 定数宣言
//****************************************
namespace {
	// モデル構成名
	const char* c_aModelPlatformName[] = {
		"NONE",					// 無し
		"FOOTLESS_00",			// 無足[00]
		"BIPEDALISM_00",		// 二足[00]
		"BIPEDALISM_01",		// 二足[01]
		"QUADRUPEDALISM_00",	// 四足[00]
		"HEXAPOD_00",			// 六足[00]
		"OCTAPOD_00",			// 八足[00]
	};

	// モデル構成の部位毎の番号
	const int c_aModelPlatformPartIdx[][CModelSetUp::PART_MAX] = {
		//-------------------//|頭      |首      |胸      |腰      |上腕[左]|上腕[右]|前腕[左]|前腕[右]|手[左]  |手[右]  |指４[左]|指４[右]|指１[左]|指１[右]|太腿[左]|太腿[右]|脛[左]  |脛[右]  |足[左]  |足[右]  |
		/* NONE              */{DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE},
		/* FOOTLESS_00       */{0       ,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE},
		/* BIPEDALISM_00     */{1       ,DATANONE,0       ,0       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,4       ,5       ,4       ,5       ,4       ,5       },
		/* BIPEDALISM_01     */{4       ,3       ,2       ,0       ,5       ,8       ,6       ,9       ,7       ,10      ,19      ,22      ,21      ,26      ,11      ,14      ,12      ,15      ,13      ,16      },
		/* QUADRUPEDALISM_00 */{1       ,DATANONE,0       ,0       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,4       ,5       ,4       ,5       ,4       ,5       },
		/* HEXAPOD_00        */{2       ,DATANONE,1       ,0       ,5       ,8       ,5       ,8       ,5       ,8       ,5       ,8       ,5       ,8       ,7       ,10      ,7       ,10      ,7       ,10      },
		/* OCTAPOD_00        */{1       ,DATANONE,1       ,0       ,4       ,12      ,4       ,12      ,5       ,13      ,5       ,13      ,5       ,13      ,10      ,18      ,10      ,18      ,11      ,19      },
	};
}
CHECK_ARRAY_SIZE(c_aModelPlatformName, CModelSetUp::PLATFORM_MAX);
CHECK_ARRAY_SIZE(c_aModelPlatformPartIdx, CModelSetUp::PLATFORM_MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CModelSetUpクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CModelSetUp::CModelSetUp() {
	m_pData = NULL;	// データ
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CModelSetUp::~CModelSetUp() {

}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CModelSetUp::Uninit(void) {
	CRegist::Uninit();	// 基底クラス終了処理

	for (int nCntData = 0; nCntData < m_num; nCntData++) {
		RNLib::Memory()->Release(&m_pData[nCntData].partsSet.pPartsData);
		RNLib::Memory()->Release(&m_pData[nCntData].collSet.pParts);
	}

	// データの破棄
	RNLib::Memory()->Release(&m_pData);

	m_num = 0;
}

//========================================
// 読み込み処理
// Author:RIKU NISHIMURA
//========================================
int CModelSetUp::Load(const char *pLoadPath, short nIdx) {
	int nNumOld  = m_num;	// 過去の総数

	if (!CRegist::Load(pLoadPath, &nIdx)) {
		return nIdx;
	}
	else {
		{// データのメモリ再確保
			Data* pNew = new Data[m_num];
			int nCopySize = m_num < nNumOld ? m_num : nNumOld;
			if (nCopySize > 0) {
				memcpy(pNew, m_pData, sizeof(Data) * nCopySize);
				delete m_pData;
			}
			m_pData = pNew;
		}
		m_pData[nIdx] = {};

		// ファイルを開く
		if (RNLib::File()->OpenLoadFile(pLoadPath)) {
			while (RNLib::File()->SearchLoop("END")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier(/* 部品設定情報       */"PARTSSET{")) { CParts3DSetUp::LoadData(&m_pData[nIdx].partsSet); }
				else if (RNLib::File()->CheckIdentifier(/* コリジョン設定情報 */"COLLISIONSET{")) { CCollision3D::LoadData(&m_pData[nIdx].collSet); }
				else if (RNLib::File()->CheckIdentifier(/* モデル構成         */"PLATFORM:")) {
					RNLib::File()->NewLine();

					// モデル構成初期化
					m_pData[nIdx].platform = PLATFORM_NONE;

					for (int nCntPtf = 0; nCntPtf < PLATFORM_MAX; nCntPtf++) {
						if (RNLib::File()->CheckIdentifier(c_aModelPlatformName[nCntPtf]))
						{// カウントのモデル構成名と一致した時、モデル構成設定
							m_pData[nIdx].platform = (PLATFORM)nCntPtf;
							break;
						}
					}
				}
			}

			// ファイルを閉じる
			RNLib::File()->CloseFile();
		}
	}

	// モデルセットアップ番号を返す
	return nIdx;
}

//========================================
// 書き込み処理
// Author:RIKU NISHIMURA
//========================================
void CModelSetUp::Save(char *pPath, int nIdx) {

	if (RNLib::File()->OpenSaveFile(pPath))
	{// ファイルが開けた場合、
		// 部品情報の書き込み処理
		CParts3DSetUp::SaveData(&m_pData[nIdx].partsSet);

		// コリジョン情報の書き込み処理
		CCollision3D::SaveData(&m_pData[nIdx].collSet);

		FILE* file = RNLib::File()->GetFile();
		
		fprintf(file, "PLATFORM: %s\n", c_aModelPlatformName[m_pData[nIdx].platform]);
		fprintf(file, "END");

		RNLib::File()->CloseFile();
	}
}

//========================================
// モデル構成の部位番号取得
// Author:RIKU NISHIMURA
//========================================
int CModelSetUp::GetPlatformPartIdx(const PLATFORM platform, const CModelSetUp::PART part) {
	return c_aModelPlatformPartIdx[platform][part];
}

//========================================
// モデル構成の名前取得
// Author:RIKU NISHIMURA
//========================================
const char* CModelSetUp::GetPlatformName(const PLATFORM platform) {
	return c_aModelPlatformName[platform];
}

//========================================
// 名前からモデル構成取得
// Author:RIKU NISHIMURA
//========================================
CModelSetUp::PLATFORM CModelSetUp::GetPlatformFromName(const char* pName) {
	for (int nCntPtf = 0; nCntPtf < PLATFORM_MAX; nCntPtf++) {
		if (!strcmp(pName, c_aModelPlatformName[nCntPtf])) {
			return (PLATFORM)nCntPtf;
		}
	}

	return PLATFORM_NONE;
}

//========================================
// メモリを指定数に初期化
// Author:RIKU NISHIMURA
//========================================
void CModelSetUp::InitMemory(const int nNum) {
	Uninit();	// 終了処理
	CRegist::InitMemory(nNum);	// 基底クラスのメモリ初期化処理

	// データのメモリ確保
	if (m_pData != NULL) {
		delete m_pData;
	}
	m_pData = new Data[nNum];

	// 確保した分のデータを全て初期化する
	for (int nCnt = 0; nCnt < nNum; nCnt++) {
		m_pData[nCnt] = {};
	}
}