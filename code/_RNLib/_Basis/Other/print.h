//========================================
// 
// ������֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ print.h ]]]
//========================================
#ifndef _PRINT_H_
#define _PRINT_H_

//****************************************
// �֐��錾
//****************************************
const char *CreateText(const char* format, ...);	// �����ɓ��͂��ꂽ������̃|�C���^��Ԃ�
const char* ConvSJistoUtf8(char* pSource);
void StrCpyDynamicMemory(char** ppDestination, const char* pSource);	// ������̃|�C���^�𓮓I�Ɋm�ۂ��A�������ۑ�����
int StrLen(char* pString);
void UninitPrint(void);	// ������֘A

#endif