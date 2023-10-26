//========================================
// 
// RNlibの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ RNlib.cpp ]]]
//========================================
#include <time.h>
#include "_ImGui\imgui.h"
#include "RNlib.h"

//****************************************
// 前方宣言
//****************************************
// imgui_impl_win32.cppのメッセージハンドラ
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//****************************************
// プロトタイプ宣言
//****************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************************************
// 静的宣言
//****************************************
namespace {
	//========== [[[ 関数宣言 ]]]
	void Init(HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Load(void);
	void Save(void);

	//========== [[[ 変数宣言 ]]]
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
//==========| RNLibの関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 取得・設定系処理
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
// メインループ
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
				WindowProc,		// ウィンドウプロシージャ
				pClassName,		// ウィンドウクラスの名前
				pWinName,		// ウィンドウの名前
				fWinWidth,		// ウィンドウの幅
				fWinHeight,		// ウィンドウの高さ
				bFullScreen,	// ウィンドウモード
				fResolution,	// 解像度倍率
			}
		);
	}

	if (bMessageLoop) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
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
		{// DirectXの処理
			m_dwCurrentTime = timeGetTime(); // 現在時刻を取得

			if ((m_dwCurrentTime - m_dwFPSLastTime) >= 500)
			{// 0.5秒経過
				// FPSを計測
				m_nFPSCount     = (m_dwFrameCount * 1000) / (m_dwCurrentTime - m_dwFPSLastTime);
				m_dwFPSLastTime = m_dwCurrentTime;	// FPSを測定した時刻を保存
				m_dwFrameCount  = 0;						// フレームカウントをクリア
			}

			// 60/1秒経過していない時は抜ける
			if ((m_dwCurrentTime - m_dwExecLastTime) <= (1000 / 60))
				return true;

			m_dwExecLastTime = m_dwCurrentTime;	// 処理開始時刻(現在時刻)を保存
			m_dwFrameCount++;							// フレームカウントを加算
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
// シーン終了処理
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
// ウィンドウプロシージャ
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
			if (MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO) == IDYES)
				DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO) == IDYES)
			DestroyWindow(hWnd);
		else
			return 0;	// (※0を返さないと終了してしまう)
		break;

	case WM_MOUSEWHEEL:
		// マウスホイールの前回転/後回転 状態設定
		if (HIWORD(wParam) == WHEEL_DELTA)
			m_input.SetWheelSpin(CInput::WHEELSPIN::FRONT);
		else
			m_input.SetWheelSpin(CInput::WHEELSPIN::BACK);
		break;

	case WM_LBUTTONDOWN:
		SetFocus(hWnd); // マウスを左クリックしたウインドウにフォーカスを合わせ、アクティブにする
		break;
	}

	// 既定の処理を返す
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| 無名名前空間の関数
//----------|---------------------------------------------------------------------
//================================================================================
namespace {
	//========================================
	// 初期化処理
	// Author:RIKU NISHIMURA
	//========================================
	void Init(HINSTANCE hInstance) {
		// 終了後にメモリリークを出力
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
		srand((unsigned int)time(0));	// 乱数の種を取得
		timeBeginPeriod(1);				// 分解能を設定
	
		m_dwCurrentTime    = 0;				// 現在時刻を初期化
		m_dwExecLastTime   = timeGetTime();	// 現在時刻を取得(保存)
		m_dwFrameCount     = 0;				// フレームカウントを初期化
		m_dwFPSLastTime    = timeGetTime();	// 現在時刻を取得(保存)
		m_nCount           = 0;
		m_bBlinkF2         = false;
		m_bBlinkF4         = false;
		m_bSpace3DStop     = false;
		m_bSpace3DStopRsrv = false;
		m_bSceneSwap       = false;

		// デバイスを取得
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
	// 終了処理
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
	
		// 分解能を戻す
		timeEndPeriod(1);
	}
	
	//========================================
	// 更新処理
	// Author:RIKU NISHIMURA
	//========================================
	void Update(void) {
		m_bSpace3DStop = m_bSpace3DStopRsrv;

		// カウント加算
		m_nCount   = (m_nCount + 1) % INT_MAX;
		m_bBlinkF2 = (m_nCount % 4 < 2);
		m_bBlinkF4 = (m_nCount % 8 < 4);

		// 全オブジェクトマネージャーの更新処理
		CObjectMgr::UpdateAllMgrs();

		//----------------------------------------
		// 各オプションの更新処理
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
	// 描画処理
	// Author:RIKU NISHIMURA
	//========================================
	void Draw(void) {

		// どうしても遷移は一番描画優先度を高くしたい。暫定対応
		m_transition.Update();

		// デバイスを取得
		LPDIRECT3DDEVICE9 device = m_window.GetD3DDevice();

		m_polygon3D.Put(ConvPosRotToMatrix(D3DXVECTOR3(0.0f, 0.0f, 43.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), true)
			->SetSize(m_window.GetWidth() * 0.05f, m_window.GetHeight() * 0.05f)
			->SetTex_Camera(&m_camera)
			->SetLighting(false)
			->SetPriority(0)
			;

		// 描画開始
		if (SUCCEEDED(device->BeginScene())) {

			if (m_drawMng.StartDraw()) {

				{// [[[ スクリーンオブジェクト描画 ]]]
					// スクリーンレンダリング開始
					CCamera::StartRenderingScreen(device);

					// 描画
					m_drawMng.Draw(device, true);

					// ImGuiの描画処理
					if (m_bUseImGui)
						ImGuiDraw();
				}// <<< >>>

				{// [[[ カメラオブジェクト描画 ]]]
					// 現在のレンダリングターゲットとZバッファを保存
					LPDIRECT3DSURFACE9 renderDef, ZBuffDef;
					D3DVIEWPORT9 viewPortDef;
					device->GetRenderTarget       (0, &renderDef);
					device->GetDepthStencilSurface(&ZBuffDef);
					device->GetViewport           (&viewPortDef);

					// レンダリング開始
					m_camera.StartRendering(device);

					// 描画
					m_drawMng.Draw(device, false);

					// レンダリング終了
					m_camera.EndRendering(device);

					// レンダリングターゲットとZバッファを元に戻す
					device->SetRenderTarget       (0, renderDef);
					device->SetDepthStencilSurface(ZBuffDef);
					device->SetViewport           (&viewPortDef);
				}// <<< >>>

				// 描画終了
				device->EndScene();

				// バックバッファをフロントバッファと入れ替え
				device->Present(NULL, NULL, NULL, NULL);
			}
			else {
				// 描画終了
				device->EndScene();
			}
		}
	
		// 設定リセット
		if ((!m_bSpace3DStop && !m_bSpace3DStopRsrv) || m_bSceneSwap) {
			m_line3D.SetReset();
			m_bSceneSwap = false;
		}
	}

	//========================================
	// 読み込み処理
	// Author:RIKU NISHIMURA
	//========================================
	void Load(void) {
		m_sound   .Load();
		m_text    .LoadFont();
		m_visual  .Load();
		m_eff3DMng.Load();
	}

	//========================================
	// 書き込み処理
	// Author:RIKU NISHIMURA
	//========================================
	void Save(void) {

	}
}