//========================================
// 
// ���̓N���X�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// ���̓N���X
class CInput {
public:
	//========== [[[ �萔��` ]]]
	static const int NUM_KEY_MAX = 256;

	//========== [[[ �񋓌^�̒�` ]]]
	enum class ACTIVE_DEVICE { KEYBOARD, CONTROLLER, MAX, };
	enum class INPUT_ANGLE { UP, DOWN, LEFT, RIGHT, MAX, };
	enum class MOUSEBUTTON { LEFT, RIGHT, MAX, };
	enum class BUTTON { UP, DOWN, LEFT, RIGHT, START, BACK, LEFT_THUMB, RIGHT_THUMB, LEFT_SHOULDER, RIGHT_SHOULDER, A, B, X, Y, LEFT_TRIGGER, RIGHT_TRIGGER, MAX, };
	enum class STICK { LEFT, RIGHT, MAX, };
	enum class WHEELSPIN { NONE, FRONT, BACK, };

	//========== [[[ �\���̂̒�` ]]]
	// �X�e�B�b�N�̓��͏��\����
	typedef struct {
		float fTiltRate;	// �|���
		float fTiltAngle;	// �|��p�x
		BYTE  aAnglePress[(int)INPUT_ANGLE::MAX];	// �����v���X���
		BYTE  aAngleTrigger[(int)INPUT_ANGLE::MAX];	// �����g���K�[���
		BYTE  aAngleRepeat[(int)INPUT_ANGLE::MAX];	// �������s�[�g���
		BYTE  aAngleRelease[(int)INPUT_ANGLE::MAX];	// ���������[�X���
		DWORD aStickCurrentTime[(int)INPUT_ANGLE::MAX];	// ���ݎ���
		DWORD aStickExecLastTime[(int)INPUT_ANGLE::MAX];	// �Ō㎞��
	}StickInput;

	//========== [[[ �֐��錾 ]]]
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
	void  FixedCursor(bool bFixed) {// �J�[�\���Œ�
		m_bFixedCursor = bFixed;
		ShowCursor(!bFixed);
	}
	bool  GetPause(void) { return (KeyTrigger(DIK_P) || ButtonTrigger((int)BUTTON::START)); }
	// �擾
	XINPUT_STATE* GetXInputState(void) { return &m_xInputState; }
	D3DXVECTOR2        GetCursorPosOnScreen(void);
	D3DXVECTOR2        GetCursorMove(void) { return m_cursorInfo.move; }
	StickInput         GetStick(STICK stick) { return m_aStick[(int)stick]; }
	ACTIVE_DEVICE GetActiveInputType(void) { return m_activeInputType; }
	// ����
	bool Press(int nKey, int nButton) { return KeyPress(nKey) || ButtonPress(nButton); }
	bool Trigger(int nKey, int nButton) { return KeyTrigger(nKey) || ButtonTrigger(nButton); }
	bool Release(int nKey, int nButton) { return KeyRelease(nKey) || ButtonRelease(nButton); }
	// �L�[�{�[�h
	bool KeyPress(int nKey) { return m_keyInputs[nKey].press != 0; }
	bool KeyTrigger(int nKey) { return m_keyInputs[nKey].trigger != 0; }
	bool KeyRelease(int nKey) { return m_keyInputs[nKey].release != 0; }
	// �}�E�X
	bool MousePress(MOUSEBUTTON btn) { return m_mouseButtonInputs[(int)btn].press != 0; }
	bool MouseTrigger(MOUSEBUTTON btn) { return m_mouseButtonInputs[(int)btn].trigger != 0; }
	bool MouseRelease(MOUSEBUTTON btn) { return m_mouseButtonInputs[(int)btn].release != 0; }
	WHEELSPIN WheelSpin(void) { return m_wheelSpin; }
	// �{�^��
	bool ButtonPress(int nButton) { return m_aButtonPress[nButton] != 0; }
	bool ButtonTrigger(int nButton) { return m_aButtonTrigger[nButton] != 0; }
	bool ButtonRepeat(int nButton) { return m_aButtonRepeat[nButton] != 0; }
	bool ButtonRelease(int nButton) { return m_aButtonRelease[nButton] != 0; }
	// �X�e�B�b�N
	float StickTiltRate(STICK stick) { return m_aStick[(int)stick].fTiltRate; }
	float StickTiltAngle(STICK stick) { return m_aStick[(int)stick].fTiltAngle; }
	bool  StickAnglePress(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAnglePress[(int)angle] != 0; }
	bool  StickAngleTrigger(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAngleTrigger[(int)angle] != 0; }
	bool  StickAngleRepeat(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAngleRepeat[(int)angle] != 0; }
	bool  StickAngleRelease(STICK stick, INPUT_ANGLE angle) { return m_aStick[(int)stick].aAngleRelease[(int)angle] != 0; }
	// �ݒ�
	void SetWheelSpin(WHEELSPIN wheelSpin) { m_wheelSpin = wheelSpin; }

private:
	//========== [[[ �萔�錾 ]]]
	static const int m_aMouseMask[(int)MOUSEBUTTON::MAX];
	static const int m_aButtonMask[(int)BUTTON::MAX];

	//========== [[[ �\���̒�` ]]]
	struct Input {
		BYTE press = 0;
		BYTE trigger = 0;
		BYTE release = 0;
	};
	struct CursorInfo {
		D3DXVECTOR2 pos = INITD3DXVECTOR2;
		D3DXVECTOR2 move = INITD3DXVECTOR2;
	};

	//========== [[[ �֐��錾 ]]]
	void UpdateKeyboard(void);
	void UpdateMouseButton(void);
	void UpdateCursor(void);
	void UpdateButton(void);
	void UpdateStick(void);
	void UpdateController(void);

	//========== [[[ �ϐ��錾 ]]]
	Input m_keyInputs[NUM_KEY_MAX];
	Input m_mouseButtonInputs[(int)MOUSEBUTTON::MAX];
	CursorInfo m_cursorInfo;
	WHEELSPIN m_wheelSpin;

	//----------�R���g���[���[----------
	/* �v���X���        */BYTE  m_aButtonPress[(int)BUTTON::MAX];
	/* �g���K�[���      */BYTE  m_aButtonTrigger[(int)BUTTON::MAX];
	/* �����[�X���      */BYTE  m_aButtonRelease[(int)BUTTON::MAX];
	/* ���s�[�g���      */BYTE  m_aButtonRepeat[(int)BUTTON::MAX];
	/* ���݂̎���        */DWORD m_aButtonCurrentTime[(int)BUTTON::MAX];
	/* �Ō�̎���        */DWORD m_aButtonExecLastTime[(int)BUTTON::MAX];
	/* �X�e�B�b�N���    */StickInput m_aStick[(int)STICK::MAX];
	/* �U���J�E���^�[    */int m_nCounterVibration;
	/* �U���J�E���^�[MAX */int m_nCounterVibrationMax;
	/* �U���{��          */float m_fVibration;
	/* XInput�̏��      */XINPUT_STATE m_xInputState;

	//========== [[[ �ϐ��錾 ]]]
	LPDIRECTINPUT8       m_inputDevice;			// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	ACTIVE_DEVICE        m_activeInputType;	// ���I�ȃf�o�C�X
	bool                 m_bFixedCursor;	// �J�[�\���Œ�t���O
};