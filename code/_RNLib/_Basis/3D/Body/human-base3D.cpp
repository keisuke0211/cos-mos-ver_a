//========================================
// 
// ヒューマン3Dベースの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ human-base3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CHuman3DBaseクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CHuman3DBase::CHuman3DBase() {
	m_pData = NULL;	// データ
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CHuman3DBase::~CHuman3DBase() {

}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CHuman3DBase::Uninit(void) {
	CRegist::Uninit();	// 基底クラス終了処理

	// データの破棄
	RNLib::Memory()->Release(&m_pData);
}

//========================================
// 読み込み処理
// Author:RIKU NISHIMURA
//========================================
int CHuman3DBase::Load(const char *pLoadPath, short nIdx) {
	int nNumOld = m_num;	// 過去の総数

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

		if (RNLib::File()->OpenLoadFile(pLoadPath)) {
			while (RNLib::File()->SearchLoop("END")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier("SETUP_PATH:")) { RNLib::File()->Scan(CFile::SCAN::MODELSUIDX, &m_pData[nIdx].nSetUpIdx); }
				else if (RNLib::File()->CheckIdentifier("EYE_POS:")) { RNLib::File()->Scan(CFile::SCAN::POS3D, &m_pData[nIdx].eyePos); }		// 目の位置
				else if (RNLib::File()->CheckIdentifier("EYE_ROT:")) { RNLib::File()->Scan(CFile::SCAN::POS3D, &m_pData[nIdx].eyeRot); }		// 目の向き
				else if (RNLib::File()->CheckIdentifier("EYE_PARENT:")) { RNLib::File()->Scan(CFile::SCAN::INT, &m_pData[nIdx].nEyeParent); }	// 目の親部品番号
				else if (RNLib::File()->CheckIdentifier("EYE_SPACE:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_pData[nIdx].fEyeSpace); }		// 目の間隔
				else if (RNLib::File()->CheckIdentifier("EYE_ROT_DIA:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_pData[nIdx].fEyeRotDia); }	// 目の回転倍率
			}

			RNLib::File()->CloseFile();
		}
	}

	// モデルセットアップ番号を返す
	return nIdx;
}

//========================================
// SaveHuman3DBase関数 - ヒューマンベース3D書き込み処理 -
// Author:RIKU NISHIMURA
//========================================
void CHuman3DBase::Save(char *pPath, int nIdx) {
	
	if (RNLib::File()->OpenSaveFile(pPath)) {
		FILE* file = RNLib::File()->GetFile();

		fprintf(file, "SETUP_PATH: %s\n",    RNLib::ModelSetUp()->GetLoadPath(m_pData[nIdx].nSetUpIdx));
		fprintf(file, "EYE_POS: %f %f %f\n", m_pData[nIdx].eyePos.x, m_pData[nIdx].eyePos.y, m_pData[nIdx].eyePos.z);
		fprintf(file, "EYE_ROT: %f %f %f\n", m_pData[nIdx].eyeRot.x, m_pData[nIdx].eyeRot.y, m_pData[nIdx].eyeRot.z);
		fprintf(file, "EYE_PARENT: %d\n",    m_pData[nIdx].nEyeParent);
		fprintf(file, "EYE_SPACE: %f\n",     m_pData[nIdx].fEyeSpace);
		fprintf(file, "EYE_ROT_DIA: %f\n",   m_pData[nIdx].fEyeRotDia);

		fprintf(file, "END\n");

		RNLib::File()->CloseFile();
	}
}

//========================================
// メモリを指定数に初期化
// Author:RIKU NISHIMURA
//========================================
void CHuman3DBase::InitMemory(const int nNum) {
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