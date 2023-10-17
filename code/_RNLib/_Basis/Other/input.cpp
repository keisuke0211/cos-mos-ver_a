//========================================
// 
// ���͊֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define REPEATE_INTERVAL   (60)
#define VIBRATION_SUBTRACT (0.02f)
#define CURSOR_DIST_BASE   (10.0f)

//****************************************
// �ÓI�����o�萔�錾
//****************************************
// �}�E�X�̃}�X�N
const int CInput::m_aMouseMask[MOUSEBUTTON_MAX] = {
	VK_LBUTTON,
	VK_RBUTTON,
};

// �{�^���̃}�X�N
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
//==========| CInput�֐��̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CInput::CInput() {

}

//========================================
// �f�X�g���N�^
//========================================
CInput::~CInput() {
	
}

//========================================
// �L�[�{�[�h�̍X�V����
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateKeyboard(void) {
	// �L�[�{�[�h�̓��͏��
	BYTE m_aKey[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(m_aKey), &m_aKey[0]))) {
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) {
			// �L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyTrigger[nCntKey] = (m_aKeyPress[nCntKey] ^ m_aKey[nCntKey])&m_aKey[nCntKey];

			// �L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyRelease[nCntKey] = (m_aKeyPress[nCntKey] ^ m_aKey[nCntKey])&~m_aKey[nCntKey];

			// ���݂̎��Ԃ��擾
			m_aKeyCurrentTime[nCntKey] = timeGetTime();

			if (m_aKey[nCntKey] && ((m_aKeyCurrentTime[nCntKey] - m_aKeyExecLastTime[nCntKey]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
				// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aKeyExecLastTime[nCntKey] = m_aKeyCurrentTime[nCntKey];

				// �L�[�{�[�h�̃��s�[�g����ۑ�
				m_aKeyRepeat[nCntKey] = m_aKey[nCntKey];
			}
			else {
				// �L�[�{�[�h�̃��s�[�g����ۑ�
				m_aKeyRepeat[nCntKey] = 0;
			}

			// �L�[�{�[�h�̃v���X����ۑ�
			m_aKeyPress[nCntKey] = m_aKey[nCntKey];

			if (m_aKey[nCntKey])
			{// ���͂��s��ꂽ���A
				// ���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
				m_activeInputType = ACTIVE_DEVICE_KEYBOARD;
			}
		}
	}
	else
	{// ���̓f�o�C�X����f�[�^���擾�ł��Ȃ��������A
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		m_pDevKeyboard->Acquire();
	}
}

//========================================
// UpdateMouse�֐� - �}�E�X�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateMouse(void) {
	// ��ʂɃt�H�[�J�X���������Ă��邩�ǂ������ׂ�
	bool bWindowFocused = RNLib::Window()->FindFocused(RNLib::Window()->GetHandle());

	for (int nCntMouse = 0; nCntMouse < MOUSEBUTTON_MAX; nCntMouse++) {
		// �}�E�X�̓��͏��
		BYTE mouseState = GetKeyState(m_aMouseMask[nCntMouse]) & (0x80) ? true : false;
		
		if (!bWindowFocused) 
		{// ��ʂɃt�H�[�J�X���������Ă��Ȃ����A
			mouseState = false;	// ���͂��U�ɂ���
		}

		// �}�E�X�̃g���K�[����ۑ�
		m_aMouseTrigger[nCntMouse] = (m_aMousePress[nCntMouse] ^ mouseState)&mouseState;

		// �}�E�X�̃����[�X����ۑ�
		m_aMouseRelease[nCntMouse] = (m_aMousePress[nCntMouse] ^ mouseState)&~mouseState;

		// ���݂̎��Ԃ��擾
		m_aMouseCurrentTime[nCntMouse] = timeGetTime();

		if (mouseState && ((m_aMouseCurrentTime[nCntMouse] - m_aMouseExecLastTime[nCntMouse]) > REPEATE_INTERVAL))
		{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			m_aMouseExecLastTime[nCntMouse] = m_aMouseCurrentTime[nCntMouse];

			// �}�E�X�̃��s�[�g����ۑ�
			m_aMouseRepeat[nCntMouse] = mouseState;
		}
		else
		{// �L�[�����͂���Ă��Ȃ��A�������͌��݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă��Ȃ����A
			// �}�E�X�̃��s�[�g����ۑ�
			m_aMouseRepeat[nCntMouse] = 0;
		}

		// �}�E�X�̃v���X����ۑ�
		m_aMousePress[nCntMouse] = mouseState;

		if (mouseState)
		{// ���͂��s��ꂽ���A
			// ���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
			m_activeInputType = ACTIVE_DEVICE_KEYBOARD;
		}
	}
}

//========================================
// UpdateCursor�֐� - �J�[�\���̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateCursor(void) {
	// �J�[�\���̉�ʏ�̈ʒu���擾
	D3DXVECTOR2 cursorPos = GetCursorPosOnScreen();

	if (m_cursorPos != cursorPos)
	{// �J�[�\���̌��݈ʒu���ۑ��ʒu���قȂ鎞�A
		// ���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
		m_activeInputType = ACTIVE_DEVICE_KEYBOARD;
	}

	// �J�[�\���̈ړ��ʂ�ݒ�
	m_cursorMove = cursorPos - m_cursorPos;

	if (m_bFixedCursor) {
		// �N���C�A���g�̈�̃T�C�Y���擾
		RECT rc;
		GetClientRect(RNLib::Window()->GetHandle(), &rc);

		// �}�E�X���W�̐ݒ�
		SetCursorPos(rc.right * 0.5f, rc.bottom * 0.5f);

		// �J�[�\���ʒu��ۑ�
		m_cursorPos = GetCursorPosOnScreen();
	}
	else {
		// �J�[�\���ʒu��ۑ�
		m_cursorPos = cursorPos;
	}
}

//========================================
// UpdateButton�֐� - �{�^���̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateButton(void) {
	// �{�^���̓��͏��
	BYTE m_aButton[BUTTON_MAX] = {};

	for (int nCntButton = 0; nCntButton < BUTTON_MAX; nCntButton++) {
		if (nCntButton == BUTTON_LEFT_TRIGGER)
		{// �J�E���g�����g���K�[�̎��A
			if (GetXInputState()->Gamepad.bLeftTrigger > 0)
			{// �������܂�Ă���
				m_aButton[nCntButton] = true;
			}
		}
		else if (nCntButton == BUTTON_RIGHT_TRIGGER)
		{// �J�E���g���E�g���K�[�̎��A
			if (GetXInputState()->Gamepad.bRightTrigger > 0)
			{// �������܂�Ă���
				m_aButton[nCntButton] = true;
			}
		}
		else if (GetXInputState()->Gamepad.wButtons & m_aButtonMask[nCntButton])
		{// ���͏����X�V
			m_aButton[nCntButton] = true;
		}

		// �{�^���̃g���K�[����ۑ�
		m_aButtonTrigger[nCntButton] = (m_aButtonPress[nCntButton] ^ m_aButton[nCntButton])&m_aButton[nCntButton];

		// �{�^���̃����[�X����ۑ�
		m_aButtonRelease[nCntButton] = (m_aButtonPress[nCntButton] ^ m_aButton[nCntButton])&~m_aButton[nCntButton];

		// ���݂̎��Ԃ��擾
		m_aButtonCurrentTime[nCntButton] = timeGetTime();

		if (m_aButton[nCntButton] && ((m_aButtonCurrentTime[nCntButton] - m_aButtonExecLastTime[nCntButton]) > REPEATE_INTERVAL))
		{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			m_aButtonExecLastTime[nCntButton] = m_aButtonCurrentTime[nCntButton];

			// �{�^���̃��s�[�g����ۑ�
			m_aButtonRepeat[nCntButton] = m_aButton[nCntButton];
		}
		else {
			// �{�^���̃��s�[�g����ۑ�
			m_aButtonRepeat[nCntButton] = 0;
		}

		// �{�^���̃v���X����ۑ�
		m_aButtonPress[nCntButton] = m_aButton[nCntButton];

		if (m_aButton[nCntButton])
		{// ���͂��s��ꂽ���A
			// ���I�ȃf�o�C�X���R���g���[���[�ɂ���
			m_activeInputType = ACTIVE_DEVICE_CONTROLLER;
		}
	}
}

//========================================
// UpdateStick�֐� - �X�e�B�b�N�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateStick(void) {
	// �X�e�B�b�N�̓��͏��
	BYTE aAngle[INPUT_ANGLE_MAX];

	// XInput�̏�Ԃ��擾
	m_xInputState.dwPacketNumber = XInputGetState(m_xInputState.dwPacketNumber, &m_xInputState);

	for (int nCntStick = 0; nCntStick < STICK_MAX; nCntStick++) {
		float X;	// �X�e�B�b�N��X��
		float Y;	// �X�e�B�b�N��Y��

		// ��ނɉ������X�e�B�b�N�̎��̒l���擾
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

		// �p�x���擾
		m_aStick[nCntStick].fTiltAngle = Find_Angle_LookFront(D3DXVECTOR3(X, Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

		// �X�e�B�b�N�̓|������擾
		m_aStick[nCntStick].fTiltRate = fabsf(X);
		if (m_aStick[nCntStick].fTiltRate < fabsf(Y)) {
			m_aStick[nCntStick].fTiltRate = fabsf(Y);
		}
		m_aStick[nCntStick].fTiltRate /= 32768.0f;

		// �������̓t���O��������
		for (int nCntAngle = 0; nCntAngle < INPUT_ANGLE_MAX; nCntAngle++) {
			aAngle[nCntAngle] = false;
		}

		if (m_aStick[nCntStick].fTiltRate > 0)
		{// �X�e�B�b�N���|����Ă��鎞�A
			// ���I�ȃf�o�C�X���R���g���[���[�ɂ���
			m_activeInputType = ACTIVE_DEVICE_CONTROLLER;

			if (false) {}
			else if ((m_aStick[nCntStick].fTiltAngle < D3DX_PI * -0.75)
				  || (m_aStick[nCntStick].fTiltAngle > D3DX_PI * 0.75))
			{// �p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
				aAngle[INPUT_ANGLE_UP] = true;
			}
			else if ((m_aStick[nCntStick].fTiltAngle > D3DX_PI * -0.25)
				  && (m_aStick[nCntStick].fTiltAngle < D3DX_PI * 0.25))
			{// �p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
				aAngle[INPUT_ANGLE_DOWN] = true;
			}
			else if ((m_aStick[nCntStick].fTiltAngle > D3DX_PI * -0.75)
				  && (m_aStick[nCntStick].fTiltAngle < D3DX_PI * -0.25))
			{// �p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
				aAngle[INPUT_ANGLE_LEFT] = true;
			}
			else if ((m_aStick[nCntStick].fTiltAngle > D3DX_PI * 0.25)
				  && (m_aStick[nCntStick].fTiltAngle < D3DX_PI * 0.75))
			{// �p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
				aAngle[INPUT_ANGLE_RIGHT] = true;
			}
		}

		for (int nCntAngle = 0; nCntAngle < INPUT_ANGLE_MAX; nCntAngle++) {
			// �X�e�B�b�N�̃g���K�[����ۑ�
			m_aStick[nCntStick].aAngleTrigger[nCntAngle] = (m_aStick[nCntStick].aAnglePress[nCntAngle] ^ aAngle[nCntAngle])&aAngle[nCntAngle];

			// �X�e�B�b�N�̃����[�X����ۑ�
			m_aStick[nCntStick].aAngleRelease[nCntAngle] = (m_aStick[nCntStick].aAnglePress[nCntAngle] ^ aAngle[nCntAngle])&~aAngle[nCntAngle];

			// ���݂̎��Ԃ��擾
			m_aStick[nCntStick].aStickCurrentTime[nCntAngle] = timeGetTime();

			if (aAngle[nCntAngle] && ((m_aStick[nCntStick].aStickCurrentTime[nCntAngle] - m_aStick[nCntStick].aStickExecLastTime[nCntAngle]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
				// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aStick[nCntStick].aStickExecLastTime[nCntAngle] = m_aStick[nCntStick].aStickCurrentTime[nCntAngle];

				// �X�e�B�b�N�̃��s�[�g����ۑ�
				m_aStick[nCntStick].aAngleRepeat[nCntAngle] = aAngle[nCntAngle];
			}
			else {
				// �X�e�B�b�N�̃��s�[�g����ۑ�
				m_aStick[nCntStick].aAngleRepeat[nCntAngle] = 0;
			}

			// �X�e�B�b�N�̃v���X����ۑ�
			m_aStick[nCntStick].aAnglePress[nCntAngle] = aAngle[nCntAngle];

			if (aAngle[nCntAngle])
			{// ���͂��s��ꂽ���A
				// ���I�ȃf�o�C�X���R���g���[���[�ɂ���
				m_activeInputType = ACTIVE_DEVICE_CONTROLLER;
			}
		}
	}
}

//========================================
// UpdateVibration�֐� - �R���g���[���[�̐U���X�V���� -
// Author:RIKU NISHIMURA
//========================================
void CInput::UpdateController(void) {
	if (m_fVibration > 0)
	{// �U���{����0�������Ă��鎞�A
		// �U���{�������Z
		m_fVibration -= VIBRATION_SUBTRACT;

		// �U���{���𐧌�
		FloatControl(&m_fVibration, 1.0f, 0);

		{// �U���t���O���^�̎��A
			XINPUT_STATE state;			//XINPUT_STATE�^ state���쐬
			XInputGetState(0, &state);	//state�ɏK�������R���g���[���̏�Ԃ��i�[
			XINPUT_VIBRATION vibration;	//XINPUT_VIBRATION vibration���쐬

			//vibration�����o�[wLeftMotorSpeed�ɒl���� ���[�^�[�X�s�[�h100%
			vibration.wLeftMotorSpeed = 65535 * m_fVibration;

			//vibration�����o�[wRightMotorSpeed�ɒl���� ���[�^�[�X�s�[�h0%
			vibration.wRightMotorSpeed = 65535 * m_fVibration;

			//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�[�f�[�^�𑗐M
			XInputSetState(0, &vibration);
		}
	}
}

//========================================
// InitInput�֐� - ���͊֘A�̏��������� -
// Author:RIKU NISHIMURA
//========================================
HRESULT CInput::Init(HINSTANCE hInstance) {
	// �}�E�X�J�[�\����\��
	//(���ŏ�����true���ƁA�ォ��v���𖳎������׈�xfalse�ɂ��Ă���true�ɂ���)
	ShowCursor(false);
	ShowCursor(true);

	// ���͏����N���A
	Clear();

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL))) {
		return E_FAIL;
	}
	
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL))) {
		return E_FAIL;
	}
	
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
		return E_FAIL;
	}

	// �����t�H�[�}�b�g
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(RNLib::Window()->GetHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))) {
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//========================================
// UninitInput�֐� - ���͊֘A�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void CInput::Uninit(void) {
	// XInput�����
	XInputEnable(false);

	// ���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevKeyboard != NULL) {
		m_pDevKeyboard->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL) {
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//========================================
// UpdateInput�֐� - ���͊֘A�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void CInput::Update(void) {
	UpdateKeyboard();	// �L�[�{�[�h
	UpdateButton();		// �{�^��
	UpdateCursor();		// �J�[�\��
	UpdateMouse();		// �}�E�X
	UpdateStick();		// �X�e�B�b�N
	UpdateController();	// �R���g���[���[�̐U��
}

//========================================
// GetCursorPosOnScreen�֐� - ��ʏ�̃J�[�\���̈ʒu���擾 -
// Author:RIKU NISHIMURA
//=======================================
D3DXVECTOR2 CInput::GetCursorPosOnScreen(void) {
	// �J�[�\���̌��݈ʒu���擾
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// �N���C�A���g�̈�̃T�C�Y���擾
	RECT rc;
	GetClientRect(RNLib::Window()->GetHandle(), &rc);

	D3DXVECTOR3 windowPos = RNLib::Window()->GetPos();	// �E�B���h�E�̈ʒu

	return D3DXVECTOR2(
		(cursorPos.x - windowPos.x) * (RNLib::Window()->GetWidth () / (float)rc.right),
		(cursorPos.y - windowPos.y) * (RNLib::Window()->GetHeight() / (float)rc.bottom));
}

//========================================
// �R���g���[���[�̐U���ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void CInput::SetVibration(float fVibration, int nTime) {
	if (m_activeInputType != ACTIVE_DEVICE_CONTROLLER) 
	{// ���I�ȃf�o�C�X���R���g���[���[�Ŗ������A
		// �������I��
		return;
	}

	if (fVibration > fVibration)
	{// �U���{�������̐U���{���������Ă��鎞�A
		// �U���{������
		fVibration = fVibration;
	}

	// �U���{���𐧌�
	FloatControl(&fVibration, 1.0f, 0);
}

//========================================
// �ړ��p�x�擾
// Author:RIKU NISHIMURA
//========================================
float CInput::GetMoveAngle(float *pRate) {
	float fAngle = GetLeftAngle(pRate) + RNLib::Camera3D()->GetRot().y;
	Limit_Angle(&fAngle);
	return fAngle;
}

//========================================
// �����͊p�x�擾
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
// �p�x���͎擾
// Author:RIKU NISHIMURA
//========================================
bool CInput::GetAngleTrigger(INPUT_ANGLE angle) {
	return (GetLeftAngleTrigger(angle) || GetRightAngleTrigger(angle));
}

//========================================
// �����͊p�x�擾
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
// �E���͊p�x�擾
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
// �E���͊p�x�擾
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
// ����擾
// Author:RIKU NISHIMURA
//========================================
bool CInput::GetDecide(void) {
	return (KeyTrigger(DIK_RETURN) || ButtonTrigger(BUTTON_A));
}

//========================================
// ���͏��̃N���A����
// Author:RIKU NISHIMURA
//========================================
void CInput::Clear(void) {
	// �L�[
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++) {
		m_aKeyPress  [nCnt] = 0;
		m_aKeyTrigger[nCnt] = 0;
		m_aKeyRelease[nCnt] = 0; 
		m_aKeyRepeat [nCnt] = 0;
	}

	// �}�E�X
	for (int nCnt = 0; nCnt < MOUSEBUTTON_MAX; nCnt++) {
		m_aMousePress  [nCnt] = 0;
		m_aMouseTrigger[nCnt] = 0;
		m_aMouseRelease[nCnt] = 0;
		m_aMouseRepeat [nCnt] = 0;
	}
	m_cursorPos  = GetCursorPosOnScreen();	// �J�[�\���ʒu
	m_cursorMove = INITD3DXVECTOR2;			// �J�[�\���ړ���
	m_wheelSpin  = WHEELSPIN_NONE;			// �z�C�[����]���

	// �R���g���[���[
	for (int nCnt = 0; nCnt < BUTTON_MAX; nCnt++) {
		m_aButtonPress  [nCnt] = 0;
		m_aButtonTrigger[nCnt] = 0;
		m_aButtonRelease[nCnt] = 0;
		m_aButtonRepeat [nCnt] = 0;
	}
	// �X�e�B�b�N
	for (int nCnt = 0; nCnt < STICK_MAX; nCnt++) {
		for (int nCntAngle = 0; nCntAngle < INPUT_ANGLE_MAX; nCntAngle++) {
			m_aStick[nCnt].aAnglePress  [nCntAngle] = 0;
			m_aStick[nCnt].aAngleTrigger[nCntAngle] = 0;
			m_aStick[nCnt].aAngleRelease[nCntAngle] = 0;
			m_aStick[nCnt].aAngleRepeat [nCntAngle] = 0;
		}
		m_aStick[nCnt].fTiltAngle = 0.0f;
	}

	m_nCounterVibration    = 0;		// �U���J�E���^�[
	m_nCounterVibrationMax = 0;		// �U���J�E���^�[MAX
	m_fVibration           = 0.0f;	// �U���{��
}