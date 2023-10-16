//========================================
// 
// �􉽊w�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ geometry.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 2�_�̋������Z�o
// Author:RIKU NISHIMURA
//========================================
float Find_Dist(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2) {
	float x = pos1.x - pos2.x;	// ��������X��
	float y = pos1.y - pos2.y;	// ��������Y��
	float z = pos1.z - pos2.z;	// ��������Z��

	// 2�_�̋�����Ԃ�
	return sqrtf((x * x) + (y * y) + (z * z));
}

//========================================
// 2�_�̋������Z�o(�����낵���_)
// Author:RIKU NISHIMURA
//========================================
float Find_Dist_LookDown(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2) {
	float x = pos1.x - pos2.x;	// ��������X��
	float z = pos1.z - pos2.z;	// ��������Z��

	// 2�_�̋�����Ԃ�
	return sqrtf((x * x) + (z * z));
}

//========================================
// 2�_�̊p�x���Z�o(���Վ��_)
// Author:RIKU NISHIMURA
//========================================
float Find_Angle_LookFront(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	float fAngle;	// �p�x

	fAngle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);
	fAngle -= D3DX_PI_HALF;
	fAngle *= -1;

	return fAngle;
}

//========================================
// 2�_�̊p�x���Z�o(�����낵���_)
// Author:RIKU NISHIMURA
//========================================
float Find_Angle_LookDown(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	float fAngle;	// �p�x

	fAngle = atan2f(targetPos.z - pos.z, targetPos.x - pos.x);
	fAngle -= D3DX_PI_HALF;
	fAngle *= -1;

	return fAngle;
}

//========================================
// 2�_�̌������Z�o
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_Rot(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	return Find_VecRot(targetPos - pos);
}

//========================================
// 2�_�̌����}�g���b�N�X���Z�o
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX Find_RotMtx(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	D3DXVECTOR3 dir = targetPos - pos;
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX  mtx;
	D3DXMatrixLookAtLH(&mtx, &pos, &targetPos, &nor);
	return mtx;
}

//========================================
// ��_���W���Z�o(�����낵���_)
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_Inter_LookDown(D3DXVECTOR3 posA1, D3DXVECTOR3 posA2, D3DXVECTOR3 posB1, D3DXVECTOR3 posB2) {
	D3DXVECTOR3 vB1B2 = posB2 - posB1;	// �x�N�g��B1��B2
	D3DXVECTOR3 vA1A2 = posA2 - posA1;	// �x�N�g��A1��A2
	D3DXVECTOR3 vA2B1 = posB1 - posA2;	// �x�N�g��A2��B1
	D3DXVECTOR3 vB1A1 = posA1 - posB1;	// �x�N�g��B1��A1

	// �ʐ�S1
	float fAreaS1 = ((vB1B2.x * vB1A1.z) - (vB1B2.z * vB1A1.x)) * 0.5f;
	// �ʐ�S2
	float fAreaS2 = ((vB1B2.x * vA2B1.z) - (vB1B2.z * vA2B1.x)) * 0.5f;

	// �ʐ�S1�̊���
	float fRate = (fAreaS1 / (fAreaS1 + fAreaS2));

	// ��_�̍��W��Ԃ�
	return	D3DXVECTOR3(
		posA1.x + (vA1A2.x * fRate),
		0.0f,
		posA1.z + (vA1A2.z * fRate));
}

//========================================
// �p�x�̍����Z�o
// Author:RIKU NISHIMURA
//========================================
float Find_AngleDiff(float fAngle, float fTargetAngle) {
	float fAngleDifference = 0.0f;	// �p�x�̍�

	// �p�x�𐧌䂷��
	Limit_Angle(&fAngle);

	if ((fAngle >= 0.0f) && (fTargetAngle >= 0.0f))
	{// �ǂ���̊p�x���v���X�̎��A �p�x�̍���ݒ�
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}
	else if ((fAngle <= 0.0f) && (fTargetAngle <= 0.0f))
	{// �ǂ���̊p�x���}�C�i�X�̎��A �p�x�̍���ݒ�
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}

	if ((fAngle >= 0.0f) && (fTargetAngle <= 0.0f))
	{// �p�x���v���X�ŁA�ڕW�p�x���}�C�i�X�̎��A
		if (fAngle - D3DX_PI <= fTargetAngle)
		{// �ڕW�p�x�������ɋ߂����A �p�x�̍���ݒ�
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle - D3DX_PI >= fTargetAngle)
		{// �ڕW�p�x���㑤�ɋ߂����A �p�x�̍���ݒ�
			fAngleDifference = (D3DX_PI - fAngle) + (D3DX_PI + fTargetAngle);
		}
	}

	if ((fAngle <= 0.0f) && (fTargetAngle >= 0.0f))
	{// �p�x���}�C�i�X�ŁA�ڕW�p�x���v���X�̎��A
		if (fAngle + D3DX_PI >= fTargetAngle)
		{// �ڕW�p�x�������ɋ߂����A �p�x�̍���ݒ�
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle + D3DX_PI <= fTargetAngle)
		{// �ڕW�p�x���㑤�ɋ߂����A �p�x�̍���ݒ�
			fAngleDifference = -(D3DX_PI + fAngle) - (D3DX_PI - fTargetAngle);
		}
	}

	return fAngleDifference;
}

//========================================
// �����̃x�N�g�����Z�o
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_RotVec(D3DXVECTOR3 rot) {
	D3DXVECTOR3 vec;

	float fSinX = sinf(rot.x);
	float fCosX = cosf(rot.x);
	float fSinY = sinf(rot.y);
	float fCosY = cosf(rot.y);

	vec.x = fSinY * fCosX;
	vec.y = fSinX;
	vec.z = fCosY * fCosX;

	D3DXVec3Normalize(&vec, &vec);

	return vec;
}

//========================================
// �x�N�g���̌������Z�o
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_VecRot(D3DXVECTOR3 vec) {
	D3DXVec3Normalize(&vec, &vec);

	return D3DXVECTOR3(
		asinf(vec.y),
		atan2f(vec.x, vec.z),
		0.0f);
}

//========================================
// �J�����ʂ܂ł̐����������Z�o
// Author:RIKU NISHIMURA
//========================================
float Find_DistToCameraPlane(D3DXVECTOR3 pos) {
	D3DXVECTOR3 camToPosVec = pos - RNLib::Camera3D()->GetPosV();
	D3DXVECTOR3 camPlaneVec = RNLib::Camera3D()->GetVec();
	float fDistance = D3DXVec3Dot(&camToPosVec, &camPlaneVec);

	return fabsf(fDistance);
}

//========================================
// �O�ς���@�����Z�o
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_VecNor(D3DXVECTOR3 start1, D3DXVECTOR3 end1, D3DXVECTOR3 start2, D3DXVECTOR3 end2) {
	D3DXVECTOR3 vec1 = end1 - start1;
	D3DXVECTOR3 vec2 = end2 - start2;
	D3DXVECTOR3 result = INITD3DXVECTOR3;
	D3DXVec3Cross(&result, &vec1, &vec2);
	D3DXVec3Normalize(&result, &result);

	return result;
}

//========================================
// �p�x��͈͓�����
// Author:RIKU NISHIMURA
//========================================
void Limit_Angle(float *pAngle) {
	if (*pAngle > D3DX_PI)
	{// �~����(��)�������Ă��鎞�A
		*pAngle = (D3DX_PI - (*pAngle - D3DX_PI)) * -1;
	}
	else if (*pAngle < -D3DX_PI)
	{// �~����(��)��������Ă��鎞�A
		*pAngle = (D3DX_PI + (*pAngle + D3DX_PI));
	}
}

//========================================
// ���������[�v����
// Author:RIKU NISHIMURA
//========================================
void Cycle_Control(D3DXVECTOR3* pRot) {
	FloatLoopControl(&pRot->x, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->y, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->z, D3DX_PI, -D3DX_PI);
}

//========================================
// �p�x���w�肳�ꂽ�����l�ɕϊ�
// Author:RIKU NISHIMURA
//========================================
float Conv_AngleToDir(float fAngle, int nDiv) {
	float fRange = ((D3DX_PI * 2) / nDiv);	// �������̊p�x��

	for (int nCntDir = 0; nCntDir < nDiv + 1; nCntDir++) {
		if (fAngle >= -D3DX_PI - (fRange * 0.5f) + (fRange * nCntDir) &&
			fAngle <= -D3DX_PI + (fRange * 0.5f) + (fRange * nCntDir))
		{// �J�E���g�̕����̊p�x���̓����̎��A�p�x��ݒ�
			fAngle = -D3DX_PI + (fRange * nCntDir);
			break;	// �J��Ԃ������𔲂���
		}
	}

	return fAngle;
}

//========================================
// �ʒu�������낵�(Z��Y)�ɕϊ�����
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Conv_LookDownPos(D3DXVECTOR3 pos) {
	float fYTemp = pos.y;
	pos.y = -pos.z;
	pos.z = fYTemp;

	return pos;
}

//========================================
// �����������낵�(Z��Y)�ɕϊ�����
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Conv_LookDownRot(D3DXVECTOR3 rot) {
	float fYTemp = rot.y;
	rot.y = -rot.z;
	rot.y *= -1;
	rot.y -= D3DX_PI;
	rot.z = fYTemp;
	rot.z += D3DX_PI;
	rot.z *= -1;

	return rot;
}

//========================================
// �����_���ȃx�N�g�����擾
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 vecRand(void) {
	float fX = fRand();
	float fY = fRand();
	float fZ = fRand();
	float fSum = fX + fY + fZ;
	if (fSum > 0.0f) {
		fX /= fSum;
		fY /= fSum;
		fZ /= fSum;

		if (rand() % 2 == 0)fX *= -1;
		if (rand() % 2 == 0)fY *= -1;
		if (rand() % 2 == 0)fZ *= -1;
	}
	else {
		fX =
		fY =
		fZ = 0.333333f;
	}

	return D3DXVECTOR3(fX, fY, fZ);
}