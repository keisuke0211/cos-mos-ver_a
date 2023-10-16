//========================================
// 
// テキスト2Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ text2D.cpp ]]]
//========================================
#include "../../../RNlib.h"
#include <wchar.h>
#include <locale.h>

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CText2Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 設定処理
// Author:RIKU NISHIMURA
//========================================
void CText2D::Set(
		const char* pString,
		const float fScaleX,
		const float fScaleY,
		const D3DXVECTOR3 pos,
	    const D3DXVECTOR3 rot,
		const CText::ALIGNMENT disp,
		const int nFont,
		const Color col) {
	if (!RNLib::Text()->CheckFontExists(nFont)) 
	{// フォントが存在しない時、処理を終了する
		return;
	}

	// ロケールを設定してマルチバイト文字に対応
	setlocale(LC_ALL, "");

	// char型の文字列をwchar_t型の文字列に変換
	size_t length = strlen(pString);
	wchar_t* wstr = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
	mbstowcs(wstr, pString, length + 1);

	CText::FontData font   = RNLib::Text()->GetFont(nFont);
	float       fWidth = RNLib::Texture()->GetWidth2D(font.nTexIdx) / font.nPtnWidth;
	float       fSpace = fWidth * fScaleX * font.fSpaceRate;

	int nStrLen = (int)wcslen(wstr);
	for (int nCntDigit = 0; nCntDigit < nStrLen; nCntDigit++) {
		if (pString[nCntDigit] == ' ') {
			continue;	// カウントの文字が空白の時、折り返す
		}
		
		D3DXVECTOR3 setPos = INITD3DXVECTOR3;	// 設定位置
		
		// 表示形式に応じた設定位置の設定
		switch (disp) {
		case CText::ALIGNMENT::CENTER:
			setPos.x += -((fSpace * nStrLen) * 0.5f) + (((float)nCntDigit + 0.5f) * fSpace);
			break;
		case CText::ALIGNMENT::LEFT:
			setPos.x += nCntDigit * fSpace;
			break;
		case CText::ALIGNMENT::RIGHT:
			setPos.x -= (fSpace * nStrLen) - nCntDigit * fSpace;
			break;
		}

		// 位置と向きをマトリックス変換
		D3DXMATRIX baseMtx = ConvPosRotToMatrix(pos, rot);
		D3DXMATRIX txtMtx  = ConvPosRotToMatrix(setPos, INITD3DXVECTOR3);

		// 基準マトリックスとテキストマトリックスを掛け合わせ、結果マトリックスを求める
		D3DXMATRIX resultMtx = MultiplyMatrix(baseMtx, txtMtx);

		// ポリゴン2Dを設定
		RNLib::Polygon2D()->Set(
			fScaleX,
			fScaleY,
			ConvMatrixToPos(resultMtx),
			ConvMatrixToRot(resultMtx),
			col,
			font.nTexIdx,
			(int)wstr[nCntDigit] - font.nStartCode,
			font.nPtnWidth,
			font.nPtnHeight);
	}

	// メモリの解放
	free(wstr);
}