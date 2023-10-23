//========================================
// 
// テキスト2Dのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "text.h"

//****************************************
// クラス定義
//****************************************
// テキスト2Dクラス
class CText2D {
public:
	//========== [[[ クラス定義 ]]]
	// 登録情報
	class CRegistInfo {
	public:
		// [[[ 関数宣言 ]]]
		CRegistInfo();
		~CRegistInfo();
		void PutPolygon2D(const bool& isOnScreen);
		CRegistInfo* SetPos(const D3DXVECTOR2& pos);
		CRegistInfo* SetAngle(const float& angle);
		CRegistInfo* SetString(const char* string);
		CRegistInfo* SetAlignment(const CText::ALIGNMENT& alignment);
		CRegistInfo* SetFontIdx(const short& fontIdx);
		CRegistInfo* SetCol(const Color& col);
		CRegistInfo* SetSize(const float& width, const float& height);
		CRegistInfo* SetSize_TexBaseScale(const float& scaleX, const float& scaleY);
		CRegistInfo* ExtendFixedTexX(const float& rateX);
		CRegistInfo* ExtendFixedTexY(const float& rateY);
		CRegistInfo* SetPriority(const short& priority);

	private:
		// [[[ 変数宣言 ]]]
		char*            m_string;
		CText::ALIGNMENT m_alignment;
		short            m_fontIdx;
		float            m_scaleX;
		float            m_scaleY;
		bool             m_isFactScale;
		D3DXVECTOR2      m_pos;
		float            m_angle;
		Color            m_col;
		bool             m_isZtest;
		bool             m_isLighting;
		bool             m_isBillboard;
		short            m_priority;
	};

	//========== [[[ 関数宣言 ]]]
	CRegistInfo* Put(const D3DXVECTOR2& pos, const float& angle, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen = false);
};