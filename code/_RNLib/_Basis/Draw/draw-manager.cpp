//========================================
// 
// 描画処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// 静的メンバ変数定義
//****************************************
CDrawMng::PROCESS_STATE  CDrawMng::ms_processState = PROCESS_STATE::REGIST_ACCEPT;
CDrawMng::CRegistInfoSum CDrawMng::ms_resistInfoSum;
CDrawMng::CRegistInfoSum CDrawMng::ms_resistInfoSumScreen;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSum;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSumOvr;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSumScreen;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSumScreenOvr;
std::thread              CDrawMng::ms_mainLoopTh(MainLoop);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 描画情報総括クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CDrawMng::CDrawInfoSum::CDrawInfoSum() {

	ms_drawInfos   = NULL;
	ms_drawInfoNum = 0;
}

//========================================
// デストラクタ
//========================================
CDrawMng::CDrawInfoSum::~CDrawInfoSum() {

}

//========================================
// 解放処理
//========================================
void CDrawMng::CDrawInfoSum::Release(void) {

	// 描画情報を解放
	if (ms_drawInfos != NULL) {
		for (int cnt = 0; cnt < ms_drawInfoNum; cnt++) {
			RNLib::Memory()->Release<CDrawInfoBase>(&ms_drawInfos[cnt]);
		}
		RNLib::Memory()->Release<CDrawInfoBase*>(&ms_drawInfos);
	}
}

//========================================
// 上書き処理
//========================================
void CDrawMng::CDrawInfoSum::Overwrite(CDrawInfoSum* pOvr) {

	// 解放処理
	Release();

	// 上書き
	ms_drawInfos         = pOvr->ms_drawInfos;
	ms_drawInfoNum       = pOvr->ms_drawInfoNum;
	pOvr->ms_drawInfos   = NULL;
	pOvr->ms_drawInfoNum = 0;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 登録情報情報総括クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CDrawMng::CRegistInfoSum::CRegistInfoSum() {

	m_polygon2DRegistInfos   = NULL;
	m_polygon2DRegistInfoNum = 0;
	m_polygon3DRegistInfos   = NULL;
	m_polygon3DRegistInfoNum = 0;
	m_text2DRegistInfos      = NULL;
	m_text2DRegistInfoNum    = 0;
	m_text3DRegistInfos      = NULL;
	m_text3DRegistInfoNum    = 0;
	m_modelRegistInfos       = NULL;
	m_modelRegistInfoNum     = 0;
}

//========================================
// デストラクタ
//========================================
CDrawMng::CRegistInfoSum::~CRegistInfoSum() {

}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 描画クラスのスレッド用静的メンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// メインループ
//========================================
void CDrawMng::MainLoop(void) {
	while (true) {
		if (ms_processState == PROCESS_STATE::REGIST_INFO_APPLY_WAIT)
		{// [ 登録情報適用待ち ]の時、
			// 登録情報を元に設置する
			PutBasedRegistInfo(ms_resistInfoSum, false);
			PutBasedRegistInfo(ms_resistInfoSumScreen, true);

			// 登録情報を描画情報に変換する
			ConvRegistInfoToDrawInfo(ms_resistInfoSum, ms_drawInfoSumOvr);
			ConvRegistInfoToDrawInfo(ms_resistInfoSumScreen, ms_drawInfoSumScreenOvr);

			// 描画情報をソートする
			SortDrawInfo(ms_drawInfoSumOvr);
			SortDrawInfo(ms_drawInfoSumScreenOvr);

			// [ 描画情報入れ替え待ち ]にする
			ms_processState = PROCESS_STATE::DRAW_INFO_SWAP_WAIT;
		}

		// ※全力で回さないように0秒スリープ
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
	}
}

//========================================
// 登録情報を元に設置する
//========================================
void CDrawMng::PutBasedRegistInfo(CRegistInfoSum& resistInfoSum, const bool& isOnScreen) {

	//----------------------------------------
	// テキスト2Dからポリゴン2Dを設置
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_text2DRegistInfoNum; cnt++) {
		resistInfoSum.m_text2DRegistInfos[cnt].PutPolygon2D(isOnScreen);
	}

	// 解放
	resistInfoSum.m_text2DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_text2DRegistInfos);

	//----------------------------------------
	// テキスト3Dからポリゴン3Dを設置
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_text3DRegistInfoNum; cnt++) {
		resistInfoSum.m_text3DRegistInfos[cnt].PutPolygon3D(isOnScreen);
	}

	// 解放
	resistInfoSum.m_text3DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_text3DRegistInfos);
}

//========================================
// 登録情報を描画情報に変換する
//========================================
void CDrawMng::ConvRegistInfoToDrawInfo(CRegistInfoSum& resistInfoSum, CDrawInfoSum& drawInfoSum) {

	int cntDrawInfo = 0;

	{// 描画情報のメモリ確保
		drawInfoSum.ms_drawInfoNum = 
			resistInfoSum.m_polygon2DRegistInfoNum +	// ポリゴン2D
			resistInfoSum.m_polygon3DRegistInfoNum +	// ポリゴン3D
			resistInfoSum.m_modelRegistInfoNum +		// モデル
			0;
		RNLib::Memory()->Alloc<CDrawInfoBase*>(&drawInfoSum.ms_drawInfos, drawInfoSum.ms_drawInfoNum);
	}

	//----------------------------------------
	// ポリゴン3D
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_polygon3DRegistInfoNum; cnt++, cntDrawInfo++) {
		drawInfoSum.ms_drawInfos[cntDrawInfo] = resistInfoSum.m_polygon3DRegistInfos[cnt].ConvToDrawInfo();
	}

	// 解放
	resistInfoSum.m_polygon3DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_polygon3DRegistInfos);

	//----------------------------------------
	// モデル
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_modelRegistInfoNum; cnt++, cntDrawInfo++) {
		drawInfoSum.ms_drawInfos[cntDrawInfo] = resistInfoSum.m_modelRegistInfos[cnt].ConvToDrawInfo();
	}

	// 解放
	resistInfoSum.m_modelRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_modelRegistInfos);

	//----------------------------------------
	// ポリゴン2D
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_polygon2DRegistInfoNum; cnt++, cntDrawInfo++) {
		drawInfoSum.ms_drawInfos[cntDrawInfo] = resistInfoSum.m_polygon2DRegistInfos[cnt].ConvToDrawInfo();
	}

	// 解放
	resistInfoSum.m_polygon2DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_polygon2DRegistInfos);
}

//========================================
// 描画情報ソート処理
//========================================
void CDrawMng::SortDrawInfo(CDrawInfoSum& drawInfoSum) {

	// 描画情報の数が0以下なら終了
	if (drawInfoSum.ms_drawInfoNum <= 0)
		return;

	//----------------------------------------
	// ローカル関数の定義
	//----------------------------------------
	struct LocalFunc {
		// [[[ 優先するか調べる(ポリゴン3Dとモデル) ]]]
		static bool FindPrioritizePolygon3DAndModel(CPolygon3D::CDrawInfo* base, CModel::CDrawInfo* target) {

			if (base->m_isZTest && !target->m_isZTest) return true;		// 基準のZテストがONで比較対象ののZテストがOFF
			if (!base->m_isZTest && target->m_isZTest) return false;	// 基準のZテストがOFFで比較対象のZテストがON
			if (base->m_distance > target->m_distance) return true;		// 基準の方が距離が遠い

			return false;
		}

		// [[[ 優先するか調べる ]]]
		static bool FindPrioritize(CDrawInfoBase& base, CDrawInfoBase& target) {

			if (&base == NULL || &target == NULL) return false;		// 片方が存在しない

			// ※↓返すのは描画を優先するかなので注意
			if (base.m_priority < target.m_priority) return true;	// 基準の方が優先度が低い
			if (base.m_priority > target.m_priority) return false;	// 基準の方が優先度が高い

			if (base.m_type == CDrawInfoBase::TYPE::POLYGON2D) {
				//----------------------------------------
				// [[[ Base:ポリゴン2D ]]]
				//----------------------------------------
				if (target.m_type == CDrawInfoBase::TYPE::POLYGON2D)
				{// [[[ Target::ポリゴン2D ]]]
					CPolygon2D::CDrawInfo* castedBase   = (CPolygon2D::CDrawInfo*)&base;
					CPolygon2D::CDrawInfo* castedTarget = (CPolygon2D::CDrawInfo*)&target;

					if (castedBase->m_isZTest && !castedTarget->m_isZTest) return true;		// 基準のZテストがONで比較対象ののZテストがOFF
					if (!castedBase->m_isZTest && castedTarget->m_isZTest) return false;	// 基準のZテストがOFFで比較対象のZテストがON
					if (castedBase->m_distance > castedTarget->m_distance) return true;		// 基準の方が距離が遠い
				}
				else if (target.m_type == CDrawInfoBase::TYPE::POLYGON3D)
				{// [[[ Target::ポリゴン3D ]]]
					return true;
				}
				else if (target.m_type == CDrawInfoBase::TYPE::MODEL)
				{// [[[ Target:モデル ]]]
					return true;
				}
				else assert(false);
			}
			else if (base.m_type == CDrawInfoBase::TYPE::POLYGON3D) {
				//----------------------------------------
				// [[[ Base:ポリゴン3D ]]]
				//----------------------------------------
				if (target.m_type == CDrawInfoBase::TYPE::POLYGON2D) 
				{// [[[ Target::ポリゴン2D ]]]
					return false;
				}
				else if (target.m_type == CDrawInfoBase::TYPE::POLYGON3D)
				{// [[[ Target::ポリゴン3D ]]]
					CPolygon3D::CDrawInfo* castedBase   = (CPolygon3D::CDrawInfo*)&base;
					CPolygon3D::CDrawInfo* castedTarget = (CPolygon3D::CDrawInfo*)&target;

					if (castedBase->m_isZTest && !castedTarget->m_isZTest) return true;		// 基準のZテストがONで比較対象ののZテストがOFF
					if (!castedBase->m_isZTest && castedTarget->m_isZTest) return false;	// 基準のZテストがOFFで比較対象のZテストがON
					if (castedBase->m_distance > castedTarget->m_distance) return true;		// 基準の方が距離が遠い
				}
				else if (target.m_type == CDrawInfoBase::TYPE::MODEL)
				{// [[[ Target:モデル ]]]
					return FindPrioritizePolygon3DAndModel((CPolygon3D::CDrawInfo*)&base, (CModel::CDrawInfo*)&target);
				}
				else assert(false);
			}
			else if (base.m_type == CDrawInfoBase::TYPE::MODEL) {
				//----------------------------------------
				// [[[ Base:モデル ]]]
				//----------------------------------------
				if (target.m_type == CDrawInfoBase::TYPE::POLYGON2D)
				{// [[[ Target::ポリゴン2D ]]]
					return false;
				}
				else if (target.m_type == CDrawInfoBase::TYPE::POLYGON3D)
				{// [[[ Target::ポリゴン3D ]]]
					return !FindPrioritizePolygon3DAndModel((CPolygon3D::CDrawInfo*)&target, (CModel::CDrawInfo*)&base);
				}
				else if (target.m_type == CDrawInfoBase::TYPE::MODEL)
				{// [[[ Target:モデル ]]]
					CModel::CDrawInfo* castedBase = (CModel::CDrawInfo*)&base;
					CModel::CDrawInfo* castedTarget = (CModel::CDrawInfo*)&target;
					
					if (castedBase->m_isZTest && !castedTarget->m_isZTest) return true;		// 基準のZテストがONで比較対象ののZテストがOFF
					if (!castedBase->m_isZTest && castedTarget->m_isZTest) return false;	// 基準のZテストがOFFで比較対象のZテストがON
					if (castedBase->m_distance > castedTarget->m_distance) return true;		// 基準の方が距離が遠い
				}
				else assert(false);
			}
			else assert(false);

			return false;
		}
	};

	//----------------------------------------
	// ソート処理
	//      cnt1
	// [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ … ]
	// ※この場合2から比較していく
	//----------------------------------------
	int cnt1Num = drawInfoSum.ms_drawInfoNum - 1;
	for (int cnt1 = 0; cnt1 < cnt1Num; cnt1++) {

		// 最優先のカウントを調べる
		int cntTop = DATANONE;
		for (int cnt2 = cnt1 + 1; cnt2 < drawInfoSum.ms_drawInfoNum; cnt2++) {
			CDrawInfoBase& drawInfoCnt2 = *drawInfoSum.ms_drawInfos[cnt2];

			//----------------------------------------
			// Cnt2の描画情報 が 今の最優先描画情報 より
			// 優先度が高いかどうか判定する
			//----------------------------------------
			bool isTopPriorityCnt2 = false;

			// 最優先のカウントがNONE(つまり最初のカウント)の時、Cnt2の方が優先度が高いとする
			if (cntTop == DATANONE) {
				isTopPriorityCnt2 = true;
			}
			else {
				isTopPriorityCnt2 = LocalFunc::FindPrioritize(drawInfoCnt2, *drawInfoSum.ms_drawInfos[cntTop]);
			}
			
			// 判定の結果…
			// Cnt2の描画情報 の方が優先度が高かった時、
			// 最優先のカウントを上書きする
			if (isTopPriorityCnt2)
				cntTop = cnt2;
		}

		// Cnt1描画情報 の方が 最優先描画情報 より優先度が低い時、入れ替える
		if (!LocalFunc::FindPrioritize(*drawInfoSum.ms_drawInfos[cnt1], *drawInfoSum.ms_drawInfos[cntTop])) {
			CDrawInfoBase* drwInfoTemp = drawInfoSum.ms_drawInfos[cnt1];
			drawInfoSum.ms_drawInfos[cnt1] = drawInfoSum.ms_drawInfos[cntTop];
			drawInfoSum.ms_drawInfos[cntTop] = drwInfoTemp;
		}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 描画クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CDrawMng::CDrawMng() {

}

//========================================
// デストラクタ
//========================================
CDrawMng::~CDrawMng() {

}

//========================================
// 設置処理(ポリゴン2D)
//========================================
CPolygon2D::CRegistInfo* CDrawMng::PutPolygon2D(const D3DXVECTOR3& pos, const float& angle, const bool& isOnScreen) {

	// 登録情報
	CPolygon2D::CRegistInfo* registInfo = NULL;;

	// スクリーン上フラグに応じて登録
	if (isOnScreen) registInfo = &RegistPolygon2D(ms_resistInfoSumScreen);
	else            registInfo = &RegistPolygon2D(ms_resistInfoSum);

	// 情報を代入
	registInfo->SetPos(pos);
	registInfo->SetAngle(angle);

	return registInfo;
}

//========================================
// 設置処理(テキスト2D)
//========================================
CText2D::CRegistInfo* CDrawMng::PutText2D(const D3DXVECTOR2& pos, const float& angle, const bool& isOnScreen) {

	// 登録情報
	CText2D::CRegistInfo* registInfo = NULL;;

	// スクリーン上フラグに応じて登録
	if (isOnScreen) registInfo = &RegistText2D(ms_resistInfoSumScreen);
	else            registInfo = &RegistText2D(ms_resistInfoSum);

	// 情報を代入
	registInfo->SetPos(pos);
	registInfo->SetAngle(angle);

	return registInfo;
}

//========================================
// 設置処理(テキスト3D)
//========================================
CText3D::CRegistInfo* CDrawMng::PutText3D(const D3DXMATRIX& mtx, const bool& isOnScreen) {

	// 登録情報
	CText3D::CRegistInfo* registInfo = NULL;;

	// スクリーン上フラグに応じて登録
	if (isOnScreen) registInfo = &RegistText3D(ms_resistInfoSumScreen);
	else            registInfo = &RegistText3D(ms_resistInfoSum);

	// 情報を代入
	registInfo->SetMtx(mtx);

	return registInfo;
}

//========================================
// 設置処理(ポリゴン3D)
//========================================
CPolygon3D::CRegistInfo* CDrawMng::PutPolygon3D(const D3DXMATRIX& mtx, const bool& isOnScreen) {
	
	// 登録情報
	CPolygon3D::CRegistInfo* registInfo = NULL;;

	// スクリーン上フラグに応じて登録
	if (isOnScreen) registInfo = &RegistPolygon3D(ms_resistInfoSumScreen);
	else            registInfo = &RegistPolygon3D(ms_resistInfoSum);

	// 情報を代入
	registInfo->SetMtx(mtx);

	return registInfo;
}

//========================================
// 設置処理(モデル)
//========================================
CModel::CRegistInfo* CDrawMng::PutModel(const D3DXMATRIX& mtx, const bool& isOnScreen) {

	// 登録受付中でない時、終了
	if (ms_processState != PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	// 登録情報
	CModel::CRegistInfo* registInfo = NULL;;

	// スクリーン上フラグに応じて登録
	if (isOnScreen) registInfo = &RegistModel(ms_resistInfoSumScreen);
	else            registInfo = &RegistModel(ms_resistInfoSum);

	// 情報を代入
	registInfo->SetMtx(mtx);

	return registInfo;
}

//========================================
// 登録処理(ポリゴン2D)
//========================================
CPolygon2D::CRegistInfo& CDrawMng::RegistPolygon2D(CRegistInfoSum& resistInfo) {

	// 登録情報数を加算
	int numOld = resistInfo.m_polygon2DRegistInfoNum++;

	// 登録情報のメモリ再確保
	RNLib::Memory()->ReAlloc<CPolygon2D::CRegistInfo>(&resistInfo.m_polygon2DRegistInfos, numOld, resistInfo.m_polygon2DRegistInfoNum);

	return resistInfo.m_polygon2DRegistInfos[numOld];
}

//========================================
// 登録処理(ポリゴン3D)
//========================================
CPolygon3D::CRegistInfo& CDrawMng::RegistPolygon3D(CRegistInfoSum& resistInfo) {

	// 登録情報数を加算
	int numOld = resistInfo.m_polygon3DRegistInfoNum++;

	// 登録情報のメモリ再確保
	RNLib::Memory()->ReAlloc<CPolygon3D::CRegistInfo>(&resistInfo.m_polygon3DRegistInfos, numOld, resistInfo.m_polygon3DRegistInfoNum);

	return resistInfo.m_polygon3DRegistInfos[numOld];
}

//========================================
// 登録処理(テキスト2D)
//========================================
CText2D::CRegistInfo& CDrawMng::RegistText2D(CRegistInfoSum& resistInfo) {

	// 登録情報数を加算
	int numOld = resistInfo.m_text2DRegistInfoNum++;

	// 登録情報のメモリ再確保
	RNLib::Memory()->ReAlloc<CText2D::CRegistInfo>(&resistInfo.m_text2DRegistInfos, numOld, resistInfo.m_text2DRegistInfoNum);

	return resistInfo.m_text2DRegistInfos[numOld];
}

//========================================
// 登録処理(テキスト3D)
//========================================
CText3D::CRegistInfo& CDrawMng::RegistText3D(CRegistInfoSum& resistInfo) {

	// 登録情報数を加算
	int numOld = resistInfo.m_text3DRegistInfoNum++;

	// 登録情報のメモリ再確保
	RNLib::Memory()->ReAlloc<CText3D::CRegistInfo>(&resistInfo.m_text3DRegistInfos, numOld, resistInfo.m_text3DRegistInfoNum);

	return resistInfo.m_text3DRegistInfos[numOld];
}

//========================================
// 登録処理(モデル)
//========================================
CModel::CRegistInfo& CDrawMng::RegistModel(CRegistInfoSum& resistInfo) {

	// 登録情報数を加算
	int numOld = resistInfo.m_modelRegistInfoNum++;

	// 登録情報のメモリ再確保
	RNLib::Memory()->ReAlloc<CModel::CRegistInfo>(&resistInfo.m_modelRegistInfos, numOld, resistInfo.m_modelRegistInfoNum);

	return resistInfo.m_modelRegistInfos[numOld];
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 描画マネージャークラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 初期化処理
//========================================
void CDrawMng::Init(void) {
	
}

//========================================
// 終了処理
//========================================
void CDrawMng::Uninit(void) {

	// メインループスレッドを斬り離す
	ms_mainLoopTh.detach();

	// 解放処理
	Release();
}

//========================================
// 解放処理
//========================================
void CDrawMng::Release(void) {

	// 描画情報を破棄
	ms_drawInfoSum.Release();
	ms_drawInfoSumOvr.Release();
	ms_drawInfoSumScreen.Release();
	ms_drawInfoSumScreenOvr.Release();
	RNLib::Memory()->Release(&ms_drawInfoSum.ms_drawInfos);
	RNLib::Memory()->Release(&ms_drawInfoSumOvr.ms_drawInfos);
	RNLib::Memory()->Release(&ms_drawInfoSumScreen.ms_drawInfos);
	RNLib::Memory()->Release(&ms_drawInfoSumScreenOvr.ms_drawInfos);

	// 頂点バッファを破棄する
	CPolygon2D::CDrawInfo::ReleaseVertexBuffer();
	CPolygon3D::CDrawInfo::ReleaseVertexBuffer();
}

//========================================
// 描画開始処理
//========================================
bool CDrawMng::StartDraw(void) {

	if (ms_processState == PROCESS_STATE::REGIST_ACCEPT)
	{// [ 登録受付 ]の時、
		// [ 登録情報適用待ち ]にする
		ms_processState = PROCESS_STATE::REGIST_INFO_APPLY_WAIT;
	}
	else if ((ms_processState == PROCESS_STATE::DRAW_INFO_SWAP_WAIT && !RNLib::GetSpace3DStop()) || RNLib::GetSceneSwap())
	{// [ 描画入れ替え待ち ]の時、
		// 描画情報を上書きする
		ms_drawInfoSum.Overwrite(&ms_drawInfoSumOvr);
		ms_drawInfoSumScreen.Overwrite(&ms_drawInfoSumScreenOvr);

		// 頂点バッファを生成する
		CPolygon2D::CDrawInfo::CreateVertexBuffer();
		CPolygon3D::CDrawInfo::CreateVertexBuffer();

		// 頂点情報を代入
		AssignVertexInfo();

		// [ 登録受付 ]にする
		ms_processState = PROCESS_STATE::REGIST_ACCEPT;

		return true;
	}

	return false;
}

//========================================
// 頂点情報代入処理
//========================================
void CDrawMng::AssignVertexInfo(void) {

	// 頂点2D情報に変換
	if (CPolygon2D::CDrawInfo::m_vtxBuff != NULL) {
		VERTEX_2D* vtxs = NULL;
		CPolygon2D::CDrawInfo::m_vtxBuff->Lock(0, 0, (void**)&vtxs, 0);

		ConvDrawInfoToVertex2DInfo(vtxs, ms_drawInfoSum);
		ConvDrawInfoToVertex2DInfo(vtxs, ms_drawInfoSumScreen);

		CPolygon2D::CDrawInfo::m_vtxBuff->Unlock();
	}

	// 頂点3D情報に変換
	if (CPolygon3D::CDrawInfo::m_vtxBuff != NULL) {
		VERTEX_3D* vtxs = NULL;
		CPolygon3D::CDrawInfo::m_vtxBuff->Lock(0, 0, (void**)&vtxs, 0);

		ConvDrawInfoToVertex3DInfo(vtxs, ms_drawInfoSum);
		ConvDrawInfoToVertex3DInfo(vtxs, ms_drawInfoSumScreen);

		CPolygon3D::CDrawInfo::m_vtxBuff->Unlock();
	}
}

//========================================
// 描画情報を頂点2D情報に変換
//========================================
void CDrawMng::ConvDrawInfoToVertex2DInfo(VERTEX_2D* vtxs, CDrawInfoSum& drawInfoSum) {

	for (int cntDrawInfo = 0; cntDrawInfo < drawInfoSum.ms_drawInfoNum; cntDrawInfo++) {
		if (drawInfoSum.ms_drawInfos[cntDrawInfo]->m_type == CDrawInfoBase::TYPE::POLYGON2D) {
			CPolygon2D::CDrawInfo& drawInfo = (CPolygon2D::CDrawInfo&)*drawInfoSum.ms_drawInfos[cntDrawInfo];
			int vtxStartIdx = 4 * drawInfo.m_idx;

			for (int cntVtx = 0; cntVtx < 4; cntVtx++) {
				int vtxIdx = vtxStartIdx + cntVtx;
				vtxs[vtxIdx] = drawInfo.m_vtxs[cntVtx];
			}
		}
	}
}

//========================================
// 描画情報を頂点3D情報に変換
//========================================
void CDrawMng::ConvDrawInfoToVertex3DInfo(VERTEX_3D* vtxs, CDrawInfoSum& drawInfoSum) {

	for (int cntDrawInfo = 0; cntDrawInfo < drawInfoSum.ms_drawInfoNum; cntDrawInfo++) {
		if (drawInfoSum.ms_drawInfos[cntDrawInfo]->m_type == CDrawInfoBase::TYPE::POLYGON3D) {
			CPolygon3D::CDrawInfo& drawInfo = (CPolygon3D::CDrawInfo&)*drawInfoSum.ms_drawInfos[cntDrawInfo];
			int vtxStartIdx = 4 * drawInfo.m_idx;

			for (int cntVtx = 0; cntVtx < 4; cntVtx++) {
				int vtxIdx = vtxStartIdx + cntVtx;
				vtxs[vtxIdx] = drawInfo.m_vtxs[cntVtx];
			}
		}
	}
}

//========================================
// 描画処理
//========================================
void CDrawMng::Draw(LPDIRECT3DDEVICE9& device, const bool& isOnScreen) {

	// ビューマトリックスを取得
	D3DXMATRIX viewMtx;
	device->GetTransform(D3DTS_VIEW, &viewMtx);

	// 描画していく
	if (isOnScreen) {
		for (int cntDrawInfo = 0; cntDrawInfo < ms_drawInfoSumScreen.ms_drawInfoNum; cntDrawInfo++) {
			if (ms_drawInfoSumScreen.ms_drawInfos[cntDrawInfo] != NULL)
				ms_drawInfoSumScreen.ms_drawInfos[cntDrawInfo]->Draw(device, viewMtx);
		}
	}
	else {
		for (int cntDrawInfo = 0; cntDrawInfo < ms_drawInfoSum.ms_drawInfoNum; cntDrawInfo++) {
			if (ms_drawInfoSum.ms_drawInfos[cntDrawInfo] != NULL)
				ms_drawInfoSum.ms_drawInfos[cntDrawInfo]->Draw(device, viewMtx);
		}
	}
}