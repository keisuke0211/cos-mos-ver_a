//========================================
// 
// ロケット
// Author:KEISUKE OTONO
// 
//========================================
// *** rocket.cpp ***
//========================================
#include "rocket.h"
#include "../../main.h"

const int s_AnimeMax = 120;			// アニメーションの最大数
const int s_RideAnimeMax = 20;		// 乗り込みアニメーションの最大数
const float s_RideAnimeMag = 1.7f;	// 乗り込みアニメーションの大きさの倍率
const float s_RotAdd = 0.02f;		// 向きの増加量
const int s_RotAnimeMax = 4;		// 小刻みアニメーションの最大 
const float s_MoveMag = 1.05f;		// 移動量の倍率
const float s_MoveAdd = 0.01f;		// 移動量の増加量
//========================================
// コンストラクタ
//========================================
CRocket::CRocket(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::ROCKET;
	m_width = SIZE_OF_1_SQUARE*3;
	m_height = SIZE_OF_1_SQUARE*3;

	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.scale = Scale3D(1.0f,1.0f,1.0f);
	m_Info.Maxscale = Scale3D(1.0f, 1.0f, 1.0f);
	m_Info.nFlyAnimeCounter = 0;
	m_Info.Animstate = CRocket::ANIME_STATE::RIDE;
	m_Info.nRideAnimeCounter = 0;
	m_Info.nModelIdx = RNLib::Model().Load("data\\MODEL\\rocket.x");
}

//========================================
// デストラクタ
//========================================
CRocket::~CRocket()
{

}

//========================================
// 初期化
//========================================
HRESULT CRocket::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	if (m_pos.y < 0)
	{// 下の世界にいるとき反転させる
		m_rot.z -= D3DX_PI;
	}
	return S_OK;
}

//========================================
// 終了
//========================================
void CRocket::Uninit(void)
{

}

//========================================
// 更新
//========================================
void CRocket::Update(void)
{
	int nCounter;
	switch (m_Info.Animstate)
	{
	case CRocket::ANIME_STATE::NONE:

		break;
	case CRocket::ANIME_STATE::RIDE:
		m_Info.nRideAnimeCounter++;
		
		if (m_Info.nRideAnimeCounter <= s_RideAnimeMax)
		{
			m_Info.scale = Scale3D(1.0f + (float)m_Info.nRideAnimeCounter / (s_RideAnimeMax * s_RideAnimeMag), 1.0f + (float)m_Info.nRideAnimeCounter / (s_RideAnimeMax * s_RideAnimeMag), 1.0f + (float)m_Info.nRideAnimeCounter / (s_RideAnimeMax * s_RideAnimeMag));
		}
		else if (m_Info.nRideAnimeCounter <= s_RideAnimeMax * 2)
		{
			if (m_Info.nRideAnimeCounter == s_RideAnimeMax + 1)
			{
				m_Info.Maxscale = m_Info.scale;
			}
			m_Info.scale = Scale3D(m_Info.Maxscale.x - (float)(m_Info.nRideAnimeCounter - s_RideAnimeMax) / (s_RideAnimeMax * s_RideAnimeMag), m_Info.Maxscale.y - (float)(m_Info.nRideAnimeCounter - s_RideAnimeMax) / (s_RideAnimeMax * s_RideAnimeMag), m_Info.Maxscale.z - (float)(m_Info.nRideAnimeCounter - s_RideAnimeMax) / (s_RideAnimeMax * s_RideAnimeMag));
		}
		else if (m_Info.nRideAnimeCounter <= s_RideAnimeMax * 3)
		{
			m_Info.Animstate = CRocket::ANIME_STATE::FLY;
			m_Info.nRideAnimeCounter = 0;
		}
		break;
	case CRocket::ANIME_STATE::FLY:
		m_Info.nFlyAnimeCounter++;
		nCounter = m_Info.nFlyAnimeCounter % s_RotAnimeMax;
		if (nCounter >= s_RotAnimeMax * 0.5f)
		{
			m_rot.z += s_RotAdd;
		}
		else
		{
			m_rot.z -= s_RotAdd;
		}

		if (m_Info.nFlyAnimeCounter >= s_AnimeMax)
		{
			m_Info.move.y *= s_MoveMag;	// 移動量に倍率をかける

			if (m_pos.y >= 0)
			{// 上の世界にいるとき
				m_Info.move.y += s_MoveAdd;
			}
			else
			{// 下の世界にいるとき
				m_Info.move.y -= s_MoveAdd;
			}
		}
		m_pos += m_Info.move;	// 位置に移動量の増加
								// 過去の位置
		break;

	}

	RNLib::Model().Put(m_pos, m_rot, m_Info.scale, m_Info.nModelIdx, false)
		->SetOutLine(true);

}

//========================================
// 描画
//========================================
void CRocket::Draw(void)
{

}