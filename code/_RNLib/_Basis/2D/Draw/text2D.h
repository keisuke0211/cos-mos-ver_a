//========================================
// 
// テキスト2Dのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ text2D.h ]]]
//========================================
#ifndef _TEXT2D_H_
#define _TEXT2D_H_

#include "../../Draw/text.h"

//****************************************
// クラス定義
//****************************************
// テキスト2Dクラス
class CText2D {
public:
	// 設定処理
	void Set(
		const char*       pString,
		const float       fScaleX,
		const float       fScaleY,
		const D3DXVECTOR3 pos   = INITD3DXVECTOR3,
	    const D3DXVECTOR3 rot   = INITD3DXVECTOR3,
		const CText::ALIGNMENT disp  = CText::ALIGNMENT::CENTER,
		const int         nFont = 0,
		const Color       col   = INITCOLOR);
};

#endif