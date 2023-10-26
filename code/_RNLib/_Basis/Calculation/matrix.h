//========================================
// 
// �}�g���b�N�X�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ matrix.h ]]]
//========================================
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "../../RNmain.h"

//****************************************
// �v���g�^�C�v�錾
//****************************************
// �ʒu�ƌ������}�g���b�N�X�ɕϊ����ĕԂ�
D3DXMATRIX ConvPosRotToMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// �}�g���b�N�X���|�����킹��
D3DXMATRIX MultiplyMatrix(D3DXMATRIX mtxParent, D3DXMATRIX mtxChild);
// �}�g���b�N�X�̈ʒu�����𕪉����ĕԂ�
D3DXVECTOR3 ConvMatrixToPos(D3DXMATRIX mtx);
// �}�g���b�N�X�̌��������𕪉����ĕԂ�
D3DXVECTOR3 ConvMatrixToRot(D3DXMATRIX mtx);
// �}�g���b�N�X�Ɍ�����ݒ�
void SetMatrixRot(D3DXMATRIX *pMtx, D3DXVECTOR3 rot);
// �}�g���b�N�X�Ɋg��{����ݒ�
void SetMatrixScale(D3DXMATRIX* pMtx, float fScale);

float FindMatrixScaleX(const D3DXMATRIX& mtx);
float FindMatrixScaleY(const D3DXMATRIX& mtx);
float FindMatrixScaleZ(const D3DXMATRIX& mtx);

#endif