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
const int	CPlayer::SWAP_INTERVAL = 30;	//スワップインターバル
int			CPlayer::s_nSwapInterval = 0;	//残りスワップインターバル

const float CPlayer::SIZE_WIDTH  = 8.0f;	//横幅
const float CPlayer::SIZE_HEIGHT = 8.0f;	//高さ

const float CPlayer::MOVE_SPEED = 0.5f;		//移動量
const float CPlayer::MAX_MOVE_SPEED = 2.7f;	//最大移動量

const float CPlayer::JUMP_POWER = 12.0f;		//基本ジャンプ量
const float CPlayer::GRAVITY_POWER = -8.0f;	//基本重力加速度
const float CPlayer::GRAVITY_CORR = 0.1f;	//基本重力係数

//=======================================
//コンストラクタ
//=======================================
CPlayer::CPlayer()
{
	s_nSwapInterval = 0;	//残りスワップインターバル

	for each (Info &Player in m_aInfo)
	{
		//情報クリア
		Player = FormatInfo();
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
	//１Ｐ初期情報
	m_aInfo[0].nModelIdx = RNLib::Model()->Load("data\\MODEL\\1P.x");
	m_aInfo[0].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;
	m_aInfo[0].side = WORLD_SIDE::FACE;

	//２Ｐ初期情報
	m_aInfo[1].nModelIdx = RNLib::Model()->Load("data\\MODEL\\2P.x");
	m_aInfo[1].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	m_aInfo[1].fJumpPower = -JUMP_POWER;
	m_aInfo[1].fGravity = -GRAVITY_POWER;
	m_aInfo[1].fGravityCorr = GRAVITY_CORR;
	m_aInfo[1].side = WORLD_SIDE::BEHIND;

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
//前回位置更新処理
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
	//前回位置更新
	SetPosOld();

	//操作処理
	ActionControl();

	//スワップ
	Swap();

	//当たり判定まとめ
	WholeCollision();

	//プレイヤーの位置更新
	for each (Info &Player in m_aInfo)
	{
		RNLib::Model()->Put(Player.pos, Player.rot, Player.nModelIdx, false)
			->SetOutLine(true);
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
	//各プレイヤーのアクションキー
	const int ACTION_KEY[NUM_PLAYER][4] = {
		{ DIK_W, DIK_S, DIK_D , DIK_A },	//１Ｐの操作キー
		{ DIK_UPARROW, DIK_DOWNARROW, DIK_RIGHTARROW, DIK_LEFTARROW}//２Ｐの操作キー
	};

	for (int nCntPlayer = 0; nCntPlayer < NUM_PLAYER; nCntPlayer++)
	{
		//情報を参照
		Info& Player = m_aInfo[nCntPlayer];

		//ジャンプ入力（空中じゃない）
		if (!Player.bJump && RNLib::Input()->Trigger(ACTION_KEY[nCntPlayer][(int)Player.side], (int)CInput::BUTTON::UP))
		{
			//ジャンプ量代入
			Player.move.y = Player.fJumpPower;

			//ジャンプした
			Player.bJump = true;
		}

		//右に移動
		if (RNLib::Input()->Press(ACTION_KEY[nCntPlayer][2], (int)CInput::BUTTON::RIGHT))
			Player.move.x += MOVE_SPEED;

		//左に移動
		if (RNLib::Input()->Press(ACTION_KEY[nCntPlayer][3], (int)CInput::BUTTON::LEFT))
			Player.move.x -= MOVE_SPEED;
	}
}

//############################
//スワップ処理
//############################
void CPlayer::Swap(void)
{
	//インターバルがあれば減少させて終了
	if (s_nSwapInterval > 0)
	{
		s_nSwapInterval--;
		return;
	}

	//各プレイヤーのアクションキー
	const int ACTION_KEY[NUM_PLAYER][2] = {
		{ DIK_S, DIK_W},	//１Ｐの操作キー
		{ DIK_DOWNARROW, DIK_UPARROW }//２Ｐの操作キー
	};

	//両者ともにスワップボタンを押している
	if (RNLib::Input()->KeyPress(ACTION_KEY[0][(int)m_aInfo[0].side]) && RNLib::Input()->KeyPress(ACTION_KEY[1][(int)m_aInfo[1].side]))
	{
		//インターバル設定
		s_nSwapInterval = SWAP_INTERVAL;

		for each (Info &Player in m_aInfo)
		{
			//位置・重力加速度・ジャンプ量・存在する世界を反転
			Player.pos.y *= -1.0f;
			Player.fGravity *= -1.0f;
			Player.fJumpPower *= -1.0f;
			Player.side = (WORLD_SIDE)(((int)Player.side + 1) % (int)WORLD_SIDE::MAX);
		}

		//前回位置更新
		SetPosOld();
	}
}

//----------------------------
//移動処理
//----------------------------
void CPlayer::Move(COLLI_VEC vec)
{
	//プレイヤーの位置更新
	for each (Info &Player in m_aInfo)
	{
		//移動量反映
		switch (vec)
		{
			case COLLI_VEC::X:
				//慣性処理
				Player.move.x += (0.0f - Player.move.x) * 0.1f;

				//Ⅹの移動量を修正
				FloatControl(&Player.move.x, MAX_MOVE_SPEED, -MAX_MOVE_SPEED);

				//位置更新
				Player.pos.x += Player.move.x;
				break;

				//重力処理
			case COLLI_VEC::Y:
				Player.move.y += (Player.fGravity - Player.move.y) * Player.fGravityCorr;

				//位置更新
				Player.pos.y += Player.move.y;
				break;
		}
	}
}

//----------------------------
//当たり判定まとめ
//----------------------------
void CPlayer::WholeCollision(void)
{
	for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++) {

		//移動処理
		Move((COLLI_VEC)nCntVec);

		//オブジェクトのポインタを格納
		CObject *obj = NULL;

		//オブジェクトを取得
		while (Manager::BlockMgr()->ListLoop(&obj)) {
			//取得したオブジェクトをキャスト
			CStageObject* stageObj = (CStageObject*)obj;

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
	const float WIDTH = pObj->GetWidth() * 0.5f;
	const float HEIGHT = pObj->GetHeight() * 0.5f;

	//ブロックの最小・最大位置
	const D3DXVECTOR2 MinPos = D3DXVECTOR2(POS.x - WIDTH, POS.y - HEIGHT);
	const D3DXVECTOR2 MaxPos = D3DXVECTOR2(POS.x + WIDTH, POS.y + HEIGHT);

	for each (Info &Player in m_aInfo)
	{
		if (value == COLLI_VEC::X)
		{//Ｘベクトルの当たり判定
			if (MinPos.y < Player.pos.y + SIZE_HEIGHT && Player.pos.y - SIZE_HEIGHT < MaxPos.y)
			{// 上下で重なっている
				//左の当たり判定
				if (Player.posOLd.x + SIZE_WIDTH <= MinPos.x &&
					Player.pos.x + SIZE_WIDTH> MinPos.x)
				{
					Player.pos.x = MinPos.x - SIZE_WIDTH;
					Player.move.x = 0.0f;
				}
				//右の当たり判定
				else if (Player.posOLd.x - SIZE_WIDTH >= MaxPos.x &&
						 Player.pos.x - SIZE_WIDTH < MaxPos.x)
				{
					Player.pos.x = MaxPos.x + SIZE_WIDTH;
					Player.move.x = 0.0f;
				}
			}
		}
		else if (value == COLLI_VEC::Y)
		{//Ｙベクトルの当たり判定
			if (MinPos.x < Player.pos.x + SIZE_WIDTH  && Player.pos.x - SIZE_WIDTH < MaxPos.x)
			{// 左右で重なっている
				//下の当たり判定
				if (Player.posOLd.y + SIZE_HEIGHT <= MinPos.y &&
					Player.pos.y + SIZE_HEIGHT > MinPos.y)
				{
					Player.pos.y = MinPos.y - SIZE_HEIGHT;
					Player.move.y = 0.0f;

					//裏の世界にいるならジャンプ可能
					if (Player.side == WORLD_SIDE::BEHIND)	Player.bJump = false;
				}
				//上の当たり判定
				else if (Player.posOLd.y - SIZE_HEIGHT >= MaxPos.y &&
						 Player.pos.y - SIZE_HEIGHT < MaxPos.y)
				{
					Player.pos.y = MaxPos.y + SIZE_HEIGHT;
					Player.move.y = 0.0f;

					//表の世界にいるならジャンプ可能
					if (Player.side == WORLD_SIDE::FACE)	Player.bJump = false;
				}
			}
		}
	}
}

//----------------------------
//プレイヤー情報設定
//指定された番号のプレイヤー情報を設定します。
//----------------------------
void CPlayer::SetInfo(const Info info, const int nNum)
{
	if (0 <= nNum || nNum < NUM_PLAYER)
	{
		//情報代入
		m_aInfo[nNum] = info;
	}
}

//----------------------------
//プレイヤー情報の初期化処理
//プレイヤー情報を初期状態にします。
//----------------------------
CPlayer::Info CPlayer::FormatInfo(void)
{
	return{
		INITD3DXVECTOR3,	//位置
		INITD3DXVECTOR3,	//前回位置
		INITD3DXVECTOR3,	//向き
		INITD3DXVECTOR3,	//移動量
		false,				//ジャンプ
		JUMP_POWER,			//ジャンプ量
		GRAVITY_POWER,		//重力
		GRAVITY_CORR ,		//重力係数
		DATANONE,			//モデル番号
		WORLD_SIDE::FACE,	//どちらの世界に存在するか
	};
}