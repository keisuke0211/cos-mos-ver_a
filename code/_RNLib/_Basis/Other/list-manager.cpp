//========================================
// 
// リストマネージャーの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list-manager.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CListMngクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CListMgr::CListMgr(void) {
	m_pTop = NULL;	// 先頭　のCHRポインタ
	m_pCur = NULL;	// 最後尾のCHRポインタ
	m_nNum = 0;
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CListMgr::~CListMgr(void) {

}

//========================================
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void CListMgr::Init(void) {

}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CListMgr::ReleaseAll(void) {
	CList* pList = m_pTop;
	while (pList != NULL) {
		CList* pListNext = pList->GetNext();

		pList->Release();

		pList = pListNext;
	}

	pList = m_pTop;
	while (pList != NULL) {
		CList* pListNext = pList->GetNext();

		// 削除フラグが真の時、解放処理
		if (pList->GetDelete())
			Release(pList);

		pList = pListNext;
	}
}

//========================================
// 更新処理
// Author:RIKU NISHIMURAS
//========================================
void CListMgr::Update(void) {
	UpdateAll();
}

//========================================
// 一括更新処理
// Author:RIKU NISHIMURAS
//========================================
void CListMgr::UpdateAll(void) {
	CList* pList = NULL;
	while (ListLoop(&pList)) {
		pList->Update();
	}

	pList = m_pTop;
	while (pList != NULL) {
		CList* pListNext = pList->GetNext();

		// 削除フラグが真の時、解放処理
		if (pList->GetDelete())
			Release(pList);

		pList = pListNext;
	}
}

//========================================
// リストループ処理
// Author:RIKU NISHIMURAS
//========================================
bool CListMgr::ListLoop(CList** ppList) {
	if (*ppList == NULL) {
		*ppList = m_pTop;
	}
	else {
		*ppList = (*ppList)->GetNext();
	}

	return (*ppList != NULL);
}

//========================================
// リスト解放処理
// Author:RIKU NISHIMURA
//========================================
void CListMgr::Release(CList* pRel) {
	if (pRel == NULL)
		return;

	SubList(pRel);

	pRel->Uninit();
	delete pRel;
}

//========================================
// リストに追加
// Author:RIKU NISHIMURA
//========================================
void CListMgr::AddList(CList* pAdd) {
	if (m_pCur == NULL)
	{// 最後尾が存在しない(※まだ1つもない)時、
		// 先頭と最後尾を新規に設定する
		m_pTop = pAdd;
		m_pCur = pAdd;

		pAdd->SetPrev(NULL);	// 前 無し
		pAdd->SetNext(NULL);	// 次 無し
	}
	else
	{// 最後尾が存在する時、
		// 元最後尾の次を新規に設定する
		m_pCur->SetNext(pAdd);

		pAdd->SetPrev(m_pCur);	// 前 元最後尾
		pAdd->SetNext(NULL);	// 次 無し

		// 最後尾を新規に設定する
		m_pCur = pAdd;
	}

	m_nNum++;
}

//========================================
// リストから削除
// Author:RIKU NISHIMURA
//========================================
void CListMgr::SubList(CList* pSub) {
	if (pSub->GetPrev() == NULL)
	{// 前が存在しない(※自分が先頭)時、
		// 先頭を次に設定する
		m_pTop = pSub->GetNext();

		if (m_pTop != NULL)
		{// 先頭が存在する時、
			m_pTop->SetPrev(NULL);	// 前 無し
		}
	}

	if (pSub->GetNext() == NULL)
	{// 次が存在しない(※自分が最後尾)時、
		// 最後尾を前に設定する
		m_pCur = pSub->GetPrev();

		if (m_pCur != NULL)
		{// 最後尾が存在する時、
			m_pCur->SetNext(NULL);	// 次 無し
		}
	}
	else
	{// 次が存在する時、
		CList* pPrev = pSub->GetPrev();
		CList* pNext = pSub->GetNext();

		// 前と次を繋ぐ
		if (pPrev != NULL)
			pPrev->SetNext(pNext);	// (※前は存在する保障が無い為チェック)
		pNext->SetPrev(pPrev);
	}

	m_nNum--;
}