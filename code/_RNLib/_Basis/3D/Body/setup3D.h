//========================================
// 
// ���f���Z�b�g�A�b�v�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "doll3D.h"
#include "../../Other/regist.h"

//****************************************
// �N���X��`
//****************************************
// ���f���Z�b�g�A�b�v�N���X
class CModelSetUp : public CRegist{
public:
	//========== [[[ �񋓌^��` ]]]
	// �\��
	typedef enum {
		PLATFORM_NONE,				// ����
		PLATFORM_FOOTLESS_00,		// ����[00]
		PLATFORM_BIPEDALISM_00,		// ��[00]
		PLATFORM_BIPEDALISM_01,		// ��[01]
		PLATFORM_QUADRUPEDALISM_00,	// �l��[00]
		PLATFORM_HEXAPOD_00,		// �Z��[00]
		PLATFORM_OCTAPOD_00,		// ����[00]
		PLATFORM_MAX,
	}PLATFORM;

	// ����
	typedef enum {
		PART_HEAD      ,	// ��
		PART_NECK      ,	// ��
		PART_CHEST     ,	// ��
		PART_WAIST     ,	// ��
		PART_UPPERARM_L,	// ��r[��]
		PART_UPPERARM_R,	// ��r[�E]
		PART_FOREARM_L ,	// �O�r[��]
		PART_FOREARM_R ,	// �O�r[�E]
		PART_HAND_L    ,	// ��[��]
		PART_HAND_R    ,	// ��[�E]
		PART_FINGER4_L ,	// �w�S[��]
		PART_FINGER4_R ,	// �w�S[�E]
		PART_FINGER1_L ,	// �w�P[��]
		PART_FINGER1_R ,	// �w�P[�E]
		PART_THIGH_L   ,	// ����[��]
		PART_THIGH_R   ,	// ����[�E]
		PART_SHIN_L    ,	// ��[��]
		PART_SHIN_R    ,	// ��[�E]
		PART_LEGS_L    ,	// ��[��]
		PART_LEGS_R    ,	// ��[�E]
		PART_MAX       ,
	}PART;

	//========== [[[ �\���̒�` ]]]
	// �f�[�^�\����
	typedef struct Data_ {
		CParts3DSetUp::Data partsSet = {};				// ���i���
		CCollision3D::Data  collSet  = {};				// �R���W�������
		PLATFORM            platform = PLATFORM_NONE;	// �\��
	}Data;

	//========== [[[ �֐��錾 ]]]
	CModelSetUp();
	~CModelSetUp();
	void        Uninit             (void);
	int         Load               (const char* pLoadPath, short nIdx = DATANONE);
	void        Save               (char* pPath, int nIdx);
	Data*       GetData            (const int nIdx) { return &m_pData[nIdx]; }
	int         GetPlatformPartIdx (const PLATFORM platform, const CModelSetUp::PART part);
	const char* GetPlatformName    (const PLATFORM platform);
	PLATFORM    GetPlatformFromName(const char* pName);
	void        InitMemory         (const int nNum);

private:
	//========== [[[ �ϐ��錾 ]]]
	Data* m_pData;
};