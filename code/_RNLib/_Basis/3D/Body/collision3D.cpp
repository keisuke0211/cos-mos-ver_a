//========================================
// 
// コリジョン3Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ colision3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CCollision3Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// データ読み込み処理
// Author:RIKU NISHIMURA
//========================================
void CCollision3D::LoadData(Data *pData) {
	if (pData->pParts != NULL)delete[] pData->pParts;
	*pData = {};

	// 部品数取得
	RNLib::File()->Scan(CFile::SCAN::INT,&pData->nPartsNum);

	// 部品のメモリ確保
	pData->pParts = new Parts[pData->nPartsNum];

	// 読み込みループ
	int nCntParts = 0;
	while (RNLib::File()->SearchLoop("}")) {
		if (false) {}
		else if (RNLib::File()->CheckIdentifier(/* 部品情報 */"PARTS{")) {
			Parts* pParts = &pData->pParts[nCntParts];

			while (RNLib::File()->SearchLoop("}")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier(/* 形     */"FORM:"))   { RNLib::File()->Scan(CFile::SCAN::INT, (int*)&pParts->form); }
				else if (RNLib::File()->CheckIdentifier(/* 幅     */"WIDTH:"))  { RNLib::File()->Scan(CFile::SCAN::FLOAT, &pParts->fWidth); }
				else if (RNLib::File()->CheckIdentifier(/* 高さ   */"HEIGHT:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &pParts->fHeight); }
				else if (RNLib::File()->CheckIdentifier(/* 奥行き */"DEPTH:"))  { RNLib::File()->Scan(CFile::SCAN::FLOAT, &pParts->fDepth); }
				else if (RNLib::File()->CheckIdentifier(/* 親     */"PARENT:")) { RNLib::File()->Scan(CFile::SCAN::INT, &pParts->nParent); }
				else if (RNLib::File()->CheckIdentifier(/* 位置   */"POS:"))    { RNLib::File()->Scan(CFile::SCAN::POS3D, &pParts->pos); }
				else if (RNLib::File()->CheckIdentifier(/* 向き   */"ROT:"))    { RNLib::File()->Scan(CFile::SCAN::POS3D, &pParts->rot); }
			}

			// 部品のカウントを加算
			nCntParts++;
			assert(nCntParts <= pData->nPartsNum);
		}
	}
}

//========================================
// データ書き込み処理
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