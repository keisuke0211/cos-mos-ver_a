//========================================
// 
// �􉽊w�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../RNmain.h"
#include "../Draw/camera.h"

//****************************************
// �N���X��`
//****************************************
// �􉽊w�N���X
class CGeometry {
public:
	//========== [[[ �֐��錾 ]]]
	static float    FindDistance             (const Pos3D& posA, const Pos3D& posB);
	static float    FindDistanceXZ           (const Pos3D& posA, const Pos3D& posB);
	static float    FindDistanceToCameraPlane(const Pos3D& pos, CCamera& camera);
	static Angle    FindAngleXY              (const Pos3D& pos, const Pos3D& targetPos);
	static Angle    FindAngleXZ              (const Pos3D& pos, const Pos3D& targetPos);
	static Rot3D    FindRot                  (const Pos3D& pos, const Pos3D& targetPos);
	static Pos3D    FindIntersectionXZ       (const Pos3D& posA1, const Pos3D& posA2, const Pos3D& posB1, const Pos3D& posB2);
	static Angle    FindAngleDifference      (const Angle& angle, const Angle& targetAngle);
	static Vector3D FindRotVec               (const Rot3D& rot);
	static Rot3D    FindVecRot               (const Vector3D& vec);
	static Normal3D FindVecNor               (const Vector3D& vecA, const Vector3D& vecB);
	static Normal3D GetRandomVec             (void);
};