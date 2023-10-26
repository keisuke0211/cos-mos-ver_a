//========================================
// 
// �`���Ԃ̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| ���p�`����N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDrawState::CDrawState() {

	m_isAssignFormerMode = true;
	m_formerMode         = {};
}

//========================================
// �f�X�g���N�^
//========================================
CDrawState::~CDrawState() {

}

//========================================
// ����������
//========================================
void CDrawState::Init(LPDIRECT3DDEVICE9& device) {

	//----------------------------------------
	// �e�N�X�`���X�e�[�W�X�e�[�g�̏����ݒ�
	//----------------------------------------
	SetTextureAlphaMode(TEXTURE_ALPHA_MODE::ENABLED, device);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//----------------------------------------
	// Z�e�X�g�̏����ݒ�
	//----------------------------------------
	SetZTestMode(ZTEST_MODE::ENABLED, device);

	//----------------------------------------
	// �J�����O�̏����ݒ�
	//----------------------------------------
	SetCullingMode(CULLING_MODE::FRONT_SIDE, device);

	//----------------------------------------
	// ���C�e�B���O�̏����ݒ�
	//----------------------------------------
	SetLightingMode(LIGHTING_MODE::ENABLED, device);

	//----------------------------------------
	// �t�H�O�̏����ݒ�
	//----------------------------------------
	SetFogMode(FOG_MODE::DISABLED, device);
	SetFogParameter(INITCOLOR, 0.0f, 0.0f, device);

	//----------------------------------------
	// �A���t�@�u�����h�̏����ݒ�
	//----------------------------------------
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//----------------------------------------
	// �T���v���[�X�e�[�g�̏����ݒ�
	//----------------------------------------
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

//========================================
// �I������
//========================================
void CDrawState::Uninit(void) {

}

//========================================
// �ꎞ�I�ȃ��[�h�ݒ���J�n
//========================================
void CDrawState::StartTemporarySetMode(void) {

	// ���̃��[�h����t���O���U�ɂ���
	m_isAssignFormerMode = false;
}

//========================================
// �ꎞ�I�ȃ��[�h�ݒ���I��
//========================================
void CDrawState::EndTemporarySetMode(LPDIRECT3DDEVICE9& device) {

	// ���̃��[�h�Őݒ肵����
	SetZTestMode(m_formerMode.ZTest, device);
	SetCullingMode(m_formerMode.culling, device);
	SetTextureAlphaMode(m_formerMode.textureAlpha, device);
	SetLightingMode(m_formerMode.lighting, device);

	// ���̃��[�h����t���O��^�ɂ���
	m_isAssignFormerMode = true;
}

//========================================
// Z�e�X�g���[�h�̐ݒ�
//========================================
void CDrawState::SetZTestMode(const ZTEST_MODE& mode, LPDIRECT3DDEVICE9& device) {

	// ���̃��[�h�Ƃ��đ��
	if (m_isAssignFormerMode)
		m_formerMode.ZTest = mode;

	switch (mode) {
		// [[[ �L�� ]]]
	case ZTEST_MODE::ENABLED: {
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}break;
		// [[[ ���� ]]]
	case ZTEST_MODE::DISABLED: {
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}break;
	}
}

//========================================
// Z�e�X�g���[�h�̐ݒ�(�t���O�w��)
//========================================
void CDrawState::SetZTestMode(const bool& isZTest, LPDIRECT3DDEVICE9& device) {

	SetZTestMode(isZTest ? ZTEST_MODE::ENABLED : ZTEST_MODE::DISABLED, device);
}

//========================================
// �J�����O���[�h�̐ݒ�
//========================================
void CDrawState::SetCullingMode(const CULLING_MODE& mode, LPDIRECT3DDEVICE9& device) {

	// ���̃��[�h�Ƃ��đ��
	if (m_isAssignFormerMode)
		m_formerMode.culling = mode;

	switch (mode) {
		// [[[ �\�� ]]]
	case CULLING_MODE::FRONT_SIDE: {
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}break;
		// [[[ ���� ]]]
	case CULLING_MODE::BACK_SIDE: {
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}break;
		// [[[ ���� ]]]
	case CULLING_MODE::BOTH_SIDES: {
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	}break;
	}
}

//========================================
// �e�N�X�`�����߃��[�h�̐ݒ�
//========================================
void CDrawState::SetTextureAlphaMode(const TEXTURE_ALPHA_MODE& mode, LPDIRECT3DDEVICE9& device) {

	// ���̃��[�h�Ƃ��đ��
	if (m_isAssignFormerMode)
		m_formerMode.textureAlpha = mode;

	switch (mode) {
		// [[[ �L�� ]]]
	case TEXTURE_ALPHA_MODE::ENABLED: {
		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �e�N�X�`���u�����h����Z�ɐݒ� (���e�N�X�`���̓����x���|���S���̐F���������Ĕw��̐F�������Ă��܂�)
	}break;
		// [[[ ���� ]]]
	case TEXTURE_ALPHA_MODE::DISABLED: {
		device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	}break;
	}
}

//========================================
// �e�N�X�`�����߃��[�h�̐ݒ�(�t���O�w��)
//========================================
void CDrawState::SetTextureAlphaMode(const bool& isTextureAlpha, LPDIRECT3DDEVICE9& device) {

	SetTextureAlphaMode(isTextureAlpha ? TEXTURE_ALPHA_MODE::ENABLED : TEXTURE_ALPHA_MODE::DISABLED, device);
}

//========================================
// ���C�e�B���O���[�h�̐ݒ�
//========================================
void CDrawState::SetLightingMode(const LIGHTING_MODE& mode, LPDIRECT3DDEVICE9& device) {

	// ���̃��[�h�Ƃ��đ��
	if (m_isAssignFormerMode)
		m_formerMode.lighting = mode;

	switch (mode) {
		// [[[ �L�� ]]]
	case LIGHTING_MODE::ENABLED: {
		device->SetRenderState(D3DRS_LIGHTING, TRUE);
	}break;
		// [[[ ���� ]]]
	case LIGHTING_MODE::DISABLED: {
		device->SetRenderState(D3DRS_LIGHTING, FALSE);
	}break;
	}
}

//========================================
// ���C�e�B���O���[�h�̐ݒ�(�t���O�w��)
//========================================
void CDrawState::SetLightingMode(const bool& isLighting, LPDIRECT3DDEVICE9& device) {

	SetLightingMode(isLighting ? LIGHTING_MODE::ENABLED : LIGHTING_MODE::DISABLED, device);
}

//========================================
// �t�H�O���[�h�̐ݒ�
//========================================
void CDrawState::SetFogMode(const FOG_MODE& mode, LPDIRECT3DDEVICE9& device) {

	// ���̃��[�h�Ƃ��đ��
	if (m_isAssignFormerMode)
		m_formerMode.fog = mode;

	switch (mode) {
		// [[[ �L�� ]]]
	case FOG_MODE::ENABLED: {
		device->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}break;
		// [[[ ���� ]]]
	case FOG_MODE::DISABLED: {
		device->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}break;
	}
}

//========================================
// �t�H�O���[�h�̐ݒ�(�t���O�w��)
//========================================
void CDrawState::SetFogMode(const bool& isFog, LPDIRECT3DDEVICE9& device) {

	SetFogMode(isFog ? FOG_MODE::ENABLED : FOG_MODE::DISABLED, device);
}

//========================================
// �t�H�O���[�h�̐ݒ�(�t���O�w��)
//========================================
void CDrawState::SetFogParameter(const Color& col, const float& startDist, const float& endDist, LPDIRECT3DDEVICE9& device) {

	device->SetRenderState(D3DRS_FOGCOLOR, ColorToD3DCOLOR(col));
	device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&startDist));
	device->SetRenderState(D3DRS_FOGEND  , *(DWORD*)(&endDist));
}