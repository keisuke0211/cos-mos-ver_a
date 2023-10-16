//========================================
// 
// ビジュアルのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ visual.h ]]]
//========================================
#ifndef _VISUAL_H_
#define _VISUAL_H_

//****************************************
// クラス定義
//****************************************
// ビジュアルクラス
class CVisual {
public:
	//========== [[[ 列挙型定義 ]]]
	enum class TEXTURE {
		// UI系
		TRANSITION_HOLE,
		// 材質系
		LAVA,
		RUGGET,	// ゴツゴツ
		MAX,
	};
	enum class MODEL {
		CLOD_S,		// 塊(小)
		CLOD_M,		// 塊(中)
		NEEDLE_M,	// 針(中)
		MAX,
	};
	enum class MOTION3D {
		// 基本
		STAND_NORMAL,

		// 特殊効果
		SPC_EFF_SLEEP,	// 睡眠

		// 予備動作
		ANTICIPATION_ARMCROSS,		// 腕を交差
		ANTICIPATION_RIGHTHOOK,		// 右拳構え

		// 攻撃
		BITE_MID,			// 噛み付き	(中)
		BREATH_FORWARD,		// 吐く     (前)
		DRILL_MID,			// 掘削		(中)
		PUNCH_RIGHT_MID,	// 殴打		(右･中)
		PUNCH_GROUND_RIGHT,	// 殴打		(地面･右)
		TACKLE_MID,			// タックル	(中)
		MAX,
	};

	//========== [[[ 関数宣言 ]]]
	CVisual();
	~CVisual();
	void Load(void);
	int GetTextureIdx (TEXTURE  tex)    { return m_aTextureIdx[(int)tex]; }
	int GetModelIdx   (MODEL    model)  { return m_aModelIdx[(int)model]; }
	int GetMotion3DIdx(MOTION3D motion) { return m_aMotion3DIdx[(int)motion]; }

private:
	//========== [[[ 変数宣言 ]]]
	int m_aTextureIdx[(int)TEXTURE::MAX];
	int m_aModelIdx[(int)MODEL::MAX];
	int m_aMotion3DIdx[(int)MOTION3D::MAX];
};

#endif