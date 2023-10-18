//========================================
// 
// モード:ゲームの処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"

//****************************************
// 前方宣言
//****************************************
class CPlayer;

//****************************************
// クラス定義
//****************************************
// モード(ゲーム)クラス
class CMode_Game :public CMode {
public:
	//========== [[[ 列挙型定義 ]]]
	enum class STATE {
		NONE,
	};

	//========== [[[ 関数宣言 ]]]
	      CMode_Game    ();
	      ~CMode_Game   ();
	void  Init          (void);
	void  Uninit        (void);
	void  Update        (void);
	void  ProcessState  (const PROCESS process);

	static CPlayer* GetPlayer(void);

private:
	static CPlayer *s_pPlayer;
};