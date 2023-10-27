//========================================
// 
// �E�B���h�E�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ window.h ]]]
//========================================
#ifndef _WINDOW_H_
#define _WINDOW_H_

//****************************************
// �}�N����`
//****************************************
#define IMGUI_CORRECT_X (0.98775f)	// ImGui�p�̃E�B���h�E�̈�␳�lX
#define IMGUI_CORRECT_Y (0.94735f)	// ImGui�p�̃E�B���h�E�̈�␳�lY
// (��ImGui�������蔻��̍ۂ�Direct3D�f�o�C�X�̉�ʃT�C�Y���Q�Ƃ��Ă���A�덷�𖄂߂�ׂ̐��l)

//****************************************
// �N���X��`
//****************************************
// �E�B���h�E�N���X
class CWindow {
public:
	//========== [[[ �\���̒�` ]]]
	// �쐬���\����
	typedef struct {
		WNDPROC     lpfnWndProc;	// �E�B���h�E�v���V�[�W��
		const char* pClassName;
		const char* pName;
		float       fWidth;
		float       fHeight;
		bool        bFullScreen;
		float       fResolution;	// �𑜓x�{��
	}CreateInfo;

	//========== [[[ �֐��錾 ]]]
	CWindow();
	~CWindow();
	void Update(void);
	void Uninit(void);
	void Destroy(void);
	int  Create       (HINSTANCE hInstance, CreateInfo ci);
	void ShowTaskBar  (const bool bShow);
	void SetFullScreen(const bool bFullScreen);
	bool FindFocused  (HWND hWnd);
	// ���b�Z�[�W����
	void Message         (const char* pText, const char* pCaption);
	void Message_ERROR   (const char* pText);
	bool Message_OKCANCEL(const char* pText, const char* pCaption);
	// �ݒ�擾
	D3DXVECTOR3       GetPos       (void) { return m_pos;         }
	float             GetWidth     (void) { return m_fWidth;      }
	float             GetHeight    (void) { return m_fHeight;     }
	float             GetCenterX   (void) { return m_fCenterX;    }
	float             GetCenterY   (void) { return m_fCenterY;    }
	D3DXVECTOR3       GetCenterPos (void) { return D3DXVECTOR3(m_fCenterX, m_fCenterY, 0.0f); }
	float             GetAreaWidth (void) { return m_fAreaWidth;  }
	float             GetAreaHeight(void) { return m_fAreaHeight; }
	float             GetResolution(void) { return m_fResolution; }
	LPDIRECT3DDEVICE9 GetD3DDevice (void) { return m_pD3DDevice;  }
	HWND              GetHandle    (void) { return m_hWnd;        }

private:
	//========== [[[ �֐��錾 ]]]
	int CreateDirect3DDevice(HINSTANCE hInstance, CreateInfo ci);

	//========== [[[ �ϐ��錾 ]]]
	D3DXVECTOR3       m_pos;
	HINSTANCE         m_hInstance;
	const char*       m_pClassName;
	float             m_fWidth;
	float             m_fHeight;
	float             m_fCenterX;
	float             m_fCenterY;
	float             m_fAreaWidth;		// �̈�̕�
	float             m_fAreaHeight;	// �̈�̍���
	float             m_fResolution;	// �𑜓x
	LPDIRECT3D9       m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	HWND              m_hWnd;
};

#endif