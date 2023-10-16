//========================================
// 
// マトリックス関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ matrix.cpp ]]]
//========================================
// RNlib
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// ConvPosRotToMatrix関数 - 位置と向きをマトリックスに変換して返す -
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX ConvPosRotToMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtx;	// 本体のマトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtx);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	return mtx;
}

//========================================
// MultiplyMatrix関数 - マトリックスを掛け合わせる -
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX MultiplyMatrix(D3DXMATRIX mtxParent, D3DXMATRIX mtxChild) {
	// 算出した部品のワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(
		&mtxChild,
		&mtxChild,
		&mtxParent);

	return mtxChild;
}

//========================================
// ConvMatrixToPos関数 - マトリックスの位置成分を分解して返す -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 ConvMatrixToPos(D3DXMATRIX mtx) {
	return D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
}

//========================================
// ConvMatrixToRot関数 - マトリックスの向き成分を分解して返す -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 ConvMatrixToRot(D3DXMATRIX mtx) {
	D3DXVECTOR3 rot;

	// 行列の3列目を取得して、D3DXVECTOR3に変換
	//rot.x = atan2(mtx._32, mtx._33);
	//rot.y = atan2(-mtx._31, sqrt(mtx._32 * mtx._32 + mtx._33 * mtx._33));
	//rot.z = atan2(mtx._21, mtx._11);

	rot.x = atan2f(mtx._32, mtx._33);
	rot.y = atan2f(-mtx._31, sqrtf(mtx._32 * mtx._32 + mtx._33 * mtx._33));
	rot.z = atan2f(mtx._21, mtx._11);

	//// 行列をクォータニオンに変換する
	//D3DXQUATERNION quaternion;
	//D3DXQuaternionRotationMatrix(&quaternion, &mtx);

	//// クォータニオンから回転成分を抜き出す
	//D3DXVECTOR3 rotation;
	//D3DXQuaternionToAxisAngle(&quaternion, &rotation, nullptr);

	return rot;
}

//========================================
// SetMatrixRot関数 - マトリックスに向きを代入 -
// Author:RIKU NISHIMURA
//========================================
void SetMatrixRot(D3DXMATRIX *pMtx, D3DXVECTOR3 rot) {
	// 初期化する向きの値
	float pitch = rot.x;
	float yaw = rot.y;
	float roll = rot.z;

	D3DXMATRIX matrix;
	D3DXMatrixIdentity(pMtx); // 行列を単位行列で初期化

	// 向きの要素を初期化
	pMtx->_11 = cos(yaw) * cos(roll);
	pMtx->_12 = cos(yaw) * sin(roll);
	pMtx->_13 = sin(yaw);
	pMtx->_21 = sin(pitch) * sin(yaw) * cos(roll) - cos(pitch) * sin(roll);
	pMtx->_22 = sin(pitch) * sin(yaw) * sin(roll) + cos(pitch) * cos(roll);
	pMtx->_23 = -sin(pitch) * cos(yaw);
	pMtx->_31 = -cos(pitch) * sin(yaw) * cos(roll) - sin(pitch) * sin(roll);
	pMtx->_32 = -cos(pitch) * sin(yaw) * sin(roll) + sin(pitch) * cos(roll);
	pMtx->_33 = cos(pitch) * cos(yaw);
}

//========================================
// マトリックスに拡大倍率を設定
// Author:RIKU NISHIMURA
//========================================
void SetMatrixScale(D3DXMATRIX* pMtx, float fScale) {
	D3DXMATRIX mtxScale = INITD3DXMATRIX;
	D3DXMatrixScaling(&mtxScale, fScale, fScale, fScale);

	*pMtx = MultiplyMatrix(*pMtx, mtxScale);
}

//========================================
// マトリックスの拡大倍率Xを調べる
//========================================
float FindMatrixScaleX(const D3DXMATRIX& mtx) {

	// マトリックスからX軸のベクトルを取得
	D3DXVECTOR3 XVector(mtx._11, mtx._12, mtx._13);

	// X軸のベクトルの長さを計算
	return D3DXVec3Length(&XVector);
}

//========================================
// マトリックスの拡大倍率Yを調べる
//========================================
float FindMatrixScaleY(const D3DXMATRIX& mtx) {

	// マトリックスからY軸のベクトルを取得
	D3DXVECTOR3 YVector(mtx._21, mtx._22, mtx._23);

	// Y軸のベクトルの長さを計算
	return D3DXVec3Length(&YVector);
}

//========================================
// マトリックスの拡大倍率Zを調べる
//========================================
float FindMatrixScaleZ(const D3DXMATRIX& mtx) {

	// マトリックスからZ軸のベクトルを取得
	D3DXVECTOR3 ZVector(mtx._31, mtx._32, mtx._33);

	// Z軸のベクトルの長さを計算
	return D3DXVec3Length(&ZVector);
}