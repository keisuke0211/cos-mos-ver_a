//========================================
// 
// セットアップ3Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| セットアップ3Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CSetUp3D::CSetUp3D() {

	m_datas = NULL;
}

//========================================
// デストラクタ
//========================================
CSetUp3D::~CSetUp3D() {

	// データの解放
	RNLib::Memory()->Release<CData>(&m_datas);
}

//========================================
// 読み込み処理
//========================================
int CSetUp3D::Load(const char* loadPath, short idx) {

	unsigned short numOld  = m_num;

	if (CRegist::Load(loadPath, idx))
	{// 読み込み成功
		// データのメモリ再確保
		RNLib::Memory()->ReAlloc<CData>(&m_datas, numOld, m_num);

		// データの破棄(番号指定の場合)
		if (idx != DATANONE)
			m_datas[idx].Release();

		// ファイルを開く
		if (RNLib::File()->OpenLoadFile(loadPath)) {
			while (RNLib::File()->SearchLoop("END")) {
				if (RNLib::File()->CheckIdentifier("boneDataSum{")) {
					BoneDataSum& boneDataSum = m_datas[idx].m_boneDataSum;
					BoneData*&   boneDatas   = boneDataSum.boneDatas;
					
					// ボーンデータ群を解放
					RNLib::Memory()->Release<BoneData>(&boneDatas);

					// ボーンデータ数読み込み
					RNLib::File()->Scan(CFile::SCAN::INT, &boneDataSum.boneDataNum);

					// ボーンデータ群のメモリ確保
					RNLib::Memory()->Alloc<BoneData>(&boneDatas, boneDataSum.boneDataNum);

					// ボーンデータ群の読み込み
					int cntBoneData = 0;
					while (RNLib::File()->SearchLoop("}")) {
						if (RNLib::File()->CheckIdentifier("boneData{")) {

							// ボーンデータ初期化
							BoneData& boneData = boneDatas[cntBoneData];
							boneData = {};

							// 部品情報の読み込みを開始
							while (RNLib::File()->SearchLoop("}")) {
								RNLib::File()->Scan(CFile::SCAN::INT, &boneData.idx, "idx");
								RNLib::File()->Scan(CFile::SCAN::MODELIDX, &boneData.modelIdx, "modelIdx");
								RNLib::File()->Scan(CFile::SCAN::INT, &boneData.parentIdx, "parentIdx");
								RNLib::File()->Scan(CFile::SCAN::POS3D, &boneData.relativePos, "relativePos");
								RNLib::File()->Scan(CFile::SCAN::POS3D, &boneData.relativeRot, "relativeRot");
							}

							// カウントを加算
							cntBoneData++;
							assert(cntBoneData <= boneDataSum.boneDataNum);
						}
					}// ボーンデータ群の読み込み終了…
					
					// ボーンデータ1つ1つの親番号をカウントに変換していく
					for (int cntBoneData = 0; cntBoneData < boneDataSum.boneDataNum; cntBoneData++) {
						BoneData& boneData = boneDatas[cntBoneData];

						// 親がDATANONEの時、折り返す
						if (boneData.parentIdx == DATANONE)
							continue;

						// 親番号と一致したボーンデータを親とし、
						// ボーンデータの親番号をカウントに変換する
						int cntBoneData2;
						for (cntBoneData2 = 0; cntBoneData2 < boneDataSum.boneDataNum; cntBoneData2++) {
							if (boneData.parentIdx == boneDatas[cntBoneData2].idx) {
								boneData.parentIdx = cntBoneData2;
								break;
							}
						}

						// 親が見つからなかった時、親番号をDATANONEにする
						if (cntBoneData2 == boneDataSum.boneDataNum)
							boneData.parentIdx = DATANONE;
					}
				}
			}

			// ファイルを閉じる
			RNLib::File()->CloseFile();
		}
	}

	return idx;
}

//========================================
// 書き込み処理
//========================================
void CSetUp3D::Save(const char* path, short idx) {

	//if (RNLib::File()->OpenSaveFile(pPath))
	//{// ファイルが開けた場合、
	//	// 部品情報の書き込み処理
	//	CParts3DSetUp::SaveData(&m_datas[nIdx].boneDataSum);
	//
	//	FILE* file = RNLib::File()->GetFile();
	//	
	//	fprintf(file, "PLATFORM: %s\n", c_aModelPlatformName[m_datas[nIdx].platform]);
	//	fprintf(file, "END");
	//
	//	RNLib::File()->CloseFile();
	//}
}

//========================================
// メモリを指定数に初期化
//========================================
void CSetUp3D::InitMemory(const unsigned short& num) {
	CRegist::InitMemory(num);

	// データのメモリ確保
	RNLib::Memory()->Alloc<CData>(&m_datas, num);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| データクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CSetUp3D::CData::CData() {

	m_boneDataSum = {};
}

//========================================
// デストラクタ
//========================================
CSetUp3D::CData::~CData() {

	// 解放処理
	Release();
}

//========================================
// 解放処理
//========================================
void CSetUp3D::CData::Release(void) {

	RNLib::Memory()->Release(&m_boneDataSum.boneDatas);
}