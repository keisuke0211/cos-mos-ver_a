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

const float CPlayer::JUMP_POWER = 11.0f;		//基本ジャンプ量
const float CPlayer::GRAVITY_POWER = -11.0f;	//基本重力加速度
const float CPlayer::GRAVITY_CORR = 0.06f;	//基本重力係数

//=======================================
//コンストラクタ
//=======================================
CPlayer::CPlayer()
{
	s_nSwapInterval = 0;	//残りスワップインターバル

	for each(Info &Player in m_aInfo)
	{
		Player.StartPos = INITD3DXVECTOR3;	//開始位置
		Player.pos = INITD3DXVECTOR3;		//位置
		Player.posOLd = INITD3DXVECTOR3;	//前回位置
		Player.rot = INITD3DXVECTOR3;		//向き
		Player.move = INITD3DXVECTOR3;		//移動量
		Player.bJump = false;				//ジャンプ
		Player.fJumpPower = 0.0f;			//ジャンプ量
		Player.fGravity = 0.0f;				//重力
		Player.fGravityCorr = 0.0f;			//重力係数
		Player.nModelIdx = DATANONE;		//モデル番号
		Player.side = WORLD_SIDE::FACE;		//どちらの世界に存在するか
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

	//初期情報設定
	Death(NULL);

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
		if (!Player.bJump && RNLib::Input()->GetTrigger(ACTION_KEY[nCntPlayer][(int)Player.side], CInput::BUTTON::UP))
		{
			//ジャンプ量代入
			Player.move.y = Player.fJumpPower;

			//ジャンプした
			Player.bJump = true;
		}

		//右に移動
		if (RNLib::Input()->GetPress(ACTION_KEY[nCntPlayer][2], CInput::BUTTON::RIGHT))
			Player.move.x += MOVE_SPEED;

		//左に移動
		if (RNLib::Input()->GetPress(ACTION_KEY[nCntPlayer][3], CInput::BUTTON::LEFT))
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
	if (RNLib::Input()->GetKeyPress(ACTION_KEY[0][(int)m_aInfo[0].side]) && RNLib::Input()->GetKeyPress(ACTION_KEY[1][(int)m_aInfo[1].side]))
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
//死亡処理
//----------------------------
void CPlayer::Death(D3DXVECTOR3 *pDeathPos)
{
	//１Ｐ初期情報
	m_aInfo[0].pos = m_aInfo[0].StartPos;
	m_aInfo[0].fJumpPower = JUMP_POWER;
	m_aInfo[0].fGravity = GRAVITY_POWER;
	m_aInfo[0].fGravityCorr = GRAVITY_CORR;
	m_aInfo[0].side = WORLD_SIDE::FACE;

	//２Ｐ初期情報
	m_aInfo[1].pos = m_aInfo[1].StartPos;
	m_aInfo[1].fJumpPower = -JUMP_POWER;
	m_aInfo[1].fGravity = -GRAVITY_POWER;
	m_aInfo[1].fGravityCorr = GRAVITY_CORR;
	m_aInfo[1].side = WORLD_SIDE::BEHIND;
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
	//一旦両プレイヤーともにジャンプ不可
	m_aInfo[0].bJump = m_aInfo[1].bJump = true;

	for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++) {

		//衝突ベクトルをキャスト
		const COLLI_VEC vec = (COLLI_VEC)nCntVec;

		//移動処理
		Move(vec);

		//オブジェクトのポインタを格納
		CObject *obj = NULL;

		//オブジェクトを取得
		while (Manager::BlockMgr()->ListLoop(&obj)) {
			//取得したオブジェクトをキャスト
			CStageObject* stageObj = (CStageObject*)obj;

			//オブジェクトの当たり判定情報取得
			const D3DXVECTOR3 POS = stageObj->GetPos();
			const float WIDTH = stageObj->GetWidth() * 0.5f;
			const float HEIGHT = stageObj->GetHeight() * 0.5f;

			//オブジェクトの最小・最大位置
			const D3DXVECTOR3 MinPos = D3DXVECTOR3(POS.x - WIDTH, POS.y - HEIGHT, 0.0f);
			const D3DXVECTOR3 MaxPos = D3DXVECTOR3(POS.x + WIDTH, POS.y + HEIGHT, 0.0f);

			for each(Info& Player in m_aInfo)
			{
				//当たった方向を格納
				const COLLI_ROT ColliRot = IsBoxCollider(Player.pos, Player.posOLd, SIZE_WIDTH, SIZE_HEIGHT, MinPos, MaxPos, vec);

				//当たっていなければスキップ
				if (ColliRot == COLLI_ROT::NONE) continue;

				//種類取得
				const CStageObject::TYPE type = stageObj->GetType();

				//種類ごとに関数分け
				switch (type)
				{
					case CStageObject::TYPE::BLOCK:			CollisionBlock(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::FILLBLOCK:		break;
					case CStageObject::TYPE::TRAMPOLINE:	break;
					case CStageObject::TYPE::SPIKE:			CollisionSpike();	break;
					case CStageObject::TYPE::MOVE_BLOCK:	break;
					case CStageObject::TYPE::METEOR:		break;
					case CStageObject::TYPE::PARTS:			break;
				}

				//当たれば即死のオブジェクトに当たっている
				if (type == CStageObject::TYPE::SPIKE ||
					type == CStageObject::TYPE::METEOR)
				{
					break;
				}
			}
		}
	}
}

//----------------------------
//ブロックの当たり判定処理
//----------------------------
void CPlayer::CollisionBlock(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	//当たった方向ごとに処理を切り替え
	switch (ColliRot)
	{
			//*********************************
			//上に当たった
			//*********************************
		case COLLI_ROT::OVER:
			//位置・移動量修正
			pInfo->pos.y = MaxPos.y + SIZE_HEIGHT;
			pInfo->move.y = 0.0f;

			//表の世界のプレイヤーならジャンプ可能
			if (pInfo->side == WORLD_SIDE::FACE) pInfo->bJump = false;
			break;

			//*********************************
			//下に当たった
			//*********************************
		case COLLI_ROT::UNDER:
			//位置・移動量修正
			pInfo->pos.y = MinPos.y - SIZE_HEIGHT;
			pInfo->move.y = 0.0f;

			//裏の世界のプレイヤーならジャンプ可能
			if (pInfo->side == WORLD_SIDE::BEHIND) pInfo->bJump = false;
			break;

			//*********************************
			//左に当たった
			//*********************************
		case COLLI_ROT::LEFT:
			//位置・移動量修正
			pInfo->pos.x = MinPos.x - SIZE_WIDTH;
			pInfo->move.x = 0.0f;
			break;

			//*********************************
			//右に当たった
			//*********************************
		case COLLI_ROT::RIGHT:
			//位置・移動量修正
			pInfo->pos.x = MaxPos.x + SIZE_WIDTH;
			pInfo->move.x = 0.0f;
			break;
	}
}

//----------------------------
//トゲの当たり判定処理
//----------------------------
void CPlayer::CollisionSpike(void)
{
	//死亡処理
	Death(NULL);
}

//========================
//対象物の中にめり込んでいるかどうか判定
//------------------------
// 引数１	pos				：現在位置
// 引数２	posOld			：前回位置
// 引数３	fWidth			：幅
// 引数４	fHeight			：高さ
// 引数５	TargetMinPos	：対象物の最小位置
// 引数６	TargetMaxPos	：対象物の最大位置
// 返り値	対象物にめりこんでいる方向を返す（NONEなら当たっていない
//========================
CPlayer::COLLI_ROT CPlayer::IsBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float fWidth, float fHeight, D3DXVECTOR3 TargetMinPos, D3DXVECTOR3 TargetMaxPos, COLLI_VEC value)
{
	//当たった方向
	COLLI_ROT ColliRot = COLLI_ROT::NONE;

	//自分の現在の最小・最大位置
	const D3DXVECTOR2 MINPOS = D3DXVECTOR2(pos.x - fWidth, pos.y - fHeight);
	const D3DXVECTOR2 MAXPOS = D3DXVECTOR2(pos.x + fWidth, pos.y + fHeight);

	//めり込んでいるか判定
	if (MINPOS.x < TargetMaxPos.x && TargetMinPos.x < MAXPOS.x &&
		MINPOS.y < TargetMaxPos.y && TargetMinPos.y < MAXPOS.y)
	{
		//自分の過去の最小・最大位置
		const D3DXVECTOR2 OLD_MINPOS = D3DXVECTOR2(posOld.x - fWidth, posOld.y - fHeight);
		const D3DXVECTOR2 OLD_MAXPOS = D3DXVECTOR2(posOld.x + fWidth, posOld.y + fHeight);

		//衝突ベクトルで処理分け
		switch (value)
		{
			case COLLI_VEC::X:
				//前回は左からめり込んでいない（今はめり込んだ
				if (OLD_MAXPOS.x <= TargetMinPos.x)		ColliRot = COLLI_ROT::LEFT;

				//前回は右からめり込んでいない（今はめり込んだ
				else if (OLD_MINPOS.x >= TargetMaxPos.x)		ColliRot = COLLI_ROT::RIGHT;
				break;

			case COLLI_VEC::Y:
				//前回は上からめり込んでいない（今はめり込んだ
				if (OLD_MINPOS.y >= TargetMaxPos.y)		ColliRot = COLLI_ROT::OVER;

				//前回は下からめり込んでいない（今はめり込んだ
				else if (OLD_MAXPOS.y <= TargetMinPos.y)		ColliRot = COLLI_ROT::UNDER;
				break;
		}
	}

	//当たった方向を返す
	return ColliRot;
}

//----------------------------
//プレイヤー情報設定
//指定された番号のプレイヤー情報を設定します。
//----------------------------
void CPlayer::SetInfo(const Info info, const int nNum)
{
	if (0 <= nNum && nNum < NUM_PLAYER)
	{
		//各プレイヤー情報設定
		m_aInfo[nNum] = info;
		m_aInfo[nNum].StartPos = info.pos;
	}
}

//----------------------------
//プレイヤー情報設定
//----------------------------
void CPlayer::SetInfo(Info p1, Info p2)
{
	//各プレイヤー情報設定
	m_aInfo[0] = p1;	m_aInfo[0].StartPos = p1.pos;
	m_aInfo[1] = p2;	m_aInfo[1].StartPos = p2.pos;
}

//----------------------------
//プレイヤー情報取得
//指定された世界にいるプレイヤーの情報を返します
//----------------------------
CPlayer::Info *CPlayer::GetInfo(WORLD_SIDE side)
{
	//１Ｐのいる世界と合致したら１Ｐ情報を返す
	if (m_aInfo[0].side == side) return &m_aInfo[0];

	//違うなら２Ｐ情報を返す
	else return &m_aInfo[1];
}