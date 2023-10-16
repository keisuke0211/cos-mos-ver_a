//========================================
// 
// 登録処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ regist.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CRegistクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CRegist::CRegist() {
	m_num       = 0;		// 総数
	m_ppLoadPath = NULL;	// 読み込み済のパス
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CRegist::~CRegist() {

}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CRegist::Uninit(void) {
	// メモリ解放
	for (int nCnt = 0; nCnt < m_num; nCnt++) {
		RNLib::Memory()->Release(&m_ppLoadPath[nCnt]);	// 読込済パス
	}
	RNLib::Memory()->Release(&m_ppLoadPath);	// 読込済パス全体
}

//========================================
// 読み込み処理
// Author:RIKU NISHIMURA
//========================================
bool CRegist::Load(const char *pPath, short *pIdx) {
	if ((!strcmp(pPath, "")) || (!strcmp(pPath, "DATANONE")))
	{// パスが何もない or データ無し指定の時、
		*pIdx = DATANONE;
		return false;	// 読み込んじゃダメ
	}
	else if (*pIdx != DATANONE)
	{// 番号指定がある時、
		if (*pIdx >= 0 && *pIdx < m_num) 
		{// 番号が範囲内であれば、
			sprintf(m_ppLoadPath[*pIdx], "%s", pPath);	// パスを保存
			return true;	// 読み込んでヨシ
		}
		else 
		{// 番号が範囲外であれば、
			assert(false);
			*pIdx = DATANONE;
			return false;	// 読み込んじゃダメ
		}
	}

	// 既に読み込まれているか確認
	for (int nCnt = 0; nCnt < m_num; nCnt++) {
		if (!strcmp(pPath, m_ppLoadPath[nCnt]))
		{// 既に同じパスのテクスチャを読み込んでいた時、
			*pIdx = nCnt;	// 番号はそのままカウント
			return false;	// 読み込んじゃダメ
		}
	}

	int nNumOld_and_idx = m_num;	// 番号

	// 総数を加算する
	m_num++;

	{// 読み込み済みパスのメモリ再確保
		char** ppNew = new char * [m_num];
		int nCopyNum = m_num < nNumOld_and_idx ? m_num : nNumOld_and_idx;
		if (nCopyNum > 0) {
			memcpy(ppNew, m_ppLoadPath, sizeof(char*) * nCopyNum);
			delete m_ppLoadPath;
		}
		m_ppLoadPath = ppNew;
		for (int nCnt = nNumOld_and_idx; nCnt < m_num; nCnt++) {
			m_ppLoadPath[nCnt] = new char[TXT_MAX];
		}
	}

	// パスを保存
	sprintf(m_ppLoadPath[nNumOld_and_idx], "%s", pPath);

	// 番号を返す
	*pIdx = nNumOld_and_idx;
	return true;	// 読み込んでヨシ
}

//========================================
// メモリ初期化処理
// Author:RIKU NISHIMURA
//========================================
void CRegist::InitMemory(const int nNum) {
	m_num = nNum;	// 数を代入

	{// 読み込み済パスのメモリ確保
		char** ppNew = new char* [m_num];
		if (m_ppLoadPath != NULL) {
			delete m_ppLoadPath;
		}
		m_ppLoadPath = ppNew;
		for (int nCnt = 0; nCnt < m_num; nCnt++) {
			m_ppLoadPath[nCnt] = new char[TXT_MAX];
		}
	}
}