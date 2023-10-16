//========================================
// 
// ギミックの処理
// Author:RYUKI FUJIWARA
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"

//****************************************
// クラス定義
//****************************************
// モードの情報構造体
class CTrampoline {
public:
	//========== [[[ 列挙型定義 ]]]
	enum class TYPE {
		NONE = 0,	//乗っていない
		GETON,		//乗っている
		LAND,		//着地した
		MAX,
	};

	//========== [[[ 関数宣言 ]]]
	CTrampoline();
	virtual        ~CTrampoline();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);
	void   SetType(TYPE type) { m_type = type; }
	TYPE   GetType(void) { return m_type; }
	static  CTrampoline* Create(void);

protected:
	
private:
	//========== [[[ 変数宣言 ]]]
	TYPE m_type;
	int ModelIdx;
};
