//========================================
// 
// �G�t�F�N�g�}�l�[�W���[�̏���
// Author:RYUKI FUJIWARA
//
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"
#include "effect.h"
#include "particle.h"

#define INIT_EFFECT_SCALE (D3DXVECTOR3(32.0f,32.0f,0.0f))

//****************************************
// �N���X
//****************************************
class CEffectMgr : public CObjectMgr {
public:
	//========== [[[ �֐��錾 ]]]
	CEffectMgr();
	virtual~CEffectMgr();
	virtual void Update(void);

	CEffect *EffectCreate(int nTex, D3DXVECTOR3 pos , D3DXVECTOR3 scale, Color col);
	CParticle *ParticleCreate(int nTex, D3DXVECTOR3 pos, D3DXVECTOR3 scale, Color col);

private:

	// *** �\���� ***

	// *** �ÓI�ϐ� ***

	// *** �ϐ� ***
};
