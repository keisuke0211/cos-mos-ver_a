//========================================
// 
// エフェクトマネージャーの処理
// Author:RYUKI FUJIWARA
// 
// 
//========================================
#include "effect-manager.h"

//========================================
// 静的変数
//========================================

//========================================
// コンストラクタ
//========================================
CEffectMgr::CEffectMgr(void)
{
}

//========================================
// デストラクタ
//========================================
CEffectMgr::~CEffectMgr()
{
}

//========================================
// 更新
//========================================
void CEffectMgr::Update(void)
{

}

//========================================
// エフェクト
//========================================
CEffect *CEffectMgr::EffectCreate(int nTex, D3DXVECTOR3 pos)
{
	CEffect *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CEffect;

	// 初期化処理
	pObj->Init(nTex);
	pObj->SetPos(pos);

	CObjectMgr::AddList((CObject*)pObj);

	return pObj;
}
//========================================
// パーティクル
//========================================
CParticle *CEffectMgr::ParticleCreate(int nTex, D3DXVECTOR3 pos)
{
	CParticle *pObj = NULL;

	if (pObj != NULL) { return pObj; }
	pObj = new CParticle;

	// 初期化処理
	pObj->Init(nTex);
	pObj->SetPos(pos);

	CObjectMgr::AddList((CObject*)pObj);

	return pObj;
}