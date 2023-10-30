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
		char	aTexFile[0xff];		// テクスチャパス
		char	aStageName[0xff];	// ステージ名

	};

	// ステージ情報
	struct StageInfo
	{
		int nRow;		// 行数
		int nLine;		// 列数
		int nRowMax;	// 行数の最大
		int nLineMax;	// 列数の最大
		int nStageIdx;	// 現在のステージ番号
		int nStageMax;	// ステージの最大値
	};

	// 色
	struct StageColor
	{
		Color Block;
		Color Trampoline;
		Color Spike;
		Color Lift;
		Color Meteor;
		Color FillBlock;
	};

	// *** 関数宣言 ***
	CStageEditor();
	~CStageEditor();

	/* ステージ切り替え	*/void SwapStage(int nStageIdx);

	// -- 取得 ---------------------------------------------
	/* 最大値			*/int GetStageMax(void) { return m_Info.nStageMax; }
	/* 現在のステージ	*/int GetStageIdx(void) { return m_Info.nStageIdx; }
	/* ステージ種類		*/StageType *GetType(void) { return m_StageType; }
	/* 変換				*/bool ToData(int &val, CSVFILE *pFile, int nRow, int nLine);

	// -- 読込 ---------------------------------------------
	/* ファイルパス	*/void FileLoad(void);
	/* ステージ読込	*/void StageLoad(int stage);

private:

	// *** 列挙型 ***
	enum Type
	{
		TYPE_BLOCK = 0,				// ブロック
		TYPE_TRAMPOLINE,			// トランポリン
		TYPE_SPIKE,					// 棘
		TYPE_LIFT,					// リフト
		TYPE_Meteor,				// 隕石
		TYPE_FILL_BLOCK_11 = 20,	// ブロック(判定 無) 1 * 1
		TYPE_FILL_BLOCK_22 = 21,	// ブロック(判定 無) 2 * 2
		TYPE_FILL_BLOCK_33 = 22,	// ブロック(判定 無) 3 * 3
		TYPE_FILL_BLOCK_44 = 23,	// ブロック(判定 無) 4 * 4
		TYPE_PLAYER_0 = 90,			// プレイヤー2
		TYPE_PLAYER_1,				// プレイヤー1
		TYPE_PARTS = 98,			// パーツ
		TYPE_GOAL,					// ゴール
		TYPE_MAX
	};

	// *** 関数宣言 ***
	/* ステージ生成 */void SetStage(int nType);

	// *** 変数宣言 ***
	static StageType *m_StageType;		// ステージ種類
	static StageColor m_StageColor;		// 色情報
	StageInfo m_Info;					// ステージ情報
};
