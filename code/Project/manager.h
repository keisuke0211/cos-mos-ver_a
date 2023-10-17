//========================================
// 
// �}�l�[�W���[����
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "Mode/mode.h"
#include "../_RNLib/RNlib.h"
#include "Object/stage-object-manager.h"

//****************************************
// ���O���
//****************************************
namespace Manager {
	//========== [[[ �֐��錾 ]]]
	void        Init       (const CMode::TYPE mode);
	void        Uninit     (void);
	void        Update     (void);
	void        Load       (void);
	void        Save       (void);
	void        SetMode    (const CMode::TYPE newMode);
	CMode::TYPE GetMode    (void);
	void        Transition (const CMode::TYPE newMode, const CTransition::TYPE transType);
	CStageObjectMgr*  BlockMgr   (void);
};