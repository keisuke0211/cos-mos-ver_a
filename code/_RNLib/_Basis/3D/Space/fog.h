//========================================
// 
// フォグのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ fog.h ]]]
//========================================
#ifndef _FOG_H_
#define _FOG_H_

//****************************************
// クラス定義
//****************************************
class CFog {
public:
	CFog();
	~CFog();
	void   Init(void);
	void   SetCol      (Color col);
	Color  GetCol      (void) { return m_col; };
	void   SetDistStart(float fDistStart);
	float& GetDistStart(void) { return m_fDistStart; }
	void   SetDistEnd  (float fDistEnd);
	float& GetDistEnd  (void) { return m_fDistEnd; }
	void   Enable      (bool bEnable);
	void   SetUse      (bool bUse) { m_bUse = bUse; }
	bool   GetUse      (void) { return m_bUse; }

private:
	Color m_col;
	float m_fDistStart;
	float m_fDistEnd;
	bool  m_bUse;
};

#endif