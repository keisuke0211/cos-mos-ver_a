//========================================
// 
// セットアップ3Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "doll3D.h"
#include "../../Mechanical/regist.h"

//****************************************
// クラス定義
//****************************************
// セットアップ3Dクラス
class CSetUp3D : public CRegist {
public:
	//========== [[[ 構造体定義 ]]]
	//----- ボーン -----
	// ボーンデータ構造体
	struct BoneData {
		int         idx = 0;
		int         modelIdx = DATANONE;
		int         parentIdx = DATANONE;
		D3DXVECTOR3 relativePos = INITD3DXVECTOR3;
		D3DXVECTOR3 relativeRot = INITD3DXVECTOR3;
		D3DXVECTOR3 rotRelativePos = INITD3DXVECTOR3;
	};

	// ボーンデータ総括構造体
	struct BoneDataSum {
		BoneData* boneDatas = NULL;
		int       boneDataNum = 0;
	};
	//----------

	// データ構造体
	class CData {
	public:
		// [[[ 関数宣言 ]]]
		CData();
		~CData();
		void Release(void);

		// [[[ 変数宣言 ]]]
		BoneDataSum m_boneDataSum;	// 部品情報
	};

	//========== [[[ 関数宣言 ]]]
	CSetUp3D();
	~CSetUp3D();
	int    Load(const char* loadPath, short idx = DATANONE);
	void   Save(const char* path, short idx);
	CData& GetData(const short& idx) { return m_datas[idx]; }
	void   InitMemory(const unsigned short& num);

private:
	//========== [[[ 変数宣言 ]]]
	CData* m_datas;
};