//========================================
// 
// リストのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list.h ]]]
//========================================
#ifndef _LIST_H_
#define _LIST_H_

//****************************************
// クラス定義
//****************************************
// リストクラス
class CList {
public:
	//========== [[[ 関数宣言 ]]]
	CList();
	virtual ~CList();
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Release(void);
	// 設定取得
	void   SetNext  (CList* pNext) { m_pNext = pNext; }
	CList* GetNext  (void)         { return m_pNext; }
	void   SetPrev  (CList* pPrev) { m_pPrev = pPrev; }
	CList* GetPrev  (void)         { return m_pPrev; }
	bool   GetDelete(void)         { return m_bDelete; }

private:
	//========== [[[ 変数宣言 ]]]
	CList* m_pPrev;
	CList* m_pNext;
	bool   m_bDelete;
};

#endif