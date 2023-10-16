//========================================
// 
// �q���[�}��3D�x�[�X�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ human-base3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CHuman3DBase�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CHuman3DBase::CHuman3DBase() {
	m_pData = NULL;	// �f�[�^
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CHuman3DBase::~CHuman3DBase() {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CHuman3DBase::Uninit(void) {
	CRegist::Uninit();	// ���N���X�I������

	// �f�[�^�̔j��
	RNLib::Memory()->Release(&m_pData);
}

//========================================
// �ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
int CHuman3DBase::Load(const char *pLoadPath, short nIdx) {
	int nNumOld = m_num;	// �ߋ��̑���

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

		if (RNLib::File()->OpenLoadFile(pLoadPath)) {
			while (RNLib::File()->SearchLoop("END")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier("SETUP_PATH:")) { RNLib::File()->Scan(CFile::SCAN::MODELSUIDX, &m_pData[nIdx].nSetUpIdx); }
				else if (RNLib::File()->CheckIdentifier("EYE_POS:")) { RNLib::File()->Scan(CFile::SCAN::POS3D, &m_pData[nIdx].eyePos); }		// �ڂ̈ʒu
				else if (RNLib::File()->CheckIdentifier("EYE_ROT:")) { RNLib::File()->Scan(CFile::SCAN::POS3D, &m_pData[nIdx].eyeRot); }		// �ڂ̌���
				else if (RNLib::File()->CheckIdentifier("EYE_PARENT:")) { RNLib::File()->Scan(CFile::SCAN::INT, &m_pData[nIdx].nEyeParent); }	// �ڂ̐e���i�ԍ�
				else if (RNLib::File()->CheckIdentifier("EYE_SPACE:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_pData[nIdx].fEyeSpace); }		// �ڂ̊Ԋu
				else if (RNLib::File()->CheckIdentifier("EYE_ROT_DIA:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_pData[nIdx].fEyeRotDia); }	// �ڂ̉�]�{��
			}

			RNLib::File()->CloseFile();
		}
	}

	// ���f���Z�b�g�A�b�v�ԍ���Ԃ�
	return nIdx;
}

//========================================
// SaveHuman3DBase�֐� - �q���[�}���x�[�X3D�������ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void CHuman3DBase::Save(char *pPath, int nIdx) {
	
	if (RNLib::File()->OpenSaveFile(pPath)) {
		FILE* file = RNLib::File()->GetFile();

		fprintf(file, "SETUP_PATH: %s\n",    RNLib::ModelSetUp()->GetLoadPath(m_pData[nIdx].nSetUpIdx));
		fprintf(file, "EYE_POS: %f %f %f\n", m_pData[nIdx].eyePos.x, m_pData[nIdx].eyePos.y, m_pData[nIdx].eyePos.z);
		fprintf(file, "EYE_ROT: %f %f %f\n", m_pData[nIdx].eyeRot.x, m_pData[nIdx].eyeRot.y, m_pData[nIdx].eyeRot.z);
		fprintf(file, "EYE_PARENT: %d\n",    m_pData[nIdx].nEyeParent);
		fprintf(file, "EYE_SPACE: %f\n",     m_pData[nIdx].fEyeSpace);
		fprintf(file, "EYE_ROT_DIA: %f\n",   m_pData[nIdx].fEyeRotDia);

		fprintf(file, "END\n");

		RNLib::File()->CloseFile();
	}
}

//========================================
// ���������w�萔�ɏ�����
// Author:RIKU NISHIMURA
//========================================
void CHuman3DBase::InitMemory(const int nNum) {
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