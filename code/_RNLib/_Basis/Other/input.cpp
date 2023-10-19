//========================================
// 
// ���̓N���X�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define VIBRATION_SUBTRACT (0.02f)

//****************************************
// �ÓI�����o�萔��`
//****************************************
// �}�E�X�̃}�X�N
const int CInput::m_aMouseMask[(int)MOUSEBUTTON::MAX] = {
	VK_LBUTTON,
	VK_RBUTTON,
};

// �{�^���̃}�X�N
const int CInput::m_aButtonMask[(int)BUTTON::MAX] = {
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
	-1,
	-1,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| ���̓N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CInput::CInput() {

	m_joyPads = NULL;
	m_joyPadNum = 0;
	m_inputDevice = NULL;
	m_keyboardDevice = NULL;
	m_activeDevice = ACTIVE_DEVICE::KEYBOARD;
	m_isFixedCursor = false;

	// ���͏����N���A
	Clear();
}

//========================================
// �f�X�g���N�^
//========================================
CInput::~CInput() {

}

//========================================
// ����������
//========================================
void CInput::Init(HINSTANCE& instanceHandle) {

	// �}�E�X�J�[�\����\��
	// (���ŏ�����true���ƁA�ォ��v���𖳎������׈�xfalse�ɂ��Ă���true�ɂ���)
	ShowCursor(false);
	ShowCursor(true);

	// XInput���J��
	XInputEnable(true);

	// DirectInput�I�u�W�F�N�g�̐���
	DirectInput8Create(instanceHandle, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_inputDevice, NULL);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	m_inputDevice->CreateDevice(GUID_SysKeyboard, &m_keyboardDevice, NULL);

	// �f�[�^�t�H�[�}�b�g��ݒ�
	m_keyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	// �����t�H�[�}�b�g
	m_keyboardDevice->SetCooperativeLevel(RNLib::Window()->GetHandle(), (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_keyboardDevice->Acquire();
}

//========================================
// �I������
//========================================
void CInput::Uninit(void) {

	// XInput�����
	XInputEnable(false);

	// ���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_keyboardDevice != NULL) {
		m_keyboardDevice->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		m_keyboardDevice->Release();
		m_keyboardDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_inputDevice != NULL) {
		m_inputDevice->Release();
		m_inputDevice = NULL;
	}

	// �W���C�p�b�h���
	RNLib::Memory()->Release(&m_joyPads);
}

//========================================
// �X�V����
//========================================
void CInput::Update(void) {

	UpdateKeyboard();
	UpdateCursor();
	UpdateMouseButton();
	UpdateJoyPad();
}

//========================================
// �N���A����
//========================================
void CInput::Clear(void) {

	for (int cntKey = 0; cntKey < NUM_KEY_MAX; cntKey++)
		m_keyInputs[cntKey] = {};

	for (int cntMouseButton = 0; cntMouseButton < (int)MOUSEBUTTON::MAX; cntMouseButton++)
		m_mouseButtonInputs[cntMouseButton] = {};

	m_cursorInfo = {};
	m_wheelSpin = WHEELSPIN::NONE;
}

//========================================
// �L�[�{�[�h�̍X�V����
//========================================
void CInput::UpdateKeyboard(void) {

	// �L�[�{�[�h�̓��͏��
	BYTE keyInputs[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_keyboardDevice->GetDeviceState(sizeof(keyInputs), &keyInputs[0]))) {
		for (int cntKey = 0; cntKey < NUM_KEY_MAX; cntKey++) {
			// �L�[�{�[�h�̃g���K�[����ۑ�
			m_keyInputs[cntKey].trigger = (m_keyInputs[cntKey].press ^ keyInputs[cntKey]) & keyInputs[cntKey];

			// �L�[�{�[�h�̃����[�X����ۑ�
			m_keyInputs[cntKey].release = (m_keyInputs[cntKey].press ^ keyInputs[cntKey]) & ~keyInputs[cntKey];

			// �L�[�{�[�h�̃v���X����ۑ�
			m_keyInputs[cntKey].press = keyInputs[cntKey];

			// ���͂��s��ꂽ���A���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
			if (keyInputs[cntKey])
				m_activeDevice = ACTIVE_DEVICE::KEYBOARD;
		}
	}
	else
	{// ���̓f�o�C�X����f�[�^���擾�ł��Ȃ��������A
		m_keyboardDevice->Acquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
	}
}

//========================================
// �}�E�X�̍X�V����
//========================================
void CInput::UpdateMouseButton(void) {

	// ��ʂɃt�H�[�J�X���������Ă��邩�ǂ������ׂ�
	bool isWindowFocused = RNLib::Window()->FindFocused(RNLib::Window()->GetHandle());

	for (int cntMouseButton = 0; cntMouseButton < (int)MOUSEBUTTON::MAX; cntMouseButton++) {

		// �}�E�X�̓��͏��
		BYTE mouseState = isWindowFocused ? (GetKeyState(m_aMouseMask[cntMouseButton]) & (0x80) ? 1 : 0) : 0;

		// �}�E�X�̃g���K�[����ۑ�
		m_mouseButtonInputs[cntMouseButton].trigger = (m_mouseButtonInputs[cntMouseButton].press ^ mouseState) & mouseState;

		// �}�E�X�̃����[�X����ۑ�
		m_mouseButtonInputs[cntMouseButton].release = (m_mouseButtonInputs[cntMouseButton].press ^ mouseState) & ~mouseState;

		// �}�E�X�̃v���X����ۑ�
		m_mouseButtonInputs[cntMouseButton].press = mouseState;

		// ���͂��s��ꂽ���A���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
		if (mouseState)
			m_activeDevice = ACTIVE_DEVICE::KEYBOARD;
	}
}

//========================================
// �J�[�\���̍X�V����
//========================================
void CInput::UpdateCursor(void) {

	// �ߋ��̈ʒu�Ƃ��ĕۑ�
	D3DXVECTOR2 oldCursorPos = m_cursorInfo.pos;

	// �N���C�A���g�̈�̃T�C�Y���擾
	RECT rc;
	GetClientRect(RNLib::Window()->GetHandle(), &rc);

	{// �J�[�\���̃E�B���h�E��̈ʒu���擾
		// �J�[�\���̌��݈ʒu���擾
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		// �E�B���h�E�̈ʒu���擾
		D3DXVECTOR3 windowPos = RNLib::Window()->GetPos();

		m_cursorInfo.pos = D3DXVECTOR2(
			(cursorPos.x - windowPos.x) * (RNLib::Window()->GetWidth() / (float)rc.right),
			(cursorPos.y - windowPos.y) * (RNLib::Window()->GetHeight() / (float)rc.bottom));
	}

	// �J�[�\���̈ړ��ʂ�ݒ�
	m_cursorInfo.move = m_cursorInfo.pos - oldCursorPos;

	// �J�[�\���̌Œ�
	if (m_isFixedCursor) {

		// �}�E�X���W�̐ݒ�
		SetCursorPos(rc.right * 0.5f, rc.bottom * 0.5f);

		// �J�[�\���ʒu��ۑ�
		D3DXVECTOR3 centerPos = RNLib::Window()->GetCenterPos();
		m_cursorInfo.pos.x = centerPos.x;
		m_cursorInfo.pos.y = centerPos.y;
	}
}

//========================================
// �W���C�p�b�h���ݒ菈��
//========================================
void CInput::SetJoyPadNum(const unsigned short& num) {

	// �������Ċm��
	RNLib::Memory()->ReAlloc(&m_joyPads, m_joyPadNum, num);

	// ������
	m_joyPadNum = num;

	// �ԍ��������Ă���
	for (int cntJoyPad = 0; cntJoyPad < m_joyPadNum; cntJoyPad++)
		m_joyPads[cntJoyPad].SetIdx(cntJoyPad);
}

//========================================
// �R���g���[���[�̍X�V����
//========================================
void CInput::UpdateJoyPad(void) {

	for (int cntJoyPad = 0; cntJoyPad < m_joyPadNum; cntJoyPad++)
		m_joyPads[cntJoyPad].Update();
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �W���C�p�b�h�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CInput::CJoyPad::CJoyPad() {

	m_idx = DATANONE;
	for (int cntButton = 0; cntButton < (int)BUTTON::MAX; cntButton++)
		m_buttonInputs[cntButton] = {};
	for (int cntStick = 0; cntStick < (int)STICK::MAX; cntStick++)
		m_sticInputs[cntStick] = {};
	m_vibrationCounter = 0;
	m_vibrationCounterMax = 0;
	m_vibration = 0.0f;
	memset(&m_xInputState, 0, sizeof(XINPUT_STATE));
}

//========================================
// �f�X�g���N�^
//========================================
CInput::CJoyPad::~CJoyPad() {

}

//========================================
// �X�V����
//========================================
void CInput::CJoyPad::Update(void) {

	// XInput�̏�Ԃ��擾
	XInputGetState(m_idx, &m_xInputState);

	UpdateButton();
	UpdateStick();
	UpdateVibration();
}

//========================================
// �{�^���̍X�V����
//========================================
void CInput::CJoyPad::UpdateButton(void) {

	for (int cntButton = 0; cntButton < (int)BUTTON::MAX; cntButton++) {

		// �{�^���̓��͏��
		BYTE button = 0;

		//----------------------------------------
		// ���͔���
		//----------------------------------------
		// [[[ ���g���K�[�̎� ]]]
		if (cntButton == (int)BUTTON::LEFT_TRIGGER)
			button = (BYTE)(m_xInputState.Gamepad.bLeftTrigger > 0);	// ������Ă邩
		// [[[ �E�g���K�[�̎� ]]]
		else if (cntButton == (int)BUTTON::RIGHT_TRIGGER)
			button = (BYTE)(m_xInputState.Gamepad.bRightTrigger > 0);	// ������Ă邩
		// [[[ ����ȊO�̃{�^���ŉ�����Ă��鎞 ]]]
		else if (m_xInputState.Gamepad.wButtons & m_aButtonMask[cntButton])
			button = 1;

		// �{�^���̃g���K�[����ۑ�
		m_buttonInputs[cntButton].trigger = (m_buttonInputs[cntButton].press ^ button) & button;

		// �{�^���̃����[�X����ۑ�
		m_buttonInputs[cntButton].release = (m_buttonInputs[cntButton].press ^ button) & ~button;

		// �{�^���̃v���X����ۑ�
		m_buttonInputs[cntButton].press = button;

		// ���͂��s��ꂽ���A���I�ȃf�o�C�X���W���C�p�b�h�ɂ���(��0�Ԗڌ���)
		if (m_idx == 0)
			if (button != 0)
				RNLib::Input()->SetActiveDevice(ACTIVE_DEVICE::JOYPAD);
	}
}

//========================================
// �X�e�B�b�N�̍X�V����
//========================================
void CInput::CJoyPad::UpdateStick(void) {

	// �X�e�B�b�N�̓��͏��
	BYTE aAngle[(int)INPUT_ANGLE::MAX];

	for (int cntStick = 0; cntStick < (int)STICK::MAX; cntStick++) {
		float X = 0.0f;	// �X�e�B�b�N��X��
		float Y = 0.0f;	// �X�e�B�b�N��Y��

		// ��ނɉ������X�e�B�b�N�̎��̒l���擾
		switch ((STICK)cntStick) {
		case STICK::LEFT:
			X = m_xInputState.Gamepad.sThumbLX;
			Y = m_xInputState.Gamepad.sThumbLY;
			break;
		case STICK::RIGHT:
			X = m_xInputState.Gamepad.sThumbRX;
			Y = m_xInputState.Gamepad.sThumbRY;
			break;
		}

		// �p�x���擾
		m_sticInputs[cntStick].tiltAngle = Find_Angle_LookFront(D3DXVECTOR3(X, Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

		// �X�e�B�b�N�̓|������擾
		m_sticInputs[cntStick].tiltRate = fabsf(X);
		if (m_sticInputs[cntStick].tiltRate < fabsf(Y)) {
			m_sticInputs[cntStick].tiltRate = fabsf(Y);
		}
		m_sticInputs[cntStick].tiltRate /= 32768.0f;

		// �������̓t���O��������
		for (int nCntAngle = 0; nCntAngle < (int)INPUT_ANGLE::MAX; nCntAngle++) {
			aAngle[nCntAngle] = false;
		}

		if (m_sticInputs[cntStick].tiltRate > 0)
		{// �X�e�B�b�N���|����Ă��鎞�A
			// �p�x���l�����ŏ�Ɉʒu����
			if ((m_sticInputs[cntStick].tiltAngle < D3DX_PI_LEFT_UP)
				|| (m_sticInputs[cntStick].tiltAngle > D3DX_PI_RIGHT_UP))
				aAngle[(int)INPUT_ANGLE::UP] = true;

			// �p�x���l�����ŉ��Ɉʒu����
			else if ((m_sticInputs[cntStick].tiltAngle > D3DX_PI_LEFT_DOWN)
				&& (m_sticInputs[cntStick].tiltAngle < D3DX_PI_RIGHT_DOWN))
				aAngle[(int)INPUT_ANGLE::DOWN] = true;

			// �p�x���l�����ō��Ɉʒu����
			else if ((m_sticInputs[cntStick].tiltAngle > D3DX_PI_LEFT_UP)
				&& (m_sticInputs[cntStick].tiltAngle < D3DX_PI_LEFT_DOWN))
				aAngle[(int)INPUT_ANGLE::LEFT] = true;

			// �p�x���l�����ŉE�Ɉʒu����
			else if ((m_sticInputs[cntStick].tiltAngle < D3DX_PI_RIGHT_UP)
				&& (m_sticInputs[cntStick].tiltAngle > D3DX_PI_RIGHT_DOWN))
				aAngle[(int)INPUT_ANGLE::RIGHT] = true;

			// ���I�ȃf�o�C�X���W���C�p�b�h�ɂ���(��0�Ԗڌ���)
			if (m_idx == 0)
				RNLib::Input()->SetActiveDevice(ACTIVE_DEVICE::JOYPAD);
		}

		for (int cntAngle = 0; cntAngle < (int)INPUT_ANGLE::MAX; cntAngle++) {

			// �X�e�B�b�N�̃g���K�[����ۑ�
			m_sticInputs[cntStick].angleInputs[cntAngle].trigger = (m_sticInputs[cntStick].angleInputs[cntAngle].press ^ aAngle[cntAngle]) & aAngle[cntAngle];

			// �X�e�B�b�N�̃����[�X����ۑ�
			m_sticInputs[cntStick].angleInputs[cntAngle].release = (m_sticInputs[cntStick].angleInputs[cntAngle].press ^ aAngle[cntAngle]) & ~aAngle[cntAngle];

			// �X�e�B�b�N�̃v���X����ۑ�
			m_sticInputs[cntStick].angleInputs[cntAngle].press = aAngle[cntAngle];
		}
	}
}

//========================================
// �U���̍X�V����
//========================================
void CInput::CJoyPad::UpdateVibration(void) {

	if (m_vibration > 0.0f)
	{// �U���{����0�������Ă��鎞�A
		// �U���{�������Z
		m_vibration -= VIBRATION_SUBTRACT;

		// �U���{���𐧌�
		if (m_vibration < 0.0f)
			m_vibration = 0.0f;

		{// �U���t���O���^�̎��A
			XINPUT_VIBRATION vibration;	// XINPUT_VIBRATION vibration���쐬

			//vibration�����o�[wLeftMotorSpeed�ɒl���� ���[�^�[�X�s�[�h100%
			vibration.wLeftMotorSpeed = 65535 * m_vibration;

			//vibration�����o�[wRightMotorSpeed�ɒl���� ���[�^�[�X�s�[�h0%
			vibration.wRightMotorSpeed = 65535 * m_vibration;

			//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�[�f�[�^�𑗐M
			XInputSetState(m_idx, &vibration);
		}
	}
}

//========================================
// �R���g���[���[�̐U���ݒ菈��
//========================================
void CInput::CJoyPad::SetVibration(const float& vibration) {

	// ���g���W���C�p�b�h0�ԂŃA�N�e�B�u�łȂ����A�������I��
	if (m_idx == 0)
		if (RNLib::Input()->GetActiveDevice() != ACTIVE_DEVICE::JOYPAD)
			return;

	// �U���{�������̐U���{���������Ă��鎞�A�U���{������
	if (m_vibration < vibration) {
		m_vibration = vibration;

		if (m_vibration > 1.0f)
			m_vibration = 1.0f;
	}
}
