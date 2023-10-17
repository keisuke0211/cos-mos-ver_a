//========================================
// 
// マネージャー処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "main.h"

//****************************************
// 名前空間
//****************************************
namespace {
	//========== [[[ 変数宣言 ]]]
	CMode*      m_modeObj;
	CMode::TYPE m_reserveModeType;
	CBlockMgr   m_blockMgr;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| Managerの関数
//----------|---------------------------------------------------------------------
//================================================================================
CBlockMgr* Manager::BlockMgr(void) { return &m_blockMgr; }

//========================================
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void Manager::Init(CMode::TYPE mode) {

	// モード設定
	SetMode(mode);
}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void Manager::Uninit(void) {

	// モードオブジェクト解放
	RNLib::Memory()->Release(&m_modeObj);
}

//========================================
// 更新処理
// Author:RIKU NISHIMURA
//========================================
void Manager::Update(void) {

	m_blockMgr.Update();

	// 予約されている時、遷移がモード設定待ちならモードを設定する
	if (m_reserveModeType != CMode::TYPE::NONE) {
		if (RNLib::Transition()->GetState() == CTransition::STATE::WAIT_SET_MODE) {
			SetMode(m_reserveModeType);
		}
	}

	// モードオブジェクトが在る時、更新処理
	if (m_modeObj != NULL) {
		m_modeObj->Update();
		m_modeObj->ProcessState(PROCESS::UPDATE);
	}
}

//========================================
// 読み込み処理
// Author:RIKU NISHIMURA
//========================================
void Manager::Load(void) {
	
}

//========================================
// 書き込み処理
// Author:RIKU NISHIMURA
//========================================
void Manager::Save(void) {
	
}

//========================================
// モードの設定処理
// Author:RIKU NISHIMURA
//========================================
void Manager::SetMode(CMode::TYPE newMode) {

	// シーンを終了
	RNLib::UninitScene();
	
	// モードオブジェクトの終了処理
	if (m_modeObj != NULL) {
		m_modeObj->Uninit();
		RNLib::Memory()->Release(&m_modeObj);
	}

	// モードオブジェクトを新たに生成
	m_modeObj = CMode::Create(newMode);
	
	// 予約モードを無しにする
	m_reserveModeType = CMode::TYPE::NONE;
}

//========================================
// モードの取得処理
// Author:RIKU NISHIMURA
//========================================
CMode::TYPE Manager::GetMode(void) {

	if (m_modeObj != NULL)
		return m_modeObj->GetType();

	return CMode::TYPE::NONE;
}

//========================================
// 遷移処理
// Author:RIKU NISHIMURA
//========================================
void Manager::Transition(CMode::TYPE newMode, CTransition::TYPE transType) {

	// モードを予約する
	m_reserveModeType = newMode;

	// 遷移設定
	RNLib::Transition()->Set(CTransition::STATE::CLOSE, transType);
}