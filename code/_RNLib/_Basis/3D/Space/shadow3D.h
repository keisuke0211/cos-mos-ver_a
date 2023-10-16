//========================================
// 
// 影3Dのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ shadow3D.h ]]]
//========================================
#ifndef _SHADOW3D_H_
#define _SHADOW3D_H_

//****************************************
// クラス定義
//****************************************
// 影3Dクラス
class CShadow3D {
public:
	//========== [[[ 関数宣言 ]]]
	/* 初期化処理 */void Init(void);
	/* 設定処理   */void Set(D3DXVECTOR3 pos);

private:
	//========== [[[ 変数宣言 ]]]
	int m_nTexIdx;	// テクスチャ番号
};

#endif