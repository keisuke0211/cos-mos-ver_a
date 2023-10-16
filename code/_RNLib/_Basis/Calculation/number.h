//========================================
// 
// ���l�����̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ number.h ]]]
//========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//****************************************
// �񋓌^��`
//****************************************
// �J�E���g�̎��
typedef enum {
	COUNTTYPE_NORMAL,	// �ʏ�
	COUNTTYPE_TURN,		// �܂�Ԃ�
	COUNTTYPE_MAX,
}COUNTTYPE;

//****************************************
// �v���g�^�C�v�錾
//****************************************
int   Counter(int *pData, int nMin, int nMax, int *pCounter, int nCountTime, COUNTTYPE countType);
bool  IntConsumption(int *pData, int nSubtract);
void  FloatControl(float *pData, float fMax, float fMin);
void  FloatLoopControl(float *pData, float fMax, float fMin);
void  IntControl(int *pData, int nMax, int nMin);
void  IntLoopControl(int *pData, int nMax, int nMin);
int   IntControlReturn(int nData, int nMax, int nMin);
int   IntLoopControlReturn(int nData, int nMax, int nMin);
bool  Lottery(float fProb);
float fRand(void);
int   Rand(int nMin, int nMax);
float Tick(float fData, float fSpace);
int   Sign(float fData);
float MaxOfZero(float fData);
int   OR(std::initializer_list<int> args);
int*  CreateRandList(int nNum);

#endif