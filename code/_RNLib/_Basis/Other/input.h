//========================================
// 
// 入力クラスの処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// クラス定義
//****************************************
// 入力クラス
class CInput {
public:
	//========== [[[ 定数定義 ]]]
	static const int NUM_KEY_MAX = 256;

	//========== [[[ 列挙型の定義 ]]]
	enum class ACTIVE_DEVICE { KEYBOARD, CONTROLLER, MAX, };
	enum class INPUT_ANGLE { UP, DOWN, LEFT, RIGHT, MAX, };
	enum class MOUSEBUTTON { LEFT, RIGHT, MAX, };
	enum class BUTTON { UP, DOWN, LEFT, RIGHT, START, BACK, LEFT_THUMB, RIGHT_THUMB, LEFT_SHOULDER, RIGHT_SHOULDER, A, B, X, Y, LEFT_TRIGGER, RIGHT_TRIGGER, MAX, };
	enum class STICK { LEFT, RIGHT, MAX, };
	enum class WHEELSPIN { NONE, FRONT, BACK, };

	//========== [[[ 構造体の定義 ]]]
	// スティックの入力情報構造体
	typedef struct {
		float fTiltRate;	// 倒し具合
		float fTiltAngle;	// 倒れ角度
		BYTE  aAnglePress[(int)INPUT_ANGLE::MAX];	// 方向プレス情報
		BYTE  aAngleTrigger[(int)INPUT_ANGLE::MAX];	// 方向トリガー情報
		BYTE  aAngleRepeat[(int)INPUT_ANGLE::MAX];	// 方向リピート情報
		BYTE  aAngleRelease[(int)INPUT_ANGLE::MAX];	// 方向リリース情報
		DWORD aStickCurrentTime[(int)INPUT_ANGLE::MAX];	// 現在時間
		DWORD aStickExecLastTime[(int)INPUT_ANGLE::MAX];	// 最後時間
	}StickInput;

	//========== [[[ 関数宣言 ]]]
	CInput();
	~CInput();
	void  Init(HINSTANCE hInstance);
	void  Uninit(void);
	void  Update(void);
	void  Clear(void);

	void  SetVibration(float fVibration, int nTime);
	float GetMoveAngle(float* pRate = NULL);
	float GetLeftAngle(float* pRate = NULL);
	bool  GetAngleTrigger(INPUT_ANGLE angle);
	bool  GetLeftAngleTrigger(INPUT_ANGLE angle);
	bool  GetRightAngleTrigger(INPUT_ANGLE angle);
	float GetRightAngle(float* pRate);
	bool  GetDecide(void);
	void  FixedCursor(bool bFixed) {// カーソル固定
		m_bFixedCursor = bFixed;
		ShowCursor(!bFixed);
	}
	bool  GetPause(void) { return (KeyTrigger(DIK_P) || ButtonTrigger((int)BUTTON::START)); }
	// 取得
	XINPUT_STATE* GetXInputState(void) { return &m_xInputState; }
	D3DXVECTOR2        GetCursorPosOnScreen(void);
	D3DXVECTOR2        GetCursorMove(void) { return m_cursorInfo.move; }
	StickInput         GetStick(STICK stick) { return m_aStick[(int)stick]; }
	ACTIVE_DEVICE GetActiveInputType(void) { return m_activeInputType; }
	// 統合
	bool Press(int nKey, int nButton) { return KeyPress(nKey) || ButtonPress(nButton); }
	bool Trigger(int nKey, int nButton) { return KeyTrigger(nKey) || ButtonTrigger(nButton); }
	bool Release(int nKey, int nButton) { return KeyRelease(nKey) || ButtonRelease(nButton); }
	// キーボード
	bool KeyPress(int nKey) { return m_keyInputs[nKey].press != 0; }
	bool KeyTrigger(int nKey) { return m_keyInputs[nKey].trigger != 0; }
	bool KeyRelease(int nKey) { return m_keyInputs[nKey].release != 0; }
	// マウス
	bool MousePress(MOUSEBUTTON btn) { return m_mouseButtonInputs[(int)btn].press != 0; }
	bool MouseTrigger(MOUSEBUTTON btn) { return m_mouseButtonInputs[(int)btn].trigger != 0; }
	bool MouseRelease(MOUSEBUTTON btn) { return m_mouseButtonInputs[(int)btn].release != 0; }
	WHEELSPIN WheelSpin(void) { return m_wheelSpin; }
	// ボタン
	bool ButtonPress(int nButton) { return m_aButtonPress[nButton] != 0; }
	bool ButtonTrigger(int nButton) { return m_aButtonTrigger[nButton] != 0; }
	bool ButtonRepeat(int nButton) { return m_aButtonRepeat[nButton] != 0; }
	bool ButtonRelease(int nButton) { return m_aButtonRelease[nButton] != 0; }
	// スティック
	float StickTiltRate(STICK stick) { return m_aStick[(int)stick].fTiltRate; }
	float StickTiltAngle(STICK stick) { return m_aStick[(int)stick].fTiltAngle; }
	bool  StickAnglePress(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAnglePress[(int)angle] != 0; }
	bool  StickAngleTrigger(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAngleTrigger[(int)angle] != 0; }
	bool  StickAngleRepeat(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAngleRepeat[(int)angle] != 0; }
	bool  StickAngleRelease(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAngleRelease[(int)angle] != 0; }
	// 設定
	void SetWheelSpin(WHEELSPIN wheelSpin) { m_wheelSpin = wheelSpin; }

private:
	//========== [[[ 定数宣言 ]]]
	static const int m_aMouseMask[(int)MOUSEBUTTON::MAX];
	static const int m_aButtonMask[(int)BUTTON::MAX];

	//========== [[[ 構造体定義 ]]]
	struct Input {
		BYTE press = 0;
		BYTE trigger = 0;
		BYTE release = 0;
	};
	struct CursorInfo {
		D3DXVECTOR2 pos = INITD3DXVECTOR2;
		D3DXVECTOR2 move = INITD3DXVECTOR2;
	};

	//========== [[[ 関数宣言 ]]]
	void UpdateKeyboard(void);
	void UpdateMouseButton(void);
	void UpdateCursor(void);
	void UpdateButton(void);
	void UpdateStick(void);
	void UpdateController(void);

	//========== [[[ 変数宣言 ]]]
	Input m_keyInputs[NUM_KEY_MAX];
	Input m_mouseButtonInputs[(int)MOUSEBUTTON::MAX];
	CursorInfo m_cursorInfo;
	WHEELSPIN m_wheelSpin;

	//----------コントローラー----------
	/* プレス情報        */BYTE  m_aButtonPress[(int)BUTTON::MAX];
	/* トリガー情報      */BYTE  m_aButtonTrigger[(int)BUTTON::MAX];
	/* リリース情報      */BYTE  m_aButtonRelease[(int)BUTTON::MAX];
	/* リピート情報      */BYTE  m_aButtonRepeat[(int)BUTTON::MAX];
	/* 現在の時間        */DWORD m_aButtonCurrentTime[(int)BUTTON::MAX];
	/* 最後の時間        */DWORD m_aButtonExecLastTime[(int)BUTTON::MAX];
	/* スティック情報    */StickInput m_aStick[(int)STICK::MAX];
	/* 振動カウンター    */int m_nCounterVibration;
	/* 振動カウンターMAX */int m_nCounterVibrationMax;
	/* 振動倍率          */float m_fVibration;
	/* XInputの状態      */XINPUT_STATE m_xInputState;

	//========== [[[ 変数宣言 ]]]
	LPDIRECTINPUT8       m_inputDevice;			// DirectInputオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;	// 入力デバイス(キーボード)へのポインタ
	ACTIVE_DEVICE        m_activeInputType;	// 動的なデバイス
	bool                 m_bFixedCursor;	// カーソル固定フラグ
};