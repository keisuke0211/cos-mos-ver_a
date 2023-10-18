//================================================================================================
//
//プレイヤー処理[player.cpp]
//Author:Hirasawa Shion
//
//================================================================================================
#include "../main.h"
#include "player.h"
#include "../../_RNLib/_Basis/Other/input.h"
#include "../../_RNLib/_Basis/Calculation/number.h"

//スワップインターバル
const int	CPlayer::SWAP_INTERVAL = 0;
bool		CPlayer::s_bSwap = false;		//スワップしたかどうか
int			CPlayer::s_nSwapInterval = 0;	//残りスワップインターバル
const float CPlayer::UPPER_GROUND = 20.0f;	//上の世界の足場位置
const float CPlayer::DOWNER_GROUND = -20.0f;//下の世界の足場位置

const float CPlayer::MOVE_SPEED = 0.5f;		//移動量
const float CPlayer::MAX_MOVE_SPEED = 3.0f;	//最大移動量

const float CPlayer::JUMP_POWER = 3.0f;		//基本ジャンプ量
const float CPlayer::GRAVITY_POWER = -3.0f;	//基本重力加速度
const float CPlayer::GRAVITY_CORR = 0.1f;	//基本重力係数

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
		m_aInfo[nCntPlayer].posOLd = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].rot = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].move = INITD3DXVECTOR3;
		m_aInfo[nCntPlayer].bJump = false;
		m_aInfo[nCntPlayer].fJumpPower = 0.0f;
		m_aInfo[nCntPlayer].fGravity = 0.0f;
		m_aInfo[nCntPlayer].fGravityCorr = 0.0f;
		m_aInfo[nCntPlayer].nModelIdx = DATANONE;
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
	m_aInfo[0].nModelIdx = RNLib::Model()->Load("data\\MODEL\\1P.x");
	m_aInfo[0].pos = D3DXVECTOR3(50.0f, UPPER_GROUND, 0.0f);
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;

	m_aInfo[1].nModelIdx = RNLib::Model()->Load("data\\MODEL\\2P.x");
	m_aInfo[1].pos = D3DXVECTOR3(-50.0f, DOWNER_GROUND, 0.0f);
	m_aInfo[1].fJumpPower = -JUMP_POWER;
	m_aInfo[1].fGravity = -GRAVITY_POWER;
	m_aInfo[1].fGravityCorr = GRAVITY_CORR;

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
//前回位置設定処理
//=======================================
void CPlayer::SetPosOld(void)
{
	//プレイヤーの前回位置更新
	for each (Info &Player in m_aInfo)
	{
		Player.posOLd = Player.pos;
	}
}

//=======================================
//更新処理
//=======================================
void CPlayer::Update(void)
{
	SetPosOld();

	//操作処理
	ActionControl();

	//移動処理
	Move();

	//当たり判定まとめ
	WholeCollision();

	//プレイヤーの位置更新
	for each (Info &Player in m_aInfo)
	{
		RNLib::Model()->Put(Player.pos, Player.rot, Player.nModelIdx, false);
	}
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

//----------------------------
//操作処理
//----------------------------
void CPlayer::ActionControl(void)
{
	//１Ｐの情報を参照
	Info& rInfo = m_aInfo[0];

	//ジャンプ入力（空中じゃない）
	if (!rInfo.bJump && RNLib::Input()->Trigger(DIK_W, CInput::BUTTON_UP))
	{
		//ジャンプ量代入
		rInfo.move.y = rInfo.fJumpPower;

		//ジャンプした
		rInfo.bJump = true;
	}

	//右に移動
	if (RNLib::Input()->Press(DIK_D, CInput::BUTTON_UP))
	{
		rInfo.move.x += MOVE_SPEED;
	}

	//左に移動
	if (RNLib::Input()->Press(DIK_A, CInput::BUTTON_UP))	rInfo.move.x -= MOVE_SPEED;
}

//----------------------------
//移動処理
//----------------------------
void CPlayer::Move(void)
{
	//プレイヤーの位置更新
	for each (Info &Player in m_aInfo)
	{
		//慣性処理
		Player.move.x += (0.0f - Player.move.x) * 0.1f;

		//Ⅹの移動量を修正
		FloatControl(&Player.move.x, MAX_MOVE_SPEED, -MAX_MOVE_SPEED);

		//重力処理
		Player.move.y += (Player.fGravity - Player.move.y) * Player.fGravityCorr;

		//移動量反映
		Player.pos += Player.move;

		//上の世界にいる
		if (Player.posOLd.y >= UPPER_GROUND &&
			Player.pos.y <= UPPER_GROUND)		//上の地面にめり込んだ
		{
			Player.pos.y = UPPER_GROUND;//地面に戻す
			Player.move.y = 0.0f;		//重力を消す
			Player.bJump = false;		//ジャンプ可能
		}

		//下の世界にいる
		else if (Player.posOLd.y <= DOWNER_GROUND &&
				 Player.pos.y >= DOWNER_GROUND)		//下の地面にめり込んだ
		{
			Player.pos.y = DOWNER_GROUND;	//地面に戻す
			Player.move.y = 0.0f;			//重力を消す
			Player.bJump = false;			//ジャンプ可能
		}
	}	
}

//----------------------------
//移動処理
//----------------------------
void CPlayer::WholeCollision(void)
{
	//オブジェクトのポインタを格納
	CObject *obj = NULL;

	while (Manager::BlockMgr()->ListLoop(&obj)) {
		CStageObject* stageObj = (CStageObject*)obj;
	
		switch (stageObj->GetType()) {
			default:
				break;
		}
	}
}