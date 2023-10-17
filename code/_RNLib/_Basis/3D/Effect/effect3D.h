//========================================
// 
// エフェクト3Dのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ effect3D.h ]]]
//========================================
#ifndef _EFFECT3D_H_
#define _EFFECT3D_H_

#include "../../Mechanical/object.h"

//****************************************
// クラス定義
//****************************************
// エフェクト3Dクラス
class CEff3D : public CObject {
public:
	//========== [[[ 定数定義 ]]]
	static const float GRAVITY_FORCE;

	//========== [[[ 列挙型定義 ]]]
	enum class POWER {
		NONE,
		LOW,
		MID,
		HIGH,
		MAX,
	};

	// 種類
	enum class TYPE {
		NONE,
		POLYGON,
		FRAGMENT,
		MAX,
	};
	enum class POLYGON_TYPE {
		NONE,
		// UI
		CALLOUT_TAKEAIM,
		CALLOUT_SILENCE,
		// 状態異常
		SLEEP,
		// 三次元空間
		RING,
		LIGHT_M,
		SMOKE_M,
		SMOKE_L,
		LIQUID_S,
		LIQUID_M,
		FRAME_M,
		LAVABALL_XS,
		SPARK_ORANGE,
		EXPLOSION_DESTROY_M,
		MAX,
	};
	enum class FRAGMENT_TYPE {
		NONE,
		S,
		M,
		MAX,
	};

	//========== [[[ 関数宣言 ]]]
	CEff3D();
	virtual ~CEff3D();
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	// 設定取得
	void SetPos (D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot (D3DXVECTOR3 rot) { m_rot = rot; }
	void SetLife(int nLife)       { m_nLife = m_nLifeMax = nLife; }

protected:
	//========== [[[ 変数宣言 ]]]
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int         m_nLife;
	int         m_nLifeMax;
};

#endif