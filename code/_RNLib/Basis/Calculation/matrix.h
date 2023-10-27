//========================================
// 
// �}�g���b�N�X�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
class CMatrix {
public:
	//========== [[[ �֐��錾 ]]]
	static Matrix  ConvPosRotToMtx     (const Pos3D& pos, const Rot3D& rot);
	static Matrix  ConvPosRotScaleToMtx(const Pos3D& pos, const Rot3D& rot, const Scale3D& scale);
	static Pos3D   ConvMtxToPos        (const Matrix& mtx);
	static Rot3D   ConvMtxToRot        (const Matrix& mtx);
	static Scale3D ConvMtxToScale      (const D3DXMATRIX& mtx);
	static Matrix  MultiplyMtx         (const Matrix& mtxA, const Matrix& mtxB);
};