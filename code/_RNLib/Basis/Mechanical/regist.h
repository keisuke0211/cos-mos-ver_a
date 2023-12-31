//========================================
// 
// 登録処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// クラス定義
//****************************************
// 登録クラス
class CRegist {
public:
	//========== [[[ 関数宣言 ]]]
	CRegist();
	virtual ~CRegist();
	virtual bool Load(const char* loadPath, short& idx);
	virtual void InitMemory(const unsigned short& num);

protected:
	//========== [[[ 関数宣言 ]]]
	void ReAllocLoadPath(const short& oldNum);

	//========== [[[ 変数宣言 ]]]
	char** m_loadPaths;
	unsigned short m_num;
};