//========================================
// 
// モード:タイトル処理
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_title.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Titleクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Title::CMode_Title(void) {
	m_TexIdx = 0;
}

//========================================
// デストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Title::~CMode_Title(void) {

}

//========================================
// 初期化処理
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Init(void) {
	CMode::Init();

	m_TexIdx = RNLib::Texture()->Load("data\\TEXTURE\\BackGround\\title.jpg");

	// 遷移設定
	RNLib::Transition()->Set(CTransition::STATE::OPEN, CTransition::TYPE::FADE);

	// カメラの視点/注視点を設定
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	// 背景色変更
	SetBGColor(Color{ 200,0,0,255 });
}

//========================================
// 終了処理
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Uninit(void) {
	CMode::Uninit();

}

//========================================
// 更新処理
// Author:KEISUKE OTONO
//========================================
void CMode_Title::Update(void) {
	CMode::Update();

	RNLib::Polygon2D()->Put(D3DXVECTOR3(RNLib::Window()->GetCenterPos().x, RNLib::Window()->GetCenterPos().y, -1.0f), 0.0f, false)
		->SetSize(1280.0f,720.0f)
		->SetCol(Color{255,255,255,255})
		->SetTex(m_TexIdx);

	if (RNLib::Input()->GetKeyTrigger(DIK_SPACE) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		Manager::Transition(CMode::TYPE::GAME, CTransition::TYPE::NONE);
}

//========================================
// 更新処理(状態)
// Author:KEISUKE OTONO
//========================================
void CMode_Title::ProcessState(const PROCESS process) {
	switch ((STATE)m_state) {
		//----------------------------------------
		// 無し
		//----------------------------------------
	case STATE::NONE: {
		switch (process) {
			// [[[ 初期処理 ]]]
		case PROCESS::INIT: {

		}break;
			// [[[ 終了処理 ]]]
		case PROCESS::UNINIT: {

		}break;
			// [[[ 更新処理 ]]]
		case PROCESS::UPDATE: {

		}break;
		}
	}break;
	}
}