//========================================
// 
// RNlib�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ RNlib.cpp ]]]
//========================================
#include <time.h>
#include "_ImGui\imgui.h"
#include "RNlib.h"

//****************************************
// �O���錾
//****************************************
// imgui_impl_win32.cpp�̃��b�Z�[�W�n���h��
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//****************************************
// �v���g�^�C�v�錾
//****************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************************************
// �ÓI�錾
//****************************************
namespace {
	//========== [[[ �֐��錾 ]]]
	void Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);
	void Save(void);

	//========== [[[ �ϐ��錾 ]]]
	RNLib::SIGNAL m_signal = RNLib::SIGNAL::NONE;
	bool          m_bUseImGui;
	int           m_nCount;
	DWORD         m_dwCurrentTime;
	DWORD         m_dwExecLastTime;
	DWORD         m_dwFrameCount;
	DWORD         m_dwFPSLastTime;
	int           m_nFPSCount;
	bool          m_bBlinkF2;
	bool          m_bBlinkF4;
	bool          m_bSpace3DStop;
	bool          m_bSpace3DStopRsrv;
	bool          m_bSceneSwap;

	//----- Items
	CText2D      m_text2D;
	CPolygon2D   m_polygon2D;
	//CMotion3D    m_motion3D;
	//CHuman3DBase m_human3DBase;
	CSetUp3D  m_modelSetUp;
	CModel       m_model;
	CEff3DMng    m_eff3DMng;
	CText3D      m_text3D;
	CPolygon3D   m_polygon3D;
	CLine3D      m_line3D;
	CFog         m_fog;
	CLight3D     m_light3D;
	CShadow3D    m_shadow3D;
	CCamera      m_camera;
	CFile        m_file;
	CInput       m_input;
	CMemory      m_memory;
	CSound       m_sound;
	CWindow      m_window;
	CText        m_text;
	CTexture     m_texture;
	CTransition  m_transition;
	CVisual      m_visual;
	CDrawMng     m_drawMng;
	CDrawState   m_drawState;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| RNLib�̊֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �擾�E�ݒ�n����
// Author:RIKU NISHIMURA
//========================================
RNLib::SIGNAL  RNLib::GetSignal     (void)       { return m_signal;        }
int            RNLib::GetCount      (void)       { return m_nCount;        }
int            RNLib::GetFPSCount   (void)       { return m_nFPSCount;     }
bool           RNLib::GetBlinkF2    (void)       { return m_bBlinkF2;      }
bool           RNLib::GetBlinkF4    (void)       { return m_bBlinkF4;      }
bool           RNLib::GetUseImGui   (void)       { return m_bUseImGui;     }
void           RNLib::SetSpace3DStop(bool bStop) { m_bSpace3DStopRsrv = bStop; }
bool           RNLib::GetSpace3DStop(void)       { return m_bSpace3DStop;  }
bool           RNLib::GetSceneSwap  (void)       { return m_bSceneSwap;    }
CText2D*       RNLib::Text2D        (void)       { return &m_text2D;       }
CPolygon2D*    RNLib::Polygon2D     (void)       { return &m_polygon2D;    }
//CMotion3D*     RNLib::Motion3D      (void)       { return &m_motion3D;     }
//CHuman3DBase*  RNLib::Human3DBase   (void)       { return &m_human3DBase;  }
CSetUp3D*   RNLib::ModelSetUp    (void)       { return &m_modelSetUp;   }
CModel*        RNLib::Model         (void)       { return &m_model;        }
CEff3DMng*     RNLib::Eff3DMng      (void)       { return &m_eff3DMng;     }
CText3D*       RNLib::Text3D        (void)       { return &m_text3D;       }
CPolygon3D*    RNLib::Polygon3D     (void)       { return &m_polygon3D;    }
CLine3D*       RNLib::Line3D        (void)       { return &m_line3D;       }
CFog*          RNLib::Fog           (void)       { return &m_fog;          }
CLight3D*      RNLib::Light3D       (void)       { return &m_light3D;      }
CShadow3D*     RNLib::Shadow3D      (void)       { return &m_shadow3D;     }
CCamera*       RNLib::Camera3D      (void)       { return &m_camera;       }
CFile*         RNLib::File          (void)       { return &m_file;         }
CInput*        RNLib::Input         (void)       { return &m_input;        }
CMemory*       RNLib::Memory        (void)       { return &m_memory;       }
CSound*        RNLib::Sound         (void)       { return &m_sound;        }
CWindow*       RNLib::Window        (void)       { return &m_window;       }
CText*         RNLib::Text          (void)       { return &m_text;         }
CTexture*      RNLib::Texture       (void)       { return &m_texture;      }
CTransition*   RNLib::Transition    (void)       { return &m_transition;   }
CVisual*       RNLib::Visual        (void)       { return &m_visual;       }
CDrawMng*      RNLib::DrawMng       (void)       { return &m_drawMng;      }
CDrawState*    RNLib::DrawStateMng  (void)       { return &m_drawState;    }

//========================================
// ���C�����[�v
// Author:RIKU NISHIMURA
//========================================
bool RNLib::MainLoop(
	int*           pEndCode,
	HINSTANCE      hInstance,
	const char*    pClassName,
	const char*    pWinName,
	const float    fWinWidth,
	const float    fWinHeight,
	const bool     bFullScreen,
	const float    fResolution,
	const bool     bUseImGui) {
	static bool bMessageLoop = false;
	static MSG  msg;

	if (m_signal == RNLib::SIGNAL::NONE) {
		m_bUseImGui = bUseImGui;
		m_window.Create(
			hInstance,
			{
				WindowProc,		// �E�B���h�E�v���V�[�W��
				pClassName,		// �E�B���h�E�N���X�̖��O
				pWinName,		// �E�B���h�E�̖��O
				fWinWidth,		// �E�B���h�E�̕�
				fWinHeight,		// �E�B���h�E�̍���
				bFullScreen,	// �E�B���h�E���[�h
				fResolution,	// �𑜓x�{��
			}
		);
	}

	if (bMessageLoop) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if (msg.message == WM_QUIT) {
				m_signal = SIGNAL::SAVE;
				bMessageLoop = false;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return true;
		}
		else
		{// DirectX�̏���
			m_dwCurrentTime = timeGetTime(); // ���ݎ������擾

			if ((m_dwCurrentTime - m_dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS���v��
				m_nFPSCount     = (m_dwFrameCount * 1000) / (m_dwCurrentTime - m_dwFPSLastTime);
				m_dwFPSLastTime = m_dwCurrentTime;	// FPS�𑪒肵��������ۑ�
				m_dwFrameCount  = 0;						// �t���[���J�E���g���N���A
			}

			// 60/1�b�o�߂��Ă��Ȃ����͔�����
			if ((m_dwCurrentTime - m_dwExecLastTime) <= (1000 / 60))
				return true;

			m_dwExecLastTime = m_dwCurrentTime;	// �����J�n����(���ݎ���)��ۑ�
			m_dwFrameCount++;							// �t���[���J�E���g�����Z
		}
	}

	switch (m_signal) {
	case RNLib::SIGNAL::NONE       :m_signal = RNLib::SIGNAL::LOAD       ; break;
	case RNLib::SIGNAL::INIT       :m_signal = RNLib::SIGNAL::UPDATE_WAIT; break;
	case RNLib::SIGNAL::UNINIT     :m_signal = RNLib::SIGNAL::END        ; break;
	case RNLib::SIGNAL::UPDATE     :m_signal = RNLib::SIGNAL::DRAW       ; break;
	case RNLib::SIGNAL::UPDATE_WAIT:m_signal = RNLib::SIGNAL::UPDATE     ; break;
	case RNLib::SIGNAL::DRAW       :m_signal = RNLib::SIGNAL::UPDATE_WAIT; break;
	case RNLib::SIGNAL::LOAD       :m_signal = RNLib::SIGNAL::INIT       ; break;
	case RNLib::SIGNAL::SAVE       :m_signal = RNLib::SIGNAL::UNINIT     ; break;
	}

	switch (m_signal) {
	case RNLib::SIGNAL::INIT:
		Init(hInstance);
		break;
	case RNLib::SIGNAL::UNINIT:
		Uninit();
		*pEndCode = (int)msg.wParam;
		break;
	case RNLib::SIGNAL::UPDATE:
		Update();
		bMessageLoop = false;
		break;
	case RNLib::SIGNAL::UPDATE_WAIT:
		bMessageLoop = true;
		break;
	case RNLib::SIGNAL::DRAW:
		Draw();
		break;
	case RNLib::SIGNAL::LOAD:
		Load();
		break;
	case RNLib::SIGNAL::SAVE:
		Save();
		break;
	case RNLib::SIGNAL::END:
		return false;
	}

	return true;
}

//========================================
// �V�[���I������
// Author:RIKU NISHIMURA
//========================================
void RNLib::UninitScene(void) {
	m_eff3DMng.ReleaseAll();
	m_sound   .Stop();
	m_light3D .SetCol(INITCOLOR);
	m_fog     .SetUse(false);
	RNLib::Camera3D()->SetFixed(false);
	m_bSceneSwap = true;
	m_bSpace3DStopRsrv = false;
}

//========================================
// �E�B���h�E�v���V�[�W��
// Author:RIKU NISHIMURA
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (m_bUseImGui) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return 0;
	}

	int nID = DATANONE;
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			if (MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO) == IDYES)
				DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO) == IDYES)
			DestroyWindow(hWnd);
		else
			return 0;	// (��0��Ԃ��Ȃ��ƏI�����Ă��܂�)
		break;

	case WM_MOUSEWHEEL:
		// �}�E�X�z�C�[���̑O��]/���] ��Ԑݒ�
		if (HIWORD(wParam) == WHEEL_DELTA)
			m_input.SetWheelSpin(CInput::WHEELSPIN::FRONT);
		else
			m_input.SetWheelSpin(CInput::WHEELSPIN::BACK);
		break;

	case WM_LBUTTONDOWN:
		SetFocus(hWnd); // �}�E�X�����N���b�N�����E�C���h�E�Ƀt�H�[�J�X�����킹�A�A�N�e�B�u�ɂ���
		break;
	}

	// ����̏�����Ԃ�
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �������O��Ԃ̊֐�
//----------|---------------------------------------------------------------------
//================================================================================
namespace {
	//========================================
	// ����������
	// Author:RIKU NISHIMURA
	//========================================
	void Init(HINSTANCE hInstance) {
		// �I����Ƀ��������[�N���o��
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
		srand((unsigned int)time(0));	// �����̎���擾
		timeBeginPeriod(1);				// ����\��ݒ�
	
		m_dwCurrentTime    = 0;				// ���ݎ�����������
		m_dwExecLastTime   = timeGetTime();	// ���ݎ������擾(�ۑ�)
		m_dwFrameCount     = 0;				// �t���[���J�E���g��������
		m_dwFPSLastTime    = timeGetTime();	// ���ݎ������擾(�ۑ�)
		m_nCount           = 0;
		m_bBlinkF2         = false;
		m_bBlinkF4         = false;
		m_bSpace3DStop     = false;
		m_bSpace3DStopRsrv = false;
		m_bSceneSwap       = false;

		// �f�o�C�X���擾
		LPDIRECT3DDEVICE9 device = m_window.GetD3DDevice();

		m_drawMng  .Init();
		m_drawState.Init(device);
		m_line3D   .Init();
		m_fog      .Init();
		m_light3D  .Init();
		m_shadow3D .Init();
		m_camera   .Init();
		m_input    .Init(hInstance);
		m_sound    .Init();
	
		//;;
		InitSetting();
	
		if (m_bUseImGui)
			ImGuiInit(m_window.GetHandle());
	}
	
	//========================================
	// �I������
	// Author:RIKU NISHIMURA
	//========================================
	void Uninit(void) {
		//m_motion3D   .Uninit();
		//m_human3DBase.Uninit();
		//m_modelSetUp .Uninit();
		m_drawMng    .Uninit();
		m_drawState  .Uninit();
		m_line3D     .Uninit();
		m_light3D    .Uninit();
		m_camera     .Uninit();
		m_text       .Uninit();
		m_input      .Uninit();
		m_window     .Uninit();
	
		//;;
		UninitSetting();
		UninitPrint();
	
		m_sound  .Uninit();

		if (m_bUseImGui)
			ImGuiUninit();
	
		// ����\��߂�
		timeEndPeriod(1);
	}
	
	//========================================
	// �X�V����
	// Author:RIKU NISHIMURA
	//========================================
	void Update(void) {
		m_bSpace3DStop = m_bSpace3DStopRsrv;

		// �J�E���g���Z
		m_nCount   = (m_nCount + 1) % INT_MAX;
		m_bBlinkF2 = (m_nCount % 4 < 2);
		m_bBlinkF4 = (m_nCount % 8 < 4);

		// �S�I�u�W�F�N�g�}�l�[�W���[�̍X�V����
		CObjectMgr::UpdateAllMgrs();

		//----------------------------------------
		// �e�I�v�V�����̍X�V����
		//----------------------------------------
		m_input   .Update();
		m_sound   .Update();
		m_light3D .Update();

		if (!m_bSpace3DStop) {
			m_camera.Update();
		}

		//;;
		UpdateSetting();
	
		m_window.Update();
		
		m_input.SetWheelSpin(CInput::WHEELSPIN::NONE);
	
		if (m_bUseImGui)
			ImGuiInitFlag();
	}

	//========================================
	// �`�揈��
	// Author:RIKU NISHIMURA
	//========================================
	void Draw(void) {

		// �ǂ����Ă��J�ڂ͈�ԕ`��D��x�������������B�b��Ή�
		m_transition.Update();

		// �f�o�C�X���擾
		LPDIRECT3DDEVICE9 device = m_window.GetD3DDevice();

		m_polygon3D.Put(ConvPosRotToMatrix(D3DXVECTOR3(0.0f, 0.0f, 43.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), true)
			->SetSize(m_window.GetWidth() * 0.05f, m_window.GetHeight() * 0.05f)
			->SetTex_Camera(&m_camera)
			->SetLighting(false)
			->SetPriority(0)
			;

		// �`��J�n
		if (SUCCEEDED(device->BeginScene())) {

			if (m_drawMng.StartDraw()) {

				{// [[[ �X�N���[���I�u�W�F�N�g�`�� ]]]
					// �X�N���[�������_�����O�J�n
					CCamera::StartRenderingScreen(device);

					// �`��
					m_drawMng.Draw(device, true);

					// ImGui�̕`�揈��
					if (m_bUseImGui)
						ImGuiDraw();
				}// <<< >>>

				{// [[[ �J�����I�u�W�F�N�g�`�� ]]]
					// ���݂̃����_�����O�^�[�Q�b�g��Z�o�b�t�@��ۑ�
					LPDIRECT3DSURFACE9 renderDef, ZBuffDef;
					D3DVIEWPORT9 viewPortDef;
					device->GetRenderTarget       (0, &renderDef);
					device->GetDepthStencilSurface(&ZBuffDef);
					device->GetViewport           (&viewPortDef);

					// �����_�����O�J�n
					m_camera.StartRendering(device);

					// �`��
					m_drawMng.Draw(device, false);

					// �����_�����O�I��
					m_camera.EndRendering(device);

					// �����_�����O�^�[�Q�b�g��Z�o�b�t�@�����ɖ߂�
					device->SetRenderTarget       (0, renderDef);
					device->SetDepthStencilSurface(ZBuffDef);
					device->SetViewport           (&viewPortDef);
				}// <<< >>>

				// �`��I��
				device->EndScene();

				// �o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɠ���ւ�
				device->Present(NULL, NULL, NULL, NULL);
			}
			else {
				// �`��I��
				device->EndScene();
			}
		}
	
		// �ݒ胊�Z�b�g
		if ((!m_bSpace3DStop && !m_bSpace3DStopRsrv) || m_bSceneSwap) {
			m_line3D.SetReset();
			m_bSceneSwap = false;
		}
	}

	//========================================
	// �ǂݍ��ݏ���
	// Author:RIKU NISHIMURA
	//========================================
	void Load(void) {
		m_sound   .Load();
		m_text    .LoadFont();
		m_visual  .Load();
		m_eff3DMng.Load();
	}

	//========================================
	// �������ݏ���
	// Author:RIKU NISHIMURA
	//========================================
	void Save(void) {

	}
}