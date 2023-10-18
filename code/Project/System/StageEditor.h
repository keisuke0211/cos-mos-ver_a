//========================================
// 
// ステージエディットの読み込み
// Author:KEISUKE OTONO
// 
//========================================
#pragma once
using namespace std;

//****************************************
// 前方宣言
//****************************************
class CSVFILE;

//****************************************
// クラス定義
//****************************************
class CStageEditor {

public:

	// 定数
	static const char* STAGE_INFO_FILE;		// ステージ情報のファイルパス

	// *** 情報構造体 ***

	// ステージ種類情報
	struct StageType
	{
		char	aFileName[0xff];	// ファイルパス
	};

	// ステージ情報
	struct StageInfo
	{
		int nRow;		// 行数
		int nLine;		// 列数
		int nRowMax;	// 行数の最大
		int nLineMax;	// 列数の最大
	};

	// *** 関数宣言 ***
	CStageEditor();
	~CStageEditor();

	// -- 取得 ---------------------------------------------
	/* 変換 */bool ToData(char* &val, CSVFILE *pFile, int nRow, int nLine);
	/* 変換 */bool ToData(int &val, CSVFILE *pFile, int nRow, int nLine);

	// -- 読込 ---------------------------------------------
	/* ファイルパス	*/void FileLoad(void);
	/* ステージ読込	*/void StageLoad(int stage);

private:

	// *** 列挙型 ***
	enum Type
	{
		TYPE_BLOCK = 0,		// 床
		TYPE_TRAMPOLINE,	// トランポリン
		TYPE_SPIKE,			// 棘
		TYPE_LIFT,			// リフト
		TYPE_Meteor,		// 隕石
		TYPE_PLAYER_0 = 90,	// プレイヤー2
		TYPE_PLAYER_1,		// プレイヤー1
		TYPE_PARTS = 98,	// パーツ
		TYPE_GOAL,			// ゴール
		TYPE_MAX
	};

	// *** 関数宣言 ***
	/* ステージ生成 */void SetStage(int nType);

	// *** 変数宣言 ***
	static StageType *m_StageType;	// ステージ種類
	static int m_StageMax;			// ステージの最大値
	StageInfo m_Info;				// ステージ情報
};
