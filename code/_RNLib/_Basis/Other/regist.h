//========================================
// 
// 登録処理のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ regist.h ]]]
//========================================
#ifndef _REGIST_H_
#define _REGIST_H_

//****************************************
// クラス定義
//****************************************
// 登録クラス
class CRegist {
public:
	//========== [[[ 関数宣言 ]]]
	/* コンストラクタ     */CRegist();
	/* デストラクタ       */virtual ~CRegist();
	/* 終了処理           */virtual void Uninit(void);
	/* 読み込み処理       */virtual bool Load(const char *pPath, short *pIdx);
	/* メモリ初期化処理   */virtual void InitMemory(const int nNum);
	/*=====[設定取得]=====*/
	/* 読み込み済パス取得 */char* GetLoadPath(int nIdx) {
		if (nIdx < 0) { return NULL; }
		return m_ppLoadPath[nIdx];
	}

protected:
	//========== [[[ 変数宣言 ]]]
	char** m_ppLoadPath;	// 読み込み済パス
	unsigned short m_num;	// 総数
};

#endif