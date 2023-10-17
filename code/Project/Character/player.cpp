//================================================================================================
//
//プレイヤー処理[player.cpp]
//Author:Hirasawa Shion
//
//================================================================================================
#include "../main.h"
#include "player.h"

//スワップインターバル
const int	CPlayer::SWAP_INTERVAL = 0;
bool		CPlayer::s_bSwap = false;		//スワップしたかどうか
int			CPlayer::s_nSwapInterval = 0;	//残りスワップインターバル

//=======================================
//コンストラクタ
//=======================================
CPlayer::CPlayer()
{
	s_bSwap = false;		//スワップしたかどうか
	s_nSwapInterval = 0;	//残りスワップインターバル

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		//情報クリア
		m_aInfo[nCntPlayer].pos = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].rot = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].move = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].bJump = false;
		m_aInfo[nCntPlayer].fJumpPower = 0.0f;
		m_aInfo[nCntPlayer].fGravity = 0.0f;
		m_aInfo[nCntPlayer].fGravityCorr = 0.0f;
		m_aInfo[nCntPlayer].nModelID = DATANONE;
	}
}

//=======================================
//デストラクタ
//=======================================
CPlayer::~CPlayer()
{

}

//=======================================
//生成処理
//=======================================
CPlayer *CPlayer::Create(void)
{
	//プレイヤーインスタンスの生成
	CPlayer *pPlayer = new CPlayer;

	//初期化処理
	pPlayer->Init();

	//プレイヤーを返す
	return pPlayer;
}

//=======================================
//初期化処理
//=======================================
HRESULT CPlayer::Init(void)
{	
	//初期化成功
	return S_OK;
}

//=======================================
//終了処理
//=======================================
void CPlayer::Uninit(void)
{

}

//=======================================
//更新処理
//=======================================
void CPlayer::Update(void)
{

}

//=======================================
//描画処理
//=======================================
void CPlayer::Draw(void)
{

}

//----------------------------
//プレイヤー情報設定
//----------------------------
void CPlayer::SetInfo(Info p1, Info p2)
{
	//各プレイヤー情報設定
	m_aInfo[0] = p1;
	m_aInfo[1] = p2;
}