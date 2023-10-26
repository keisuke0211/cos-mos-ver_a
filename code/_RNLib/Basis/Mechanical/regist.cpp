//========================================
// 
// �o�^����
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�o�^�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CRegist::CRegist() {

	m_num       = 0;
	m_loadPaths = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CRegist::~CRegist() {

	// �ǂݍ��݃p�X�̉��
	for (int nCnt = 0; nCnt < m_num; nCnt++)
		RNLib::Memory().Release(&m_loadPaths[nCnt]);
	RNLib::Memory().Release(&m_loadPaths);
}

//========================================
// �ǂݍ��ݏ���
//========================================
bool CRegist::Load(const char* loadPath, short& idx) {

	// �p�X���� or DATANONE�w��̎��A
	// �ԍ���DATANONE�w�肵�ēǂݒ��~
	if ((!strcmp(loadPath, "")) || (!strcmp(loadPath, "DATANONE"))) {
		idx = NONEDATA;
		return false;
	}

	// �ԍ��w�肪���鎞�A
	if (idx != NONEDATA) {

		// �ԍ����͈͓��ł���΁A
		// �p�X��ۑ����ēǂݍ��݊J�n
		if (idx >= 0 && idx < m_num) {
			sprintf(m_loadPaths[idx], "%s", loadPath);
			return true;
		}
		 
		// �ԍ����͈͊O�ł���΁A
		// �ԍ���DATANONE�w�肵�ēǂݍ��ݒ��~
		assert(false);
		idx = NONEDATA;

		return false;
	}

	// ���ɓǂݍ��܂�Ă��邩�m�F
	for (int cnt = 0; cnt < m_num; cnt++) {

		// ���ɓ����p�X��ǂݍ���ł������A
		// �ԍ����J�E���g�Ŏw�肵�ēǂݍ��ݒ��~
		if (!strcmp(loadPath, m_loadPaths[cnt])) {
			idx = cnt;
			return false;
		}
	}

	// �ߋ��̐� �� �ԍ�
	int numOld = m_num++;

	{// �ǂݍ��ݍς݃p�X�̃������Ċm��
		char** newLoadPaths = new char*[m_num];

		// �ߋ�����0���z���Ă��鎞�A���������R�s�[
		if (numOld > 0) {
			memcpy(newLoadPaths, m_loadPaths, sizeof(char*) * numOld);
			delete m_loadPaths;
		}

		// �ǂݍ��݃p�X�̃|�C���^�����ւ���
		m_loadPaths = newLoadPaths;
		m_loadPaths[numOld] = new char[TXT_MAX];
	}

	// �p�X��ۑ�
	sprintf(m_loadPaths[numOld], "%s", loadPath);

	// �ԍ����w��
	idx = numOld;

	// �ǂݍ��݊J�n
	return true;
}

//========================================
// ����������������
//========================================
void CRegist::InitMemory(const unsigned short& num) {

	// ������
	m_num = num;

	{// �ǂݍ��ݍσp�X�̃������m��
		char** newLoadPaths = new char*[m_num];

		// �ǂݍ��݃p�X�̉��
		for (int nCnt = 0; nCnt < m_num; nCnt++)
			RNLib::Memory().Release<char>(&m_loadPaths[nCnt]);
		RNLib::Memory().Release<char*>(&m_loadPaths);

		// �ǂݍ��݃p�X�̃|�C���^�����ւ���
		m_loadPaths = newLoadPaths;

		// �����񃁃����m��
		for (int nCnt = 0; nCnt < m_num; nCnt++) {
			m_loadPaths[nCnt] = new char[TXT_MAX];
		}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [����J]�o�^�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �ǂݍ��ݍσp�X�̃��������Z�b�g����
//========================================
void CRegist::ReAllocLoadPath(const short& oldNum) {

	for (int cnt = oldNum; cnt < m_num; cnt++) {
		RNLib::Memory().Release(&m_loadPaths[cnt]);
	}
	RNLib::Memory().ReAlloc(&m_loadPaths, m_num, oldNum);
}