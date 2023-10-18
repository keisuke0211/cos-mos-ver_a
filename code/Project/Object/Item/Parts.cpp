//========================================
// 
// パーツの処理
// Author:KOMURO HIROMU
// 
//========================================
#include "Parts.h"
#include "../../main.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CTrampolineクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================
static const D3DXVECTOR3 PARTS_ADDROT = { 0.0f,0.02f,0.0f };				// パーツの回転の移動量

//========================================
// コンストラクタ
//========================================
CParts::CParts(void) {
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::PARTS;	// 種類の設定
							// 大きさの設定
	m_width = SIZE_OF_1_SQUARE * 3;
	m_height = SIZE_OF_1_SQUARE * 3;

	// 各情報の初期化
	ModelIdx = RNLib::Model()->Load("data\\MODEL\\Block.x");
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fblink = 0.0f;
	m_nblinlAnim = 0;
}

//========================================
// デストラクタ
//========================================
CParts::~CParts(void) {

}

//========================================
// 初期化処理
// Author:KOMURO HIROMU
//========================================
void CParts::Init(void) {

}

//========================================
// 終了処理
// Author:KOMURO HIROMU
//========================================
void CParts::Uninit(void) {

}

//========================================
// 更新処理
// Author:KOMURO HIROMU
//========================================
void CParts::Update(void) {

	m_rot += PARTS_ADDROT;	// 回転の移動量の増加
	float fBrightness = fabsf(m_rot.y) / (D3DX_PI * 0.5f);

	if (fBrightness >= 1.0f)
	{
		fBrightness = fBrightness - (fBrightness  - 1.0f);
	}

	if (fBrightness < 0)
	{
		fBrightness = fabsf(fBrightness);
	}
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}

	RNLib::Model()->Put(m_pos, m_rot, ModelIdx, false)
		->SetCol(Color{ 0,(int)(255* fBrightness),255,255 })
		;
}

//========================================
// 描画処理
// Author:KOMURO HIROMU
//========================================
void CParts::Draw(void) {


}