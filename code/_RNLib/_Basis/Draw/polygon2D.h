//========================================
// 
// ポリゴン2Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "draw-info.h"
#include "../3D/Camera/camera.h"

//****************************************
// クラス定義
//****************************************
// ポリゴン2Dクラス
class CPolygon2D {
public:
	//========== [[[ クラス定義 ]]]
	// 描画情報
	class CDrawInfo : public CDrawInfoBase {
	public:
		// [[[ 関数宣言 ]]]
		CDrawInfo();
		~CDrawInfo();
		void Draw(LPDIRECT3DDEVICE9& device, const D3DXMATRIX& viewMtx);
		static void CreateVertexBuffer(void);
		static void ReleaseVertexBuffer(void);

		// [[[ 変数宣言 ]]]
		short     m_idx;
		short     m_texIdx;
		CCamera*  m_texCamera;
		bool      m_isZTest;
		float     m_distance;
		VERTEX_2D m_vtxs[4];

		static LPDIRECT3DVERTEXBUFFER9 m_vtxBuff;
		static int m_idxCount;
	};

	// 登録情報
	class CRegistInfo {
	public:
		// [[[ 関数宣言 ]]]
		CRegistInfo();
		~CRegistInfo();
		CPolygon2D::CDrawInfo* ConvToDrawInfo(void);
		CRegistInfo* SetPos              (const D3DXVECTOR3& pos);
		CRegistInfo* SetAngle            (const float& angle);
		CRegistInfo* SetCol              (const Color& col);
		CRegistInfo* SetTex              (const short& texIdx, const unsigned short& ptn = 0, const unsigned short& ptnX = 1, const unsigned short& ptnY = 1, const D3DXVECTOR3& ptnPos = INITD3DXVECTOR3);
		CRegistInfo* SetTex_Camera       (CCamera* camera);
		CRegistInfo* SetSize             (const float& width, const float& height);
		CRegistInfo* SetSize_TexBaseScale(const float& scaleX, const float& scaleY);
		CRegistInfo* ExtendFixedTexX     (const float& rateX);
		CRegistInfo* ExtendFixedTexY     (const float& rateY);
		CRegistInfo* SetZTest            (const bool& isZTest);
		CRegistInfo* SetTexMirrorX       (const bool& isMirror);
		CRegistInfo* SetPriority         (const short& priority);

		// [[[ 変数宣言 ]]]
		static int m_resistCount;

	private:
		// [[[ 変数宣言 ]]]
		float          m_scaleX;
		float          m_scaleY;
		bool           m_isFactScale;
		D3DXVECTOR3    m_pos;
		float          m_angle;
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
		bool           m_isTexMirrorX;
		short          m_priority;
	};

	//========== [[[ 関数宣言 ]]]
	CRegistInfo* Put(const D3DXVECTOR3& pos, const float& angle, const bool& isOnScreen = false);
	// 頂点情報設定系
	void SetVtxPos        (VERTEX_2D* vtxs, const D3DXVECTOR3& pos, const float& angle, const float& width, const float& height);
	void SetVtxPos        (VERTEX_2D* vtxs, const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& pos2, const D3DXVECTOR3& pos3);
	void SetVtxPos_TopLeft(VERTEX_2D* vtxs, const D3DXVECTOR3& pos, const float& width, const float& height);
	void ApplyResolution  (VERTEX_2D* vtxs);
	void SetVtxRHW        (VERTEX_2D* vtxs);
	void SetVtxCol        (VERTEX_2D* vtxs, const Color& col);
	void SetVtxTex_Cut    (VERTEX_2D* vtxs, const D3DXVECTOR2& cutPos, const float& width, const float& height);
	void SetVtxTex_Cut    (VERTEX_2D* vtxs, const D3DXVECTOR2& cutPos, const float& size);
};