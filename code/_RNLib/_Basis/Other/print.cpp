//========================================
// 
// ������̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ print.cpp ]]]
//========================================
#include "../../RNlib.h"

//****************************************
// �ÓI�ϐ��錾
//****************************************
static char* pBuffer = NULL;
static char* pBuffer2 = NULL;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �����ɓ��͂��ꂽ������̃|�C���^��Ԃ�
// Author:RIKU NISHIMURA
//========================================
const char *CreateText(const char* pFormat, ...) {
	va_list args;  // �ϒ������̂��߂̃��X�g
	int size;
	
	// ���������g�p����Ă�����������
	if (pBuffer != NULL) {
		free(pBuffer);
	}

	va_start(args, pFormat);  // �ϒ������̏������n�߂�

	 // �o�͂��镶����̃T�C�Y���擾����
	size = vsnprintf(NULL, 0, pFormat, args);
	va_end(args);  // �ϒ������̏������I������

	// ������̃T�C�Y�ɍ��킹���������𓮓I�Ɋm�ۂ���
	pBuffer = (char*)malloc(size + 1);

	va_start(args, pFormat);  // �ϒ������̏������ēx�n�߂�
	vsprintf(pBuffer, pFormat, args);  // �o�b�t�@�ɕ��������������
	va_end(args);  // �ϒ������̏������I������

	return pBuffer;  // ������̃|�C���^��Ԃ�
}

// http://www.lab.its55.com/?p=32
const char* ConvSJistoUtf8(char* pSource)
{
	//ShiftJIS����UTF-16�֕ϊ�
	const int nSize = ::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)
		pSource, -1, NULL, 0);

	char* buffUtf16 = new char[nSize * 2 + 2];
	::MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pSource, -1, (LPWSTR)
		buffUtf16, nSize);

	//UTF-16����Shift-JIS�֕ϊ�
	const int nSizeUtf8 = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)
		buffUtf16, -1, NULL, 0, NULL, NULL);

	char* buffUtf8 = new char[nSizeUtf8 * 2];
	ZeroMemory(buffUtf8, nSizeUtf8 * 2);
	::WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)
		buffUtf8, nSizeUtf8, NULL, NULL);

	// ���������g�p����Ă�����������
	if (pBuffer2 != NULL) {
		free(pBuffer2);
	}

	pBuffer2 = (char*)malloc(nSizeUtf8);
	memcpy(pBuffer2, buffUtf8, nSizeUtf8);

	delete buffUtf16;
	delete buffUtf8;

	return pBuffer2;
}

//========================================
// ������̃|�C���^�𓮓I�Ɋm�ۂ��A�������ۑ�����
// Author:RIKU NISHIMURA
//========================================
void StrCpyDynamicMemory(char** ppDestination, const char* pSource) {
	if (pSource == NULL)
		return;

	// ������̒����ɉ����ă��������m�ۂ���
	int nStrLen = strlen(pSource);
	if (*ppDestination != NULL) {
		delete* ppDestination;
	}
	*ppDestination = new char[nStrLen + 1];

	// ��������R�s�[����
	strcpy(*ppDestination, pSource);
}

//========================================
// ������̒������擾
// Author:RIKU NISHIMURA
//========================================
int StrLen(char* pString) {
	// char�^�̕������wchar_t�^�̕�����ɕϊ�
	size_t length = strlen(pString);
	wchar_t* wstr = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
	mbstowcs(wstr, pString, length + 1);
	int nStrLen = (int)wcslen(wstr);
	free(wstr);
	return nStrLen;
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void UninitPrint(void) {
	// ���������g�p����Ă�����������
	if (pBuffer != NULL) {
		free(pBuffer);
	}
	if (pBuffer2 != NULL) {
		free(pBuffer2);
	}
}