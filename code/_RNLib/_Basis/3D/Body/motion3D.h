//========================================
// 
// モーション3Dのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ motion3D.h ]]]
//========================================
#ifndef _MOTION3D_H_
#define _MOTION3D_H_

#include "setup3D.h"
#include "../../Other/regist.h"

//****************************************
// クラス定義
//****************************************
class CMotion3D : public CRegist {
public:
	//========== [[[ 列挙型定義 ]]]
	// コマンド
	typedef enum {
		CMD_LABEL_MOVE,				// 移動
		CMD_LABEL_SPIN,				// 回転
		CMD_LABEL_STEP,				// 足踏
		CMD_LABEL_SCALE,			// 拡大縮小
		CMD_LABEL_STEP_REACTION,	// 足踏反応
		CMD_LABEL_MAX,
	}CMD_LABEL;

	//========== [[[ 構造体定義 ]]]
	// コマンドデータ構造体
	typedef struct CmdData_ {
		const char* pLabelName;	// ラベル名
		int         nDataNum;	// 引数の数
	}CmdData;
	// コマンド情報構造体
	typedef struct Cmd_ {
		int       nTime   = 0;				// 時間
		CMD_LABEL command = (CMD_LABEL)0;	// コマンドの種類
		float*    pData   = NULL;			// 引数
	}Cmd;
	// 部品毎のコマンド情報構造体
	typedef struct PartsCmd_ {
		bool bMove   = false;	// 移動フラグ
		bool bSpin   = false;	// 回転フラグ
		int  nCmdNum = 0;		// コマンド数
		Cmd* pCmd    = NULL;	// コマンド情報
	}PartsCmd;

	// モデル構成毎のデータ構造体
	typedef struct PlatformData_{
		int       nPartsNum = 0;	// 部品数
		PartsCmd* pPartsCmd = NULL;	// 部品毎のコマンド情報
	}PlatformData;
	// データ構造体
	typedef struct Data_ {
		int  nLoopTime = 0;		// ループ時間
		bool bLoop     = false;	// ループするかフラグ
		PlatformData pfData[CModelSetUp::PLATFORM_MAX] = {};
	}Data;

	//========== [[[ 関数宣言 ]]]
	/* 終了処理             */void      Uninit(void);
	/* 読み込み処理         */int       Load(const char* pPath, short nIdx = DATANONE);
	/* 書き込み処理         */void      Save(const char* pPath, const int nIdx);
	/* データ取得           */Data*     GetData(void)                                               { return m_pData; }
	/* 部品毎のコマンド取得 */PartsCmd* GetPartsCmd(int nIdx, CModelSetUp::PLATFORM pf, int nParts) { return &m_pData[nIdx].pfData[pf].pPartsCmd[nParts]; }
	/* コマンドデータ取得   */CmdData   GetCmdData(CMD_LABEL cmd)                                   { return CMD_DATA[cmd]; }
	/* メモリ初期化処理     */void      InitMemory(const int nNum);

	//========== [[[ 変数宣言 ]]]
	Data* m_pData;	// データ

private:
	//========== [[[ 静的定数宣言 ]]]
	static const CmdData CMD_DATA[CMD_LABEL_MAX];	// コマンドデータ
};

#endif