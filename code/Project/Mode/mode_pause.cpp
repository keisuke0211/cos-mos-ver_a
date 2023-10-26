//========================================
// 
// モード:ポーズ処理
// Author:KEISUKE OTONO
// 
//========================================
#include "../main.h"
#include "mode_pause.h"

//========================================
// 静的変数
//========================================
bool CMode_Pause::m_bPause = false;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMode_Resultクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================


//========================================
// コンストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Pause::CMode_Pause(void) {

}

//========================================
// デストラクタ
// Author:KEISUKE OTONO
//========================================
CMode_Pause::~CMode_Pause(void) {

}

//========================================
// 初期化処理
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::Init(void) {
	CMode::Init();

	// 遷移設定
	RNLib::Transition()->Set(CTransition::STATE::NONE, CTransition::TYPE::NONE);

	// カメラの視点/注視点を設定
	RNLib::Camera3D()->SetGeometryInfo(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 状態設定
	SetState((int)STATE::NONE);

	// 背景色変更
	SetBGColor(Color{ 0,200,0,255 });
}

//========================================
// 終了処理
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::Uninit(void) {
	CMode::Uninit();

}

//========================================
// 更新処理
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::Update(void) {
	CMode::Update();

	m_bPause = true;
	if (m_bPause)
	{
		if (RNLib::Input()->GetKeyTrigger(DIK_P) && RNLib::Transition()->GetState() == CTransition::STATE::NONE)
		{
			Manager::UninitMode();

			m_bPause = false;
		}
	}

}

//========================================
// 更新処理(状態)
// Author:KEISUKE OTONO
//========================================
void CMode_Pause::ProcessState(const PROCESS process) {
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
			return;
		}break;
		}
	}break;
	}
}
