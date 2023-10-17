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
class CTrampoline : public CList {
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
	void   SetType(TYPE type) { m_type = type; }			//種類設定
	TYPE   GetType(void) { return m_type; }					//種類取得
	void   SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			//位置設定
	void   SetScale(D3DXVECTOR3 scale) { m_scale = scale; }	//拡縮設定

protected:
	
private:
	//========== [[[ 変数宣言 ]]]
	TYPE m_type;			//種類
	int m_modelIdx;			//モデル番号
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_scale;	//大きさ
};
