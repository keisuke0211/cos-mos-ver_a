//========================================
// 
// �`���Ԃ̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// �`���ԃN���X
class CDrawState {
public:
	//========== [[[ �񋓌^��` ]]]]
	// Z�e�X�g���[�h
	enum class ZTEST_MODE {
		ENABLED,	// �L��
		DISABLED,	// ����
	};
	// �J�����O���[�h
	enum class CULLING_MODE {
		FRONT_SIDE,	// �\��
		BACK_SIDE,	// ����
		BOTH_SIDES,	// ����
	};
	// �e�N�X�`�����߃��[�h
	enum class TEXTURE_ALPHA_MODE {
		ENABLED,	// �L��
		DISABLED,	// ����
	};
	// ���C�e�B���O���[�h
	enum class LIGHTING_MODE {
		ENABLED,	// �L��
		DISABLED,	// ����
	};

	//========== [[[ �֐��錾 ]]]
	CDrawState();
	~CDrawState();
	void Init(LPDIRECT3DDEVICE9& device);
	void Uninit(void);
	void StartTemporarySetMode(void);
	void EndTemporarySetMode(LPDIRECT3DDEVICE9& device);
	void SetZTestMode(const ZTEST_MODE& mode, LPDIRECT3DDEVICE9& device);
	void SetZTestMode(const bool& isZTest, LPDIRECT3DDEVICE9& device);
	void SetCullingMode(const CULLING_MODE& mode, LPDIRECT3DDEVICE9& device);
	void SetTextureAlphaMode(const TEXTURE_ALPHA_MODE& mode, LPDIRECT3DDEVICE9& device);
	void SetTextureAlphaMode(const bool& isTextureAlpha, LPDIRECT3DDEVICE9& device);
	void SetLightingMode(const LIGHTING_MODE& mode, LPDIRECT3DDEVICE9& device);
	void SetLightingMode(const bool& isLighting, LPDIRECT3DDEVICE9& device);

private:
	//========== [[[ �\���̒�` ]]]]
	struct FormerMode {
		ZTEST_MODE         ZTest        = ZTEST_MODE::ENABLED;
		CULLING_MODE       Culling      = CULLING_MODE::FRONT_SIDE;
		TEXTURE_ALPHA_MODE TextureAlpha = TEXTURE_ALPHA_MODE::ENABLED;
		LIGHTING_MODE      Lighting     = LIGHTING_MODE::ENABLED;
	};

	//========== [[[ �ϐ��錾 ]]]]
	bool m_isAssignFormerMode;
	FormerMode m_formerMode;
};