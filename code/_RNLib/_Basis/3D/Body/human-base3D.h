//========================================
// 
// ヒューマン3Dベースのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ human-base3D.h ]]]
//========================================
#pragma once

#include "../../Mechanical/regist.h"
#include "../../../RNmain.h"

//****************************************
// クラス定義
//****************************************
// ヒューマン3Dベースクラス
class CHuman3DBase :public CRegist{
public:
	//========== [[[ 構造体定義 ]]]
	// データ構造体
	typedef struct Data_ {
		//----- 基本情報 -----
		int         nSetUpIdx  = 0;					// モデルセットアップ番号
		//----- 目 -----
		D3DXVECTOR3 eyePos     = INITD3DXVECTOR3;	// 目の位置
		D3DXVECTOR3 eyeRot     = INITD3DXVECTOR3;	// 目の向き
		int         nEyeParent = -1;				// 目の親部品番号
		float       fEyeSpace  = 0.0f;				// 目の間隔
		float       fEyeRotDia = 0.0f;				// 目の回転倍率
	}Data;

	//========== [[[ 関数宣言 ]]]
	/* コンストラクタ   */CHuman3DBase();
	/* デストラクタ     */~CHuman3DBase();
	/* 終了処理         */void Uninit(void);
	/* 読み込み処理     */int  Load(const char* pLoadPath, short nIdx = DATANONE);
	/* 書き込み処理     */void Save(char* pPath, int nIdx);
	/* データ取得       */Data* GetData(const int nIdx) { return &m_pData[nIdx]; }
	/* メモリ初期化処理 */void InitMemory(const int nNum);

private:
	//========== [[[ 変数宣言 ]]]
	Data* m_pData;	// データ
};