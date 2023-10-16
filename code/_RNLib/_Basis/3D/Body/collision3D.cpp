//========================================
// 
// �R���W����3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ colision3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CCollision3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �f�[�^�ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
void CCollision3D::LoadData(Data *pData) {
	if (pData->pParts != NULL)delete[] pData->pParts;
	*pData = {};

	// ���i���擾
	RNLib::File()->Scan(CFile::SCAN::INT,&pData->nPartsNum);

	// ���i�̃������m��
	pData->pParts = new Parts[pData->nPartsNum];

	// �ǂݍ��݃��[�v
	int nCntParts = 0;
	while (RNLib::File()->SearchLoop("}")) {
		if (false) {}
		else if (RNLib::File()->CheckIdentifier(/* ���i��� */"PARTS{")) {
			Parts* pParts = &pData->pParts[nCntParts];

			while (RNLib::File()->SearchLoop("}")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier(/* �`     */"FORM:"))   { RNLib::File()->Scan(CFile::SCAN::INT, (int*)&pParts->form); }
				else if (RNLib::File()->CheckIdentifier(/* ��     */"WIDTH:"))  { RNLib::File()->Scan(CFile::SCAN::FLOAT, &pParts->fWidth); }
				else if (RNLib::File()->CheckIdentifier(/* ����   */"HEIGHT:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &pParts->fHeight); }
				else if (RNLib::File()->CheckIdentifier(/* ���s�� */"DEPTH:"))  { RNLib::File()->Scan(CFile::SCAN::FLOAT, &pParts->fDepth); }
				else if (RNLib::File()->CheckIdentifier(/* �e     */"PARENT:")) { RNLib::File()->Scan(CFile::SCAN::INT, &pParts->nParent); }
				else if (RNLib::File()->CheckIdentifier(/* �ʒu   */"POS:"))    { RNLib::File()->Scan(CFile::SCAN::POS3D, &pParts->pos); }
				else if (RNLib::File()->CheckIdentifier(/* ����   */"ROT:"))    { RNLib::File()->Scan(CFile::SCAN::POS3D, &pParts->rot); }
			}

			// ���i�̃J�E���g�����Z
			nCntParts++;
			assert(nCntParts <= pData->nPartsNum);
		}
	}
}

//========================================
// �f�[�^�������ݏ���
// Author:RIKU NISHIMURA
//========================================
void CCollision3D::SaveData(Data* pData) {
	FILE* pFile = RNLib::File()->GetFile();
	fprintf(pFile, "COLLISIONSET{ %d\n", pData->nPartsNum);
	for (int nCntParts = 0; nCntParts < pData->nPartsNum; nCntParts++) {
		Parts& parts = pData->pParts[nCntParts];

		fprintf(pFile, "	PARTS{ %d\n", (int)parts.form);
		fprintf(pFile, "		FORM: %d\n", (int)parts.form);
		fprintf(pFile, "		WIDTH: %f\n", parts.fWidth);
		fprintf(pFile, "		HEIGHT: %f\n", parts.fHeight);
		fprintf(pFile, "		DEPTH: %f\n", parts.fDepth);
		fprintf(pFile, "		PARENT: %d\n", parts.nParent);
		fprintf(pFile, "		POS: %f %f %f\n", parts.pos.x, parts.pos.y, parts.pos.z);
		fprintf(pFile, "		ROT: %f %f %f\n", parts.rot.x, parts.rot.y, parts.rot.z);
		fprintf(pFile, "	}\n");
	}
	fprintf(pFile, "}\n");
}