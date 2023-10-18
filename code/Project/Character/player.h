//================================================================================================
//
//プレイヤー処理[player.h]
//Author:Hirasawa Shion
//
//================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//前方宣言
class CStageObject;

//プレイヤークラス
class CPlayer
{
public:
	//表裏どちらの世界に存在するか
	enum class WORLD_SIDE	{
		FACE = 0,	//表
		BEHIND,		//裏
		MAX,
	};

	//当たり判定の順番列挙
	enum class COLLI_VEC {
		X = 0,	//Ⅹベクトル
		Y,		//Ｙベクトル
		MAX
	};

	//プレイヤー情報
	struct Info
	{
		D3DXVECTOR3 pos;			//位置
		D3DXVECTOR3 posOLd;			//前回位置
		D3DXVECTOR3 rot;			//向き
		D3DXVECTOR3 move;			//移動量
		bool		bJump;			//ジャンプ
		float		fJumpPower;		//ジャンプ量
		float		fGravity;		//重力
		float		fGravityCorr;	//重力係数
		int			nModelIdx;		//モデル番号
		WORLD_SIDE  side;			//どちらの世界に存在するか
	};

	static const float SIZE_WIDTH;	//横幅
	static const float SIZE_HEIGHT;	//高さ

	static const int SWAP_INTERVAL;	//スワップインターバル
	static const int NUM_PLAYER = 2;//プレイヤーの数

	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//----------------------------
	//プレイヤー生成
	//プレイヤーのポインタを返します
	//----------------------------
	static CPlayer *Create(void);

	//----------------------------
	//プレイヤー情報設定
	//各プレイヤーの位置情報などを引数に渡してください。
	//構造体「Info」に関してはplayer.hのクラス宣言を確認してください。
	//----------------------------
	void SetInfo(Info p1, Info p2);

	// 位置設定
	void SetPos(int idx, D3DXVECTOR3 pos) { m_aInfo[idx].pos = pos; }

	//----------------------------
	//プレイヤー情報取得
	//関数を呼ぶ前にInfo構造体を二人分宣言し、
	//順番に引数に入れてください。
	//引数は参照型なので、引数に入れるだけで情報が代入されます。
	//----------------------------
	void GetInfo(Info& rP1, Info& rP2) { rP1 = m_aInfo[0]; rP2 = m_aInfo[1]; }
	
private:
	static int	s_nSwapInterval;//残りスワップインターバル

	static const float MOVE_SPEED;		//移動量
	static const float MAX_MOVE_SPEED;	//最大移動量

	static const float JUMP_POWER;		//基本ジャンプ量
	static const float GRAVITY_POWER;	//基本重力加速度
	static const float GRAVITY_CORR;	//基本重力係数

	void SetPosOld(void);
	void ActionControl(void);
	void Move(COLLI_VEC vec);
	void Swap(void);

	void WholeCollision(void);
	void CollisionBlock(CStageObject *pObj, COLLI_VEC value);

	Info m_aInfo[NUM_PLAYER];	//各プレイヤーの情報
};

#endif