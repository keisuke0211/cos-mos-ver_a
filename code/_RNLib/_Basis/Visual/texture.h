//========================================
// 
// �e�N�X�`���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../Other/regist.h"
#include "../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
// �e�N�X�`���N���X
class CTexture : public CRegist {
public:
	//========== [[[ �֐��錾 ]]]
	CTexture();
	~CTexture();
	void Init(void);
	void Uninit(void);
	int Load(const char *loadPath);
	void Set(LPDIRECT3DDEVICE9 pDevice, int nTex);

	// �ݒ�擾
	float GetWidth(int nTex) {
		if (nTex < 0)
			return 0.0f;
		D3DSURFACE_DESC desc;
		m_texs[nTex]->GetLevelDesc(0, &desc);
		return (float)desc.Width;
	}
	float GetWidth2D(int nTex) { return GetWidth(nTex) * PIXEL2D_SIZE; }
	float GetWidth3D(int nTex) { return GetWidth(nTex) * PIXEL3D_SIZE; }
	float GetHeight(int nTex) {
		if (nTex < 0)
			return 0.0f;
		D3DSURFACE_DESC desc;
		m_texs[nTex]->GetLevelDesc(0, &desc);
		return (float)desc.Height;
	}
	float GetHeight2D(int nTex) { return GetHeight(nTex) * PIXEL2D_SIZE; }
	float GetHeight3D(int nTex) { return GetHeight(nTex) * PIXEL3D_SIZE; }
	int GetCrntPtn(int nPtnX, int nPtnY, int nSpan);

private:
	//========== [[[ �ϐ��錾 ]]]
	LPDIRECT3DTEXTURE9* m_texs;
};