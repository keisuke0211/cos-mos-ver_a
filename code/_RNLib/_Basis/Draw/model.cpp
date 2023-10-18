//========================================
// 
// モデルの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// 定数定義
//****************************************
#define OUTLINE_ADD_DIST (0.2f)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| モデルクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CModel::CModel() {

	m_datas = NULL;
}

//========================================
// デストラクタ
//========================================
CModel::~CModel() {

}

//========================================
// 終了処理
//========================================
void CModel::Uninit(void) {
	CRegist::Uninit();

	// 解放処理
	Release();
}

//========================================
// 解放処理
//========================================
void CModel::Release(void) {

	// データの破棄
	for (int nCnt = 0; nCnt < m_num; nCnt++) {
		m_datas[nCnt].Release();
	}
	RNLib::Memory()->Release<CData>(&m_datas);
}

//========================================
// 読み込み処理
//========================================
short CModel::Load(const char *loadPath, short idx) {

	unsigned short numOld = m_num;

	if (CRegist::Load(loadPath, &idx)) 
	{// 読み込み成功
		// データのメモリ再確保
		RNLib::Memory()->ReAlloc<CData>(&m_datas, numOld, m_num);

		// データの破棄(番号指定の場合)
		if (idx != DATANONE) {
			m_datas[idx].Release();
		}

		// Xファイルの読み込み
		LPDIRECT3DDEVICE9 device = RNLib::Window()->GetD3DDevice();
		if (FAILED(D3DXLoadMeshFromX(loadPath, D3DXMESH_SYSTEMMEM, device, NULL, &m_datas[idx].m_matBuff, NULL, (DWORD*)&m_datas[idx].m_matNum, &m_datas[idx].m_mesh))) 
		{// 読み込み失敗
			// データのメモリリセット
			RNLib::Memory()->ReAlloc<CData>(&m_datas, m_num, numOld);

			// 読み込み済パスのメモリリセット
			RNLib::Memory()->ReAlloc<char*>(&m_ppLoadPath, m_num, numOld);

			// 数をリセット
			m_num = numOld;

			return DATANONE;
		}
		else 
		{// 読み込みに成功した時、
			//----------------------------------------
			// 輪郭線メッシュの生成 & 半径の最大を調べる
			//----------------------------------------
			{
				// 輪郭線用にもう一度読み込む
				D3DXLoadMeshFromX(loadPath, D3DXMESH_SYSTEMMEM, device, NULL, NULL, NULL, NULL, &m_datas[idx].m_outLineMesh);

				// 頂点フォーマットのサイズを取得
				DWORD dwSizeFVF = D3DXGetFVFVertexSize(m_datas[idx].m_outLineMesh->GetFVF());

				// 頂点バッファをロック
				BYTE* vtxBuff;
				m_datas[idx].m_outLineMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vtxBuff);

				// 法線方向に加算
				int nVtxNum = (int)m_datas[idx].m_outLineMesh->GetNumVertices();
				for (int nCntVtx = 0; nCntVtx < nVtxNum; nCntVtx++) {
					D3DXVECTOR3* pos =  (D3DXVECTOR3*)(vtxBuff + (dwSizeFVF * nCntVtx));
					D3DXVECTOR3  nor = *(D3DXVECTOR3*)(vtxBuff + (dwSizeFVF * nCntVtx) + D3DXGetFVFVertexSize(D3DFVF_XYZ));

					{// 半径の最大を調べる
						float dist = Find_Dist(INITD3DXVECTOR3, *pos);

						if (m_datas[idx].m_radiusMax < dist) {
							m_datas[idx].m_radiusMax = dist;
						}
					}

					*pos += nor * OUTLINE_ADD_DIST;
				}

				// 頂点バッファをアンロック
				m_datas[idx].m_outLineMesh->UnlockVertexBuffer();
			}// <<< >>>

			// マテリアル情報に対するポインタを取得
			D3DXMATERIAL* mats = (D3DXMATERIAL*)m_datas[idx].m_matBuff->GetBufferPointer();

			// テクスチャ番号のメモリ確保
			RNLib::Memory()->Alloc<short>(&m_datas[idx].m_texIdxs, m_datas[idx].m_matNum);

			// テクスチャの読み込み
			for (int nCntMat = 0; nCntMat < m_datas[idx].m_matNum; nCntMat++) {
				if (mats[nCntMat].pTextureFilename != NULL) {
					m_datas[idx].m_texIdxs[nCntMat] = RNLib::Texture()->Load(mats[nCntMat].pTextureFilename);
				}
				else {
					m_datas[idx].m_texIdxs[nCntMat] = DATANONE;
				}
			}
		}
	}

	return idx;
}

//========================================
// 設置処理
//========================================
CModel::CRegistInfo* CModel::Put(const D3DXMATRIX& mtx, const short& modelIdx, const bool& isOnScreen) {

	// 登録受付中でない時、終了
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng()->PutModel(mtx, isOnScreen)
		->SetModel(modelIdx);
}

//========================================
// 設置処理(位置と向きで指定)
//========================================
CModel::CRegistInfo* CModel::Put(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const short& modelIdx, const bool& isOnScreen) {
	
	return Put(ConvPosRotToMatrix(pos, rot), modelIdx, isOnScreen);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| データクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CModel::CData::CData() {

	m_texIdxs     = NULL;
	m_mesh        = NULL;
	m_outLineMesh = NULL;
	m_matBuff     = NULL;
	m_matNum      = 0;
	m_radiusMax   = 0.0f;
}

//========================================
// デストラクタ
//========================================
CModel::CData::~CData() {

}

//========================================
// 解放処理
//========================================
void CModel::CData::Release(void) {

	// テクスチャ番号の破棄
	RNLib::Memory()->Release<short>(&m_texIdxs);

	// メッシュの破棄
	if (m_mesh != NULL) {
		m_mesh->Release();
		m_mesh = NULL;
	}

	// 輪郭線メッシュの破棄
	if (m_outLineMesh != NULL) {
		m_outLineMesh->Release();
		m_outLineMesh = NULL;
	}

	// マテリアルの破棄
	if (m_matBuff != NULL) {
		m_matBuff->Release();
		m_matBuff = NULL;
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 描画情報クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CModel::CDrawInfo::CDrawInfo() {

	m_mtx                  = INITD3DXMATRIX;
	m_col                  = INITCOLOR;
	m_modelIdx             = DATANONE;
	m_texIdx               = DATANONE;
	m_isZTest              = true;
	m_isLighting           = true;
	m_isOutLine            = false;
	m_brightnessOfEmissive = 1.0f;
	m_distance             = 0.0f;
}

//========================================
// デストラクタ
//========================================
CModel::CDrawInfo::~CDrawInfo() {

}

//========================================
// 描画処理
//========================================
void CModel::CDrawInfo::Draw(LPDIRECT3DDEVICE9& device, const D3DXMATRIX& viewMtx) {

	//----------------------------------------
	// 事前準備
	//----------------------------------------
	// モデルデータを取得
	CData& modelData = RNLib::Model()->GetData(m_modelIdx);

	// 本体のワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &m_mtx);

	// マテリアルデータへのポインタを取得
	D3DXMATERIAL* mats = (D3DXMATERIAL*)modelData.m_matBuff->GetBufferPointer();

	//----------------------------------------
	// 一時的な描画モード設定を開始
	//----------------------------------------
	RNLib::DrawStateMng()->StartTemporarySetMode();

	RNLib::DrawStateMng()->SetLightingMode(m_isLighting, device);

	for (int cntMat = 0; cntMat < modelData.m_matNum; cntMat++) {
		
		//----------------------------------------
		// パラメーターに応じた設定
		//----------------------------------------
		{// [[[ マテリアルの設定 ]]]
			Color setCol = m_col;

			// 発光部分の明るさが設定されている時、
			if (m_brightnessOfEmissive < 1.0f) {

				// 発光要素があれば適用
				if (0.0f < mats[cntMat].MatD3D.Emissive.r + mats[cntMat].MatD3D.Emissive.g + mats[cntMat].MatD3D.Emissive.b) {
					setCol = BrightnessToColor(setCol, m_brightnessOfEmissive);
				}
			}
			
			// マテリアルを設定
			SetMaterial(device, &mats[cntMat].MatD3D, setCol);
		}

		// [[[ テクスチャの設定 ]]]
		if (m_texIdx == DATANONE)
			RNLib::Texture()->Set(device, modelData.m_texIdxs[cntMat]);
		else
			RNLib::Texture()->Set(device, m_texIdx);

		//----------------------------------------
		// 描画
		//----------------------------------------
		// 表面を描画
		RNLib::DrawStateMng()->SetCullingMode(CDrawState::CULLING_MODE::FRONT_SIDE, device);
		modelData.m_mesh->DrawSubset(cntMat);

		//----------------------------------------
		// 輪郭線の描画
		//----------------------------------------
		if (m_isOutLine) {

			// マテリアルの設定
			SetMaterial(device, &mats[cntMat].MatD3D, COLOR_BLACK);

			// 裏面を描画
			RNLib::DrawStateMng()->SetCullingMode(CDrawState::CULLING_MODE::BACK_SIDE, device);
			modelData.m_outLineMesh->DrawSubset(cntMat);
		}
	}

	//----------------------------------------
	// 一時的な描画モード設定を終了
	//----------------------------------------
	RNLib::DrawStateMng()->EndTemporarySetMode(device);
}

//========================================
// マテリアル設定処理
//========================================
void CModel::CDrawInfo::SetMaterial(LPDIRECT3DDEVICE9& device, D3DMATERIAL9* mat, const Color& col) {

	// マテリアルの材質パラメータを保存
	D3DXCOLOR DiffuseTemp  = mat->Diffuse;
	D3DXCOLOR EmissiveTemp = mat->Emissive;

	// マテリアルの材質パラメータを設定
	mat->Diffuse.r  = DiffuseTemp.r * ((float)col.r / 255);
	mat->Diffuse.g  = DiffuseTemp.g * ((float)col.g / 255);
	mat->Diffuse.b  = DiffuseTemp.b * ((float)col.b / 255);
	mat->Diffuse.a  = DiffuseTemp.a * ((float)col.a / 255);
	mat->Emissive.r = EmissiveTemp.r * ((float)col.r / 255);
	mat->Emissive.g = EmissiveTemp.g * ((float)col.g / 255);
	mat->Emissive.b = EmissiveTemp.b * ((float)col.b / 255);
	mat->Emissive.a = EmissiveTemp.a * ((float)col.a / 255);

	// マテリアルの設定
	device->SetMaterial(mat);

	// マテリアルの材質パラメータを元に戻す
	mat->Diffuse  = DiffuseTemp;
	mat->Emissive = EmissiveTemp;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 登録情報クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CModel::CRegistInfo::CRegistInfo() {

	m_mtx                  = INITD3DXMATRIX;
	m_col                  = INITCOLOR;
	m_modelIdx             = DATANONE;
	m_texIdx               = DATANONE;
	m_isZTest              = false;
	m_isLighting           = true;
	m_isOutLine            = false;
	m_brightnessOfEmissive = 1.0f;
	m_priority             = 0;
}

//========================================
// デストラクタ
//========================================
CModel::CRegistInfo::~CRegistInfo() {

}

//========================================
// 描画情報に変換
//========================================
CModel::CDrawInfo* CModel::CRegistInfo::ConvToDrawInfo(void) {

	// 描画情報のメモリ確保
	CDrawInfo* drawInfo = NULL;
	RNLib::Memory()->Alloc<CDrawInfo>(&drawInfo);

	// 情報を代入
	// (基底)
	drawInfo->m_type                 = CDrawInfoBase::TYPE::MODEL;
	drawInfo->m_priority             = m_priority;
	// (継承)
	drawInfo->m_mtx                  = m_mtx;
	drawInfo->m_col                  = m_col;
	drawInfo->m_modelIdx             = m_modelIdx;
	drawInfo->m_texIdx               = m_texIdx;
	drawInfo->m_isZTest              = m_isZTest;
	drawInfo->m_isLighting           = m_isLighting;
	drawInfo->m_isOutLine            = m_isOutLine;
	drawInfo->m_brightnessOfEmissive = m_brightnessOfEmissive;
	{// 距離を算出
		// 拡大倍率の最大を算出
		float scaleMax = 0.0f; {
			float scaleX = FindMatrixScaleX(m_mtx);
			float scaleY = FindMatrixScaleY(m_mtx);
			float scaleZ = FindMatrixScaleZ(m_mtx);

			scaleMax = scaleX;
			if (scaleMax < scaleY)
				scaleMax = scaleY;
			if (scaleMax < scaleZ)
				scaleMax = scaleZ;
		}
		drawInfo->m_distance = Find_DistToCameraPlane(ConvMatrixToPos(m_mtx)) - (RNLib::Model()->GetData(m_modelIdx).m_radiusMax * scaleMax);
	}

	return drawInfo;
}


//========================================
// マトリックスを設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetMtx(const D3DXMATRIX& mtx) {

	if (this == NULL)
		return NULL;

	m_mtx = mtx;

	return this;
}

//========================================
// 色を設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetCol(const Color& col) {

	if (this == NULL)
		return NULL;

	m_col = col;

	return this;
}

//========================================
// モデルを設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetModel(const short& modelIdx) {

	if (this == NULL)
		return NULL;

	m_modelIdx = modelIdx;

	return this;
}

//========================================
// テクスチャを設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetTex(const short& texIdx) {

	if (this == NULL)
		return NULL;

	m_texIdx = texIdx;

	return this;
}

//========================================
// Zテストを設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetZTest(const bool& isZTest) {

	if (this == NULL)
		return NULL;

	m_isZTest = isZTest;

	return this;
}

//========================================
// ライティングを設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetLighting(const bool& isLighting) {

	if (this == NULL)
		return NULL;

	m_isLighting = isLighting;

	return this;
}

//========================================
// 輪郭線を設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetOutLine(const bool& isOutLine) {

	if (this == NULL)
		return NULL;

	m_isOutLine = isOutLine;

	return this;
}

//========================================
// 発光部分の明るさを設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetBrightnessOfEmissive(const float& brightnessOfEmissive) {

	if (this == NULL)
		return NULL;

	m_brightnessOfEmissive = brightnessOfEmissive;

	return this;
}

//========================================
// 優先度設定
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetPriority(const short& priority) {

	if (this == NULL)
		return NULL;

	m_priority = priority;

	return this;
}
