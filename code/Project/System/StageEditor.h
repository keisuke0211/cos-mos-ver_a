//========================================
// 
// ステージエディットの読み込み
// Author:KEISUKE OTONO
// 
//========================================
#pragma once

//****************************************
// クラス定義
//****************************************
class CStageEditor {

public:

	// 定数
	static const char* STAGE_INFO_FILE;		// ステージ情報のファイルパス
	static const float SIZE_SPACE;

	// *** 情報構造体 ***

	// ステージ種類情報
	struct StageType
	{
		char	aFileName[0xff];	// ファイルパス
	};

	// *** 関数宣言 ***
	CStageEditor();
	~CStageEditor();

	// -- 読込 ---------------------------------------------
	/* ファイルパス	*/void FileLoad(void);
	/* ステージ読込	*/void StageLoad(int stage);

private:

	// *** 列挙型 ***
	enum Type
	{
		TYPE_BLOCK = 0,		// 床
		TYPE_TRAMPOLINE,	// トランポリン
		TYPE_THORN,			// 棘
		TYPE_LIFT,			// リフト
		TYPE_Meteor,		// 隕石
		TYPE_MAX
	};

	// *** 関数宣言 ***
	///* ステージ生成 */void SetStage();

	// *** 変数宣言 ***
	static StageType *m_StageType;
	static int m_StageMax;
};
