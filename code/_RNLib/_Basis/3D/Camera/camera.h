//========================================
// 
// �J�����̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// �J�����N���X
class CCamera {
public:
	//========== [[[ �񋓌^��` ]]]
	// ���
	enum class STATE {
		NONE,
		GRAB_AIR_MOUSE,		// �}�E�X�Œ���͂�
		RECIPROCATE_SPIN,	// ������]
		MAX,
	};

	// �U���̋���
	enum class VIB_POWER { LOW, MID, HIGH, MAX, };

	//========== [[[ �֐��錾 ]]]
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetTexture(LPDIRECT3DDEVICE9 device) { device->SetTexture(0, m_texturesMT[0]); }
	// �ݒ�n
	static void StartRenderingScreen(LPDIRECT3DDEVICE9 device);
	void StartRendering (LPDIRECT3DDEVICE9 device);
	void EndRendering   (LPDIRECT3DDEVICE9 device);
	void SetGeometryInfo(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR);
	void SetVib         (const VIB_POWER vibPower);
	void SetRadianGoal  (const float fGoal) { m_radianGoal = fGoal; }
	void SetFixed       (const bool bFixed) { m_isFixed = bFixed; };
	void PivotToPosV    (void)              { if (m_state == STATE::NONE) m_isPivotToPosV = true; }
	void PivotToPosR    (void)              { if (m_state == STATE::NONE) m_isPivotToPosV = false; }
	// �擾
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	D3DXVECTOR3 GetRot (void) { return m_rot; }
	D3DXVECTOR3 GetVec (void) { return m_posR - m_posV; }
	D3DXVECTOR3 GetNor (void) { 
		D3DXVECTOR3 vec = GetVec();
		return *D3DXVec3Normalize(&vec, &vec);
	}
	// ��Ԍn
	void RemoveState    (void) { SetState(STATE::NONE); }
	void GrabAirMouse   (const float moveForce, const float spinForce, const float zoomForce);
	void ReciprocateSpin(const D3DXVECTOR3 posR, const float dist, const D3DXVECTOR3 rotA, const D3DXVECTOR3 rotB, const int time);
	// ����n
	void ParallelMove(const D3DXVECTOR3 move) { m_posV += move; m_posR += move; }
	void Spin        (const D3DXVECTOR3 add)  { m_spin += add;   }

private:
	//========== [[[ �\���̐錾 ]]]
	struct GrabAirMouseInfo {
		float moveForce;
		float spinForce;
		float zoomForce;
	};
	struct ReciprocateSpinInfo {
		D3DXVECTOR3 rotA = INITD3DXVECTOR3;
		D3DXVECTOR3 rotB = INITD3DXVECTOR3;
		int time  = 0;
		int count = 0;
	};

	//========== [[[ �֐��錾 ]]]
	static void SetUpProjectionMatrix(LPDIRECT3DDEVICE9 device, const float radian);
	void ProcessState(const PROCESS process);
	void SetState(const STATE state);

	//========== [[[ �ϐ��̐錾 ]]]
	D3DXVECTOR3 m_posV;		// ���_
	D3DXVECTOR3 m_posR;		// �����_
	D3DXVECTOR3 m_posVib;	// �U���ʒu
	// �^���n
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_spin;
	float       m_dist;
	float       m_radian;
	float       m_radianGoal;
	float       m_vibForce;
	// ��Ԍn
	bool        m_isPivotToPosV;
	bool        m_isFixed;
	STATE       m_state;
	void*       m_stateInfo;
	// �}���`�^�[�Q�b�g�����_�����O
	LPDIRECT3DTEXTURE9      m_texturesMT[2];	// �����_�����O�^�[�Q�b�g�p�e�N�X�`��
	LPDIRECT3DSURFACE9      m_rendersMT[2];		// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	LPDIRECT3DSURFACE9      m_ZBuffMT;			// �e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9            m_viewportMT;		// �e�N�X�`�������_�����O�p�r���[�|�[�g
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuffMT;		// �t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
};