//========================================
// 
// ���f���Z�b�g�A�b�v�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//****************************************
// �萔�錾
//****************************************
namespace {
	// ���f���\����
	const char* c_aModelPlatformName[] = {
		"NONE",					// ����
		"FOOTLESS_00",			// ����[00]
		"BIPEDALISM_00",		// ��[00]
		"BIPEDALISM_01",		// ��[01]
		"QUADRUPEDALISM_00",	// �l��[00]
		"HEXAPOD_00",			// �Z��[00]
		"OCTAPOD_00",			// ����[00]
	};

	// ���f���\���̕��ʖ��̔ԍ�
	const int c_aModelPlatformPartIdx[][CModelSetUp::PART_MAX] = {
		//-------------------//|��      |��      |��      |��      |��r[��]|��r[�E]|�O�r[��]|�O�r[�E]|��[��]  |��[�E]  |�w�S[��]|�w�S[�E]|�w�P[��]|�w�P[�E]|����[��]|����[�E]|��[��]  |��[�E]  |��[��]  |��[�E]  |
		/* NONE              */{DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE},
		/* FOOTLESS_00       */{0       ,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE,DATANONE},
		/* BIPEDALISM_00     */{1       ,DATANONE,0       ,0       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,4       ,5       ,4       ,5       ,4       ,5       },
		/* BIPEDALISM_01     */{4       ,3       ,2       ,0       ,5       ,8       ,6       ,9       ,7       ,10      ,19      ,22      ,21      ,26      ,11      ,14      ,12      ,15      ,13      ,16      },
		/* QUADRUPEDALISM_00 */{1       ,DATANONE,0       ,0       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,2       ,3       ,4       ,5       ,4       ,5       ,4       ,5       },
		/* HEXAPOD_00        */{2       ,DATANONE,1       ,0       ,5       ,8       ,5       ,8       ,5       ,8       ,5       ,8       ,5       ,8       ,7       ,10      ,7       ,10      ,7       ,10      },
		/* OCTAPOD_00        */{1       ,DATANONE,1       ,0       ,4       ,12      ,4       ,12      ,5       ,13      ,5       ,13      ,5       ,13      ,10      ,18      ,10      ,18      ,11      ,19      },
	};
}
CHECK_ARRAY_SIZE(c_aModelPlatformName, CModelSetUp::PLATFORM_MAX);
CHECK_ARRAY_SIZE(c_aModelPlatformPartIdx, CModelSetUp::PLATFORM_MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CModelSetUp�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CModelSetUp::CModelSetUp() {
	m_pData = NULL;	// �f�[�^
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CModelSetUp::~CModelSetUp() {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CModelSetUp::Uninit(void) {
	CRegist::Uninit();	// ���N���X�I������

	for (int nCntData = 0; nCntData < m_num; nCntData++) {
		RNLib::Memory()->Release(&m_pData[nCntData].partsSet.pPartsData);
		RNLib::Memory()->Release(&m_pData[nCntData].collSet.pParts);
	}

	// �f�[�^�̔j��
	RNLib::Memory()->Release(&m_pData);

	m_num = 0;
}

//========================================
// �ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
int CModelSetUp::Load(const char *pLoadPath, short nIdx) {
	int nNumOld  = m_num;	// �ߋ��̑���

	if (!CRegist::Load(pLoadPath, &nIdx)) {
		return nIdx;
	}
	else {
		{// �f�[�^�̃������Ċm��
			Data* pNew = new Data[m_num];
			int nCopySize = m_num < nNumOld ? m_num : nNumOld;
			if (nCopySize > 0) {
				memcpy(pNew, m_pData, sizeof(Data) * nCopySize);
				delete m_pData;
			}
			m_pData = pNew;
		}
		m_pData[nIdx] = {};

		// �t�@�C�����J��
		if (RNLib::File()->OpenLoadFile(pLoadPath)) {
			while (RNLib::File()->SearchLoop("END")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier(/* ���i�ݒ���       */"PARTSSET{")) { CParts3DSetUp::LoadData(&m_pData[nIdx].partsSet); }
				else if (RNLib::File()->CheckIdentifier(/* �R���W�����ݒ��� */"COLLISIONSET{")) { CCollision3D::LoadData(&m_pData[nIdx].collSet); }
				else if (RNLib::File()->CheckIdentifier(/* ���f���\��         */"PLATFORM:")) {
					RNLib::File()->NewLine();

					// ���f���\��������
					m_pData[nIdx].platform = PLATFORM_NONE;

					for (int nCntPtf = 0; nCntPtf < PLATFORM_MAX; nCntPtf++) {
						if (RNLib::File()->CheckIdentifier(c_aModelPlatformName[nCntPtf]))
						{// �J�E���g�̃��f���\�����ƈ�v�������A���f���\���ݒ�
							m_pData[nIdx].platform = (PLATFORM)nCntPtf;
							break;
						}
					}
				}
			}

			// �t�@�C�������
			RNLib::File()->CloseFile();
		}
	}

	// ���f���Z�b�g�A�b�v�ԍ���Ԃ�
	return nIdx;
}

//========================================
// �������ݏ���
// Author:RIKU NISHIMURA
//========================================
void CModelSetUp::Save(char *pPath, int nIdx) {

	if (RNLib::File()->OpenSaveFile(pPath))
	{// �t�@�C�����J�����ꍇ�A
		// ���i���̏������ݏ���
		CParts3DSetUp::SaveData(&m_pData[nIdx].partsSet);

		// �R���W�������̏������ݏ���
		CCollision3D::SaveData(&m_pData[nIdx].collSet);

		FILE* file = RNLib::File()->GetFile();
		
		fprintf(file, "PLATFORM: %s\n", c_aModelPlatformName[m_pData[nIdx].platform]);
		fprintf(file, "END");

		RNLib::File()->CloseFile();
	}
}

//========================================
// ���f���\���̕��ʔԍ��擾
// Author:RIKU NISHIMURA
//========================================
int CModelSetUp::GetPlatformPartIdx(const PLATFORM platform, const CModelSetUp::PART part) {
	return c_aModelPlatformPartIdx[platform][part];
}

//========================================
// ���f���\���̖��O�擾
// Author:RIKU NISHIMURA
//========================================
const char* CModelSetUp::GetPlatformName(const PLATFORM platform) {
	return c_aModelPlatformName[platform];
}

//========================================
// ���O���烂�f���\���擾
// Author:RIKU NISHIMURA
//========================================
CModelSetUp::PLATFORM CModelSetUp::GetPlatformFromName(const char* pName) {
	for (int nCntPtf = 0; nCntPtf < PLATFORM_MAX; nCntPtf++) {
		if (!strcmp(pName, c_aModelPlatformName[nCntPtf])) {
			return (PLATFORM)nCntPtf;
		}
	}

	return PLATFORM_NONE;
}

//========================================
// ���������w�萔�ɏ�����
// Author:RIKU NISHIMURA
//========================================
void CModelSetUp::InitMemory(const int nNum) {
	Uninit();	// �I������
	CRegist::InitMemory(nNum);	// ���N���X�̃���������������

	// �f�[�^�̃������m��
	if (m_pData != NULL) {
		delete m_pData;
	}
	m_pData = new Data[nNum];

	// �m�ۂ������̃f�[�^��S�ď���������
	for (int nCnt = 0; nCnt < nNum; nCnt++) {
		m_pData[nCnt] = {};
	}
}