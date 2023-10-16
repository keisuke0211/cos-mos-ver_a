//========================================
// 
// 部品3Dセットアップの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ parts3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
#define PAUSE_RESET_TIME (10)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CParts3Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CParts3DSetUp::CParts3DSetUp(void) {
	m_pos			 = INITD3DXVECTOR3;
	m_rot			 = INITD3DXVECTOR3;
	m_bMotionStop	 = false;		
	m_bDrawCollision = false;		
	m_nModelSetUp	 = 0;			
	m_nMotion		 = 0;			
	m_nMotionOld	 = 0;			
	m_nMotionCounter = 0;			
	m_col			 = CLEARCOLOR;	
	m_fBrOfEm        = 1.0f;
	m_fScale         = 1.0f;
	m_pParts		 = NULL;
	m_pCLParts       = NULL;
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CParts3DSetUp::~CParts3DSetUp(void) {

}

//========================================
// モデル設定処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::ModelSet(Data *pPartsSet) {
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
		PartsState *pParts = &m_pParts[nCntParts];	// 部品の情報のポインタ
		PartsData *pPartsType = &pPartsSet->pPartsData[nCntParts];	// 部品の種類毎の情報のポインタ
		D3DXVECTOR3 posResult;	// 位置(結果)
		D3DXVECTOR3 rotResult;	// 向き(結果)

		{//========== [[[ 位置(結果)を更新 ]]]
			if (pParts->bPosAnim)
			{// 位置アニメフラグが真の時、カウンターの進行率に応じて位置を更新
				float fRate = Easing(pParts->easePos, pParts->nCounterPosAnim, pParts->nPosAnimTime - 1);
				pParts->pos = (pParts->posOld * (1.0f - fRate)) + (pParts->targetPos * fRate);
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
				pParts->rot = (pParts->rotOld * (1.0f - fRate)) + (pParts->targetRot * fRate);
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
		pParts->mtx = pMtxParts[nCntParts];
	}

	// 部品毎のマトリックスのメモリ解放
	delete pMtxParts;

	if (m_pCLParts != NULL) 
	{// コリジョン部品が存在する時、コリジョン部品の位置計算
		CModelSetUp::Data* pModelSetUp = RNLib::ModelSetUp()->GetData(m_nModelSetUp);
		for (int nCntCLParts = 0; nCntCLParts < pModelSetUp->collSet.nPartsNum; nCntCLParts++) {
			CCollision3D::Parts collParts = pModelSetUp->collSet.pParts[nCntCLParts];
			D3DXVECTOR3 pos = INITD3DXVECTOR3;
			D3DXVECTOR3 rot = INITD3DXVECTOR3;

			if (pModelSetUp->collSet.pParts[nCntCLParts].nParent == DATANONE) {
				pos = m_pos;
				rot = m_rot;
			}
			else {
				CParts3DSetUp::PartsState parts = {};	// 部品情報

				if (GetPartsState_Idx(pModelSetUp->collSet.pParts[nCntCLParts].nParent, &parts)) {
					pos = ConvMatrixToPos(parts.mtx);
					rot = ConvMatrixToRot(parts.mtx);
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
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::Init(int nSetUpNum) {
	// モデルセットアップ情報
	CModelSetUp::Data setUp = *RNLib::ModelSetUp()->GetData(nSetUpNum);

	// 初期化
	m_nModelSetUp	 = nSetUpNum;		// モデルセットアップ番号を設定
	m_pos			 = INITD3DXVECTOR3;	// 本体位置
	m_rot			 = INITD3DXVECTOR3;	// 本体向き
	m_bMotionStop	 = false;			// 停止フラグ
	m_bDrawCollision = false;			// 当たり判定描画フラグ
	m_nMotion		 = DATANONE;		// モーション番号
	m_nMotionOld	 = DATANONE;		// モーション番号(過去)
	m_nMotionCounter = 0;				// モーションカウンター
	m_col			 = INITCOLOR;		// 色

	if (setUp.partsSet.nPartsNum > 0) 
	{// 部品数が0を超えていた時、
		// 部品情報のポインタのメモリを部品数分確保する
		if (m_pParts != NULL) {
			delete m_pParts;
		}
		m_pParts = new PartsState[setUp.partsSet.nPartsNum];

		// ポーズ初期化
		InitPause();
	}
	else 
	{// 部品数が0を超えていなかった時、
		if (m_pParts != NULL) {
			delete[] m_pParts;
			m_pParts = NULL;
		}
	}

	if (setUp.collSet.nPartsNum > 0) 
	{// コリジョン部品数が0を越えていた時、
		// コリジョン部品の情報ポインタのメモリを部品数分確保する
		if (m_pCLParts != NULL) {
			delete m_pCLParts;
		}
		m_pCLParts = new CLParts[setUp.collSet.nPartsNum];
	}
	else
	{// 部品数が0を超えていなかった時、
		if (m_pCLParts != NULL) {
			delete[] m_pCLParts;
			m_pCLParts = NULL;
		}
	}
}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::Uninit(void) {
	RNLib::Memory()->Release(&m_pParts);		// 部品情報のメモリ解放
	RNLib::Memory()->Release(&m_pCLParts);		// コリジョン部品情報のメモリ解放
}

//========================================
// 更新処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::Update(void) {
	// モデルセットアップ情報
	CModelSetUp::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	if (m_nModelSetUp != DATANONE)
	{// モデルセットアップ番号が-1 or の時、
		if (!m_bMotionStop)
		{// 停止していない時、
			// モーション設定
			MotionSet(setUp.partsSet);

			// モーションの更新処理
			MotionUpdate(m_nMotion, setUp.partsSet);
		}

		// モデルの設定処理
		ModelSet(&setUp.partsSet);

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
bool CParts3DSetUp::GetMotionEnd(void) {
	return m_nMotionCounter >= RNLib::Motion3D()->GetData()[m_nMotion].nLoopTime;
}

//========================================
// モーション踏み取得
// Author:RIKU NISHIMURA
//========================================
bool CParts3DSetUp::GetMotionStep(void) {
	CModelSetUp::Data modelSetUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);
	CMotion3D  ::Data motion     =  RNLib::Motion3D  ()->GetData()[m_nMotion];

	for (int nCntParts = 0; nCntParts < modelSetUp.partsSet.nPartsNum; nCntParts++) {
		if (m_pParts[nCntParts].bStepReaction)
		{// 足踏反応フラグが真の時、
			return true;
		}
		else if (m_pParts[nCntParts].bStep)
		{// 足踏フラグが真の時、
			if (m_pParts[nCntParts].nCounterRotAnim == m_pParts[nCntParts].nRotAnimTime) {
				return true;
			}
		}
	}

	return false;
}

//========================================
// ポーズ初期化
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::InitPause(void) {
	if (m_nModelSetUp == DATANONE)
		return;

	// モデルセットアップ情報
	CModelSetUp::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntParts = 0; nCntParts < setUp.partsSet.nPartsNum; nCntParts++) {
		PartsData* pPartsType = &setUp.partsSet.pPartsData[nCntParts];	// 部品の種類毎の情報のポインタ

		m_pParts[nCntParts] = {};	// 部品の情報を初期化

		// マトリックスに相対位置/向きを適用
		m_pParts[nCntParts].mtx = ConvPosRotToMatrix(pPartsType->fixedRelativePos, pPartsType->fixedRelativeRot);
	}
}

//========================================
// 部品情報取得(番号指定)
// Author:RIKU NISHIMURA
//========================================
bool CParts3DSetUp::GetPartsState_Idx(int nIdx, PartsState* pParts) {
	// モデルセットアップ情報
	CModelSetUp::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntParts = 0; nCntParts < setUp.partsSet.nPartsNum; nCntParts++) {
		if (setUp.partsSet.pPartsData[nCntParts].nIdx == nIdx) {
			*pParts = m_pParts[nCntParts];
			return true;
		}
	}

	return false;
}

//========================================
// 部品情報取得(部位指定)
// Author:RIKU NISHIMURA
//========================================
bool CParts3DSetUp::GetPartsState_Part(int nPart, PartsState* pParts) {
	// モデルセットアップ情報
	CModelSetUp::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	// モデル構成に応じた部位番号取得
	int nIdx = RNLib::ModelSetUp()->GetPlatformPartIdx(setUp.platform, (CModelSetUp::PART)nPart);

	for (int nCntParts = 0; nCntParts < setUp.partsSet.nPartsNum; nCntParts++) {
		if (setUp.partsSet.pPartsData[nCntParts].nIdx == nIdx) {
			*pParts = m_pParts[nCntParts];
			return true;
		}
	}

	*pParts = m_pParts[0];

	return false;
}

//========================================
// モーション3Dの設定処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::MotionSet(Data partsSet) {
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
bool CParts3DSetUp::MotionUpdate(int nMotion, Data partsSet) {
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
void CParts3DSetUp::LoadMotionAnim(Data partsSet) {
	CModelSetUp::PLATFORM platform = RNLib::ModelSetUp()->GetData(m_nModelSetUp)->platform;
	CMotion3D::Data       motion   = RNLib::Motion3D()->GetData()[m_nMotion];

	// 部品全ての一部情報初期化
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		m_pParts[nCntParts].bStepReaction = false;
	}

	// 部品毎のアニメの読み込み
	for (int nCntPartsAnim = 0; nCntPartsAnim < motion.pfData[platform].nPartsNum; nCntPartsAnim++) {
		// 部品毎のモーション3Dの情報
		CMotion3D::PartsCmd partsMotion3D = motion.pfData[platform].pPartsCmd[nCntPartsAnim];

		for (int nCntCmd = 0; nCntCmd < partsMotion3D.nCmdNum; nCntCmd++) {
			CMotion3D::Cmd cmd = partsMotion3D.pCmd[nCntCmd];	// コマンド情報
			PartsState *pParts = m_pParts;	// 部品3Dの情報

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
					pParts->posOld          = pParts->pos;	// 元の位置を設定
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
					pParts->rotOld          = pParts->rot;	// 元の向きを設定
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
void CParts3DSetUp::MotionAnim(Data partsSet) {
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		// 部品の情報のポインタ
		PartsState *pParts = &m_pParts[nCntParts];

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
void CParts3DSetUp::MotionClear(Data partsSet, int nMotion) {
	if (nMotion == DATANONE)
		return;

	CMotion3D::Data motion = RNLib::Motion3D()->GetData()[nMotion];
	CModelSetUp::PLATFORM platform = RNLib::ModelSetUp()->GetData(m_nModelSetUp)->platform;

	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		m_pParts[nCntParts].bScaleAnim = false;
		m_pParts[nCntParts].bStep      = false;

		if (motion.pfData[platform].pPartsCmd == NULL) {
			m_pParts[nCntParts].bPosAnim = false;
		}
		else if (motion.pfData[platform].pPartsCmd[nCntParts].bMove) {
			m_pParts[nCntParts].bPosAnim = false;
		}
		else {
			m_pParts[nCntParts].easePos         = EASE_LINEAR;
			m_pParts[nCntParts].bPosAnim        = true;
			m_pParts[nCntParts].nCounterPosAnim = 0;
			m_pParts[nCntParts].nPosAnimTime    = PAUSE_RESET_TIME;
			m_pParts[nCntParts].posOld          = m_pParts[nCntParts].pos;	
			m_pParts[nCntParts].targetPos       = INITD3DXVECTOR3;
		}

		if (motion.pfData[platform].pPartsCmd == NULL) {
			m_pParts[nCntParts].bRotAnim = false;
		}
		else if (motion.pfData[platform].pPartsCmd[nCntParts].bSpin) {
			m_pParts[nCntParts].bRotAnim = false;
		}
		else {
			m_pParts[nCntParts].easeRot         = EASE_LINEAR;
			m_pParts[nCntParts].bRotAnim        = true;
			m_pParts[nCntParts].nCounterRotAnim = 0;
			m_pParts[nCntParts].nRotAnimTime    = PAUSE_RESET_TIME;
			m_pParts[nCntParts].rotOld          = m_pParts[nCntParts].rot;	
			m_pParts[nCntParts].targetRot       = INITD3DXVECTOR3;
		}
	}
}

//========================================
// コリジョン描画処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::DrawCollision(void) {
	CModelSetUp::Data* pModelSetUp = RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntCollParts = 0; nCntCollParts < pModelSetUp->collSet.nPartsNum; nCntCollParts++) {
		CCollision3D::Parts collParts = pModelSetUp->collSet.pParts[nCntCollParts];
		D3DXVECTOR3 pos = INITD3DXVECTOR3;
		D3DXVECTOR3 rot = INITD3DXVECTOR3;

		if (pModelSetUp->collSet.pParts[nCntCollParts].nParent == DATANONE) {
			pos = m_pos;
			rot = m_rot;
		}
		else {
			CParts3DSetUp::PartsState parts = {};	// 部品情報

			if (GetPartsState_Idx(pModelSetUp->collSet.pParts[nCntCollParts].nParent, &parts)) {
				pos = ConvMatrixToPos(parts.mtx);
				rot = ConvMatrixToRot(parts.mtx);
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
void CParts3DSetUp::LoadData(Data *pPartsSet) {

	// 部品設定情報を初期化
	if (pPartsSet->pPartsData != NULL) {
		delete[] pPartsSet->pPartsData;
		pPartsSet->pPartsData = NULL;
	}
	*pPartsSet = {};

	// 部品数読み込み
	RNLib::File()->Scan(CFile::SCAN::INT,&pPartsSet->nPartsNum);

	// 部品の種類毎の情報のメモリ確保
	if (pPartsSet->nPartsNum > 0) {
		pPartsSet->pPartsData = new PartsData[pPartsSet->nPartsNum];
	}

	int nCntParts = 0;	// 部品のカウント

	// 部品設定情報の読み込みを開始
	while (RNLib::File()->SearchLoop("}")) {
		if (false) {}
		else if (RNLib::File()->CheckIdentifier(/* 部品情報 */"PARTS{")) {
			// 部品の種類毎の情報のポインタ
			pPartsSet->pPartsData[nCntParts] = {};
			PartsData& parts = pPartsSet->pPartsData[nCntParts];

			// 部品情報の読み込みを開始
			while (RNLib::File()->SearchLoop("}")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier(/* 部品番号   */"INDEX:"))        { RNLib::File()->Scan(CFile::SCAN::INT, &parts.nIdx); }
				else if (RNLib::File()->CheckIdentifier(/* モデルパス */"MODEL_PATH:"))   { RNLib::File()->Scan(CFile::SCAN::MODELIDX, &parts.nModelIdx); }
				else if (RNLib::File()->CheckIdentifier(/* 親部品番号 */"PARENT:"))       { RNLib::File()->Scan(CFile::SCAN::INT, &parts.nParent); }
				else if (RNLib::File()->CheckIdentifier(/* 相対位置   */"RELATIVE_POS:")) { RNLib::File()->Scan(CFile::SCAN::POS3D, &parts.fixedRelativePos); }
				else if (RNLib::File()->CheckIdentifier(/* 相対角度   */"RELATIVE_ROT:")) { RNLib::File()->Scan(CFile::SCAN::POS3D, &parts.fixedRelativeRot); }
				else if (RNLib::File()->CheckIdentifier(/* 親部品番号 */"LIGHTING:"))     { RNLib::File()->Scan(CFile::SCAN::BOOL, &parts.bLighting); }
			}

			nCntParts++;	// 部品のカウントを加算
			assert(nCntParts <= pPartsSet->nPartsNum);
		}
	}

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++) {
		PartsData& parts = pPartsSet->pPartsData[nCntParts];
		if (parts.nParent == DATANONE)
			continue;

		int nCntParts2;
		for (nCntParts2 = 0; nCntParts2 < pPartsSet->nPartsNum; nCntParts2++) {
			if (parts.nParent == pPartsSet->pPartsData[nCntParts2].nIdx) {
				parts.nParent = nCntParts2;
				break;
			}
		}

		if (nCntParts2 == pPartsSet->nPartsNum)
			parts.nParent = DATANONE;
	}
}

//========================================
// 部品設定情報3Dの書き込み処理
// Author:RIKU NISHIMURA
//========================================
void CParts3DSetUp::SaveData(Data *pPartsSet) {
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