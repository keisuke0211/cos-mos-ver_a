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

	static const char* STAGE_INFO_FILE;		// ステージ情報のファイルパス

public:

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
	/* ステージ読込	*/void StageLoad(const char *pFileName);

private:
	// *** 変数宣言 ***
	static StageType *m_StageType;
};
