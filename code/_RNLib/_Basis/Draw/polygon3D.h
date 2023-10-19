//========================================
// 
// �|���S��3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "draw-info.h"
#include "../3D/Camera/camera.h"

//****************************************
// �N���X��`
//****************************************
// �|���S��3D�N���X
class CPolygon3D {
public:
	//========== [[[ �N���X��` ]]]
	// �`����
	class CDrawInfo : public CDrawInfoBase {
	public:
		// [[[ �֐��錾 ]]]
		CDrawInfo();
		~CDrawInfo();
		void Draw(LPDIRECT3DDEVICE9& device, const D3DXMATRIX& viewMtx);
		static void CreateVertexBuffer(void);
		static void ReleaseVertexBuffer(void);

		// [[[ �ϐ��錾 ]]]
		short      m_idx;
		D3DXMATRIX m_mtx;
		short      m_texIdx;
		CCamera*   m_texCamera;
		bool       m_isZTest, m_isLighting, m_isBillboard;
		float      m_distance;
		VERTEX_3D  m_vtxs[4];

		static LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
		static int m_idxCount;
	};

	// �o�^���
	class CRegistInfo {
	public:
		// [[[ �֐��錾 ]]]
		CRegistInfo();
		~CRegistInfo();
		CPolygon3D::CDrawInfo* ConvToDrawInfo(void);
		CRegistInfo* SetMtx              (const D3DXMATRIX& mtx);
		CRegistInfo* SetVtxPos           (const D3DXVECTOR3 pos0, const D3DXVECTOR3 pos1, const D3DXVECTOR3 pos2, const D3DXVECTOR3 pos3);
		CRegistInfo* SetCol              (const Color& col);
		CRegistInfo* SetTex              (const short& texIdx, const unsigned short& ptn = 0, const unsigned short& ptnX = 1, const unsigned short& ptnY = 1, const D3DXVECTOR3& ptnPos = INITD3DXVECTOR3);
		CRegistInfo* SetTex_Camera       (CCamera* camera);
		CRegistInfo* SetSize             (const float& width, const float& height);
		CRegistInfo* SetSize_TexBaseScale(const float& scaleX, const float& scaleY);
		CRegistInfo* ExtendFixedTexX     (const float& rateX);
		CRegistInfo* ExtendFixedTexY     (const float& rateY);
		CRegistInfo* SetZTest            (const bool& isZTest);
		CRegistInfo* SetLighting         (const bool& isLighting);
		CRegistInfo* SetBillboard        (const bool& isBillboard);
		CRegistInfo* SetTexMirrorX       (const bool& isMirror);
		CRegistInfo* SetPriority         (const short& priority);

		// [[[ �ϐ��錾 ]]]
		static int m_resistCount;

	private:
		// [[[ �ϐ��錾 ]]]
		float          m_scaleX;
		float          m_scaleY;
		bool           m_isFactScale;
		D3DXMATRIX     m_mtx;
		D3DXVECTOR3    m_vtxPoses[4];
		bool           m_isSetVtxPoses;
		Color          m_col;
		short          m_texIdx;
		CCamera*       m_texCamera;
		unsigned short m_ptn;
		unsigned short m_ptnX;
		unsigned short m_ptnY;
		float          m_ptnScaleX;
		float          m_ptnScaleY;
		D3DXVECTOR3    m_ptnPos;
		bool           m_isZtest;
		bool           m_isLighting;
		bool           m_isBillboard;
		bool           m_isTexMirrorX;
		short          m_priority;
	};

	//========== [[[ �ݒ�֐� ]]]
	CRegistInfo* Put(const D3DXMATRIX& mtx, const bool& isOnScreen = false);
	CRegistInfo* Put(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const bool& isOnScreen = false);
};