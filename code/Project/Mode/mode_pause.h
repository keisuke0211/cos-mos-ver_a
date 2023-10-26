//========================================
// 
// モード:ポーズの処理
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// クラス定義
//****************************************
// モード(リザルト)クラス
class CMode_Pause :public CMode {
public:
	//========== [[[ 列挙型定義 ]]]
	enum class STATE {
		NONE,
	};

	//========== [[[ 関数宣言 ]]]
	CMode_Pause();
	~CMode_Pause();
	void  Init(void);
	void  Uninit(void);
	void  Update(void);
	void  ProcessState(const PROCESS process);

	// -- 設定 --------------------------------------------
	/* ポーズ */static void SetPause(bool bPause) { m_bPause = bPause; }

	// -- 取得 --------------------------------------------
	/* ポーズ	*/static bool IsPause(void) { return m_bPause; }

private:
	static bool m_bPause;

};