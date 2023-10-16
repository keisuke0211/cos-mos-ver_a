//========================================
// 
// リストマネージャーのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list-manager.h ]]]
//========================================
#ifndef _LIST_MANAGER_H_
#define _LIST_MANAGER_H_

#include "list.h"

//****************************************
// クラス定義
//****************************************
// リストマネージャークラス
class CListMgr {
public:
	//========== [[[ 関数宣言 ]]]
	CListMgr();
	virtual ~CListMgr();
	virtual void Init(void);
	virtual void ReleaseAll(void);
	virtual void Update(void);
	void   Release(CList* pList);
	void   AddList(CList* pAdd);
	void   SubList(CList* pSub);
	int    GetNum(void) { return m_nNum; }
	CList* GetTop(void) { return m_pTop; }
	bool ListLoop(CList** ppList);

private:
	//========== [[[ 関数宣言 ]]]
	void UpdateAll(void);

	//========== [[[ 変数宣言 ]]]
	CList* m_pTop;	// 先頭　のCHRポインタ
	CList* m_pCur;	// 最後尾のCHRポインタ
	int    m_nNum;
};

#endif