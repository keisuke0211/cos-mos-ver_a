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

const float CPlayer::JUMP_POWER = 8.0f;		//基本ジャンプ量
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
//当たり判定まとめ
//----------------------------
void CPlayer::WholeCollision(void)
{
	//オブジェクトのポインタを格納
	CObject *obj = NULL;

	//オブジェクトを取得
	while (Manager::BlockMgr()->ListLoop(&obj)) {
		//取得したオブジェクトをキャスト
		CStageObject* stageObj = (CStageObject*)obj;
	
		for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++)
		{
			//種類ごとに関数分け
			switch (stageObj->GetType())
			{
				case CStageObject::TYPE::BLOCK:		CollisionBlock(stageObj, (COLLI_VEC)nCntVec);	break;
				case CStageObject::TYPE::TRAMPOLINE:	break;
				case CStageObject::TYPE::MOVE_BLOCK:	break;
				case CStageObject::TYPE::METEOR:		break;
			}
		}
	}
}

//----------------------------
//ブロックの当たり判定処理
//----------------------------
void CPlayer::CollisionBlock(CStageObject *pObj, COLLI_VEC value)
{
	//ブロックの当たり判定情報取得
	const D3DXVECTOR3 POS = pObj->GetPos();
	const float WIDTH = pObj->GetWidth();
	const float HEIGHT = pObj->GetHeight();

	//ブロックの最小・最大位置
	const D3DXVECTOR2 MinPos = D3DXVECTOR2(POS.x - WIDTH, POS.y - HEIGHT);
	const D3DXVECTOR2 MaxPos = D3DXVECTOR2(POS.x + WIDTH, POS.y + HEIGHT);

	for each (Info &Player in m_aInfo)
	{
		//Ｘベクトルの当たり判定
		if (value == COLLI_VEC::X)
		{
			//最小位置より下  or  最大位置より上  ならスキップ
			if (MinPos.y > Player.pos.y || Player.pos.y > MaxPos.y) continue;

			//左の当たり判定
			if (Player.posOLd.x <= MinPos.x &&
				Player.pos.x > MinPos.x)
			{
				Player.pos.x = MinPos.x;
				Player.move.x = 0.0f;
			}
			//右の当たり判定
			else if(Player.posOLd.x >= MaxPos.x &&
					Player.pos.x < MaxPos.x)
			{
				Player.pos.x = MaxPos.x;
				Player.move.x = 0.0f;
			}
		}

		//Ｙベクトルの当たり判定
		else if (value == COLLI_VEC::Y)
		{
			//最小位置より左  or  最大位置より右  ならスキップ
			if (MinPos.x > Player.pos.x || Player.pos.x > MaxPos.x) continue;

			//下の当たり判定
			if (Player.posOLd.y <= MinPos.y &&
				Player.pos.y > MinPos.y)
			{
				Player.pos.y = MinPos.y;
				Player.move.y = 0.0f;
			}
			//上の当たり判定
			else if (Player.posOLd.y >= MaxPos.y &&
					 Player.pos.y < MaxPos.y)
			{
				Player.pos.y = MaxPos.y;
				Player.move.y = 0.0f;
			}
		}
	}
}