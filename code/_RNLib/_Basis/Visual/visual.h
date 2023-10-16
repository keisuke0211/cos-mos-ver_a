//========================================
// 
// rWAÌwb_t@C
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ visual.h ]]]
//========================================
#ifndef _VISUAL_H_
#define _VISUAL_H_

//****************************************
// NXè`
//****************************************
// rWANX
class CVisual {
public:
	//========== [[[ ñ^è` ]]]
	enum class TEXTURE {
		// UIn
		TRANSITION_HOLE,
		// Þ¿n
		LAVA,
		RUGGET,	// ScSc
		MAX,
	};
	enum class MODEL {
		CLOD_S,		// ò(¬)
		CLOD_M,		// ò()
		NEEDLE_M,	// j()
		MAX,
	};
	enum class MOTION3D {
		// î{
		STAND_NORMAL,

		// ÁêøÊ
		SPC_EFF_SLEEP,	// °

		// \õ®ì
		ANTICIPATION_ARMCROSS,		// rðð·
		ANTICIPATION_RIGHTHOOK,		// E\¦

		// U
		BITE_MID,			// Ýt«	()
		BREATH_FORWARD,		// f­     (O)
		DRILL_MID,			// @í		()
		PUNCH_RIGHT_MID,	// £Å		(E¥)
		PUNCH_GROUND_RIGHT,	// £Å		(nÊ¥E)
		TACKLE_MID,			// ^bN	()
		MAX,
	};

	//========== [[[ Öé¾ ]]]
	CVisual();
	~CVisual();
	void Load(void);
	int GetTextureIdx (TEXTURE  tex)    { return m_aTextureIdx[(int)tex]; }
	int GetModelIdx   (MODEL    model)  { return m_aModelIdx[(int)model]; }
	int GetMotion3DIdx(MOTION3D motion) { return m_aMotion3DIdx[(int)motion]; }

private:
	//========== [[[ Ïé¾ ]]]
	int m_aTextureIdx[(int)TEXTURE::MAX];
	int m_aModelIdx[(int)MODEL::MAX];
	int m_aMotion3DIdx[(int)MOTION3D::MAX];
};

#endif