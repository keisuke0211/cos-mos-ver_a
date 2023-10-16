//========================================
// 
// �E�B���h�E�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ window.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CWindow�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CWindow::CWindow(void) {
	m_pos         = INITD3DXVECTOR3;
	m_pClassName  = NULL;
	m_fWidth      = 0.0f;
	m_fHeight     = 0.0f;
	m_fCenterX    = 0.0f;
	m_fCenterY    = 0.0f;
	m_fAreaWidth  = 0.0f;
	m_fAreaHeight = 0.0f;
	m_fResolution = 0.0f;
	m_pD3D        = NULL;
	m_pD3DDevice  = NULL;
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CWindow::~CWindow(void) {

}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CWindow::Update(void) {
	RECT rec;
	GetWindowRect(m_hWnd, &rec);
	m_pos = D3DXVECTOR3(rec.left, rec.top, 0.0f);
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CWindow::Uninit(void) {
	// Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL) {
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL) {
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(m_pClassName, m_hInstance);

	ShowTaskBar(true);
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CWindow::Destroy(void) {
	DestroyWindow(m_hWnd);
}

//========================================
// CreateWindowRN�֐� - �E�C���h�E�쐬 -
// Author:RIKU NISHIMURA
//========================================
int CWindow::Create(HINSTANCE hInstance, CreateInfo cwi) {
	// �E�C���h�E�N���X�̍\����
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						// �E�C���h�E�̃X�^�C��
		cwi.lpfnWndProc,				// �E�C���h�E�v���V�[�W��
		0,								// 0�ɂ���
		0,								// 0�ɂ���
		hInstance,						// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �N���C�A���g�̈�̔w�i�F
		NULL,							// ���j���[�o�[
		cwi.pClassName,					// �E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	// �t�@�C���̃A�C�R��
	};

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�C���h�E�𐶐�
	m_hWnd = CreateWindowEx(
		0,								// �g���E�C���h�E�X�^�C��
		cwi.pClassName,					// �E�C���h�E�N���X�̖��O
		cwi.pName,						// �E�C���h�E�̖��O
		WS_SYSMENU | WS_MINIMIZEBOX,	// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,					// �E�C���h�E�̍���X���W
		CW_USEDEFAULT,					// �E�C���h�E�̍���Y���W
		cwi.fWidth,						// �E�C���h�E�̕�
		cwi.fHeight,					// �E�C���h�E�̍���
		NULL,							// �e�E�C���h�E�̃n���h��
		NULL,							// ���j���[�n���h���܂���
		hInstance,						// �C���X�^���X�n���h��
		NULL);							// �E�C���h�E�쐬�f�[�^

	// Direct3D�f�o�C�X�̐���
	if (CreateDirect3DDevice(hInstance, cwi) == -1)
		return -1;

	// �E�B���h�E�̃��[�h��ݒ肷��
	SetFullScreen(cwi.bFullScreen);

	return 0;
}

//========================================
// Direct3D�f�o�C�X�̐���
// Author:RIKU NISHIMURA
//========================================
int CWindow::CreateDirect3DDevice(HINSTANCE hInstance, CreateInfo ci) {
	// �E�B���h�E�̏����L��
	m_hInstance    = hInstance;
	m_pClassName   = ci.pClassName;
	m_fWidth       = ci.fWidth;
	m_fHeight      = ci.fHeight;
	m_fCenterX     = ci.fWidth  * 0.5f;
	m_fCenterY     = ci.fHeight * 0.5f;
	m_fAreaWidth   = ci.fWidth  * ci.fResolution;
	m_fAreaHeight  = ci.fHeight * ci.fResolution;
	m_fResolution  = ci.fResolution;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
		return -1;

	// ���݂̃f�B�X�v���C���[�h���擾
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^���[���N���A
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// ��ʃT�C�Y�ݒ�(ImGui�ɉ�����)
	if (RNLib::GetUseImGui()) {
		d3dpp.BackBufferWidth  = ci.fWidth  * IMGUI_CORRECT_X;
		d3dpp.BackBufferHeight = ci.fHeight * IMGUI_CORRECT_Y;
	}
	else {
		d3dpp.BackBufferWidth  = ci.fWidth  * ci.fResolution;
		d3dpp.BackBufferHeight = ci.fHeight * ci.fResolution;
	}

	d3dpp.BackBufferFormat           = d3ddm.Format;				// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount            = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD;		// �_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil     = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed                   = !ci.bFullScreen;				// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// Direct3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice))) {

		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice))) {

			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				m_hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice))) {
				return -1;
			}
		}
	}

	return 0;
}

//========================================
// �^�X�N�o�[�̕\��/��\����؂�ւ�
// Author:RIKU NISHIMURA
// �Q�l: https://dixq.net/forum/viewtopic.php?t=12505
//========================================
void CWindow::ShowTaskBar(const bool bShow) {
	// �^�X�N�o�[�̃n���h�����擾
	HWND hTask;
	hTask = FindWindow((LPCSTR)"Shell_TrayWnd", NULL);

	if (bShow) {
		ShowWindow(hTask, SW_SHOW);
		SetFocus(m_hWnd);	// ���̃E�B���h�E�Ƀt�H�[�J�X�𓖂Ă�
	}
	else {
		ShowWindow(hTask, SW_HIDE);
	}
}

//========================================
// �t���X�N���[���ݒ�
// Author:RIKU NISHIMURA
//========================================
void CWindow::SetFullScreen(bool bFullScreen) {
	HDC hDC       = GetDC(GetDesktopWindow());		// �f�X�N�g�b�v�̃n���h��
	int nScrSizeX = GetDeviceCaps(hDC, HORZRES);	// �f�X�N�g�b�v�̉�ʃT�C�YX
	int nScrSizeY = GetDeviceCaps(hDC, VERTRES);	// �f�X�N�g�b�v�̉�ʃT�C�YY

	// �f�X�N�g�b�v�̃n���h���������
	ReleaseDC(GetDesktopWindow(), hDC);

	if (bFullScreen) {
		SetWindowPos(
			m_hWnd,
			HWND_TOP,
			0,
			0,
			nScrSizeX,
			nScrSizeY,
			SWP_SHOWWINDOW);

		// �X�^�C���ύX
		SetWindowLong(m_hWnd,
			GWL_STYLE, WS_POPUP);
	}
	else {
		SetWindowPos(
			m_hWnd,
			HWND_TOP,
			(nScrSizeX * 0.5f) - (m_fWidth  * 0.5f),	// �ʒu�𒆉��ɍ��킹��
			(nScrSizeY * 0.5f) - (m_fHeight * 0.5f),
			m_fWidth,
			m_fHeight,
			SWP_SHOWWINDOW);

		// �X�^�C���ύX
		SetWindowLong(m_hWnd, GWL_STYLE,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	}

	ShowWindow(m_hWnd, SW_NORMAL);	// �E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(m_hWnd);			// �N���C�A���g�̈���X�V
	ShowTaskBar(!bFullScreen);		// �^�X�N�o�[��\��/��\��
}

//========================================
// ���b�Z�[�W����
// Author:RIKU NISHIMURA
//========================================
void CWindow::Message(const char *pText, const char *pCaption) {
	MessageBox(m_hWnd, pText, pCaption, MB_OK);
}

//========================================
// ���b�Z�[�W����(OK or CANCEL)
// Author:RIKU NISHIMURA
//========================================
bool CWindow::Message_OKCANCEL(const char* pText, const char* pCaption) {
	switch (MessageBox(m_hWnd, pText, pCaption, MB_OKCANCEL)) {
	case IDOK:
		return true;
	case IDCANCEL:
		return false;
	}

	return false;
}

//========================================
// �t�H�[�J�X���������Ă��邩���ׂ�
// Author:RIKU NISHIMURA
//========================================
bool CWindow::FindFocused(HWND hWnd) {
	HRESULT hr = m_pD3DDevice->TestCooperativeLevel();

	// �f�o�C�X�������Ă���ꍇ�̓t�H�[�J�X���������Ă��Ȃ��Ƃ݂Ȃ�
	if (hr == D3DERR_DEVICELOST || hr == D3DERR_DEVICENOTRESET)
		return false;

	return (GetForegroundWindow() == hWnd);
}