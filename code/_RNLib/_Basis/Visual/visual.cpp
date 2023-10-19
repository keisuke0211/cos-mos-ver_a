//========================================
// 
// �r�W���A���̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ visual.cpp ]]]
//========================================
#include "../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define VISUALFILE_PATH "data\\_RNData\\VisualSetting.txt"

//****************************************
// �萔��`
//****************************************
namespace {
	// �e�N�X�`����
	const char* c_aTexName[] = {
		"TRANSITION_HOLE",
		"LAVA",
		"RUGGET",
	};

	// ���f����
	const char* c_aModelName[] = {
		"CLOD_S",
		"CLOD_M",
		"NEEDLE_M",
	};

	// ���[�V����3D��
	const char* c_aMotionName[] = {
		"STAND_NORMAL",
		"SPC_EFF_SLEEP",
		"ANTICIPATION_ARMCROSS",
		"ANTICIPATION_RIGHTHOOK",
		"BITE_MID",
		"BREATH_FORWARD",
		"DRILL_MID",
		"PUNCH_RIGHT_MID",
		"PUNCH_GROUND_RIGHT",
		"TACKLE_MID",
	};
}
CHECK_ARRAY_SIZE(c_aTexName   , (int)CVisual::TEXTURE ::MAX);
CHECK_ARRAY_SIZE(c_aModelName , (int)CVisual::MODEL   ::MAX);
CHECK_ARRAY_SIZE(c_aMotionName, (int)CVisual::MOTION3D::MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CVisual�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CVisual::CVisual() {
	for (int nCntModel = 0; nCntModel < (int)MODEL::MAX; nCntModel++) {
		m_aModelIdx[nCntModel] = DATANONE;
	}
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CVisual::~CVisual() {
	
}

//========================================
// �ǂݍ���
// Author:RIKU NISHIMURA
//========================================
void CVisual::Load(void) {
	return;

	if (!RNLib::File()->OpenLoadFile(VISUALFILE_PATH))
		return;

	// �ǂݍ��݃��[�v
	while (RNLib::File()->SearchLoop("END")) {
		if (RNLib::File()->CheckIdentifier("TEXTURE{")) {
			while (RNLib::File()->SearchLoop("}")) {
				for (int nCntTex = 0; nCntTex < (int)TEXTURE::MAX; nCntTex++)
					RNLib::File()->Scan(CFile::SCAN::TEXIDX, &m_aTextureIdx[nCntTex], CreateText("%s:", c_aTexName[nCntTex]));
			}
		}
		else if (RNLib::File()->CheckIdentifier("MODEL{")) {
			while (RNLib::File()->SearchLoop("}")) {
				for (int nCntModel = 0; nCntModel < (int)MODEL::MAX; nCntModel++)
					RNLib::File()->Scan(CFile::SCAN::MODELIDX, &m_aModelIdx[nCntModel], CreateText("%s:", c_aModelName[nCntModel]));
			}
		}
		else if (RNLib::File()->CheckIdentifier("MOTION3D{")) {
			while (RNLib::File()->SearchLoop("}")) {
				for (int nCntMotion = 0; nCntMotion < (int)MOTION3D::MAX; nCntMotion++)
					RNLib::File()->Scan(CFile::SCAN::MOTION3DIDX, &m_aMotion3DIdx[nCntMotion], CreateText("%s:", c_aMotionName[nCntMotion]));
			}
		}
	}

	RNLib::File()->CloseFile();
}