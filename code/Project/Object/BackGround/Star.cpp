//========================================
// 
// 星の処理
// Author:KOMURO HIROMU
// 
//========================================
#include "Star.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================
static const int s_maxAnimeCounter = 120;		// アニメーションのカウンター最大
static const D3DXVECTOR3 s_moveRot = D3DXVECTOR3(0.0005f, 0.0005f, 0.0f);
static const float s_PosOver = 100.0f;	

//========================================
// コンストラクタ
//========================================
CStar::CStar(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// 種類の設定
								// 大きさの設定
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// 各情報の初期化
	m_rot = INITD3DXVECTOR3;
	m_move = INITD3DXVECTOR3;
	m_col = Color{ 255,255,255,255 };
	m_rot = INITD3DXVECTOR3;
	m_moveCounter = 0;
}

//========================================
// デストラクタ
//========================================
CStar::~CStar(void) {

}

//========================================
// 初期化処理
// Author:KOMURO HIROMU
//========================================
void CStar::Init(void) {
	//ModelIdx = RNLib::Model()->Load(s_modelPaths[(int)m_Star_type]);
	//RNLib::Texture()->Load();
	m_posOld = m_pos;
}

//========================================
// 終了処理
// Author:KOMURO HIROMU
//========================================
void CStar::Uninit(void) {

}

//========================================
// 更新処理
// Author:KOMURO HIROMU
//========================================
void CStar::Update(void) {
	
	RNLib::Polygon3D()->Put(m_pos, m_rot, false)
		->SetSize(100.0f,100.0f);
}

//========================================
// 描画処理
// Author:KOMURO HIROMU
//========================================
void CStar::Draw(void) {


}