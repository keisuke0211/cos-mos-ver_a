//========================================
// 
// �������֘A����
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
class CMemory {
public:
	//========== [[[ �֐��錾 ]]]
	std::mutex& GetMutex(void) { return m_memoryMutex; }

	//========================================
	// �������m�ۏ���
	//========================================
	template <class T>void Alloc(T** alloc, const int num = 1, const bool isMutex = true) {
		
		// ������Ă���
		Release(alloc);

		// ����0�ȉ��̎��A�I��
		if (num <= 0)
			return;

		// ��������̈�Mutex�����b�N
		if (isMutex)
			std::lock_guard<std::mutex> lock(m_memoryMutex);

		// �������m�ۂ���
		*alloc = new T[num];
	}
	//========================================
	// �������m�ۏ���(�T�C�Y�w��)
	//========================================
	void Alloc(void** alloc, size_t size, const int num = 1, const bool isMutex = true) {
		
		// ������Ă���
		Release(alloc);

		// ��������̈�Mutex�����b�N
		if (isMutex)
			std::lock_guard<std::mutex> lock(m_memoryMutex);

		// �������m�ۂ���
		*alloc = malloc(size);
	}
	//========================================
	// �������Ċm�ۏ���
	//========================================
	template <class T>void ReAlloc(T** alloc, const int beforeNum, const int afterNum, const bool isMutex = true) {

		// �V��������0�ȉ��̎��A������ďI��
		if (afterNum <= 0) {
			Release(alloc);
			return;
		}

		// �R�s�[�����V���������z���Ȃ��悤����
		int copyNum = beforeNum;
		if (copyNum > afterNum)
			copyNum = afterNum;

		// �V�������������m�ۂ���
		T* newAlloc = NULL;
		Alloc<T>(&newAlloc, afterNum, isMutex);

		// �ߋ��̐���0���z���Ă��鎞�A���������R�s�[����
		if (beforeNum > 0) {
			if (*alloc != NULL)
				memcpy(newAlloc, *alloc, sizeof(T) * copyNum);
		}

		// �Â��̈��������A�V�����|�C���^�ɓ���ւ���
		Release(alloc);
		*alloc = newAlloc;
	}
	//========================================
	// �������������
	//========================================
	template <class T>void Release(T** release) {

		// NULL�Ȃ������Ȃ�
		if (*release == NULL)
			return;

		// ���
		delete[] (*release);
		*release = NULL;
	}

private:
	//========== [[[ �ϐ��錾 ]]]
	std::mutex m_memoryMutex;
};