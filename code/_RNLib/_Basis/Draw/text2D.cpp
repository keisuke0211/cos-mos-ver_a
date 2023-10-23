//========================================
// 
// テキスト2Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"
#include <locale.h>

//================================================================================
//----------|---------------------------------------------------------------------
//==========| テキスト2Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 設置処理
//========================================
CText2D::CRegistInfo* CText2D::Put(const D3DXVECTOR2& pos, const float& angle, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen) {

	// 登録受付中でない時、終了
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng()->PutText2D(pos, angle, isOnScreen)
		->SetString(string)
		->SetAlignment(alignment)
		->SetFontIdx(fontIdx);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 登録情報クラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CText2D::CRegistInfo::CRegistInfo() {

	m_string = NULL;
	m_alignment = CText::ALIGNMENT::CENTER;
	m_fontIdx = DATANONE;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_isFactScale = false;
	m_pos = INITD3DXVECTOR2;
	m_angle = 0.0f;
	m_col = INITCOLOR;
	m_isZtest = true;
	m_isLighting = true;
	m_isBillboard = false;
	m_priority = 0;
}

//========================================
// デストラクタ
//========================================
CText2D::CRegistInfo::~CRegistInfo() {

	// 文字列のメモリ解放
	RNLib::Memory()->Release(&m_string);
}

//========================================
// 設置処理(ポリゴン2D)
//========================================
void CText2D::CRegistInfo::PutPolygon2D(const bool& isOnScreen) {

	// フォントデータを取得
	CText::FontData fontData = RNLib::Text()->GetFont(m_fontIdx);

	//----------------------------------------
	// 幅/高さ/間隔を算出
	//----------------------------------------
	float charWidth = 0.0f;
	float charHeight = 0.0f;
	float charSpace = 0.0f;
	if (m_isFactScale) {
		charWidth = m_scaleX;
		charHeight = m_scaleY;
	}
	else {
		charWidth = (RNLib::Texture()->GetWidth(fontData.nTexIdx) * PIXEL2D_SIZE) / fontData.nPtnWidth;
		charHeight = (RNLib::Texture()->GetHeight(fontData.nTexIdx) * PIXEL2D_SIZE) / fontData.nPtnHeight;
	}
	charSpace = charWidth * m_scaleX * fontData.fSpaceRate;

	//----------------------------------------
	// ロケールを設定してマルチバイト文字に対応
	//----------------------------------------
	setlocale(LC_ALL, "");

	//----------------------------------------
	// char型の文字列をwchar_t型の文字列に変換
	//----------------------------------------
	size_t   length(strlen(m_string));
	wchar_t* wstr((wchar_t*)malloc((length + 1) * sizeof(wchar_t)));
	mbstowcs(wstr, m_string, length + 1);

	//----------------------------------------
	// 一文字ずつ設置していく
	//----------------------------------------
	int strLen = (int)wcslen(wstr);
	for (int cntChar = 0; cntChar < strLen; cntChar++) {

		// カウントの文字が空白の時、折り返す
		if (m_string[cntChar] == ' ')
			continue;

		// [[[ 表示形式に応じた設定位置の設定 ]]]
		D3DXVECTOR2 setPos = INITD3DXVECTOR2;
		switch (m_alignment) {
		case CText::ALIGNMENT::CENTER: {
			setPos.x += ((strLen * -0.5f) + cntChar + 0.5f) * charSpace;
		}break;
		case CText::ALIGNMENT::LEFT: {
			setPos.x += cntChar * charSpace;
		}break;
		case CText::ALIGNMENT::RIGHT: {
			setPos.x += (-strLen + cntChar + 1) * charSpace;
		}break;
		}

		// [[[ 結果マトリックスの算出 ]]]
		D3DXMATRIX resultMtx; {

			// 基準マトリックスとテキストマトリックスを求める
			D3DXMATRIX baseMtx = INITD3DXMATRIX;
			D3DXMATRIX textMtx = INITD3DXMATRIX;

			{// 通常の時、
				D3DXVECTOR3 charPos = D3DXVECTOR3(setPos.x, setPos.y, 0.0f);
				baseMtx = ConvPosRotToMatrix(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, m_angle));
				textMtx = ConvPosRotToMatrix(charPos, INITD3DXVECTOR3);
			}

			// 基準マトリックスとテキストマトリックスを掛け合わせる
			resultMtx = MultiplyMatrix(baseMtx, textMtx);
		}

		// ポリゴン2Dを設置
		RNLib::DrawMng()->PutPolygon2D(ConvMatrixToPos(resultMtx), ConvMatrixToRot(resultMtx).z, isOnScreen)
			->SetSize(charWidth, charHeight)
			->SetCol(m_col)
			->SetTex(fontData.nTexIdx, (int)wstr[cntChar] - (int)fontData.nStartCode, fontData.nPtnWidth, fontData.nPtnHeight)
			->SetZTest(m_isZtest);
	}

	// wchar_t型文字列の解放
	free(wstr);
}

//========================================
// 位置を設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetPos(const D3DXVECTOR2& pos) {

	if (this == NULL)
		return NULL;

	m_pos = pos;

	return this;
}

//========================================
// 角度を設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetAngle(const float& angle) {

	if (this == NULL)
		return NULL;

	m_angle = angle;

	return this;
}

//========================================
// 文字列を設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetString(const char* string) {

	if (this == NULL)
		return NULL;

	StrCpyDynamicMemory(&m_string, string);

	return this;
}

//========================================
// 配置を設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetAlignment(const CText::ALIGNMENT& alignment) {

	if (this == NULL)
		return NULL;

	m_alignment = alignment;

	return this;
}

//========================================
// フォント番号を設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetFontIdx(const short& fontIdx) {

	if (this == NULL)
		return NULL;

	m_fontIdx = fontIdx;

	return this;
}

//========================================
// 色を設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetCol(const Color& col) {

	if (this == NULL)
		return NULL;

	m_col = col;

	return this;
}

//========================================
// 大きさを設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetSize(const float& width, const float& height) {

	if (this == NULL)
		return NULL;

	m_scaleX = width;
	m_scaleY = height;
	m_isFactScale = true;

	return this;
}

//========================================
// 大きさを設定(テクスチャ基準で拡大)
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetSize_TexBaseScale(const float& scaleX, const float& scaleY) {

	if (this == NULL)
		return NULL;

	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_isFactScale = false;

	return this;
}

//========================================
// 優先度設定
//========================================
CText2D::CRegistInfo* CText2D::CRegistInfo::SetPriority(const short& priority) {

	if (this == NULL)
		return NULL;

	m_priority = priority;

	return this;
}