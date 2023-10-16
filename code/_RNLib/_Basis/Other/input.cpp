//========================================
// 
// 入力関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
#define REPEATE_INTERVAL   (60)
#define VIBRATION_SUBTRACT (0.02f)
#define CURSOR_DIST_BASE   (10.0f)

//****************************************
// 静的メンバ定数宣言
//****************************************
// マウスのマスク
const int CInput::m_aMouseMask[MOUSEBUTTON_MAX] = {
	VK_LBUTTON,
	VK_RBUTTON,
};

// ボタンのマスク
const int CInput::m_aButtonMask[BUTTON_MAX] = {
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	-1,
	-1,
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CInput関数のメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
//========================================
CInput::CInput() {

}

//========================================
// デストラクタ
//========================================
CInput::~CInput() {
	
}

//========================================
// キーボードの更新処理
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateKeyboard(void) {
	// キーボードの入力情報
	BYTE m_aKey[NUM_KEY_MAX];

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(m_aKey), &m_aKey[0]))) {
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) {
			// キーボードのトリガー情報を保存
			m_aKeyTrigger[nCntKey] = (m_aKeyPress[nCntKey] ^ m_aKey[nCntKey])&m_aKey[nCntKey];

			// キーボードのリリース情報を保存
			m_aKeyRelease[nCntKey] = (m_aKeyPress[nCntKey] ^ m_aKey[nCntKey])&~m_aKey[nCntKey];

			// 現在の時間を取得
			m_aKeyCurrentTime[nCntKey] = timeGetTime();

			if (m_aKey[nCntKey] && ((m_aKeyCurrentTime[nCntKey] - m_aKeyExecLastTime[nCntKey]) > REPEATE_INTERVAL))
			{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
				// 最後に真を返した時間を保存
				m_aKeyExecLastTime[nCntKey] = m_aKeyCurrentTime[nCntKey];

				// キーボードのリピート情報を保存
				m_aKeyRepeat[nCntKey] = m_aKey[nCntKey];
			}
			else {
				// キーボードのリピート情報を保存
				m_aKeyRepeat[nCntKey] = 0;
			}

			// キーボードのプレス情報を保存
			m_aKeyPress[nCntKey] = m_aKey[nCntKey];

			if (m_aKey[nCntKey])
			{// 入力が行われた時、
				// 動的なデバイスをキーボードにする
				m_activeInputType = ACTIVE_DEVICE_KEYBOARD;
			}
		}
	}
	else
	{// 入力デバイスからデータを取得できなかった時、
		// キーボードへのアクセス権を取得
		m_pDevKeyboard->Acquire();
	}
}

//========================================
// UpdateMouse関数 - マウスの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateMouse(void) {
	// 画面にフォーカスが当たっているかどうか調べる
	bool bWindowFocused = RNLib::Window()->FindFocused(RNLib::Window()->GetHandle());

	for (int nCntMouse = 0; nCntMouse < MOUSEBUTTON_MAX; nCntMouse++) {
		// マウスの入力情報
		BYTE mouseState = GetKeyState(m_aMouseMask[nCntMouse]) & (0x80) ? true : false;
		
		if (!bWindowFocused) 
		{// 画面にフォーカスが当たっていない時、
			mouseState = false;	// 入力を偽にする
		}

		// マウスのトリガー情報を保存
		m_aMouseTrigger[nCntMouse] = (m_aMousePress[nCntMouse] ^ mouseState)&mouseState;

		// マウスのリリース情報を保存
		m_aMouseRelease[nCntMouse] = (m_aMousePress[nCntMouse] ^ mouseState)&~mouseState;

		// 現在の時間を取得
		m_aMouseCurrentTime[nCntMouse] = timeGetTime();

		if (mouseState && ((m_aMouseCurrentTime[nCntMouse] - m_aMouseExecLastTime[nCntMouse]) > REPEATE_INTERVAL))
		{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
			// 最後に真を返した時間を保存
			m_aMouseExecLastTime[nCntMouse] = m_aMouseCurrentTime[nCntMouse];

			// マウスのリピート情報を保存
			m_aMouseRepeat[nCntMouse] = mouseState;
		}
		else
		{// キーが入力されていない、もしくは現在の時間と最後に真を返した時間の差がリピートの間隔を越えていない時、
			// マウスのリピート情報を保存
			m_aMouseRepeat[nCntMouse] = 0;
		}

		// マウスのプレス情報を保存
		m_aMousePress[nCntMouse] = mouseState;

		if (mouseState)
		{// 入力が行われた時、
			// 動的なデバイスをキーボードにする
			m_activeInputType = ACTIVE_DEVICE_KEYBOARD;
		}
	}
}

//========================================
// UpdateCursor関数 - カーソルの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateCursor(void) {
	// カーソルの画面上の位置を取得
	D3DXVECTOR2 cursorPos = GetCursorPosOnScreen();

	if (m_cursorPos != cursorPos)
	{// カーソルの現在位置が保存位置を異なる時、
		// 動的なデバイスをキーボードにする
		m_activeInputType = ACTIVE_DEVICE_KEYBOARD;
	}

	// カーソルの移動量を設定
	m_cursorMove = cursorPos - m_cursorPos;

	if (m_bFixedCursor) {
		// クライアント領域のサイズを取得
		RECT rc;
		GetClientRect(RNLib::Window()->GetHandle(), &rc);

		// マウス座標の設定
		SetCursorPos(rc.right * 0.5f, rc.bottom * 0.5f);

		// カーソル位置を保存
		m_cursorPos = GetCursorPosOnScreen();
	}
	else {
		// カーソル位置を保存
		m_cursorPos = cursorPos;
	}
}

//========================================
// UpdateButton関数 - ボタンの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateButton(void) {
	// ボタンの入力情報
	BYTE m_aButton[BUTTON_MAX] = {};

	for (int nCntButton = 0; nCntButton < BUTTON_MAX; nCntButton++) {
		if (nCntButton == BUTTON_LEFT_TRIGGER)
		{// カウントが左トリガーの時、
			if (GetXInputState()->Gamepad.bLeftTrigger > 0)
			{// 押し込まれている
				m_aButton[nCntButton] = true;
			}
		}
		else if (nCntButton == BUTTON_RIGHT_TRIGGER)
		{// カウントが右トリガーの時、
			if (GetXInputState()->Gamepad.bRightTrigger > 0)
			{// 押し込まれている
				m_aButton[nCntButton] = true;
			}
		}
		else if (GetXInputState()->Gamepad.wButtons & m_aButtonMask[nCntButton])
		{// 入力情報を更新
			m_aButton[nCntButton] = true;
		}

		// ボタンのトリガー情報を保存
		m_aButtonTrigger[nCntButton] = (m_aButtonPress[nCntButton] ^ m_aButton[nCntButton])&m_aButton[nCntButton];

		// ボタンのリリース情報を保存
		m_aButtonRelease[nCntButton] = (m_aButtonPress[nCntButton] ^ m_aButton[nCntButton])&~m_aButton[nCntButton];

		// 現在の時間を取得
		m_aButtonCurrentTime[nCntButton] = timeGetTime();

		if (m_aButton[nCntButton] && ((m_aButtonCurrentTime[nCntButton] - m_aButtonExecLastTime[nCntButton]) > REPEATE_INTERVAL))
		{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
			// 最後に真を返した時間を保存
			m_aButtonExecLastTime[nCntButton] = m_aButtonCurrentTime[nCntButton];

			// ボタンのリピート情報を保存
			m_aButtonRepeat[nCntButton] = m_aButton[nCntButton];
		}
		else {
			// ボタンのリピート情報を保存
			m_aButtonRepeat[nCntButton] = 0;
		}

		// ボタンのプレス情報を保存
		m_aButtonPress[nCntButton] = m_aButton[nCntButton];

		if (m_aButton[nCntButton])
		{// 入力が行われた時、
			// 動的なデバイスをコントローラーにする
			m_activeInputType = ACTIVE_DEVICE_CONTROLLER;
		}
	}
}

//========================================
// UpdateStick関数 - スティックの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateStick(void) {
	// スティックの入力情報
	BYTE aAngle[INPUT_ANGLE_MAX];

	// XInputの状態を取得
	m_xInputState.dwPacketNumber = XInputGetState(m_xInputState.dwPacketNumber, &m_xInputState);

	for (int nCntStick = 0; nCntStick < STICK_MAX; nCntStick++) {
		float X;	// スティックのX軸
		float Y;	// スティックのY軸

		// 種類に応じたスティックの軸の値を取得
		switch (nCntStick) {
		case STICK_LEFT:
			X = GetXInputState()->Gamepad.sThumbLX;
			Y = GetXInputState()->Gamepad.sThumbLY;
			break;
		case STICK_RIGHT:
			X = GetXInputState()->Gamepad.sThumbRX;
			Y = GetXInputState()->Gamepad.sThumbRY;
			break;
		default:
			assert(false);
			X = 0.0f;
			Y = 0.0f;
			break;
		}

		// 角度を取得
		m_aStick[nCntStick].fTiltAngle = Find_Angle_LookFront(D3DXVECTOR3(X, Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

		// スティックの倒し具合を取得
		m_aStick[nCntStick].fTiltRate = fabsf(X);
		if (m_aStick[nCntStick].fTiltRate < fabsf(Y)) {
			m_aStick[nCntStick].fTiltRate = fabsf(Y);
		}
		m_aStick[nCntStick].fTiltRate /= 32768.0f;

		// 方向入力フラグを初期化
		for (int nCntAngle = 0; nCntAngle < INPUT_ANGLE_MAX; nCntAngle++) {
			aAngle[nCntAngle] = false;
		}

		if (m_aStick[nCntStick].fTiltRate > 0)
		{// スティックが倒されている時、
			// 動的なデバイスをコントローラーにする
			m_activeInputType = ACTIVE_DEVICE_CONTROLLER;

			if (false) {}
			else if ((m_aStick[nCntStick].fTiltAngle < D3DX_PI * -0.75)
				  || (m_aStick[nCntStick].fTiltAngle > D3DX_PI * 0.75))
			{// 角度が四分割で上に位置する時、上フラグを真にする
				aAngle[INPUT_ANGLE_UP] = true;
			}
			else if ((m_aStick[nCntStick].fTiltAngle > D3DX_PI * -0.25)
				  && (m_aStick[nCntStick].fTiltAngle < D3DX_PI * 0.25))
			{// 角度が四分割で下に位置する時、下フラグを真にする
				aAngle[INPUT_ANGLE_DOWN] = true;
			}
			else if ((m_aStick[nCntStick].fTiltAngle > D3DX_PI * -0.75)
				  && (m_aStick[nCntStick].fTiltAngle < D3DX_PI * -0.25))
			{// 角度が四分割で左に位置する時、左フラグを真にする
				aAngle[INPUT_ANGLE_LEFT] = true;
			}
			else if ((m_aStick[nCntStick].fTiltAngle > D3DX_PI * 0.25)
				  && (m_aStick[nCntStick].fTiltAngle < D3DX_PI * 0.75))
			{// 角度が四分割で右に位置する時、右フラグを真にする
				aAngle[INPUT_ANGLE_RIGHT] = true;
			}
		}

		for (int nCntAngle = 0; nCntAngle < INPUT_ANGLE_MAX; nCntAngle++) {
			// スティックのトリガー情報を保存
			m_aStick[nCntStick].aAngleTrigger[nCntAngle] = (m_aStick[nCntStick].aAnglePress[nCntAngle] ^ aAngle[nCntAngle])&aAngle[nCntAngle];

			// スティックのリリース情報を保存
			m_aStick[nCntStick].aAngleRelease[nCntAngle] = (m_aStick[nCntStick].aAnglePress[nCntAngle] ^ aAngle[nCntAngle])&~aAngle[nCntAngle];

			// 現在の時間を取得
			m_aStick[nCntStick].aStickCurrentTime[nCntAngle] = timeGetTime();

			if (aAngle[nCntAngle] && ((m_aStick[nCntStick].aStickCurrentTime[nCntAngle] - m_aStick[nCntStick].aStickExecLastTime[nCntAngle]) > REPEATE_INTERVAL))
			{// キーが入力されていて、かつ現在の時間と最後に真を返した時間の差がリピートの間隔を越えていた時、
				// 最後に真を返した時間を保存
				m_aStick[nCntStick].aStickExecLastTime[nCntAngle] = m_aStick[nCntStick].aStickCurrentTime[nCntAngle];

				// スティックのリピート情報を保存
				m_aStick[nCntStick].aAngleRepeat[nCntAngle] = aAngle[nCntAngle];
			}
			else {
				// スティックのリピート情報を保存
				m_aStick[nCntStick].aAngleRepeat[nCntAngle] = 0;
			}

			// スティックのプレス情報を保存
			m_aStick[nCntStick].aAnglePress[nCntAngle] = aAngle[nCntAngle];

			if (aAngle[nCntAngle])
			{// 入力が行われた時、
				// 動的なデバイスをコントローラーにする
				m_activeInputType = ACTIVE_DEVICE_CONTROLLER;
			}
		}
	}
}

//========================================
// UpdateVibration関数 - コントローラーの振動更新処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateController(void) {
	if (m_fVibration > 0)
	{// 振動倍率が0を上回っている時、
		// 振動倍率を減算
		m_fVibration -= VIBRATION_SUBTRACT;

		// 振動倍率を制御
		FloatControl(&m_fVibration, 1.0f, 0);

		{// 振動フラグが真の時、
			XINPUT_STATE state;			//XINPUT_STATE型 stateを作成
			XInputGetState(0, &state);	//stateに習得したコントローラの状態を格納
			XINPUT_VIBRATION vibration;	//XINPUT_VIBRATION vibrationを作成

			//vibrationメンバーwLeftMotorSpeedに値を代入 モータースピード100%
			vibration.wLeftMotorSpeed = 65535 * m_fVibration;

			//vibrationメンバーwRightMotorSpeedに値を代入 モータースピード0%
			vibration.wRightMotorSpeed = 65535 * m_fVibration;

			//ジョイスティックにバイブレーターデータを送信
			XInputSetState(0, &vibration);
		}
	}
}

//========================================
// InitInput関数 - 入力関連の初期化処理 -
// Author:RIKU NISHIMURA
//========================================
HRESULT CInput::Init(HINSTANCE hInstance) {
	// マウスカーソルを表示
	//(※最初からtrueだと、後から要求を無視される為一度falseにしてからtrueにする)
	ShowCursor(false);
	ShowCursor(true);

	// 入力情報をクリア
	Clear();

	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
		return E_FAIL;
	}
	
	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL))) {
		return E_FAIL;
	}
	
	// データフォーマットを設定
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
		return E_FAIL;
	}

	// 協調フォーマット
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(RNLib::Window()->GetHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) {
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//========================================
// UninitInput関数 - 入力関連の終了処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::Uninit(void) {
	// XInputを閉じる
	XInputEnable(false);

	// 入力デバイス(キーボード)の破棄
	if (m_pDevKeyboard != NULL) {
		m_pDevKeyboard->Unacquire();	// キーボードへのアクセス権を放棄
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// DirectInputオブジェクトの破棄
	if (m_pInput != NULL) {
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//========================================
// UpdateInput関数 - 入力関連の更新処理 -
// Author:RIKU NISHIMURA
//========================================
void CInput::Update(void) {
	UpdateKeyboard();	// キーボード
	UpdateButton();		// ボタン
	UpdateCursor();		// カーソル
	UpdateMouse();		// マウス
	UpdateStick();		// スティック
	UpdateController();	// コントローラーの振動
}

//========================================
// GetCursorPosOnScreen関数 - 画面上のカーソルの位置を取得 -
// Author:RIKU NISHIMURA
//=======================================
D3DXVECTOR2 CInput::GetCursorPosOnScreen(void) {
	// カーソルの現在位置を取得
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// クライアント領域のサイズを取得
	RECT rc;
	GetClientRect(RNLib::Window()->GetHandle(), &rc);

	D3DXVECTOR3 windowPos = RNLib::Window()->GetPos();	// ウィンドウの位置

	return D3DXVECTOR2(
		(cursorPos.x - windowPos.x) * (RNLib::Window()->GetWidth () / (float)rc.right),
		(cursorPos.y - windowPos.y) * (RNLib::Window()->GetHeight() / (float)rc.bottom));
}

//========================================
// コントローラーの振動設定処理
// Author:RIKU NISHIMURA
//========================================
void CInput::SetVibration(float fVibration, int nTime) {
	if (m_activeInputType != ACTIVE_DEVICE_CONTROLLER) 
	{// 動的なデバイスがコントローラーで無い時、
		// 処理を終了
		return;
	}

	if (fVibration > fVibration)
	{// 振動倍率が元の振動倍率を上回っている時、
		// 振動倍率を代入
		fVibration = fVibration;
	}

	// 振動倍率を制御
	FloatControl(&fVibration, 1.0f, 0);
}

//========================================
// 移動角度取得
// Author:RIKU NISHIMURA
//========================================
float CInput::GetMoveAngle(float *pRate) {
	float fAngle = GetLeftAngle(pRate) + RNLib::Camera3D()->GetRot().y;
	Limit_Angle(&fAngle);
	return fAngle;
}

//========================================
// 左入力角度取得
// Author:RIKU NISHIMURA
//========================================
float CInput::GetLeftAngle(float *pRate) {
	float fMoveAngle = 0.0f;
	if (pRate != NULL)
		*pRate = 1.0f;

	if          (KeyPress(DIK_W)) {
		if      (KeyPress(DIK_A)) { fMoveAngle = ANGLE_UP_LEFT; }
		else if (KeyPress(DIK_D)) { fMoveAngle = ANGLE_UP_RIGHT; }
		else                      { fMoveAngle = ANGLE_UP; }
	}
	else if     (KeyPress(DIK_S)) {
		if      (KeyPress(DIK_A)) { fMoveAngle = ANGLE_DOWN_LEFT; }
		else if (KeyPress(DIK_D)) { fMoveAngle = ANGLE_DOWN_RIGHT; }
		else                      { fMoveAngle = ANGLE_DOWN; }
	}
	else if     (KeyPress(DIK_A)) { fMoveAngle = ANGLE_LEFT; }
	else if     (KeyPress(DIK_D)) { fMoveAngle = ANGLE_RIGHT; }
	else if     (StickTiltRate(STICK_LEFT) > 0.0f) { 
		if (pRate != NULL)
			*pRate = StickTiltRate(STICK_LEFT);
		fMoveAngle = -StickTiltAngle(STICK_LEFT) + D3DX_PI;
	}
	else {
		if (pRate != NULL)
			*pRate = 0.0f;
		return 0.0f;
	}

	return fMoveAngle;
}

//========================================
// 角度入力取得
// Author:RIKU NISHIMURA
//========================================
bool CInput::GetAngleTrigger(INPUT_ANGLE angle) {
	return (GetLeftAngleTrigger(angle) || GetRightAngleTrigger(angle));
}

//========================================
// 左入力角度取得
// Author:RIKU NISHIMURA
//========================================
bool CInput::GetLeftAngleTrigger(INPUT_ANGLE angle) {
	switch (angle) {
	case INPUT_ANGLE_UP:
		return (KeyTrigger(DIK_W) || StickAngleTrigger(STICK_LEFT, INPUT_ANGLE_UP));
	case INPUT_ANGLE_DOWN:
		return (KeyTrigger(DIK_S) || StickAngleTrigger(STICK_LEFT, INPUT_ANGLE_DOWN));
	case INPUT_ANGLE_LEFT:
		return (KeyTrigger(DIK_A) || StickAngleTrigger(STICK_LEFT, INPUT_ANGLE_LEFT));
	case INPUT_ANGLE_RIGHT:
		return (KeyTrigger(DIK_D) || StickAngleTrigger(STICK_LEFT, INPUT_ANGLE_RIGHT));
	}

	return false;
}

//========================================
// 右入力角度取得
// Author:RIKU NISHIMURA
//========================================
bool CInput::GetRightAngleTrigger(INPUT_ANGLE angle) {
	switch (angle) {
	case INPUT_ANGLE_UP:
		return (KeyTrigger(DIK_UP  )  || StickAngleTrigger(STICK_RIGHT, INPUT_ANGLE_UP));
	case INPUT_ANGLE_DOWN:
		return (KeyTrigger(DIK_DOWN)  || StickAngleTrigger(STICK_RIGHT, INPUT_ANGLE_DOWN));
	case INPUT_ANGLE_LEFT:
		return (KeyTrigger(DIK_LEFT)  || StickAngleTrigger(STICK_RIGHT, INPUT_ANGLE_LEFT));
	case INPUT_ANGLE_RIGHT:
		return (KeyTrigger(DIK_RIGHT) || StickAngleTrigger(STICK_RIGHT, INPUT_ANGLE_RIGHT));
	}

	return false;
}

//========================================
// 右入力角度取得
// Author:RIKU NISHIMURA
//========================================
float CInput::GetRightAngle(float *pRate) {
	float fMoveAngle = 0.0f;
	*pRate = 1.0f;

	D3DXVECTOR2 cursorMove = GetCursorMove();

	if          (KeyPress(DIK_UP   )) {
		if      (KeyPress(DIK_LEFT )) { fMoveAngle = ANGLE_UP_LEFT; }
		else if (KeyPress(DIK_RIGHT)) { fMoveAngle = ANGLE_UP_RIGHT; }
		else                          { fMoveAngle = ANGLE_UP; }
	}
	else if     (KeyPress(DIK_DOWN )) {
		if      (KeyPress(DIK_LEFT )) { fMoveAngle = ANGLE_DOWN_LEFT; }
		else if (KeyPress(DIK_RIGHT)) { fMoveAngle = ANGLE_DOWN_RIGHT; }
		else                          { fMoveAngle = ANGLE_DOWN; }
	}
	else if     (KeyPress(DIK_LEFT )) { fMoveAngle = ANGLE_LEFT; }
	else if     (KeyPress(DIK_RIGHT)) { fMoveAngle = ANGLE_RIGHT; }
	else if     (StickTiltRate(STICK_RIGHT) > 0.0f) { 
		*pRate = StickTiltRate(STICK_RIGHT);
		fMoveAngle = -StickTiltAngle(STICK_RIGHT) + D3DX_PI;
	}
	else if (cursorMove.x + cursorMove.y != 0.0f) {
		float fMoveDist = Find_Dist(INITD3DXVECTOR3, D3DXVECTOR3(cursorMove.x, cursorMove.y, 0.0f));
		if (fMoveDist > CURSOR_DIST_BASE)
			fMoveDist = CURSOR_DIST_BASE;
		*pRate     = fMoveDist / CURSOR_DIST_BASE;
		fMoveAngle = Find_Angle_LookFront(INITD3DXVECTOR3, D3DXVECTOR3(cursorMove.x, cursorMove.y, 0.0f));
	}
	else {
		*pRate = 0.0f;
		return 0.0f;
	}

	return fMoveAngle;
}

//========================================
// 決定取得
// Author:RIKU NISHIMURA
//========================================
bool CInput::GetDecide(void) {
	return (KeyTrigger(DIK_RETURN) || ButtonTrigger(BUTTON_A));
}

//========================================
// 入力情報のクリア処理
// Author:RIKU NISHIMURA
//========================================
void CInput::Clear(void) {
	// キー
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++) {
		m_aKeyPress  [nCnt] = 0;
		m_aKeyTrigger[nCnt] = 0;
		m_aKeyRelease[nCnt] = 0; 
		m_aKeyRepeat [nCnt] = 0;
	}

	// マウス
	for (int nCnt = 0; nCnt < MOUSEBUTTON_MAX; nCnt++) {
		m_aMousePress  [nCnt] = 0;
		m_aMouseTrigger[nCnt] = 0;
		m_aMouseRelease[nCnt] = 0;
		m_aMouseRepeat [nCnt] = 0;
	}
	m_cursorPos  = GetCursorPosOnScreen();	// カーソル位置
	m_cursorMove = INITD3DXVECTOR2;			// カーソル移動量
	m_wheelSpin  = WHEELSPIN_NONE;			// ホイール回転状態

	// コントローラー
	for (int nCnt = 0; nCnt < BUTTON_MAX; nCnt++) {
		m_aButtonPress  [nCnt] = 0;
		m_aButtonTrigger[nCnt] = 0;
		m_aButtonRelease[nCnt] = 0;
		m_aButtonRepeat [nCnt] = 0;
	}
	// スティック
	for (int nCnt = 0; nCnt < STICK_MAX; nCnt++) {
		for (int nCntAngle = 0; nCntAngle < INPUT_ANGLE_MAX; nCntAngle++) {
			m_aStick[nCnt].aAnglePress  [nCntAngle] = 0;
			m_aStick[nCnt].aAngleTrigger[nCntAngle] = 0;
			m_aStick[nCnt].aAngleRelease[nCntAngle] = 0;
			m_aStick[nCnt].aAngleRepeat [nCntAngle] = 0;
		}
		m_aStick[nCnt].fTiltAngle = 0.0f;
	}

	m_nCounterVibration    = 0;		// 振動カウンター
	m_nCounterVibrationMax = 0;		// 振動カウンターMAX
	m_fVibration           = 0.0f;	// 振動倍率
}