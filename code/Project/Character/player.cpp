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
#include "../Object/Block/move-block.h"
#include "../Object/Gimmick/meteor.h"
#include "../Object/Gimmick/trampoline.h"

//スワップインターバル
const int	CPlayer::SWAP_INTERVAL = 30;	//スワップインターバル
int			CPlayer::s_nSwapInterval = 0;	//残りスワップインターバル

const float CPlayer::SIZE_WIDTH  = 8.0f;	//横幅
const float CPlayer::SIZE_HEIGHT = 8.0f;	//高さ

const float CPlayer::MOVE_SPEED = 0.5f;		//移動量
const float CPlayer::MAX_MOVE_SPEED = 2.7f;	//最大移動量

const float CPlayer::JUMP_POWER = 3.0f;	//基本ジャンプ量
const float CPlayer::GRAVITY_POWER = -3.0f;	//基本重力加速度
const float CPlayer::GRAVITY_CORR = 0.01f;	//基本重力係数

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
		Player.bGround = false;				//地面に接しているか
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

	//情報更新
	UpdateInfo();
}

//----------------------------
//情報更新処理
//----------------------------
void CPlayer::UpdateInfo(void)
{
	for each (Info &Player in m_aInfo)
	{
		//位置設定
		RNLib::Model()->Put(Player.pos, Player.rot, Player.nModelIdx, false)
			->SetOutLine(true);

		//スワップ先のマークを描画する位置
		D3DXVECTOR3 MarkPos = Player.pos;
		MarkPos.y *= -1.0f;

		RNLib::Polygon3D()->Put(MarkPos, INITD3DXVECTOR3)
			->SetSize(20.0f, 20.0f)
			->SetBillboard(true);
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
			Player.bGround = false;				//地面から離れた
			Player.move.y = Player.fJumpPower;	//ジャンプ量代入
			Player.bJump = true;				//ジャンプした
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
	m_aInfo[0].bGround = m_aInfo[1].bGround = false;

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
				//プレイヤーの近くにオブジェクトがあるか判定
				{
					const D3DXVECTOR3 PosDiff = POS - Player.pos;
					const float fLength = D3DXVec3Length(&PosDiff);

					const float fWIDTH_SUM = WIDTH + SIZE_WIDTH;
					const float fHEIGHT_SUM = HEIGHT + SIZE_WIDTH;

					float flength = sqrtf(fWIDTH_SUM * fWIDTH_SUM + fHEIGHT_SUM * fHEIGHT_SUM);

					if (fLength > sqrtf(fWIDTH_SUM * fWIDTH_SUM + fHEIGHT_SUM * fHEIGHT_SUM)) continue;
				}

				//種類取得
				const CStageObject::TYPE type = stageObj->GetType();

				//前回位置
				D3DXVECTOR3 PosOld = POS;

				//移動するオブジェクトは、前回位置を特別に設定
				switch (type)
				{
					//移動床
					case CStageObject::TYPE::MOVE_BLOCK:
					{
						CMoveBlock *pBlock = (CMoveBlock *)stageObj;
						PosOld = pBlock->GetPosOld();
					}
						break;

						//隕石
					case CStageObject::TYPE::METEOR:
					{
						CMeteor *pMeteor = (CMeteor *)stageObj;
						//PosOld = pMeteor->GetPosOld();
					}
						break;
				}

				//当たった方向を格納
				const COLLI_ROT ColliRot = IsBoxCollider(Player.pos, Player.posOLd, SIZE_WIDTH, SIZE_HEIGHT, POS, PosOld, WIDTH, HEIGHT, vec);

				//当たっていなければスキップ
				if (ColliRot == COLLI_ROT::NONE) continue;

				//種類ごとに関数分け
				switch (type)
				{
					case CStageObject::TYPE::BLOCK:			CollisionBlock(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::FILLBLOCK:		break;
					case CStageObject::TYPE::TRAMPOLINE:	CollisionTrampoline(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::SPIKE:			CollisionSpike(&Player, MinPos, MaxPos, ColliRot);	break;
					case CStageObject::TYPE::MOVE_BLOCK:	CollisionMoveBlock(&Player, (CMoveBlock *)stageObj, MinPos, MaxPos, ColliRot);	break;
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

#if 0
	//プレイヤーの位置更新
	for(int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	{
		RNLib::Text2D()->Put(D3DXVECTOR2(20.0f, 20.0f + 25.0f * nCnt), 0.0f, CreateText("%dPのY座標：%f", nCnt, m_aInfo[nCnt].pos.y), CText::ALIGNMENT::LEFT, 0);
	}

	RNLib::Text2D()->Put(D3DXVECTOR2(20.0f, 80.0f), 0.0f, CreateText("FPS：%d", RNLib::GetFPSCount()), CText::ALIGNMENT::LEFT, 0);
#endif

	////プレイヤーの位置更新
	//for (int nCnt = 0; nCnt < NUM_PLAYER; nCnt++)
	//{
	//	RNLib::Text3D()->Put(D3DXVECTOR3(20.0f, 20.0f + 25.0f * nCnt, 0.0f), INITD3DXVECTOR3, CreateText("%dPのY座標：%f", nCnt, m_aInfo[nCnt].pos.y), CText::ALIGNMENT::LEFT, 0);
	//}

	//RNLib::Text3D()->Put(D3DXVECTOR3(20.0f, 80.0f, 0.0f), INITD3DXVECTOR3, CreateText("FPS：%d", RNLib::GetFPSCount()), CText::ALIGNMENT::LEFT, 0);

}

//----------------------------
//上からの当たり判定による位置修正
//----------------------------
void CPlayer::FixPos_OVER(float *pPosY, float fMaxPosY, float *pMoveY)
{
	//位置・移動量修正
	*pPosY = fMaxPosY + SIZE_HEIGHT;
	*pMoveY = 0.0f;
}

//----------------------------
//下からの当たり判定による位置修正
//----------------------------
void CPlayer::FixPos_UNDER(float *pPosY, float fMinPosY, float *pMoveY)
{
	//位置・移動量修正
	*pPosY = fMinPosY - SIZE_HEIGHT;
	*pMoveY = 0.0f;
}

//----------------------------
//左からの当たり判定による位置修正
//----------------------------
void CPlayer::FixPos_LEFT(float *pPosX, float fMinPosX, float *pMoveX)
{
	//位置・移動量修正
	*pPosX = fMinPosX - SIZE_WIDTH;
	*pMoveX = 0.0f;
}

//----------------------------
//右からの当たり判定による位置修正
//----------------------------
void CPlayer::FixPos_RIGHT(float *pPosX, float fMaxPosX, float *pMoveX)
{
	//位置・移動量修正
	*pPosX = fMaxPosX + SIZE_WIDTH;
	*pMoveX = 0.0f;
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
			FixPos_OVER(&pInfo->pos.y, MaxPos.y, &pInfo->move.y);

			//表の世界のプレイヤー
			if (pInfo->side == WORLD_SIDE::FACE) {
				pInfo->bGround = true;	//地面に接している
				pInfo->bJump = false;	//ジャンプ可能
			}
			break;

			//*********************************
			//下に当たった
			//*********************************
		case COLLI_ROT::UNDER:
			//位置・移動量修正
			FixPos_UNDER(&pInfo->pos.y, MinPos.y, &pInfo->move.y);

			//裏の世界のプレイヤーならジャンプ可能
			if (pInfo->side == WORLD_SIDE::BEHIND) {
				pInfo->bGround = true;	//地面に接している
				pInfo->bJump = false;	//ジャンプ可能
			}
			break;

			//*********************************
			//左に当たった
			//*********************************
		case COLLI_ROT::LEFT:
			//位置・移動量修正
			FixPos_LEFT(&pInfo->pos.x, MinPos.x, &pInfo->move.x);
			break;

			//*********************************
			//右に当たった
			//*********************************
		case COLLI_ROT::RIGHT:
			//位置・移動量修正
			FixPos_RIGHT(&pInfo->pos.x, MaxPos.x, &pInfo->move.x);
			break;
	}
}

//----------------------------
//トランポリンの当たり判定処理
//----------------------------
void CPlayer::CollisionTrampoline(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	//当たった方向ごとに処理を切り替え
	switch (ColliRot)
	{
		//*********************************
		//上に当たった
		//*********************************
		case COLLI_ROT::OVER:
			//位置・移動量修正
			FixPos_OVER(&pInfo->pos.y, MaxPos.y, &pInfo->move.y);

			//表の世界のプレイヤー
			if (pInfo->side == WORLD_SIDE::FACE) {
				pInfo->bGround = true;	//地面に接している
				pInfo->bJump = false;	//ジャンプ可能
			}
			break;

			//*********************************
			//下に当たった
			//*********************************
		case COLLI_ROT::UNDER:
			//位置・移動量修正
			FixPos_UNDER(&pInfo->pos.y, MinPos.y, &pInfo->move.y);

			//裏の世界のプレイヤーならジャンプ可能
			if (pInfo->side == WORLD_SIDE::BEHIND) {
				pInfo->bGround = true;	//地面に接している
				pInfo->bJump = false;	//ジャンプ可能
			}
			break;
	}
}

//----------------------------
//トゲの当たり判定処理
//----------------------------
void CPlayer::CollisionSpike(Info *pInfo, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	//当たった方向ごとに処理を切り替え
	switch (ColliRot)
	{
		//*********************************
		//上下どちらかに当たった
		//*********************************
		case COLLI_ROT::OVER:
		case COLLI_ROT::UNDER:
			//死亡処理
			Death(NULL);
			break;

			//*********************************
			//左に当たった
			//*********************************
		case COLLI_ROT::LEFT:
			//位置・移動量修正
			FixPos_LEFT(&pInfo->pos.x, MinPos.x, &pInfo->move.x);
			break;

			//*********************************
			//右に当たった
			//*********************************
		case COLLI_ROT::RIGHT:
			//位置・移動量修正
			FixPos_RIGHT(&pInfo->pos.x, MaxPos.x, &pInfo->move.x);
			break;
	}
}

//----------------------------
//移動床の当たり判定処理
//----------------------------
void CPlayer::CollisionMoveBlock(Info *pInfo, CMoveBlock *pMoveBlock, D3DXVECTOR3 MinPos, D3DXVECTOR3 MaxPos, COLLI_ROT ColliRot)
{
	switch (ColliRot)
	{
			//*********************************
			//上に当たった
			//*********************************
		case COLLI_ROT::OVER:
			//位置・移動量修正
			FixPos_OVER(&pInfo->pos.y, MaxPos.y, &pInfo->move.y);

			//表の世界のプレイヤーの場合
			if (pInfo->side == WORLD_SIDE::FACE)
			{
				pInfo->pos += pMoveBlock->GetMove();
				pInfo->bGround = true;	//地面に接している
				pInfo->bJump = false;	//ジャンプ可能
			}
			break;

			//*********************************
			//下に当たった
			//*********************************
		case COLLI_ROT::UNDER:
			//位置・移動量修正
			FixPos_UNDER(&pInfo->pos.y, MinPos.y, &pInfo->move.y);

			//裏の世界のプレイヤーならジャンプ可能
			if (pInfo->side == WORLD_SIDE::BEHIND)
			{
				pInfo->pos += pMoveBlock->GetMove();
				pInfo->bGround = true;	//地面に接している
				pInfo->bJump = false;	//ジャンプ可能
			}
			break;

			//*********************************
			//左に当たった
			//*********************************
		case COLLI_ROT::LEFT:
			//位置・移動量修正
			FixPos_LEFT(&pInfo->pos.x, MinPos.x, &pInfo->move.x);
			break;

			//*********************************
			//右に当たった
			//*********************************
		case COLLI_ROT::RIGHT:
			//位置・移動量修正
			FixPos_RIGHT(&pInfo->pos.x, MaxPos.x, &pInfo->move.x);
			break;

		case COLLI_ROT::UNKNOWN:
			/*
			//移動床 -> プレイヤーへの当たり判定処理を実行
			const D3DXVECTOR3 BlockPos = pMoveBlock->GetPos();
			const D3DXVECTOR3 BlockPosOld = pMoveBlock->GetPosOld();
			const float fWidth = pMoveBlock->GetWidth() * 0.5f;
			const float fHeight = pMoveBlock->GetHeight() * 0.5f;
			const D3DXVECTOR3 PlayerMinPos = D3DXVECTOR3(pInfo->pos.x - SIZE_WIDTH, pInfo->pos.y - SIZE_HEIGHT, 0.0f);
			const D3DXVECTOR3 PlayerMaxPos = D3DXVECTOR3(pInfo->pos.x + SIZE_WIDTH, pInfo->pos.y + SIZE_HEIGHT, 0.0f);

			//移動床からの当たり判定
			for (int nCntVec = 0; nCntVec < (int)COLLI_VEC::MAX; nCntVec++)
			{
				//プレイヤーのどの方向に当たっているか
				COLLI_ROT ColliRot_Player = IsBoxCollider(BlockPos, BlockPosOld, fWidth, fHeight, PlayerMinPos, PlayerMaxPos, (COLLI_VEC)nCntVec);

				//それでも当たらないなら、スキップ
				if (ColliRot_Player == COLLI_ROT::NONE || ColliRot_Player == COLLI_ROT::UNKNOWN) continue;

				//当たった方向（上下・左右）を反転する
				{
					//当たった方向をint型に変換 - 1
					const int nRot = (int)ColliRot_Player;

					ColliRot_Player = (COLLI_ROT)(nRot - 1 + 2 * (nRot % 2));
				}

				//もう一度当たり判定
				CollisionMoveBlock(pInfo, pMoveBlock, MinPos, MaxPos, ColliRot_Player);
			}
			*/
			break;
	}
}

//========================
//対象物の中にめり込んでいるかどうか判定
//------------------------
// 引数１	pos			：現在位置
// 引数２	posOld		：前回位置
// 引数３	fWidth		：幅
// 引数４	fHeight		：高さ
// 引数５	TargetPos	：対象の現在位置
// 引数６	TargetPosOld：対象の前回位置（オブジェクトにPosOld変数が無いなら、現在位置をいれればOK
// 引数７	TargetWidth	：対象の幅
// 引数８	TargetHeight：対象の高さ
// 引数９	value		：ベクトル
// 返り値	対象物にめりこんでいる方向を返す（NONEなら当たっていない
//========================
CPlayer::COLLI_ROT CPlayer::IsBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, float fWidth, float fHeight, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetPosOld, float TargetWidth, float TargetHeight, COLLI_VEC value)
{
	//自分の現在の最小・最大位置
	const D3DXVECTOR2 MinPos = D3DXVECTOR2(pos.x - fWidth, pos.y - fHeight);
	const D3DXVECTOR2 MaxPos = D3DXVECTOR2(pos.x + fWidth, pos.y + fHeight);

	//対象の現在の最小・最大位置
	const D3DXVECTOR2 TARGET_MinPos = D3DXVECTOR2(TargetPos.x - fWidth, TargetPos.y - fHeight);
	const D3DXVECTOR2 TARGET_MaxPos = D3DXVECTOR2(TargetPos.x + fWidth, TargetPos.y + fHeight);

	//めり込んでいるか判定
	if (MinPos.x < TARGET_MaxPos.x && TARGET_MinPos.x < MaxPos.x &&
		MinPos.y < TARGET_MaxPos.y && TARGET_MinPos.y < MaxPos.y)
	{
		//自分の過去の最小・最大位置
		const D3DXVECTOR2 OLD_MINPOS = D3DXVECTOR2(posOld.x - fWidth, posOld.y - fHeight);
		const D3DXVECTOR2 OLD_MAXPOS = D3DXVECTOR2(posOld.x + fWidth, posOld.y + fHeight);

		//対象の前回の最小・最大位置
		const D3DXVECTOR2 TARGET_MinPosOld = D3DXVECTOR2(TargetPosOld.x - fWidth, TargetPosOld.y - fHeight);
		const D3DXVECTOR2 TARGET_MaxPosOld = D3DXVECTOR2(TargetPosOld.x + fWidth, TargetPosOld.y + fHeight);

		//衝突ベクトルで処理分け
		switch (value)
		{
			case COLLI_VEC::X:
				//前回は左からめり込んでいない（今はめり込んだ
				if (OLD_MAXPOS.x <= TARGET_MinPosOld.x)			return COLLI_ROT::LEFT;

				//前回は右からめり込んでいない（今はめり込んだ
				else if (OLD_MINPOS.x >= TARGET_MaxPosOld.x)	return COLLI_ROT::RIGHT;
				break;

			case COLLI_VEC::Y:
				//前回は上からめり込んでいない（今はめり込んだ
				if (OLD_MINPOS.y >= TARGET_MaxPosOld.y)			return COLLI_ROT::OVER;

				//前回は下からめり込んでいない（今はめり込んだ
				else if (OLD_MAXPOS.y <= TARGET_MinPosOld.y)	return COLLI_ROT::UNDER;
				break;
		}

		//当たった方向が分からない
		return COLLI_ROT::UNKNOWN;
	}

	//当たらなかった
	return COLLI_ROT::NONE;
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