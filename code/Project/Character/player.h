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

	//当たり判定が働いた方向
	enum class COLLI_ROT {
		NONE = 0,	//何もなし
		OVER,		//上
		UNDER,		//下
		LEFT,		//左
		RIGHT,		//右
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
	//プレイヤー情報の初期化処理
	//プレイヤー情報を初期状態を返します
	//----------------------------
	Info FormatInfo(void);

	//----------------------------
	//プレイヤー情報設定
	//各プレイヤーの位置情報などを引数に渡してください。
	//構造体「Info」に関してはplayer.hのクラス宣言を確認してください。
	//----------------------------
	void SetInfo(Info p1, Info p2);

	//----------------------------
	//プレイヤー情報設定
	//指定された番号のプレイヤー情報を設定します。
	//----------------------------
	void SetInfo(const Info info, const int nNum);

	// 位置設定
	void SetPos(int idx, D3DXVECTOR3 pos) { m_aInfo[idx].pos = pos; }

	//----------------------------
	//プレイヤー情報取得
	//各引数にプレイヤー情報のアドレスを渡します
	//----------------------------
	void GetInfo(Info *pP1, Info *pP2) { pP1 = &m_aInfo[0]; pP2 = &m_aInfo[1]; }
	
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