//========================================
// 
// �|���S��2D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
// �|���S��2D�N���X
class CPolygon2D {
public:
	//========== [[[ �\���̒�` ]]]
	// �`����\����
	typedef struct DrawSet_ {
		int nTex = DATANONE;
	}DrawSet;

	//========== [[[ �֐��錾 ]]]
	CPolygon2D();
	~CPolygon2D();
	void Init(void);
	void Uninit(void);
	void Draw(void);
	void Set(
		const float       fScaleX,
		const float       fScaleY,
		const D3DXVECTOR3 pos     = INITD3DXVECTOR3,
		const D3DXVECTOR3 rot     = INITD3DXVECTOR3,
		const Color       col     = INITCOLOR,
		const int         nTex    = DATANONE,
		const int         nPtn    = 0,
		const int         nPtnX   = 1,
		const int         nPtnY   = 1,
		const bool        bMirror = false);
	void SetGauge(
		const float       fRate,
		const float       fScaleX,
		const float       fScaleY,
		const D3DXVECTOR3 pos     = INITD3DXVECTOR3,
		const Color       col     = INITCOLOR,
		const int         nTex    = DATANONE,
		const int         nPtn    = 0,
		const int         nPtnX   = 1,
		const int         nPtnY   = 1,
		const bool        bMirror = false);
	void SetVtx(
		const D3DXVECTOR3 aVtxPos0,
		const D3DXVECTOR3 aVtxPos1,
		const D3DXVECTOR3 aVtxPos2,
		const D3DXVECTOR3 aVtxPos3,
		const Color       col     = INITCOLOR,
		const int         nTex    = DATANONE,
		const int         nPtn    = 0,
		const int         nPtnX   = 1,
		const int         nPtnY   = 1,
		const bool        bMirror = false);
	void SetReset(void);

	// ���_���ݒ�n
	static void SetVtxPos        (VERTEX_2D* vtxs, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float width, const float height);
	static void SetVtxPos        (VERTEX_2D* vtxs, const D3DXVECTOR3 pos0, const D3DXVECTOR3 pos1, const D3DXVECTOR3 pos2, const D3DXVECTOR3 pos3);
	static void SetVtxPos_TopLeft(VERTEX_2D* vtxs, const D3DXVECTOR3 pos, const float width, const float height);
	static void ApplyResolution  (VERTEX_2D* vtxs);
	static void SetVtxRHW        (VERTEX_2D* vtxs);
	static void SetVtxCol        (VERTEX_2D* vtxs, const Color col);
	static void SetVtxTex        (VERTEX_2D* vtxs, const int nPtn, const int nPtnMaxX, const int nPtnMaxY, const D3DXVECTOR3* pPos, const bool bMirror);
	static void SetVtxTex_Cut    (VERTEX_2D* vtxs, const D3DXVECTOR2 cutPos, const float size);
	static void SetVtxTex_Cut    (VERTEX_2D* vtxs, const D3DXVECTOR2 cutPos, const float width, const float height);

private:
	//========== [[[ �ϐ��錾 ]]]
	DrawSet* m_pDrawSet;
	int      m_nDrawSetNum;
	LPDIRECT3DVERTEXBUFFER9* m_ppVtxBuff;
};