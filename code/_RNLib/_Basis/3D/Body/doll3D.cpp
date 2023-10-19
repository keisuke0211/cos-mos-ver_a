//========================================
// 
// ドール3Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
#define PAUSE_RESET_TIME (10)

#if 0
//================================================================================
//----------|---------------------------------------------------------------------
//==========| ボーン状態クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CDoll3D::CBoneState::CBoneState() {

	m_pos			= INITD3DXVECTOR3;
	m_rot			= INITD3DXVECTOR3;
	m_scale			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_resultMtx		= INITD3DXMATRIX;
	m_animeStateSum = {};
}

//========================================
// デストラクタ
//========================================
CDoll3D::CBoneState::~CBoneState() {

}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| ドール3Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CDoll3D::CDoll3D(void) {

	m_pos			 = INITD3DXVECTOR3;
	m_rot			 = INITD3DXVECTOR3;
	m_boneStates     = NULL;

	m_bMotionStop	 = false;
	m_bDrawCollision = false;		
	m_nModelSetUp	 = 0;			
	m_nMotion		 = 0;			
	m_nMotionOld	 = 0;			
	m_nMotionCounter = 0;			
	m_col			 = CLEARCOLOR;	
	m_fBrOfEm        = 1.0f;
	m_fScale         = 1.0f;
}

//========================================
// デストラクタ
//========================================
CDoll3D::~CDoll3D(void) {

	// 部品情報のメモリ解放
	RNLib::Memory()->Release(&m_boneStates);
}

//========================================
// 初期化処理
//========================================
void CDoll3D::SetUp(const short& setUpIdx) {

	// セットアップデータ取得
	CSetUp3D::CData& setUp = RNLib::ModelSetUp()->GetData(setUpIdx);

	//----------------------------------------
	// ボーン状態メモリ
	// 部品数が0を越えている > メモリ確保
	//----------------------------------------
	if (setUp.m_boneDataSum.boneDataNum > 0)
		RNLib::Memory()->Alloc<CBoneState>(&m_boneStates, setUp.m_boneDataSum.boneDataNum);
	else
		RNLib::Memory()->Release<CBoneState>(&m_boneStates);
}

//========================================
// モデル設定処理
//========================================
void CDoll3D::ModelSet(Data *pPartsSet) {

	// 部品数0以下の時、処理を終了する
	if (pPartsSet->nPartsNum <= 0)return;

	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();	// デバイスを取得
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DXMATRIX mtxSelf;				// 本体のマトリックス
	D3DXMATRIX *pMtxParts = NULL;	// 部品毎のマトリックスのポインタ

	// 部品毎のマトリックスのメモリを部品数分確保
	pMtxParts = new D3DXMATRIX[pPartsSet->nPartsNum];

	// 本体のワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxSelf);

	// 本体の向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

	// 本体の位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

	// 本体のワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++) {
		CBoneState *pParts = &m_boneStates[nCntParts];	// 部品の情報のポインタ
		PartsData *pPartsType = &pPartsSet->pPartsData[nCntParts];	// 部品の種類毎の情報のポインタ
		D3DXVECTOR3 posResult;	// 位置(結果)
		D3DXVECTOR3 rotResult;	// 向き(結果)

		{//========== [[[ 位置(結果)を更新 ]]]
			if (pParts->bPosAnim)
			{// 位置アニメフラグが真の時、カウンターの進行率に応じて位置を更新
				float fRate = Easing(pParts->easePos, pParts->nCounterPosAnim, pParts->nPosAnimTime - 1);
				pParts->pos = (pParts->oldPos * (1.0f - fRate)) + (pParts->targetPos * fRate);
			}

			// 結果位置を求める
			posResult = pParts->pos + pPartsType->fixedRelativePos;

			// 親番号が-1の時、結果位置に拡大倍率を乗算
			if (pPartsType->nParent == -1) {
				posResult *= m_fScale;
			}
		}

		float fStepRate = 0.0f;	// 足踏割合

		{//========== [[[ 向き(結果)を更新 ]]]
			if (pParts->bStep) 
			{// 足踏フラグが真の時、
				int nCounter = pParts->nCounterRotAnim;
				if (nCounter > pParts->nRotAnimTime) {
					nCounter = pParts->nRotAnimTime;
				}
				int nCounterReset = pParts->nCounterRotAnim - (pParts->nStepTime - pParts->nStepResetTime);
				if (nCounterReset < 0) {
					nCounterReset = 0;
				}
				fStepRate = Easing(EASE_LINEAR, nCounter, pParts->nRotAnimTime) * (1.0f - Easing(EASE_LINEAR, nCounterReset, pParts->nStepResetTime));
			}
			else if (pParts->bRotAnim)
			{// 向きアニメフラグが真の時、カウンターの進行率に応じて向きを更新
				float fRate = Easing(pParts->easeRot, pParts->nCounterRotAnim, pParts->nRotAnimTime - 1);
				pParts->rot = (pParts->oldRot * (1.0f - fRate)) + (pParts->targetRot * fRate);
			}

			// 結果位置を求める
			rotResult = pParts->rot + pPartsType->fixedRelativeRot;
		}

		{//========== [[[ 拡大倍率(結果)を更新 ]]]
			if (pParts->bScaleAnim)
			{// 拡大倍率アニメフラグが真の時、カウンターの進行率に応じて拡大倍率を更新
				float fRate = Easing(pParts->easeScale, pParts->nCounterScaleAnim, pParts->nScaleAnimTime - 1);
				pParts->scale = (pParts->scaleOld * (1.0f - fRate)) + (pParts->targetScale * fRate);
			}
		}

		{// 部品のワールドマトリックスの算出
			// 部品のワールドマトリックスの初期化
			D3DXMatrixIdentity(&pMtxParts[nCntParts]);

			if (pPartsType->nParent == -1)
			{// 親番号が-1の時、モデルのサイズを適用
				D3DXMatrixScaling(
					&pMtxParts[nCntParts],
					m_fScale * pParts->scale.x, 
					m_fScale * pParts->scale.y, 
					m_fScale * pParts->scale.z);
			}
			else 
			{// 親がいる時、自身の拡大倍率のみ適用
				D3DXMatrixScaling(
					&pMtxParts[nCntParts],
					pParts->scale.x,
					pParts->scale.y,
					pParts->scale.z);
			}

			D3DXMATRIX mtxOvl = pMtxParts[nCntParts];	// 現状マトリックスを保存

			// 部品の向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rotResult.y, rotResult.x, rotResult.z);
			D3DXMatrixMultiply(&pMtxParts[nCntParts], &pMtxParts[nCntParts], &mtxRot);

			// 部品の位置を反映
			D3DXMatrixTranslation(&mtxTrans, posResult.x, posResult.y, posResult.z);
			D3DXMatrixMultiply(&pMtxParts[nCntParts], &pMtxParts[nCntParts], &mtxTrans);

			// 親の部品のマトリックス
			D3DXMATRIX mtxParent;

			// 部品の親番号が-1(親無し)でない時、親マトリックスを設定。親無しであれば自身のマトリックスを設定
			if (pPartsType->nParent != -1) { mtxParent = pMtxParts[pPartsType->nParent]; }
			else                           { mtxParent = mtxSelf; }

			// 算出した部品のワールドマトリックスと親のマトリックスを掛け合わせる
			D3DXMatrixMultiply(
				&pMtxParts[nCntParts],
				&pMtxParts[nCntParts],
				&mtxParent);

			if (pParts->bStep) {
				// サイズを変更
				D3DXMatrixScaling(&mtxOvl, m_fScale, m_fScale, m_fScale);

				// 本体の向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
				D3DXMatrixMultiply(&mtxOvl, &mtxOvl, &mtxRot);

				// 部品の位置を代入
				mtxOvl._41 = pMtxParts[nCntParts]._41;
				mtxOvl._42 = pMtxParts[nCntParts]._42;
				mtxOvl._43 = pMtxParts[nCntParts]._43;

				// 割合でマトリックスを求める
				pMtxParts[nCntParts] = (pMtxParts[nCntParts] * (1.0f - fStepRate)) + (mtxOvl * fStepRate);
			}
		}

		// モデルの設定処理
		RNLib::Model()->Put(pMtxParts[nCntParts], pPartsType->nModelIdx)
			->SetCol(m_col)
			->SetLighting(pPartsType->bLighting)
			->SetOutLine(true)
			->SetBrightnessOfEmissive(m_fBrOfEm);

		// マトリックスを部品に保存
		pParts->resultMtx = pMtxParts[nCntParts];
	}

	// 部品毎のマトリックスのメモリ解放
	delete pMtxParts;

	if (m_pCLParts != NULL) 
	{// コリジョン部品が存在する時、コリジョン部品の位置計算
		CSetUp3D::Data* pModelSetUp = RNLib::ModelSetUp()->GetData(m_nModelSetUp);
		for (int nCntCLParts = 0; nCntCLParts < pModelSetUp->collSet.nPartsNum; nCntCLParts++) {
			CCollision3D::Parts collParts = pModelSetUp->collSet.pParts[nCntCLParts];
			D3DXVECTOR3 pos = INITD3DXVECTOR3;
			D3DXVECTOR3 rot = INITD3DXVECTOR3;

			if (pModelSetUp->collSet.pParts[nCntCLParts].nParent == DATANONE) {
				pos = m_pos;
				rot = m_rot;
			}
			else {
				CDoll3D::CBoneState parts = {};	// 部品情報

				if (GetPartsState_Idx(pModelSetUp->collSet.pParts[nCntCLParts].nParent, &parts)) {
					pos = ConvMatrixToPos(parts.resultMtx);
					rot = ConvMatrixToRot(parts.resultMtx);
				}
				else {
					pos = m_pos;
					rot = m_rot;
				}
			}

			D3DXMATRIX mtx = MultiplyMatrix(
				ConvPosRotToMatrix(collParts.pos, collParts.rot),
				ConvPosRotToMatrix(pos, rot));
			m_pCLParts[nCntCLParts].pos = ConvMatrixToPos(mtx);
			m_pCLParts[nCntCLParts].rot = ConvMatrixToRot(mtx);
		}
	}
}


//========================================
// 更新処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::Update(void) {
	// モデルセットアップ情報
	CSetUp3D::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	if (m_nModelSetUp != DATANONE)
	{// モデルセットアップ番号が-1 or の時、
		if (!m_bMotionStop)
		{// 停止していない時、
			// モーション設定
			MotionSet(setUp.boneDataSum);

			// モーションの更新処理
			MotionUpdate(m_nMotion, setUp.boneDataSum);
		}

		// モデルの設定処理
		ModelSet(&setUp.boneDataSum);

		if (m_bDrawCollision)
			DrawCollision();
	}

	// 影を設定
	RNLib::Shadow3D()->Set(m_pos);
}

//========================================
// モーション終了取得
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetMotionEnd(void) {
	return m_nMotionCounter >= RNLib::Motion3D()->GetData()[m_nMotion].nLoopTime;
}

//========================================
// モーション踏み取得
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetMotionStep(void) {
	CSetUp3D::Data modelSetUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);
	CMotion3D  ::Data motion     =  RNLib::Motion3D  ()->GetData()[m_nMotion];

	for (int nCntParts = 0; nCntParts < modelSetUp.boneDataSum.nPartsNum; nCntParts++) {
		if (m_boneStates[nCntParts].bStepReaction)
		{// 足踏反応フラグが真の時、
			return true;
		}
		else if (m_boneStates[nCntParts].bStep)
		{// 足踏フラグが真の時、
			if (m_boneStates[nCntParts].nCounterRotAnim == m_boneStates[nCntParts].nRotAnimTime) {
				return true;
			}
		}
	}

	return false;
}

//========================================
// 部品情報取得(番号指定)
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetPartsState_Idx(int nIdx, CBoneState* pParts) {
	// モデルセットアップ情報
	CSetUp3D::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntParts = 0; nCntParts < setUp.boneDataSum.nPartsNum; nCntParts++) {
		if (setUp.boneDataSum.pPartsData[nCntParts].nIdx == nIdx) {
			*pParts = m_boneStates[nCntParts];
			return true;
		}
	}

	return false;
}

//========================================
// 部品情報取得(部位指定)
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetPartsState_Part(int nPart, CBoneState* pParts) {
	// モデルセットアップ情報
	CSetUp3D::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	// モデル構成に応じた部位番号取得
	int nIdx = RNLib::ModelSetUp()->GetPlatformPartIdx(setUp.platform, (CSetUp3D::PART)nPart);

	for (int nCntParts = 0; nCntParts < setUp.boneDataSum.nPartsNum; nCntParts++) {
		if (setUp.boneDataSum.pPartsData[nCntParts].nIdx == nIdx) {
			*pParts = m_boneStates[nCntParts];
			return true;
		}
	}

	*pParts = m_boneStates[0];

	return false;
}

//========================================
// モーション3Dの設定処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::MotionSet(Data partsSet) {
	if (m_nMotion == m_nMotionOld)
	{// 既にそのモーション番号に設定されている時、
		return;	// 処理を終了する
	}

	// モーションクリア
	MotionClear(partsSet, m_nMotion);
	
	// 過去のモーション番号として保存
	m_nMotionOld = m_nMotion;

	// モーションカウンターを初期化
	m_nMotionCounter = 0;
}

//========================================
// モーション3Dの更新処理
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::MotionUpdate(int nMotion, Data partsSet) {
	if (nMotion == DATANONE) {
		return false;
	}

	CMotion3D::Data motion = RNLib::Motion3D()->GetData()[nMotion];	// モーション情報

	if (motion.nLoopTime == DATANONE)
	{// モーションのループ時間が無しの時、
		// 処理を終了する
		return false;
	}

	// モーションのアニメ3D読み込み処理
	LoadMotionAnim(partsSet);

	// モーションのアニメ処理
	MotionAnim(partsSet);

	// モーションがループしたかフラグ
	bool bMotionLoop = false;

	if (++m_nMotionCounter > motion.nLoopTime)
	{// モーションカウンターを加算した結果ループ時間に達した時、
		bMotionLoop = true;	// モーションがループしたかフラグを真にする

		if (motion.bLoop)
		{// ループするかフラグが真の時、
			// モーションカウンターをループ制御
			IntLoopControl(&m_nMotionCounter, motion.nLoopTime + 1, 0);
		}
		else
		{// ループするかフラグが偽の時、
			// モーションカウンターを制御
			IntControl(&m_nMotionCounter, motion.nLoopTime + 1, 0);
		}
	}

	// モーションがループしたかフラグを返す
	return bMotionLoop;
}


//========================================
// モーション3Dのアニメ読み込み処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::LoadMotionAnim(Data partsSet) {
	CSetUp3D::PLATFORM platform = RNLib::ModelSetUp()->GetData(m_nModelSetUp)->platform;
	CMotion3D::Data       motion   = RNLib::Motion3D()->GetData()[m_nMotion];

	// 部品全ての一部情報初期化
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		m_boneStates[nCntParts].bStepReaction = false;
	}

	// 部品毎のアニメの読み込み
	for (int nCntPartsAnim = 0; nCntPartsAnim < motion.pfData[platform].nPartsNum; nCntPartsAnim++) {
		// 部品毎のモーション3Dの情報
		CMotion3D::PartsCmd partsMotion3D = motion.pfData[platform].pPartsCmd[nCntPartsAnim];

		for (int nCntCmd = 0; nCntCmd < partsMotion3D.nCmdNum; nCntCmd++) {
			CMotion3D::Cmd cmd = partsMotion3D.pCmd[nCntCmd];	// コマンド情報
			CBoneState *pParts = m_boneStates;	// 部品3Dの情報

			{// 一致した部品番号までポインタを進める
				bool bFind = false;	// 一致部品確認フラグ
				for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++, pParts++) {
					if (partsSet.pPartsData[nCntParts].nIdx == nCntPartsAnim)
					{// 部品毎のアニメカウントと部品番号が一致した時、
						bFind = true;
						break;
					}
				}

				if ((m_nMotionCounter != cmd.nTime) || (!bFind))
				{// カウンターが実行時間と一致していない or 一致部品未確認、
					continue;
				}
			}

			// コマンドラベルに応じた処理
			switch (cmd.command) {
			case CMotion3D::CMD_LABEL_MOVE: {
				D3DXVECTOR3 pos       = D3DXVECTOR3(cmd.pData[0], cmd.pData[1], cmd.pData[2]);	// 位置
				int         nMoveTime = (int)cmd.pData[3];			// 移動にかかる時間
				EASE        ease      = (EASE)((int)cmd.pData[4]);	// 補間

				if (nMoveTime == 0)
				{// 移動にかかる時間が0の時、
					pParts->pos = pos;	// 位置を直接代入
				}
				else
				{// 移動にかかる時間が0でない時、
					pParts->easePos         = ease;			// 位置補間を設定
					pParts->oldPos          = pParts->pos;	// 元の位置を設定
					pParts->targetPos       = pos;			// 目標位置を代入
					pParts->nPosAnimTime    = nMoveTime;	// 位置アニメにかかる時間を代入
					pParts->nCounterPosAnim = 0;			// 位置アニメカウンターを初期化
					pParts->bPosAnim        = true;			// 位置アニメフラグを真にする
				}
			}
			break;
			case CMotion3D::CMD_LABEL_SPIN: {
				D3DXVECTOR3 rot       = D3DXVECTOR3(cmd.pData[0], cmd.pData[1], cmd.pData[2]);	// 向き
				int         nSpinTime = (int)cmd.pData[3];			// 回転にかかる時間
				EASE        ease      = (EASE)((int)cmd.pData[4]);	// 補間

				if (nSpinTime == 0)
				{// 回転にかかる時間が0の時、
					pParts->rot = rot;	// 向きを直接代入
				}
				else
				{// 回転にかかる時間が0でない時、
					pParts->easeRot         = ease;			// 向き補間を設定
					pParts->oldRot          = pParts->rot;	// 元の向きを設定
					pParts->targetRot       = rot;			// 目標向きを代入
					pParts->nRotAnimTime    = nSpinTime;	// 向きアニメにかかる時間を代入
					pParts->nCounterRotAnim = 0;			// 向きアニメカウンターを初期化
					pParts->bRotAnim        = true;			// 向きアニメフラグを真にする
				}
			}
			break;
			case CMotion3D::CMD_LABEL_STEP: {
				pParts->nRotAnimTime    = (int)cmd.pData[0];	// 向きアニメにかかる時間を代入
				pParts->nCounterRotAnim = 0;					// 向きアニメカウンターを初期化
				pParts->bRotAnim        = false;				// 向きアニメフラグを偽にする
				pParts->bStep           = true;					// 足踏フラグ真
				pParts->nStepTime       = (int)cmd.pData[1];	// 足踏時間
				pParts->nStepResetTime  = (int)cmd.pData[2];	// 足踏戻る時間
			}
			break;
			case CMotion3D::CMD_LABEL_SCALE: {
				D3DXVECTOR3 scale      = D3DXVECTOR3(cmd.pData[0], cmd.pData[1], cmd.pData[2]);	// 拡大倍率
				int         nScaleTime = (int)cmd.pData[3];			// 移動にかかる時間
				EASE        ease       = (EASE)((int)cmd.pData[4]);	// 補間

				if (nScaleTime == 0)
				{// 移動にかかる時間が0の時、
					pParts->scale = scale;	// 拡大倍率を直接代入
				}
				else
				{// 移動にかかる時間が0でない時、
					pParts->easeScale         = ease;			// 拡大倍率補間を設定
					pParts->scaleOld          = pParts->scale;	// 元の拡大倍率を設定
					pParts->targetScale       = scale;			// 目標拡大倍率を代入
					pParts->nScaleAnimTime    = nScaleTime;		// 拡大縮小アニメにかかる時間を代入
					pParts->nCounterScaleAnim = 0;				// 拡大縮小アニメカウンターを初期化
					pParts->bScaleAnim        = true;			// 拡大縮小アニメフラグを真にする
				}
			}
			break;
			case CMotion3D::CMD_LABEL_STEP_REACTION: {
				pParts->bStepReaction = true;	// 足踏反応フラグ真
			}
			break;
			default:
				assert(false);
				break;
			}
		}
	}
}

//========================================
// モーション3Dのアニメ処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::MotionAnim(Data partsSet) {
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		// 部品の情報のポインタ
		CBoneState *pParts = &m_boneStates[nCntParts];

		if (pParts->bPosAnim)
		{// 位置アニメフラグが真の時、
			if (++pParts->nCounterPosAnim >= pParts->nPosAnimTime)
			{// 位置アニメカウンターを加算した結果位置アニメにかかる時間を上回った時、
				pParts->bPosAnim = false;	// 位置アニメフラグを偽にする
			}
		}

		if (pParts->bStep) 
		{// 足踏フラグが真の時、
			if (++pParts->nCounterRotAnim >= pParts->nStepTime)
			{// 向きアニメカウンターを加算した結果足踏時間を上回った時、
				pParts->bStep = false;	// 足踏フラグを偽にする
			}
		}
		else if (pParts->bRotAnim)
		{// 角度アニメフラグが真の時、
			if (++pParts->nCounterRotAnim >= pParts->nRotAnimTime)
			{// 向きアニメカウンターを加算した結果向きアニメにかかる時間を上回った時、
				pParts->bRotAnim = false;	// 向きアニメフラグを偽にする
			}
		}

		if (pParts->bScaleAnim)
		{// 拡大縮小アニメフラグが真の時、
			if (++pParts->nCounterScaleAnim >= pParts->nScaleAnimTime)
			{// 拡大縮小アニメカウンターを加算した結果拡大縮小アニメにかかる時間を上回った時、
				pParts->bScaleAnim = false;	// 拡大縮小アニメフラグを偽にする
			}
		}
	}
}

//========================================
// モーションのクリア処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::MotionClear(Data partsSet, int nMotion) {
	if (nMotion == DATANONE)
		return;

	CMotion3D::Data motion = RNLib::Motion3D()->GetData()[nMotion];
	CSetUp3D::PLATFORM platform = RNLib::ModelSetUp()->GetData(m_nModelSetUp)->platform;

	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		m_boneStates[nCntParts].bScaleAnim = false;
		m_boneStates[nCntParts].bStep      = false;

		if (motion.pfData[platform].pPartsCmd == NULL) {
			m_boneStates[nCntParts].bPosAnim = false;
		}
		else if (motion.pfData[platform].pPartsCmd[nCntParts].bMove) {
			m_boneStates[nCntParts].bPosAnim = false;
		}
		else {
			m_boneStates[nCntParts].easePos         = EASE_LINEAR;
			m_boneStates[nCntParts].bPosAnim        = true;
			m_boneStates[nCntParts].nCounterPosAnim = 0;
			m_boneStates[nCntParts].nPosAnimTime    = PAUSE_RESET_TIME;
			m_boneStates[nCntParts].oldPos          = m_boneStates[nCntParts].pos;	
			m_boneStates[nCntParts].targetPos       = INITD3DXVECTOR3;
		}

		if (motion.pfData[platform].pPartsCmd == NULL) {
			m_boneStates[nCntParts].bRotAnim = false;
		}
		else if (motion.pfData[platform].pPartsCmd[nCntParts].bSpin) {
			m_boneStates[nCntParts].bRotAnim = false;
		}
		else {
			m_boneStates[nCntParts].easeRot         = EASE_LINEAR;
			m_boneStates[nCntParts].bRotAnim        = true;
			m_boneStates[nCntParts].nCounterRotAnim = 0;
			m_boneStates[nCntParts].nRotAnimTime    = PAUSE_RESET_TIME;
			m_boneStates[nCntParts].oldRot          = m_boneStates[nCntParts].rot;	
			m_boneStates[nCntParts].targetRot       = INITD3DXVECTOR3;
		}
	}
}

//========================================
// コリジョン描画処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::DrawCollision(void) {
	CSetUp3D::Data* pModelSetUp = RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntCollParts = 0; nCntCollParts < pModelSetUp->collSet.nPartsNum; nCntCollParts++) {
		CCollision3D::Parts collParts = pModelSetUp->collSet.pParts[nCntCollParts];
		D3DXVECTOR3 pos = INITD3DXVECTOR3;
		D3DXVECTOR3 rot = INITD3DXVECTOR3;

		if (pModelSetUp->collSet.pParts[nCntCollParts].nParent == DATANONE) {
			pos = m_pos;
			rot = m_rot;
		}
		else {
			CDoll3D::CBoneState parts = {};	// 部品情報

			if (GetPartsState_Idx(pModelSetUp->collSet.pParts[nCntCollParts].nParent, &parts)) {
				pos = ConvMatrixToPos(parts.resultMtx);
				rot = ConvMatrixToRot(parts.resultMtx);
			}
			else {
				pos = m_pos;
				rot = m_rot;
			}
		}

		D3DXMATRIX mtx = MultiplyMatrix(
			ConvPosRotToMatrix(collParts.pos, collParts.rot),
			ConvPosRotToMatrix(pos, rot));
		pos = ConvMatrixToPos(mtx);
		rot = ConvMatrixToRot(mtx);

		// 形に応じたライン設定
		switch (pModelSetUp->collSet.pParts[nCntCollParts].form) {
		case CCollision3D::FORM_SPHERE: {
			RNLib::Line3D()->Set_Sphere(
				pos,
				rot,
				collParts.fWidth,
				{ 255,0,0,255 },
				false
			);
			break;
		}
		case CCollision3D::FORM_CUBE: {
			RNLib::Line3D()->Set_Cube(
				pos,
				rot,
				collParts.fWidth,
				collParts.fHeight,
				collParts.fDepth,
				{ 255,0,0,255 },
				false
			);
			break;
		}
		case CCollision3D::FORM_CYLINDER: {
			RNLib::Line3D()->Set_Cylinder(
				pos,
				rot,
				collParts.fWidth,
				collParts.fHeight,
				{ 255,0,0,255 },
				false
			);
			break;
		}
		}
	}
}

//========================================
// 部品設定情報3Dの読み込み処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::LoadData(Data *pPartsSet) {

	
}

//========================================
// 部品設定情報3Dの書き込み処理
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::SaveData(Data *pPartsSet) {
	FILE* pFile = RNLib::File()->GetFile();
	fprintf(pFile, "PARTSSET{ %d\n", pPartsSet->nPartsNum);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++) {
		PartsData *pPartsType = &pPartsSet->pPartsData[nCntParts];

		fprintf(pFile, "	PARTS{\n");
		fprintf(pFile, "		INDEX: %d\n", pPartsType->nIdx);
		fprintf(pFile, "		MODEL_PATH: %s\n", RNLib::Model()->GetLoadPath(pPartsType->nModelIdx));
		fprintf(pFile, "		PARENT: %d\n", pPartsType->nParent == DATANONE ? DATANONE : pPartsSet->pPartsData[pPartsType->nParent].nIdx);
		fprintf(pFile, "		RELATIVE_POS: %f %f %f\n",
				pPartsType->fixedRelativePos.x,
				pPartsType->fixedRelativePos.y,
				pPartsType->fixedRelativePos.z);
		fprintf(pFile, "		RELATIVE_ROT: %f %f %f\n",
				pPartsType->fixedRelativeRot.x,
				pPartsType->fixedRelativeRot.y,
				pPartsType->fixedRelativeRot.z);
		fprintf(pFile, "		LIGHTING: %d\n", (int)pPartsType->bLighting);
		fprintf(pFile, "	}\n");
	}
	fprintf(pFile, "}\n");
}
#endif