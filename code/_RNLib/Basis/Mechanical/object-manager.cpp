//========================================
// 
// オブジェクトマネージャーの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| オブジェクトマネージャークラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//****************************************
// 静的メンバ変数定義
//****************************************
CObjectMgr** CObjectMgr::ms_objectMgrs = NULL;
unsigned short CObjectMgr::ms_objectMgrNum = NULL;

//========================================
// [静的] 全マネージャー更新処理
//========================================
void CObjectMgr::UpdateAllMgrs(void) {

	// 全マネージャーの全更新処理と更新処理を行う
	for (int cntObjectMgr = 0; cntObjectMgr < ms_objectMgrNum; cntObjectMgr++) {
		ms_objectMgrs[cntObjectMgr]->UpdateAll();
		ms_objectMgrs[cntObjectMgr]->Update();
	}
}

//========================================
// [静的] マネージャーを排除
//========================================
void CObjectMgr::SubMgr(CObjectMgr* mgr) {

	bool isSub = false;
	for (int cntObjectMgr = 0; cntObjectMgr < ms_objectMgrNum; cntObjectMgr++) {
		if (isSub) 
		{// 排除し終えた
			// 1つ前にずらす
			ms_objectMgrs[cntObjectMgr - 1] = ms_objectMgrs[cntObjectMgr];
			ms_objectMgrs[cntObjectMgr] = NULL;
		}
		else 
		{// 排除してない
			if (mgr == ms_objectMgrs[cntObjectMgr]) 
			{// カウントと対象アドレスが一致した時、
				// 総数を減らし、排除フラグを真にする
				ms_objectMgrNum--;
				isSub = true;
			}
		}
	}

	// 排除出来た時、メモリを再確保
	if (isSub)
		RNLib::Memory().ReAlloc<CObjectMgr*>(&ms_objectMgrs, ms_objectMgrNum + 1, ms_objectMgrNum);
}

//========================================
// コンストラクタ
//========================================
CObjectMgr::CObjectMgr(void) {

	{// オブジェクトマネージャー列に追加する
		int numOld = ms_objectMgrNum++;
		RNLib::Memory().ReAlloc<CObjectMgr*>(&ms_objectMgrs, numOld, ms_objectMgrNum, false);
		ms_objectMgrs[numOld] = this;
	}

	m_top = NULL;
	m_cur = NULL;
	m_num = 0;
}

//========================================
// デストラクタ
//========================================
CObjectMgr::~CObjectMgr(void) {

	// 全開放処理
	CObjectMgr::ReleaseAll();

	// 自身をマネージャー列から排除
	SubMgr(this);
}

//========================================
// 全開放処理
//========================================
void CObjectMgr::ReleaseAll(void) {

	// 先頭から順番に最後尾まで削除フラグを立たせる
	// (※継承先の要素は解放されるが、
	//    本体は解放せず、死亡フラグを立たせる)
	CObject* obj = NULL;
	while (ListLoop(&obj)) {

		obj->Delete();
	}

	// 削除フラグが立っているオブジェクトを解放する
	ReleaseDeleteObj();
}

//========================================
// 一括更新処理
// Author:RIKU NISHIMURAS
//========================================
void CObjectMgr::UpdateAll(void) {

	// 先頭から順番に最後尾まで更新していく
	CObject* pList = NULL;
	while (ListLoop(&pList)) {

		pList->Update();
	}

	// 削除フラグが立っているオブジェクトを解放する
	ReleaseDeleteObj();
}

//========================================
// 削除フラグが立っているオブジェクトを解放する
//========================================
void CObjectMgr::ReleaseDeleteObj(void) {

	// 先頭から順番に最後尾まで解放していく
	// (※削除フラグが真の時、解放処理)
	CObject* obj = m_top;
	while (obj != NULL) {
		CObject* nextObj = obj->GetNext();

		// 削除フラグが真の時、解放処理
		if (obj->GetDelete())
			Release(obj);

		obj = nextObj;
	}
}

//========================================
// リストループ処理
//========================================
bool CObjectMgr::ListLoop(CObject** obj) {

	if (*obj == NULL)
		*obj = m_top;
	else
		*obj = (*obj)->GetNext();

	return (*obj != NULL);
}

//========================================
// オブジェクト解放処理
//========================================
void CObjectMgr::Release(CObject* obj) {

	// 既にNULLであれば終了
	if (obj == NULL)
		return;

	// リストから削除
	SubList(obj);

	// 終了して解放
	obj->Uninit();
	delete obj;
}

//========================================
// リストに追加
//========================================
void CObjectMgr::AddList(CObject* obj) {

	if (m_cur == NULL)
	{// 最後尾が存在しない(※まだ1つもない)時、
		// 先頭と最後尾を新規に設定する
		m_top = obj;
		m_cur = obj;

		obj->SetPrev(NULL);	// 前 無し
		obj->SetNext(NULL);	// 次 無し
	}
	else
	{// 最後尾が存在する時、
		// 元最後尾の次を新規に設定する
		m_cur->SetNext(obj);

		obj->SetPrev(m_cur);	// 前 元最後尾
		obj->SetNext(NULL);		// 次 無し

		// 最後尾を新規に設定する
		m_cur = obj;
	}

	m_num++;
}

//========================================
// リストから排除
//========================================
void CObjectMgr::SubList(CObject* obj) {

	if (obj->GetPrev() == NULL)
	{// 前が存在しない(※自分が先頭)時、
		// 先頭を次に設定する
		m_top = obj->GetNext();

		if (m_top != NULL)
		{// 先頭が存在する時、
			m_top->SetPrev(NULL);	// 前 無し
		}
	}

	if (obj->GetNext() == NULL)
	{// 次が存在しない(※自分が最後尾)時、
		// 最後尾を前に設定する
		m_cur = obj->GetPrev();

		if (m_cur != NULL)
		{// 最後尾が存在する時、
			m_cur->SetNext(NULL);	// 次 無し
		}
	}
	else
	{// 次が存在する時、
		CObject* prev = obj->GetPrev();
		CObject* next = obj->GetNext();

		// 前と次を繋ぐ
		if (prev != NULL)
			prev->SetNext(next);	// (※前は存在する保障が無い為チェック)
		next->SetPrev(prev);
	}

	m_num--;
}