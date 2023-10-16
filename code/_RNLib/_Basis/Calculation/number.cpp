//========================================
// 
// ���l����
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ number.cpp ]]]
//========================================
#include "../../RNlib.h"
#include <iostream>
#include <initializer_list>
#include <random>

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// Counter�֐� - �J�E���g���� -
// Author:RIKU NISHIMURA
//========================================
int Counter(int *pData, int nMin, int nMax, int *pCounter, int nCountTime, COUNTTYPE countType)
{
	if (nCountTime != -1)
	{// �J�E���g�ɂ����鎞�Ԃ�-1�łȂ����A
		if (pCounter == NULL) 
		{// �J�E���^�[�̃|�C���^��NULL�̎��A
			*pData += 1;	// �l�����Z
		}
		else
		{// �J�E���^�[�̃|�C���^��NULL�łȂ����A
			*pCounter += 1;	// �J�E���^�[�����Z

			if (*pCounter >= nCountTime)
			{// �J�E���^�[���J�E���g�ɂ����鎞�ԂɒB�������A
				*pCounter = 0;	// �J�E���^�[������������
				*pData += 1;	// �l�����Z
			}
		}
	}
	else
	{// �J�E���g�ɂ����鎞�Ԃ�-1�̎��A
		// �l�����̂܂ܕԂ�
		return *pData;
	}

	// �J�E���g�̎�ނɉ������l��Ԃ�
	switch (countType)
	{
	case COUNTTYPE_NORMAL:
		
		// �l������ŏ�]�Z�������ʂ�Ԃ�
		return nMin + (*pData %= (nMax - nMin + 1));
	case COUNTTYPE_TURN:

		if ((*pData / (nMax - nMin)) % 2 == 0)
		{// �l������ŏ��Z�������ʂ��������������A
			// �l������ŏ�]�Z�������ʂ�Ԃ�
			return nMin + (*pData %= (nMax - nMin));
		}
		else
		{//�p�^�[��������ŏ��Z�������ʂ�����������A
			//�������p�^�[��������ŏ�]�Z�������ʂ����Z�������ʂ�Ԃ�
			return nMax - (*pData % (nMax - nMin));
		}

	default:
		assert(false);
		return 0;
	}
}

//========================================
// IntConsumption�֐� - int�^�̒l�̏���� -
// Author:RIKU NISHIMURA
//========================================
bool IntConsumption(int *pData, int nSubtract) 
{
	if ((*pData -= nSubtract) >= 0)
	{// �l�������ʂ����Z��������0�ȏ�̎��A
		return true;	// �^��Ԃ�
	}
	else 
	{// �l�������ʂ����Z��������0��������Ă��鎞�A
		*pData += nSubtract;	// ���Z���������Z
		return false;			// �U��Ԃ�
	}
}

//========================================
// FloatControl�֐� - float�^�̒l�̐��䏈�� -
// Author:RIKU NISHIMURA
//========================================
void FloatControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// �ő�l�������Ă������A
		// �ő�l����
		*pData = fMax;
	}
	else if (*pData < fMin)
	{// �ŏ��l��������Ă������A
		// �ŏ��l����
		*pData = fMin;
	}
}

//========================================
// FloatLoopControl�֐� - float�^�̒l�̃��[�v���䏈�� -
// Author:RIKU NISHIMURA
//========================================
void FloatLoopControl(float *pData, float fMax, float fMin) {
	float fRange = fMax - fMin;
	while (*pData < fMin) {
		*pData += fRange;
	}
	while (*pData >= fMax) {
		*pData -= fRange;
	}
}

//========================================
// IntControl�֐� - int�^�̒l�̐��䏈�� -
// Author:RIKU NISHIMURA
//========================================
void IntControl(int *pData, int nMax, int nMin)
{
	if (*pData > nMax)
	{// �ő�l�������Ă������A
		// �ő�l����
		*pData = nMax;
	}
	else if (*pData < nMin)
	{// �ŏ��l��������Ă������A
		// �ŏ��l����
		*pData = nMin;
	}
}

//========================================
// IntLoopControl�֐� - int�^�̒l�̃��[�v���䏈�� -
// Author:RIKU NISHIMURA
//========================================
void IntLoopControl(int *pData, int nMax, int nMin) {
	int nRange = nMax - nMin;
	while (*pData < nMin) {
		*pData += nRange;
	}
	while (*pData >= nMax) {
		*pData -= nRange;
	}
}

//========================================
// IntControlReturn�֐� - int�^�̒l�̐��䏈��(���ʂ�Ԃ�) -
// Author:RIKU NISHIMURA
//========================================
int IntControlReturn(int nData, int nMax, int nMin)
{
	if (nData > nMax)
	{// �ő�l�������Ă������A
		// �ő�l����
		nData = nMax;
	}
	else if (nData < nMin)
	{// �ŏ��l��������Ă������A
		// �ŏ��l����
		nData = nMin;
	}

	return nData;
}

//========================================
// IntLoopControlReturn�֐� - int�^�̒l�̃��[�v���䏈��(���ʂ�Ԃ�) -
// Author:RIKU NISHIMURA
//========================================
int IntLoopControlReturn(int nData, int nMax, int nMin)
{
	if (nData >= nMax)
	{// �ő�l�ȏ�̎��A
		// �ŏ��l����
		nData = nMin;
	}
	else if (nData < nMin)
	{// �ŏ��l��������Ă������A
		// �ő�l����
		nData = nMax - 1;
	}

	return nData;
}

//========================================
// Lottery�֐� - ���I���� -
// Author:RIKU NISHIMURA
//========================================
bool Lottery(float fProb)
{
	if (fProb > (0.1f * (rand() % 1000)))
	{// ���I�������A
		// �^��Ԃ�
		return true;
	}
	else
	{// ���I���Ȃ��������A
		// �U��Ԃ�
		return false;
	}
}

//========================================
// fRand�֐� - �����̗�����Ԃ� -
// Author:RIKU NISHIMURA
//========================================
float fRand(void) {
	return (float)rand() / RAND_MAX;
}

//========================================
// Rand�֐� - ������Ԃ� -
// Author:RIKU NISHIMURA
//========================================
int Rand(int nMin, int nMax) 
{
	return nMin + (rand() % (nMax - nMin));
}

//========================================
// Tick�֐� - �l���Ԋu���݂ŕԂ� -
//========================================
float Tick(float fData, float fSpace)
{
	return (int)(fData / fSpace) * fSpace;
}

//========================================
// Sign�֐� - �^����ꂽ�l�ɉ�����1�𕄍��t���ŕԂ� -
// Author:RIKU NISHIMURA
//========================================
int Sign(float fData)
{
	if (fData == 0)
	{// ������0���������A
		// 0��Ԃ�
		return 0;
	}
	
	return fData > 0.0f ? 1 : -1;
}

//========================================
// MaxOfZero�֐� - �^����ꂽ�l��0�ȉ��̎���0���A0�ȏ�̎��͒l�����̂܂ܕԂ� -
// Author:RIKU NISHIMURA
//========================================
float MaxOfZero(float fData) 
{
	if (fData <= 0.0f)
	{
		return 0.0f;
	}
	return fData;
}

//========================================
// �^����ꂽ�����l�������_���ɕԂ�
// Author:RIKU NISHIMURA
//========================================
int OR(std::initializer_list<int> args) {
	int randomIndex = std::rand() % args.size();

	auto it = args.begin();
	std::advance(it, randomIndex);

	return *it;
}

//========================================
// �����_�����X�g���쐬
// Author:RIKU NISHIMURA
//========================================
int* CreateRandList(int num) {
	int* pList = NULL;
	RNLib::Memory()->Alloc<int>(&pList, num);
	for (int nCnt = 0; nCnt < num; nCnt++) {
		pList[nCnt] = nCnt;
	}
	for (int nCnt = 0; nCnt < num; nCnt++) {
		int nSwap = nCnt + rand() % (num - nCnt);
		int nTemp = pList[nCnt];
		pList[nCnt]  = pList[nSwap];
		pList[nSwap] = nTemp;
	}

	return pList;
}