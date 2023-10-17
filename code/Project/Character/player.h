//================================================================================================
//
//プレイヤー処理[player.h]
//Author:Hirasawa Shion
//
//================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//プレイヤークラス
class CPlayer
{
public:
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
	};

	static const int SWAP_INTERVAL;	//スワップインターバル
	static const int NUM_PLAYER = 2;//プレイヤーの数

	static const float UPPER_GROUND;	//上の世界の足場位置
	static const float DOWNER_GROUND;	//下の世界の足場位置

	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

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

private:
	static bool	s_bSwap;		//スワップしたかどうか
	static int	s_nSwapInterval;//残りスワップインターバル

	static const float MOVE_SPEED;		//移動量
	static const float MAX_MOVE_SPEED;	//最大移動量

	static const float JUMP_POWER;		//基本ジャンプ量
	static const float GRAVITY_POWER;	//基本重力加速度
	static const float GRAVITY_CORR;	//基本重力係数

	void SetPosOld(void);
	void ActionControl(void);
	void Move(void);

	Info m_aInfo[NUM_PLAYER];	//各プレイヤーの情報
};

#endif