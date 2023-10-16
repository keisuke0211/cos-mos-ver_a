//========================================
// 
// 幾何学の処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ geometry.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 2点の距離を算出
// Author:RIKU NISHIMURA
//========================================
float Find_Dist(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2) {
	float x = pos1.x - pos2.x;	// 平方根のX辺
	float y = pos1.y - pos2.y;	// 平方根のY辺
	float z = pos1.z - pos2.z;	// 平方根のZ辺

	// 2点の距離を返す
	return sqrtf((x * x) + (y * y) + (z * z));
}

//========================================
// 2点の距離を算出(見下ろし視点)
// Author:RIKU NISHIMURA
//========================================
float Find_Dist_LookDown(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2) {
	float x = pos1.x - pos2.x;	// 平方根のX辺
	float z = pos1.z - pos2.z;	// 平方根のZ辺

	// 2点の距離を返す
	return sqrtf((x * x) + (z * z));
}

//========================================
// 2点の角度を算出(俯瞰視点)
// Author:RIKU NISHIMURA
//========================================
float Find_Angle_LookFront(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	float fAngle;	// 角度

	fAngle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);
	fAngle -= D3DX_PI_HALF;
	fAngle *= -1;

	return fAngle;
}

//========================================
// 2点の角度を算出(見下ろし視点)
// Author:RIKU NISHIMURA
//========================================
float Find_Angle_LookDown(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	float fAngle;	// 角度

	fAngle = atan2f(targetPos.z - pos.z, targetPos.x - pos.x);
	fAngle -= D3DX_PI_HALF;
	fAngle *= -1;

	return fAngle;
}

//========================================
// 2点の向きを算出
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_Rot(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos) {
	return Find_VecRot(targetPos - pos);
}

//========================================
// 2点の向きマトリックスを算出
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
// 交点座標を算出(見下ろし視点)
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Find_Inter_LookDown(D3DXVECTOR3 posA1, D3DXVECTOR3 posA2, D3DXVECTOR3 posB1, D3DXVECTOR3 posB2) {
	D3DXVECTOR3 vB1B2 = posB2 - posB1;	// ベクトルB1⇒B2
	D3DXVECTOR3 vA1A2 = posA2 - posA1;	// ベクトルA1⇒A2
	D3DXVECTOR3 vA2B1 = posB1 - posA2;	// ベクトルA2⇒B1
	D3DXVECTOR3 vB1A1 = posA1 - posB1;	// ベクトルB1⇒A1

	// 面積S1
	float fAreaS1 = ((vB1B2.x * vB1A1.z) - (vB1B2.z * vB1A1.x)) * 0.5f;
	// 面積S2
	float fAreaS2 = ((vB1B2.x * vA2B1.z) - (vB1B2.z * vA2B1.x)) * 0.5f;

	// 面積S1の割合
	float fRate = (fAreaS1 / (fAreaS1 + fAreaS2));

	// 交点の座標を返す
	return	D3DXVECTOR3(
		posA1.x + (vA1A2.x * fRate),
		0.0f,
		posA1.z + (vA1A2.z * fRate));
}

//========================================
// 角度の差を算出
// Author:RIKU NISHIMURA
//========================================
float Find_AngleDiff(float fAngle, float fTargetAngle) {
	float fAngleDifference = 0.0f;	// 角度の差

	// 角度を制御する
	Limit_Angle(&fAngle);

	if ((fAngle >= 0.0f) && (fTargetAngle >= 0.0f))
	{// どちらの角度もプラスの時、 角度の差を設定
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}
	else if ((fAngle <= 0.0f) && (fTargetAngle <= 0.0f))
	{// どちらの角度もマイナスの時、 角度の差を設定
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}

	if ((fAngle >= 0.0f) && (fTargetAngle <= 0.0f))
	{// 角度がプラスで、目標角度がマイナスの時、
		if (fAngle - D3DX_PI <= fTargetAngle)
		{// 目標角度が下側に近い時、 角度の差を設定
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle - D3DX_PI >= fTargetAngle)
		{// 目標角度が上側に近い時、 角度の差を設定
			fAngleDifference = (D3DX_PI - fAngle) + (D3DX_PI + fTargetAngle);
		}
	}

	if ((fAngle <= 0.0f) && (fTargetAngle >= 0.0f))
	{// 角度がマイナスで、目標角度がプラスの時、
		if (fAngle + D3DX_PI >= fTargetAngle)
		{// 目標角度が下側に近い時、 角度の差を設定
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle + D3DX_PI <= fTargetAngle)
		{// 目標角度が上側に近い時、 角度の差を設定
			fAngleDifference = -(D3DX_PI + fAngle) - (D3DX_PI - fTargetAngle);
		}
	}

	return fAngleDifference;
}

//========================================
// 向きのベクトルを算出
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
// ベクトルの向きを算出
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
// カメラ面までの垂直距離を算出
// Author:RIKU NISHIMURA
//========================================
float Find_DistToCameraPlane(D3DXVECTOR3 pos) {
	D3DXVECTOR3 camToPosVec = pos - RNLib::Camera3D()->GetPosV();
	D3DXVECTOR3 camPlaneVec = RNLib::Camera3D()->GetVec();
	float fDistance = D3DXVec3Dot(&camToPosVec, &camPlaneVec);

	return fabsf(fDistance);
}

//========================================
// 外積から法線を算出
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
// 角度を範囲内制御
// Author:RIKU NISHIMURA
//========================================
void Limit_Angle(float *pAngle) {
	if (*pAngle > D3DX_PI)
	{// 円周率(正)を上回っている時、
		*pAngle = (D3DX_PI - (*pAngle - D3DX_PI)) * -1;
	}
	else if (*pAngle < -D3DX_PI)
	{// 円周率(負)を下回っている時、
		*pAngle = (D3DX_PI + (*pAngle + D3DX_PI));
	}
}

//========================================
// 向きをループ制御
// Author:RIKU NISHIMURA
//========================================
void Cycle_Control(D3DXVECTOR3* pRot) {
	FloatLoopControl(&pRot->x, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->y, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->z, D3DX_PI, -D3DX_PI);
}

//========================================
// 角度→指定された分割値に変換
// Author:RIKU NISHIMURA
//========================================
float Conv_AngleToDir(float fAngle, int nDiv) {
	float fRange = ((D3DX_PI * 2) / nDiv);	// 方向毎の角度幅

	for (int nCntDir = 0; nCntDir < nDiv + 1; nCntDir++) {
		if (fAngle >= -D3DX_PI - (fRange * 0.5f) + (fRange * nCntDir) &&
			fAngle <= -D3DX_PI + (fRange * 0.5f) + (fRange * nCntDir))
		{// カウントの方向の角度幅の内側の時、角度を設定
			fAngle = -D3DX_PI + (fRange * nCntDir);
			break;	// 繰り返し処理を抜ける
		}
	}

	return fAngle;
}

//========================================
// 位置→見下ろし基準(Z⇔Y)に変換する
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 Conv_LookDownPos(D3DXVECTOR3 pos) {
	float fYTemp = pos.y;
	pos.y = -pos.z;
	pos.z = fYTemp;

	return pos;
}

//========================================
// 向き→見下ろし基準(Z⇔Y)に変換する
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
// ランダムなベクトルを取得
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