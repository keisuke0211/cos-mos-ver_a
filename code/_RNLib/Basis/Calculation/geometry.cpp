//========================================
// 
// �􉽊w�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�􉽊w�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// [�ÓI]2�_�̋����𒲂ׂ�
//========================================
float CGeometry::FindDistance(const Pos3D& posA, const Pos3D& posB) {

	const float x(posA.x - posB.x);	// ��������X��
	const float y(posA.y - posB.y);	// ��������Y��
	const float z(posA.z - posB.z);	// ��������Z��

	// 2�_�̋�����Ԃ�
	return sqrtf((x * x) + (y * y) + (z * z));
}

//========================================
// [�ÓI]2�_�̋����𒲂ׂ�(XZ����)
//========================================
float CGeometry::FindDistanceXZ(const Pos3D& posA, const Pos3D& posB) {

	const float x(posA.x - posB.x);	// ��������X��
	const float z(posA.z - posB.z);	// ��������Z��

	// 2�_�̋�����Ԃ�
	return sqrtf((x * x) + (z * z));
}

//========================================
// [�ÓI]�J�����ʂ܂ł̐��������𒲂ׂ�
//========================================
float CGeometry::FindDistanceToCameraPlane(const Pos3D& pos, CCamera& camera) {

	Vector3D camToPosVec(pos - camera.GetPosV());
	Vector3D camPlaneVec(camera.GetVec());

	return fabsf(D3DXVec3Dot(&camToPosVec, &camPlaneVec));
}

//========================================
// [�ÓI]2�_�̊p�x�𒲂ׂ�(XY����)
//========================================
Angle CGeometry::FindAngleXY(const Pos3D& pos, const Pos3D& targetPos) {
	
	return -(atan2f(targetPos.y - pos.y, targetPos.x - pos.x) - D3DX_PI_HALF);
}

//========================================
// [�ÓI]2�_�̊p�x�𒲂ׂ�(XZ����)
//========================================
Angle CGeometry::FindAngleXZ(const Pos3D& pos, const Pos3D& targetPos) {
	
	return -(atan2f(targetPos.z - pos.z, targetPos.x - pos.x) - D3DX_PI_HALF);
}

//========================================
// [�ÓI]2�_�̌����𒲂ׂ�
//========================================
Rot3D CGeometry::FindRot(const Pos3D& pos, const Pos3D& targetPos) {

	return CGeometry::FindVecRot(targetPos - pos);
}

//========================================
// [�ÓI]��_���W�𒲂ׂ�(XZ����)
//========================================
Pos3D CGeometry::FindIntersectionXZ(const Pos3D& posA1, const Pos3D& posA2, const Pos3D& posB1, const Pos3D& posB2) {

	const Vector3D B1B2Vec(posB2 - posB1);	// �x�N�g��B1��B2
	const Vector3D A1A2Vec(posA2 - posA1);	// �x�N�g��A1��A2
	const Vector3D A2B1Vec(posB1 - posA2);	// �x�N�g��A2��B1
	const Vector3D B1A1Vec(posA1 - posB1);	// �x�N�g��B1��A1
	const float areaS1(((B1B2Vec.x * B1A1Vec.z) - (B1B2Vec.z * B1A1Vec.x)) * 0.5f);	// �ʐ�S1
	const float areaS2(((B1B2Vec.x * A2B1Vec.z) - (B1B2Vec.z * A2B1Vec.x)) * 0.5f);	// �ʐ�S2
	const float S1Rate((areaS1 / (areaS1 + areaS2)));	// �ʐ�S1�̊���

	return Pos3D(posA1.x + (A1A2Vec.x * S1Rate), 0.0f, posA1.z + (A1A2Vec.z * S1Rate));
}

//========================================
// [�ÓI]�p�x�̍��𒲂ׂ�
//========================================
Angle CGeometry::FindAngleDifference(const Angle& angle, const Angle& targetAngle) {
	
	// [[[ angle = + & targetAngle = + ]]]
	if ((angle >= 0.0f) && (targetAngle >= 0.0f))
		return targetAngle - angle;
	// [[[ angle = - & targetAngle = - ]]]
	else if ((angle <= 0.0f) && (targetAngle <= 0.0f))
		return targetAngle - angle;

	// [[[ angle = + & targetAngle = - ]]]
	if ((angle >= 0.0f) && (targetAngle <= 0.0f)) {

		// �ڕW�p�x�������ɋ߂�
		if (angle - D3DX_PI <= targetAngle)
			return targetAngle - angle;

		// �ڕW�p�x���㑤�ɋ߂�
		else if (angle - D3DX_PI >= targetAngle)
			return (D3DX_PI - angle) + (D3DX_PI + targetAngle);
	}

	// [[[ angle = - & targetAngle = + ]]]
	if ((angle <= 0.0f) && (targetAngle >= 0.0f)) {

		// �ڕW�p�x�������ɋ߂�
		if (angle + D3DX_PI >= targetAngle)
			return targetAngle - angle;

		// �ڕW�p�x���㑤�ɋ߂�
		else if (angle + D3DX_PI <= targetAngle)
			return -(D3DX_PI + angle) - (D3DX_PI - targetAngle);
	}

	assert(false);

	return 0.0f;
}

//========================================
// [�ÓI]�����̃x�N�g���𒲂ׂ�
//========================================
Vector3D CGeometry::FindRotVec(const Rot3D& rot) {

	const float sinX(sinf(rot.x));
	const float cosX(cosf(rot.x));
	const float sinY(sinf(rot.y));
	const float cosY(cosf(rot.y));

	Vector3D vec(sinY * cosX, sinX, cosY * cosX);
	D3DXVec3Normalize(&vec, &vec);

	return vec;
}

//========================================
// [�ÓI]�x�N�g���̌����𒲂ׂ�
//========================================
Rot3D CGeometry::FindVecRot(const Vector3D& vec) {

	Normal3D nor = vec;
	D3DXVec3Normalize(&nor, &nor);

	return Rot3D(asinf(vec.y), atan2f(vec.x, vec.z), 0.0f);
}

//========================================
// [�ÓI]�O�ς���@���𒲂ׂ�
//========================================
Normal3D CGeometry::FindVecNor(const Vector3D& vecA, const Vector3D& vecB) {

	Normal3D nor(INITNORMAL3D);
	D3DXVec3Cross(&nor, &vecA, &vecB);
	D3DXVec3Normalize(&nor, &nor);

	return nor;
}

//========================================
// [�ÓI]�����_���ȃx�N�g�����擾
//========================================
Normal3D CGeometry::GetRandomVec(void) {

	float x  (fRand());
	float y  (fRand());
	float z  (fRand());
	float sum(x + y + z);
	if (sum > 0.0f) {
		x /= sum;
		y /= sum;
		z /= sum;

		if (rand() % 2 == 0)x *= -1;
		if (rand() % 2 == 0)y *= -1;
		if (rand() % 2 == 0)z *= -1;
	}
	else {
		x = y = z = 0.333333f;
	}

	return Normal3D(x, y, z);
}