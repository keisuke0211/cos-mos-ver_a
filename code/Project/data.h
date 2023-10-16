//========================================
// 
// データのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ data.h ]]]
//========================================
#ifndef _DATA_H_
#define _DATA_H_

//****************************************
// クラス定義
//****************************************
// データクラス
class CData {
public:
	//========== [[[ 関数宣言 ]]]
	CData() {
		m_highCoin = 0;
	}
	~CData() {}
	bool SetHighCoin(int coin) {
		if (m_highCoin < coin) {
			m_highCoin = coin;
			return true;
		}
		return false;
	}
	int  GetHighCoin(void) { return m_highCoin; }

private:
	//========== [[[ 変数宣言 ]]]
	int m_highCoin;
};

#endif