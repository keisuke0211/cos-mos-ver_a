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

#if 1
		// �V��������0�ȉ��̎��A������ďI��
		if (afterNum <= 0) {
			Release(alloc);
			return;
		}
		else if (beforeNum == afterNum) {
			// ���̕ϓ����������A�I��
			return;
		}

		// �V�����T�C�Y���̃��������m��
		T* newAlloc = new T[afterNum];

		// �R�s�[����v�f��������
		int copyNum = (beforeNum < afterNum) ? beforeNum : afterNum;

		// ���̃f�[�^��V�����̈�ɃR�s�[
		memcpy(newAlloc, *alloc, sizeof(T) * copyNum);

		// �V�����ǉ����ꂽ�v�f�ɑ΂��ăf�t�H���g�R���X�g���N�^���Ă�
		for (int i = beforeNum; i < afterNum; ++i) {
			new (newAlloc + i) T();
		}

		// �Â������������
		delete[] *alloc;

		// �V�����|�C���^�ɓ���ւ���
		*alloc = newAlloc;
#endif

#if 0
		// �V��������0�ȉ��̎��A������ďI��
		if (afterNum <= 0) {
			Release(alloc);
			return;
		}
		else if (beforeNum <= 0)
		{// ���̐���0�ȉ��̎��A���ʂɊm�ۂ��ďI��
			Alloc(alloc, afterNum, isMutex);
			return;
		}
		else if (beforeNum == afterNum)
		{// ���̕ϓ����������A�I��
			return;
		}

		// ���������ŏI�T�C�Y���m��(��malloc�ŃR���X�g���N�^�������)
		T* newAlloc = (T*)malloc(sizeof(T) * afterNum);

		if (beforeNum < afterNum) {
			//----------------------------------------
			// �����������ꍇ
			//----------------------------------------
			// New�|�C���^�Ɍ��̃T�C�Y���̃��������R�s�[
			memcpy(newAlloc, *alloc, sizeof(T) * beforeNum);

			// �������T�C�Y���̃������m��
			int increasedNum = -beforeNum + afterNum;
			T* increased = new T[increasedNum];

			// New�|�C���^�ɑ������T�C�Y���̃��������R�s�[
			memcpy((newAlloc + beforeNum), increased, sizeof(T) * increasedNum);

			// �ꎞ�����������(��free�Ńf�X�g���N�^�������)
			free(increased);
		}
		else {
			//----------------------------------------
			// �����������ꍇ
			//----------------------------------------
			// New�|�C���^�ɕK�v�ȃT�C�Y�����������R�s�[
			memcpy(newAlloc, *alloc, sizeof(T) * afterNum);

			// ���������������m��(��malloc�ŃR���X�g���N�^�������)
			int increasedNum = beforeNum - afterNum;
			T* increased = (T*)malloc(sizeof(T) * increasedNum);

			// Dec�|�C���^�Ɍ��������̃��������R�s�[
			memcpy(increased, (*alloc + afterNum), sizeof(T) * increasedNum);

			// ���������̃����������
			delete[] increased;
		}

		// �Â������������(��free�Ńf�X�g���N�^�������)
		free(*alloc);

		// �V�����|�C���^�ɓ���ւ���
		*alloc = newAlloc;
#endif
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