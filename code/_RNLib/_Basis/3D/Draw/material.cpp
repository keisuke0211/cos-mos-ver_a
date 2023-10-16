//========================================
// 
// �}�e���A���֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ material.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// SetMaterial�֐� - �}�e���A���̐ݒ� -
// Author:RIKU NISHIMURA
//========================================
void SetMaterial(LPDIRECT3DDEVICE9 pDevice, D3DMATERIAL9 *pMat, Color col, bool bLighting) {
	// �}�e���A���̍ގ��p�����[�^��ۑ�
	D3DXCOLOR DiffuseTemp  = pMat->Diffuse;
	D3DXCOLOR EmissiveTemp = pMat->Emissive;

	// �}�e���A���̍ގ��p�����[�^��ݒ�
	pMat->Diffuse.r  = DiffuseTemp.r * ((float)col.r / 255);
	pMat->Diffuse.g  = DiffuseTemp.g * ((float)col.g / 255);
	pMat->Diffuse.b  = DiffuseTemp.b * ((float)col.b / 255);
	pMat->Diffuse.a  = DiffuseTemp.a * ((float)col.a / 255);
	pMat->Emissive.r = EmissiveTemp.r * ((float)col.r / 255);
	pMat->Emissive.g = EmissiveTemp.g * ((float)col.g / 255);
	pMat->Emissive.b = EmissiveTemp.b * ((float)col.b / 255);
	pMat->Emissive.a = EmissiveTemp.a * ((float)col.a / 255);

	// �}�e���A���̐ݒ�
	pDevice->SetMaterial(pMat);

	// �}�e���A���̍ގ��p�����[�^�����ɖ߂�
	pMat->Diffuse  = DiffuseTemp;
	pMat->Emissive = EmissiveTemp;
}

//void SetMaterial(LPDIRECT3DDEVICE9 pDevice, D3DMATERIAL9* pMat, Color col, bool bLighting) {
//	// �}�e���A���̍ގ��p�����[�^��ۑ�
//	D3DXCOLOR DiffuseTemp = pMat->Diffuse;
//	D3DXCOLOR EmissiveTemp = pMat->Emissive;
//
//	// �}�e���A���̍ގ��p�����[�^��ݒ�
//	pMat->Diffuse.r = DiffuseTemp.r * ((float)col.r / (float)255);
//	pMat->Diffuse.g = DiffuseTemp.g * ((float)col.g / (float)255);
//	pMat->Diffuse.b = DiffuseTemp.b * ((float)col.b / (float)255);
//	pMat->Diffuse.a = DiffuseTemp.a * ((float)col.a / (float)255);
//
//	if (bLighting) {
//		// ���C�e�B���O�̗L���ɂ���
//		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//	}
//	else {
//		pMat->Emissive.r = DiffuseTemp.r * ((float)col.r / (float)255);
//		pMat->Emissive.g = DiffuseTemp.g * ((float)col.g / (float)255);
//		pMat->Emissive.b = DiffuseTemp.b * ((float)col.b / (float)255);
//		pMat->Emissive.a = DiffuseTemp.a * ((float)col.a / (float)255);
//
//		if (pMat->Emissive.r + pMat->Emissive.g + pMat->Emissive.b > 0.0f)
//		{// ���S�������A
//			// ���C�e�B���O�̖����ɂ���
//			pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//		}
//		else {
//			// ���C�e�B���O�̗L���ɂ���
//			pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//		}
//	}
//
//	// �}�e���A���̐ݒ�
//	pDevice->SetMaterial(pMat);
//
//	// �}�e���A���̍ގ��p�����[�^�����ɖ߂�
//	pMat->Diffuse = DiffuseTemp;
//	pMat->Emissive = EmissiveTemp;
//}