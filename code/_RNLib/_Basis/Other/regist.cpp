//========================================
// 
// �o�^����
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ regist.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CRegist�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CRegist::CRegist() {
	m_num       = 0;		// ����
	m_ppLoadPath = NULL;	// �ǂݍ��ݍς̃p�X
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CRegist::~CRegist() {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CRegist::Uninit(void) {
	// ���������
	for (int nCnt = 0; nCnt < m_num; nCnt++) {
		RNLib::Memory()->Release(&m_ppLoadPath[nCnt]);	// �Ǎ��σp�X
	}
	RNLib::Memory()->Release(&m_ppLoadPath);	// �Ǎ��σp�X�S��
}

//========================================
// �ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
bool CRegist::Load(const char *pPath, short *pIdx) {
	if ((!strcmp(pPath, "")) || (!strcmp(pPath, "DATANONE")))
	{// �p�X�������Ȃ� or �f�[�^�����w��̎��A
		*pIdx = DATANONE;
		return false;	// �ǂݍ��񂶂�_��
	}
	else if (*pIdx != DATANONE)
	{// �ԍ��w�肪���鎞�A
		if (*pIdx >= 0 && *pIdx < m_num) 
		{// �ԍ����͈͓��ł���΁A
			sprintf(m_ppLoadPath[*pIdx], "%s", pPath);	// �p�X��ۑ�
			return true;	// �ǂݍ���Ń��V
		}
		else 
		{// �ԍ����͈͊O�ł���΁A
			assert(false);
			*pIdx = DATANONE;
			return false;	// �ǂݍ��񂶂�_��
		}
	}

	// ���ɓǂݍ��܂�Ă��邩�m�F
	for (int nCnt = 0; nCnt < m_num; nCnt++) {
		if (!strcmp(pPath, m_ppLoadPath[nCnt]))
		{// ���ɓ����p�X�̃e�N�X�`����ǂݍ���ł������A
			*pIdx = nCnt;	// �ԍ��͂��̂܂܃J�E���g
			return false;	// �ǂݍ��񂶂�_��
		}
	}

	int nNumOld_and_idx = m_num;	// �ԍ�

	// ���������Z����
	m_num++;

	{// �ǂݍ��ݍς݃p�X�̃������Ċm��
		char** ppNew = new char * [m_num];
		int nCopyNum = m_num < nNumOld_and_idx ? m_num : nNumOld_and_idx;
		if (nCopyNum > 0) {
			memcpy(ppNew, m_ppLoadPath, sizeof(char*) * nCopyNum);
			delete m_ppLoadPath;
		}
		m_ppLoadPath = ppNew;
		for (int nCnt = nNumOld_and_idx; nCnt < m_num; nCnt++) {
			m_ppLoadPath[nCnt] = new char[TXT_MAX];
		}
	}

	// �p�X��ۑ�
	sprintf(m_ppLoadPath[nNumOld_and_idx], "%s", pPath);

	// �ԍ���Ԃ�
	*pIdx = nNumOld_and_idx;
	return true;	// �ǂݍ���Ń��V
}

//========================================
// ����������������
// Author:RIKU NISHIMURA
//========================================
void CRegist::InitMemory(const int nNum) {
	m_num = nNum;	// ������

	{// �ǂݍ��ݍσp�X�̃������m��
		char** ppNew = new char* [m_num];
		if (m_ppLoadPath != NULL) {
			delete m_ppLoadPath;
		}
		m_ppLoadPath = ppNew;
		for (int nCnt = 0; nCnt < m_num; nCnt++) {
			m_ppLoadPath[nCnt] = new char[TXT_MAX];
		}
	}
}