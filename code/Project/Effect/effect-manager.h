//========================================
// 
// �G�t�F�N�g�}�l�[�W���[�̏���
// Author:RYUKI FUJIWARA
//
// 
//========================================
#include "../../_RNLib/RNlib.h"
#include "effect.h"

//****************************************
// �N���X
//****************************************
class CEffectMgr : public CObjectMgr {
public:
	//========== [[[ �֐��錾 ]]]
	CEffectMgr();
	virtual~CEffectMgr();
	virtual void Update(void);

	CEffect *EffectCreate(D3DXVECTOR3 pos);

private:

	// *** �\���� ***

	// *** �ÓI�ϐ� ***

	// *** �ϐ� ***
};
