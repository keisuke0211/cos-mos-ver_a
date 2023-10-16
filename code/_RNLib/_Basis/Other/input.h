//========================================
// 
// 入力関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ input.h ]]]
//========================================
#ifndef _INPUT_H_
#define _INPUT_H_

//****************************************
// クラス定義
//****************************************
// 入力クラス
class CInput {
public:
	//========== [[[ 定数定義 ]]]
	static const int NUM_KEY_MAX = 256;

	//========== [[[ 列挙型の定義 ]]]
	// 動的なデバイス
	typedef enum {
		ACTIVE_DEVICE_KEYBOARD,
		ACTIVE_DEVICE_CONTROLLER,
		ACTIVE_DEVICE_MAX,
	}ACTIVE_DEVICE_TYPE;

	// 入力方向
	typedef enum {
		INPUT_ANGLE_UP,
		INPUT_ANGLE_DOWN,
		INPUT_ANGLE_LEFT,
		INPUT_ANGLE_RIGHT,
		INPUT_ANGLE_MAX,
	}INPUT_ANGLE;

	// 入力番号
	typedef enum {
		MOUSEBUTTON_LEFT,
		MOUSEBUTTON_RIGHT,
		MOUSEBUTTON_MAX,
	}MOUSEBUTTON;
	typedef enum {
		BUTTON_UP,				// 上キー
		BUTTON_DOWN,			// 下キー
		BUTTON_LEFT,			// 左キー
		BUTTON_RIGHT,			// 右キー
		BUTTON_START,			// スタートキー
		BUTTON_BACK,			// バックキー
		BUTTON_LEFT_THUMB,		// 左スティック
		BUTTON_RIGHT_THUMB,		// 右スティック
		BUTTON_LEFT_SHOULDER,	// 左トリガー
		BUTTON_RIGHT_SHOULDER,	// 右トリガー
		BUTTON_A,				// Aボタン
		BUTTON_B,				// Bボタン
		BUTTON_X,				// Xボタン
		BUTTON_Y,				// Yボタン
		BUTTON_LEFT_TRIGGER,	// 左トリガー
		BUTTON_RIGHT_TRIGGER,	// 右トリガー
		BUTTON_MAX,
	}BUTTON;
	typedef enum {
		STICK_LEFT,
		STICK_RIGHT,
		STICK_MAX,
	}STICK;

	// マウスホイールの回転状態
	typedef enum {
		WHEELSPIN_NONE,		// 無し
		WHEELSPIN_FRONT,	// 前回転
		WHEELSPIN_BACK,		// 後回転
	}WHEELSPIN;

	//========== [[[ 構造体の定義 ]]]
	// スティックの入力情報構造体
	typedef struct {
		float fTiltRate;	// 倒し具合
		float fTiltAngle;	// 倒れ角度
		BYTE  aAnglePress       [INPUT_ANGLE_MAX];	// 方向プレス情報
		BYTE  aAngleTrigger     [INPUT_ANGLE_MAX];	// 方向トリガー情報
		BYTE  aAngleRepeat      [INPUT_ANGLE_MAX];	// 方向リピート情報
		BYTE  aAngleRelease     [INPUT_ANGLE_MAX];	// 方向リリース情報
		DWORD aStickCurrentTime [INPUT_ANGLE_MAX];	// 現在時間
		DWORD aStickExecLastTime[INPUT_ANGLE_MAX];	// 最後時間
	}StickInput;

	//========== [[[ 関数宣言 ]]]
	CInput();
	~CInput();
	HRESULT Init(HINSTANCE hInstance);
	void  Uninit(void);
	void  Update(void);
	void  Clear(void);
	void  SetVibration(float fVibration, int nTime);
	float GetMoveAngle(float* pRate = NULL);
	float GetLeftAngle(float* pRate = NULL);
	bool  GetAngleTrigger     (INPUT_ANGLE angle);
	bool  GetLeftAngleTrigger (INPUT_ANGLE angle);
	bool  GetRightAngleTrigger(INPUT_ANGLE angle);
	float GetRightAngle(float* pRate);
	bool  GetDecide(void);
	void  FixedCursor(bool bFixed) {// カーソル固定
		m_bFixedCursor = bFixed; 
		ShowCursor(!bFixed);
	}
	bool  GetPause(void) { return (KeyTrigger(DIK_P) || ButtonTrigger(BUTTON_START)); }
	// 取得
	XINPUT_STATE*      GetXInputState(void)     { return &m_xInputState; }
	D3DXVECTOR2        GetCursorPosOnScreen(void);
	D3DXVECTOR2        GetCursorMove(void)      { return m_cursorMove; }
	StickInput         GetStick(STICK stick)    { return m_aStick[stick]; }
	ACTIVE_DEVICE_TYPE GetActiveInputType(void) { return m_activeInputType; }
	// キーボード
	bool KeyPress  (int nKey) { return m_aKeyPress  [nKey] != 0; }
	bool KeyTrigger(int nKey) { return m_aKeyTrigger[nKey] != 0; }
	bool KeyRepeat (int nKey) { return m_aKeyRepeat [nKey] != 0; }
	bool KeyRelease(int nKey) { return m_aKeyRelease[nKey] != 0; }
	// マウス
	bool MousePress  (MOUSEBUTTON btn) { return m_aMousePress  [btn] != 0;  }
	bool MouseTrigger(MOUSEBUTTON btn) { return m_aMouseTrigger[btn] != 0;  }
	bool MouseRepeat (MOUSEBUTTON btn) { return m_aMouseRepeat [btn] != 0;  }
	bool MouseRelease(MOUSEBUTTON btn) { return m_aMouseRelease[btn] != 0;  }
	WHEELSPIN WheelSpin(void)          { return m_wheelSpin; }
	// ボタン
	bool ButtonPress  (int nButton) { return m_aButtonPress  [nButton] != 0; }
	bool ButtonTrigger(int nButton) { return m_aButtonTrigger[nButton] != 0; }
	bool ButtonRepeat (int nButton) { return m_aButtonRepeat [nButton] != 0; }
	bool ButtonRelease(int nButton) { return m_aButtonRelease[nButton] != 0; }
	// スティック
	float StickTiltRate    (STICK stick) { return m_aStick[stick].fTiltRate; }
	float StickTiltAngle   (STICK stick) { return m_aStick[stick].fTiltAngle; }
	bool  StickAnglePress  (STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAnglePress  [angle] != 0; }
	bool  StickAngleTrigger(STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAngleTrigger[angle] != 0; }
	bool  StickAngleRepeat (STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAngleRepeat [angle] != 0; }
	bool  StickAngleRelease(STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAngleRelease[angle] != 0; }
	// 設定
	void SetWheelSpin(WHEELSPIN wheelSpin) { m_wheelSpin = wheelSpin; }

private:
	//========== [[[ 定数宣言 ]]]
	static const int m_aMouseMask[MOUSEBUTTON_MAX];
	static const int m_aButtonMask[BUTTON_MAX];

	//========== [[[ 変数宣言 ]]]
	//----------キーボード----------
	/* プレス情報   */BYTE m_aKeyPress    [NUM_KEY_MAX];
	/* トリガー情報 */BYTE m_aKeyTrigger  [NUM_KEY_MAX];
	/* リリース情報 */BYTE m_aKeyRelease  [NUM_KEY_MAX];
	/* リピート情報 */BYTE m_aKeyRepeat   [NUM_KEY_MAX];
	/* 現在の時間   */DWORD m_aKeyCurrentTime  [NUM_KEY_MAX];
	/* 最後の時間   */DWORD m_aKeyExecLastTime [NUM_KEY_MAX];
	//----------マウス----------
	/* プレス情報       */BYTE  m_aMousePress   [MOUSEBUTTON_MAX];
	/* トリガー情報     */BYTE  m_aMouseTrigger [MOUSEBUTTON_MAX];
	/* リリース情報     */BYTE  m_aMouseRelease [MOUSEBUTTON_MAX];
	/* リピート情報     */BYTE  m_aMouseRepeat  [MOUSEBUTTON_MAX];
	/* 現在の時間       */DWORD m_aMouseCurrentTime  [MOUSEBUTTON_MAX];
	/* 最後の時間       */DWORD m_aMouseExecLastTime [MOUSEBUTTON_MAX];
	/* カーソル位置     */D3DXVECTOR2 m_cursorPos;
	/* カーソル移動量   */D3DXVECTOR2 m_cursorMove;
	/* ホイール回転状態 */WHEELSPIN m_wheelSpin;
	//----------コントローラー----------
	/* プレス情報        */BYTE  m_aButtonPress        [BUTTON_MAX];
	/* トリガー情報      */BYTE  m_aButtonTrigger      [BUTTON_MAX];
	/* リリース情報      */BYTE  m_aButtonRelease      [BUTTON_MAX];
	/* リピート情報      */BYTE  m_aButtonRepeat       [BUTTON_MAX];
	/* 現在の時間        */DWORD m_aButtonCurrentTime  [BUTTON_MAX];
	/* 最後の時間        */DWORD m_aButtonExecLastTime [BUTTON_MAX];
	/* スティック情報    */StickInput m_aStick[STICK_MAX];
	/* 振動カウンター    */int m_nCounterVibration;
	/* 振動カウンターMAX */int m_nCounterVibrationMax;
	/* 振動倍率          */float m_fVibration;
	/* XInputの状態      */XINPUT_STATE m_xInputState;

	//========== [[[ 変数宣言 ]]]
	LPDIRECTINPUT8       m_pInput;			// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;	// 入力デバイス(キーボード)へのポインタ
	ACTIVE_DEVICE_TYPE   m_activeInputType;	// 動的なデバイス
	bool                 m_bFixedCursor;	// カーソル固定フラグ

	//========== [[[ 関数宣言 ]]]
	void UpdateKeyboard(void);
	void UpdateMouse(void);
	void UpdateCursor(void);
	void UpdateButton(void);
	void UpdateStick(void);
	void UpdateController(void);
};

#endif