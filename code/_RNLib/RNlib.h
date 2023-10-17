//========================================
// 
// RNlibのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ RNlib.h ]]]
//========================================
#ifndef _RNLIB_H_
#define _RNLIB_H_

#include "RNmain.h"
//========== [[[ 3D ]]]
#include "_Basis/3D/Body/collision3D.h"
#include "_Basis/3D/Body/human-base3D.h"
#include "_Basis/3D/Body/setup3D.h"
#include "_Basis/3D/Body/motion3D.h"
#include "_Basis/3D/Body/doll3D.h"
#include "_Basis/3D/Camera/camera.h"
#include "_Basis/3D/Draw/line3D.h"
#include "_Basis/3D/Effect/eff3D-fragment.h"
#include "_Basis/3D/Effect/eff3D-polygon.h"
#include "_Basis/3D/Effect/effect3D.h"
#include "_Basis/3D/Effect/effect3D_manager.h"
#include "_Basis/3D/Space/fog.h"
#include "_Basis/3D/Space/light3D.h"
#include "_Basis/3D/Space/shadow3D.h"
//========== [[[ Calculation ]]]
#include "_Basis/Calculation/easing.h"
#include "_Basis/Calculation/geometry.h"
#include "_Basis/Calculation/matrix.h"
#include "_Basis/Calculation/number.h"
//========== [[[ Draw ]]]
#include "_Basis/Draw/draw-manager.h"
#include "_Basis/Draw/draw-state.h"
#include "_Basis/Draw/model.h"
#include "_Basis/Draw/polygon2D.h"
#include "_Basis/Draw/polygon3D.h"
#include "_Basis/Draw/text.h"
#include "_Basis/Draw/text2D.h"
#include "_Basis/Draw/text3D.h"
//========== [[[ Mechanical ]]]
#include "_Basis/Mechanical/memory.h"
#include "_Basis/Mechanical/object.h"
#include "_Basis/Mechanical/object-manager.h"
//========== [[[ Other ]]]
#include "_Basis/Other/color.h"
#include "_Basis/Other/file.h"
#include "_Basis/Other/input.h"
#include "_Basis/Other/print.h"
#include "_Basis/Other/regist.h"
#include "_Basis/Other/setting.h"
#include "_Basis/Other/sound.h"
#include "_Basis/Other/window.h"
#include "_Basis/Visual/texture.h"
#include "_Basis/Visual/transition.h"
#include "_Basis/Visual/visual.h"

#include "_ImGui/imgui_crt-wgt.h"
#include "_ImGui/imgui_main.h"

//****************************************
// メモリリークチェックの定義
//****************************************
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG

#ifdef CHECK_MEM_LEAK
#ifdef new
#undef new
#endif
#endif // CHECK_MEM_LEAK

// 普段使用禁止
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

//****************************************
// 名前空間
//****************************************
namespace RNLib {

	//========== [[[ 列挙型定義 ]]]
	enum class SIGNAL {
		NONE,
		INIT,
		UNINIT,
		UPDATE,
		UPDATE_WAIT,
		DRAW,
		LOAD,
		SAVE,
		END,
	};

	//========== [[[ 関数宣言 ]]]
	bool MainLoop(
		int*           pEndCode,
		HINSTANCE      hInstance,
		const char*    pClassName,
		const char*    pWinName,
		const float    fWinWidth,
		const float    fWinHeight,
		const bool     bFullScreen,
		const float    fResolution,
		const bool     bUseImGui = false);
	SIGNAL GetSignal      (void);
	void   UninitScene    (void);
	int    GetCount       (void);
	int    GetFPSCount    (void);
	bool   GetBlinkF2     (void);
	bool   GetBlinkF4     (void);
	bool   GetUseImGui    (void);
	void   SetSpace3DStop (bool bStop);
	bool   GetSpace3DStop (void);
	bool   GetSceneSwap   (void);

	CText2D*      Text2D      (void);
	CPolygon2D*   Polygon2D   (void);				
	CMotion3D*    Motion3D    (void);
	CHuman3DBase* Human3DBase (void);
	CModelSetUp*  ModelSetUp  (void);
	CModel*       Model       (void);
	CEff3DMng*    Eff3DMng    (void);
	CText3D*      Text3D      (void);
	CPolygon3D*   Polygon3D   (void);
	CLine3D*      Line3D      (void);
	CFog*         Fog         (void);
	CLight3D*     Light3D     (void);
	CShadow3D*    Shadow3D    (void);
	CCamera*      Camera3D    (void);
	CFile*        File        (void);
	CInput*       Input       (void);
	CMemory*      Memory      (void);
	CSound*       Sound       (void);
	CWindow*      Window      (void);
	CText*        Text        (void);
	CTexture*     Texture     (void);
	CTransition*  Transition  (void);
	CVisual*      Visual      (void);
	CDrawMng*     DrawMng     (void);
	CDrawState*   DrawStateMng(void);
}

#endif