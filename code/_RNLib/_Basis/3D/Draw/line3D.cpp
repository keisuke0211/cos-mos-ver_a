//========================================
// 
// ライン3D関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ line3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
#define SPHERE_DIVISION   (16)	// 球の分割数
#define CYLINDER_DIVISION (16)	// 筒の分割数

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CLine3D::CLine3D() {
	m_pDrawSet    = NULL;	// 描画設定情報
	m_nDrawSetNum = 0;		// 描画設定数
	m_ppVtxBuff   = NULL;	// 頂点バッファへのダブルポインタ
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CLine3D::~CLine3D() {

}

//========================================
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Init(void) {

}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Uninit(void) {
	// 頂点バッファの破棄
	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		if (m_ppVtxBuff[nCntSet] != NULL) {
			m_ppVtxBuff[nCntSet]->Release();
			m_ppVtxBuff[nCntSet] = NULL;
		}
	}
	RNLib::Memory()->Release(&m_ppVtxBuff);
}

//========================================
// 描画処理
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Draw(bool bZTest) {
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();
	D3DXMATRIX mtxSelf;				// 本体マトリックス
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスを初期値で設定
	D3DXMatrixIdentity(&mtxSelf);
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	// レンダリングステートを設定
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャを設定しない
	RNLib::Texture()->Set(pDevice, DATANONE);

	// Zテストフラグに応じた有効/無効設定
	if (bZTest) {
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
	else {
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		if (m_pDrawSet[nCntSet].bZTest != bZTest)
			continue;

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_ppVtxBuff[nCntSet], 0, sizeof(Vertex3D));

		// ポリゴン3Dの描画
		pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	}

	// レンダリングステートを元に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//========================================
// 設定処理
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, Color col, bool bZTest) {
	// 過去の個数&現在の番号
	int nNumOld_and_idx = m_nDrawSetNum;

	m_nDrawSetNum++;	// 描画設定数を加算

	{// 描画設定情報のメモリ再確保
		DrawSet* pNew = new DrawSet[m_nDrawSetNum];
		int nCopySize = m_nDrawSetNum < nNumOld_and_idx ? m_nDrawSetNum : nNumOld_and_idx;
		if (nCopySize > 0) {
			memcpy(pNew, m_pDrawSet, sizeof(DrawSet) * nCopySize);
			delete m_pDrawSet;
		}
		m_pDrawSet = pNew;
	}
	
	// 描画設定情報を代入
	m_pDrawSet[nNumOld_and_idx].bZTest = bZTest;

	{// 頂点バッファへのダブルポインタのメモリ再確保
		LPDIRECT3DVERTEXBUFFER9* pNew = new LPDIRECT3DVERTEXBUFFER9[m_nDrawSetNum];
		int nCopySize = m_nDrawSetNum < nNumOld_and_idx ? m_nDrawSetNum : nNumOld_and_idx;
		if (nCopySize > 0) {
			memcpy(pNew, m_ppVtxBuff, sizeof(LPDIRECT3DVERTEXBUFFER9) * nCopySize);
			delete m_ppVtxBuff;
		}
		m_ppVtxBuff = pNew;
	}

	m_ppVtxBuff[nNumOld_and_idx] = NULL;

	// 頂点バッファの生成
	if (FAILED(RNLib::Window()->GetD3DDevice()->CreateVertexBuffer(
		sizeof(Vertex3D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_ppVtxBuff[nNumOld_and_idx],
		NULL))) {
		assert(false);	// !失敗
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	Vertex3D* pVtx;
	m_ppVtxBuff[nNumOld_and_idx]->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = pos0;
	pVtx[1].pos = pos1;

	// 色を代入
	pVtx[0].col = 
	pVtx[1].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);

	// 頂点座標をアンロックする
	m_ppVtxBuff[nNumOld_and_idx]->Unlock();
}

//========================================
// 設定処理(円)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Circle(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col, bool bZTest) {
	D3DXVECTOR3 aVtxPos[CYLINDER_DIVISION];

	for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
		// 分割カウントに応じてXZ座標を設定
		aVtxPos[nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));
		aVtxPos[nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));

		// 部品の幅/高さ/奥行きを反映
		aVtxPos[nCntDiv].x *= fRadius;
		aVtxPos[nCntDiv].z *= fRadius;
		aVtxPos[nCntDiv].y = 0.0f;

		// 頂点位置を
		// 位置向きmtxと頂点位置mtxを掛け合わせて座標値に変換したものにする
		D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
		D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntDiv], INITD3DXVECTOR3);
		aVtxPos[nCntDiv] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
	}

	for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
		Set(aVtxPos[nCntDiv],
			aVtxPos[(nCntDiv + 1) % CYLINDER_DIVISION],
			col, bZTest);
	}
}

//========================================
// 設定処理(球)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Sphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col, bool bZTest) {
	enum { l_SIRCLE_XZ, l_SIRCLE_XY, l_SIRCLE_YZ, l_SIRCLE_MAX };
	D3DXVECTOR3 aVtxPos[l_SIRCLE_MAX][SPHERE_DIVISION];

	for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++) {
		for (int nCntDiv = 0; nCntDiv < SPHERE_DIVISION; nCntDiv++) {
			aVtxPos[nCntCircle][nCntDiv] = INITD3DXVECTOR3;

			// 円カウントと分割カウントに応じて座標を設定
			switch (nCntCircle) {
			case l_SIRCLE_XZ:
				aVtxPos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				aVtxPos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				break;
			case l_SIRCLE_XY:
				aVtxPos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				aVtxPos[nCntCircle][nCntDiv].y = cosf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				break;
			case l_SIRCLE_YZ:
				aVtxPos[nCntCircle][nCntDiv].y = sinf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				aVtxPos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)SPHERE_DIVISION)) * fRadius;
				break;
			}
			

			// 頂点位置を
			// 位置向きmtxと頂点位置mtxを掛け合わせて座標値に変換したものにする
			D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
			D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntCircle][nCntDiv], INITD3DXVECTOR3);
			aVtxPos[nCntCircle][nCntDiv] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
		}
	}

	// ライン設定
	for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++) {
		for (int nCntDiv = 0; nCntDiv < SPHERE_DIVISION; nCntDiv++) {
			Set(aVtxPos[nCntCircle][nCntDiv],
				aVtxPos[nCntCircle][(nCntDiv + 1) % SPHERE_DIVISION],
				col, bZTest);
		}
	}
}

//========================================
// 設定処理(立方体)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Cube(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, Color col, bool bZTest) {
	//   A1-----B1
	//  /      /|
	// C1-----D1B2
	// |      |/
	// C2-----D2
	enum { l_A1, l_B1, l_C1, l_D1, l_A2, l_B2, l_C2, l_D2, l_MAX };
	D3DXVECTOR3 aVtxPos[l_MAX] = {
		D3DXVECTOR3(-1, 1, 1),
		D3DXVECTOR3( 1, 1, 1),
		D3DXVECTOR3(-1, 1,-1),
		D3DXVECTOR3( 1, 1,-1),
		D3DXVECTOR3(-1,-1, 1),
		D3DXVECTOR3( 1,-1, 1),
		D3DXVECTOR3(-1,-1,-1),
		D3DXVECTOR3( 1,-1,-1)
	};

	// 部品の幅/高さ/奥行きを反映
	for (int nCntVtx = 0; nCntVtx < l_MAX; nCntVtx++) {
		aVtxPos[nCntVtx] *= 0.5f;
		aVtxPos[nCntVtx].x *= fWidth;
		aVtxPos[nCntVtx].y *= fHeight;
		aVtxPos[nCntVtx].z *= fDepth;

		// 頂点位置を
		// 位置向きmtxと頂点位置mtxを掛け合わせて座標値に変換したものにする
		D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
		D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntVtx], INITD3DXVECTOR3);
		aVtxPos[nCntVtx] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
	}

	// 上の辺
	Set(aVtxPos[l_A1], aVtxPos[l_B1], col, bZTest);
	Set(aVtxPos[l_A1], aVtxPos[l_C1], col, bZTest);
	Set(aVtxPos[l_D1], aVtxPos[l_C1], col, bZTest);
	Set(aVtxPos[l_D1], aVtxPos[l_B1], col, bZTest);
	// 下の辺
	Set(aVtxPos[l_A2], aVtxPos[l_B2], col, bZTest);
	Set(aVtxPos[l_A2], aVtxPos[l_C2], col, bZTest);
	Set(aVtxPos[l_D2], aVtxPos[l_C2], col, bZTest);
	Set(aVtxPos[l_D2], aVtxPos[l_B2], col, bZTest);
	// 縦の辺
	Set(aVtxPos[l_A1], aVtxPos[l_A2], col, bZTest);
	Set(aVtxPos[l_B1], aVtxPos[l_B2], col, bZTest);
	Set(aVtxPos[l_C1], aVtxPos[l_C2], col, bZTest);
	Set(aVtxPos[l_D1], aVtxPos[l_D2], col, bZTest);
}

//========================================
// 設定処理(筒)
// Author:RIKU NISHIMURA
//========================================
void CLine3D::Set_Cylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, Color col, bool bZTest) {
	enum { l_SIRCLE_UPPER, l_SIRCLE_BOTTOM, l_SIRCLE_MAX };
	D3DXVECTOR3 aVtxPos[l_SIRCLE_MAX][CYLINDER_DIVISION];

	for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++) {
		for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
			// 円のカウントに応じたY座標を設定
			switch (nCntCircle) {
			case l_SIRCLE_UPPER:
				aVtxPos[nCntCircle][nCntDiv].y = 1;
				break;
			case l_SIRCLE_BOTTOM:
				aVtxPos[nCntCircle][nCntDiv].y = -1;
				break;
			}

			// 分割カウントに応じてXZ座標を設定
			aVtxPos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));
			aVtxPos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)CYLINDER_DIVISION));

			// 部品の幅/高さ/奥行きを反映
			aVtxPos[nCntCircle][nCntDiv].x *= fRadius;
			aVtxPos[nCntCircle][nCntDiv].z *= fRadius;
			aVtxPos[nCntCircle][nCntDiv].y *= fHeight * 0.5f;

			// 頂点位置を
			// 位置向きmtxと頂点位置mtxを掛け合わせて座標値に変換したものにする
			D3DXMATRIX posRotMtx = ConvPosRotToMatrix(pos, rot);
			D3DXMATRIX vtxPoxMtx = ConvPosRotToMatrix(aVtxPos[nCntCircle][nCntDiv], INITD3DXVECTOR3);
			aVtxPos[nCntCircle][nCntDiv] = ConvMatrixToPos(MultiplyMatrix(posRotMtx, vtxPoxMtx));
		}
	}

	for (int nCntDiv = 0; nCntDiv < CYLINDER_DIVISION; nCntDiv++) {
		// 縦の辺
		Set(aVtxPos[l_SIRCLE_UPPER][nCntDiv],
			aVtxPos[l_SIRCLE_BOTTOM][nCntDiv],
			col, bZTest);

		// 上の周囲辺
		Set(aVtxPos[l_SIRCLE_UPPER][nCntDiv],
			aVtxPos[l_SIRCLE_UPPER][(nCntDiv + 1) % CYLINDER_DIVISION],
			col, bZTest);

		// 下の周囲辺
		Set(aVtxPos[l_SIRCLE_BOTTOM][nCntDiv],
			aVtxPos[l_SIRCLE_BOTTOM][(nCntDiv + 1) % CYLINDER_DIVISION],
			col, bZTest);
	}
}

//========================================
// 設定リセット
// Author:RIKU NISHIMURA
//========================================
void CLine3D::SetReset(void) {
	// 頂点バッファの破棄
	for (int nCntSet = 0; nCntSet < m_nDrawSetNum; nCntSet++) {
		if (m_ppVtxBuff[nCntSet] != NULL) {
			m_ppVtxBuff[nCntSet]->Release();
			m_ppVtxBuff[nCntSet] = NULL;
		}
	}
	RNLib::Memory()->Release(&m_ppVtxBuff);
	RNLib::Memory()->Release(&m_pDrawSet);

	m_nDrawSetNum = 0;	// 描画設定数を初期化
}