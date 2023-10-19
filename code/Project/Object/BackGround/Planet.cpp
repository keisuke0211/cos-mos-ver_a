//========================================
// 
// 惑星の処理
// Author:KOMURO HIROMU
// 
//========================================
#include "Planet.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

static const char* s_modelPaths[(int)CPlanet::STAR_TYPE::MAX] = {
	"data\\MODEL\\Saturn_Star.x",
	"data\\MODEL\\Saturn_2_Star.x",
	"data\\MODEL\\Saturn_4_Star.x",
	"data\\MODEL\\Saturn_8_Star.x",
};
static const D3DXVECTOR3 s_moveRot = D3DXVECTOR3(0.0005f, 0.0005f, 0.0f);

//========================================
// コンストラクタ
//========================================
CPlanet::CPlanet(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::BACKGROUND;	// 種類の設定
								// 大きさの設定
	m_width = SIZE_OF_1_SQUARE * 5;
	m_height = SIZE_OF_1_SQUARE * 5;

	// 各情報の初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = Color{ 255,255,255,255 };
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================
// デストラクタ
//========================================
CPlanet::~CPlanet(void) {

}

//========================================
// 初期化処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Init(void) {
	ModelIdx = RNLib::Model()->Load(s_modelPaths[(int)m_Star_type]);

}

//========================================
// 終了処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Uninit(void) {

}

//========================================
// 更新処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Update(void) {

	m_pos += m_move;
	m_rot += s_moveRot;

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false)
		->SetCol(m_col);
		
}

//========================================
// 描画処理
// Author:KOMURO HIROMU
//========================================
void CPlanet::Draw(void) {


}