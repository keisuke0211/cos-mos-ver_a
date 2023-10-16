//========================================
// 
// ���͊֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ input.h ]]]
//========================================
#ifndef _INPUT_H_
#define _INPUT_H_

//****************************************
// �N���X��`
//****************************************
// ���̓N���X
class CInput {
public:
	//========== [[[ �萔��` ]]]
	static const int NUM_KEY_MAX = 256;

	//========== [[[ �񋓌^�̒�` ]]]
	// ���I�ȃf�o�C�X
	typedef enum {
		ACTIVE_DEVICE_KEYBOARD,
		ACTIVE_DEVICE_CONTROLLER,
		ACTIVE_DEVICE_MAX,
	}ACTIVE_DEVICE_TYPE;

	// ���͕���
	typedef enum {
		INPUT_ANGLE_UP,
		INPUT_ANGLE_DOWN,
		INPUT_ANGLE_LEFT,
		INPUT_ANGLE_RIGHT,
		INPUT_ANGLE_MAX,
	}INPUT_ANGLE;

	// ���͔ԍ�
	typedef enum {
		MOUSEBUTTON_LEFT,
		MOUSEBUTTON_RIGHT,
		MOUSEBUTTON_MAX,
	}MOUSEBUTTON;
	typedef enum {
		BUTTON_UP,				// ��L�[
		BUTTON_DOWN,			// ���L�[
		BUTTON_LEFT,			// ���L�[
		BUTTON_RIGHT,			// �E�L�[
		BUTTON_START,			// �X�^�[�g�L�[
		BUTTON_BACK,			// �o�b�N�L�[
		BUTTON_LEFT_THUMB,		// ���X�e�B�b�N
		BUTTON_RIGHT_THUMB,		// �E�X�e�B�b�N
		BUTTON_LEFT_SHOULDER,	// ���g���K�[
		BUTTON_RIGHT_SHOULDER,	// �E�g���K�[
		BUTTON_A,				// A�{�^��
		BUTTON_B,				// B�{�^��
		BUTTON_X,				// X�{�^��
		BUTTON_Y,				// Y�{�^��
		BUTTON_LEFT_TRIGGER,	// ���g���K�[
		BUTTON_RIGHT_TRIGGER,	// �E�g���K�[
		BUTTON_MAX,
	}BUTTON;
	typedef enum {
		STICK_LEFT,
		STICK_RIGHT,
		STICK_MAX,
	}STICK;

	// �}�E�X�z�C�[���̉�]���
	typedef enum {
		WHEELSPIN_NONE,		// ����
		WHEELSPIN_FRONT,	// �O��]
		WHEELSPIN_BACK,		// ���]
	}WHEELSPIN;

	//========== [[[ �\���̂̒�` ]]]
	// �X�e�B�b�N�̓��͏��\����
	typedef struct {
		float fTiltRate;	// �|���
		float fTiltAngle;	// �|��p�x
		BYTE  aAnglePress       [INPUT_ANGLE_MAX];	// �����v���X���
		BYTE  aAngleTrigger     [INPUT_ANGLE_MAX];	// �����g���K�[���
		BYTE  aAngleRepeat      [INPUT_ANGLE_MAX];	// �������s�[�g���
		BYTE  aAngleRelease     [INPUT_ANGLE_MAX];	// ���������[�X���
		DWORD aStickCurrentTime [INPUT_ANGLE_MAX];	// ���ݎ���
		DWORD aStickExecLastTime[INPUT_ANGLE_MAX];	// �Ō㎞��
	}StickInput;

	//========== [[[ �֐��錾 ]]]
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
	void  FixedCursor(bool bFixed) {// �J�[�\���Œ�
		m_bFixedCursor = bFixed; 
		ShowCursor(!bFixed);
	}
	bool  GetPause(void) { return (KeyTrigger(DIK_P) || ButtonTrigger(BUTTON_START)); }
	// �擾
	XINPUT_STATE*      GetXInputState(void)     { return &m_xInputState; }
	D3DXVECTOR2        GetCursorPosOnScreen(void);
	D3DXVECTOR2        GetCursorMove(void)      { return m_cursorMove; }
	StickInput         GetStick(STICK stick)    { return m_aStick[stick]; }
	ACTIVE_DEVICE_TYPE GetActiveInputType(void) { return m_activeInputType; }
	// �L�[�{�[�h
	bool KeyPress  (int nKey) { return m_aKeyPress  [nKey] != 0; }
	bool KeyTrigger(int nKey) { return m_aKeyTrigger[nKey] != 0; }
	bool KeyRepeat (int nKey) { return m_aKeyRepeat [nKey] != 0; }
	bool KeyRelease(int nKey) { return m_aKeyRelease[nKey] != 0; }
	// �}�E�X
	bool MousePress  (MOUSEBUTTON btn) { return m_aMousePress  [btn] != 0;  }
	bool MouseTrigger(MOUSEBUTTON btn) { return m_aMouseTrigger[btn] != 0;  }
	bool MouseRepeat (MOUSEBUTTON btn) { return m_aMouseRepeat [btn] != 0;  }
	bool MouseRelease(MOUSEBUTTON btn) { return m_aMouseRelease[btn] != 0;  }
	WHEELSPIN WheelSpin(void)          { return m_wheelSpin; }
	// �{�^��
	bool ButtonPress  (int nButton) { return m_aButtonPress  [nButton] != 0; }
	bool ButtonTrigger(int nButton) { return m_aButtonTrigger[nButton] != 0; }
	bool ButtonRepeat (int nButton) { return m_aButtonRepeat [nButton] != 0; }
	bool ButtonRelease(int nButton) { return m_aButtonRelease[nButton] != 0; }
	// �X�e�B�b�N
	float StickTiltRate    (STICK stick) { return m_aStick[stick].fTiltRate; }
	float StickTiltAngle   (STICK stick) { return m_aStick[stick].fTiltAngle; }
	bool  StickAnglePress  (STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAnglePress  [angle] != 0; }
	bool  StickAngleTrigger(STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAngleTrigger[angle] != 0; }
	bool  StickAngleRepeat (STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAngleRepeat [angle] != 0; }
	bool  StickAngleRelease(STICK stick, INPUT_ANGLE angle) { return m_aStick[stick].aAngleRelease[angle] != 0; }
	// �ݒ�
	void SetWheelSpin(WHEELSPIN wheelSpin) { m_wheelSpin = wheelSpin; }

private:
	//========== [[[ �萔�錾 ]]]
	static const int m_aMouseMask[MOUSEBUTTON_MAX];
	static const int m_aButtonMask[BUTTON_MAX];

	//========== [[[ �ϐ��錾 ]]]
	//----------�L�[�{�[�h----------
	/* �v���X���   */BYTE m_aKeyPress    [NUM_KEY_MAX];
	/* �g���K�[��� */BYTE m_aKeyTrigger  [NUM_KEY_MAX];
	/* �����[�X��� */BYTE m_aKeyRelease  [NUM_KEY_MAX];
	/* ���s�[�g��� */BYTE m_aKeyRepeat   [NUM_KEY_MAX];
	/* ���݂̎���   */DWORD m_aKeyCurrentTime  [NUM_KEY_MAX];
	/* �Ō�̎���   */DWORD m_aKeyExecLastTime [NUM_KEY_MAX];
	//----------�}�E�X----------
	/* �v���X���       */BYTE  m_aMousePress   [MOUSEBUTTON_MAX];
	/* �g���K�[���     */BYTE  m_aMouseTrigger [MOUSEBUTTON_MAX];
	/* �����[�X���     */BYTE  m_aMouseRelease [MOUSEBUTTON_MAX];
	/* ���s�[�g���     */BYTE  m_aMouseRepeat  [MOUSEBUTTON_MAX];
	/* ���݂̎���       */DWORD m_aMouseCurrentTime  [MOUSEBUTTON_MAX];
	/* �Ō�̎���       */DWORD m_aMouseExecLastTime [MOUSEBUTTON_MAX];
	/* �J�[�\���ʒu     */D3DXVECTOR2 m_cursorPos;
	/* �J�[�\���ړ���   */D3DXVECTOR2 m_cursorMove;
	/* �z�C�[����]��� */WHEELSPIN m_wheelSpin;
	//----------�R���g���[���[----------
	/* �v���X���        */BYTE  m_aButtonPress        [BUTTON_MAX];
	/* �g���K�[���      */BYTE  m_aButtonTrigger      [BUTTON_MAX];
	/* �����[�X���      */BYTE  m_aButtonRelease      [BUTTON_MAX];
	/* ���s�[�g���      */BYTE  m_aButtonRepeat       [BUTTON_MAX];
	/* ���݂̎���        */DWORD m_aButtonCurrentTime  [BUTTON_MAX];
	/* �Ō�̎���        */DWORD m_aButtonExecLastTime [BUTTON_MAX];
	/* �X�e�B�b�N���    */StickInput m_aStick[STICK_MAX];
	/* �U���J�E���^�[    */int m_nCounterVibration;
	/* �U���J�E���^�[MAX */int m_nCounterVibrationMax;
	/* �U���{��          */float m_fVibration;
	/* XInput�̏��      */XINPUT_STATE m_xInputState;

	//========== [[[ �ϐ��錾 ]]]
	LPDIRECTINPUT8       m_pInput;			// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	ACTIVE_DEVICE_TYPE   m_activeInputType;	// ���I�ȃf�o�C�X
	bool                 m_bFixedCursor;	// �J�[�\���Œ�t���O

	//========== [[[ �֐��錾 ]]]
	void UpdateKeyboard(void);
	void UpdateMouse(void);
	void UpdateCursor(void);
	void UpdateButton(void);
	void UpdateStick(void);
	void UpdateController(void);
};

#endif