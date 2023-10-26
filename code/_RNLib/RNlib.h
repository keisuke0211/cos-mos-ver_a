//========================================
// 
// RN���C�u�����̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �w�b�_�C���N���[�h
//****************************************
#include "RNmain.h"
//========== [[[ 3DObject ]]]
#include "Basis/3DObject/Body/setup3D.h"
#include "Basis/3DObject/Body/motion3D.h"
#include "Basis/3DObject/Body/doll3D.h"
//========== [[[ Calculation ]]]
#include "Basis/Calculation/ease.h"
#include "Basis/Calculation/geometry.h"
#include "Basis/Calculation/matrix.h"
#include "Basis/Calculation/number.h"
//========== [[[ Other... ]]]
#include "Basis/default-data.h"
#include "Basis/input.h"
#include "Basis/setting.h"
#include "Basis/sound.h"
//========== [[[ Draw ]]]
#include "Basis/Draw/PutObject/model.h"
#include "Basis/Draw/PutObject/polygon2D.h"
#include "Basis/Draw/PutObject/polygon3D.h"
#include "Basis/Draw/PutObject/text2D.h"
#include "Basis/Draw/PutObject/text3D.h"
#include "Basis/Draw/camera.h"
#include "Basis/Draw/color.h"
#include "Basis/Draw/draw-manager.h"
#include "Basis/Draw/draw-state.h"
#include "Basis/Draw/light3D.h"
#include "Basis/Draw/text.h"
#include "Basis/Draw/texture.h"
#include "Basis/Draw/transition.h"
//========== [[[ Mechanical ]]]
#include "Basis/Mechanical/file.h"
#include "Basis/Mechanical/memory.h"
#include "Basis/Mechanical/object.h"
#include "Basis/Mechanical/object-manager.h"
#include "Basis/Mechanical/print.h"
#include "Basis/Mechanical/regist.h"
#include "Basis/Mechanical/window.h"

//****************************************
// ���������[�N�`�F�b�N�̒�`
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

// ���i�g�p�֎~
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

//****************************************
// ���O���
//****************************************
namespace RNLib {

	//========== [[[ �񋓌^��` ]]]
	enum class SIGNAL { NONE, INIT, UNINIT, UPDATE, UPDATE_WAIT, DRAW, LOAD, SAVE, END, };

	//========== [[[ �֐��錾 ]]]
	bool MainLoop(int* pEndCode, HINSTANCE hInstance, const char* pClassName, const char* pWinName, const float fWinWidth, const float fWinHeight, const bool bFullScreen, const float fResolution);
	SIGNAL GetSignal      (void);
	void   UninitScene    (void);
	int    GetCount       (void);
	int    GetFPSCount    (void);
	bool   GetBlinkF2     (void);
	bool   GetBlinkF4     (void);
	void   SetSpace3DStop (bool bStop);
	bool   GetSpace3DStop (void);
	bool   GetSceneSwap   (void);
	//========== [[[ RN�I�u�W�F�N�g ]]]
	// 3DObject
	CMotion3D&    Motion3D   (void);
	CSetUp3D&     SetUp3D    (void);
	// Calculation
	CEase&        Ease       (void);
	CGeometry&    Geometry   (void);
	CMatrix&      Matrix     (void);
	// Other...
	CDefaultData& DefaultData(void);

	CText2D&      Text2D      (void);
	CPolygon2D&   Polygon2D   (void);
	CModel&       Model       (void);
	CText3D&      Text3D      (void);
	CPolygon3D&   Polygon3D   (void);
	CLight3D&     Light3D     (void);
	CCamera&      Camera3D    (void);
	CFile&        File        (void);
	CInput&       Input       (void);
	CMemory&      Memory      (void);
	CSound&       Sound       (void);
	CWindow&      Window      (void);
	CText&        Text        (void);
	CTexture&     Texture     (void);
	CTransition&  Transition  (void);
	CDrawMng&     DrawMng     (void);
	CDrawState&   DrawStateMng(void);
}