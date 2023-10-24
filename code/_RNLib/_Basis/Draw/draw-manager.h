//========================================
// 
// 描画処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "draw-info.h"
#include "polygon2D.h"
#include "polygon3D.h"
#include "model.h"
#include "text2D.h"
#include "text3D.h"
#include "../../RNmain.h"
#include "../Mechanical/memory.h"

//****************************************
// クラス定義
//****************************************
// 描画クラス
class CDrawMng {
public:
	//----------------------------------------
	// 列挙型定義
	//----------------------------------------
	// 処理状態
	enum class PROCESS_STATE {
		REGIST_ACCEPT,			// 登録受付
		REGIST_INFO_APPLY_WAIT,	// 登録情報適用待ち
		DRAW_INFO_SWAP_WAIT,	// 描画情報入れ替え待ち
	};

	//----------------------------------------
	// クラス定義
	//----------------------------------------
	// 描画情報総括クラス
	class CDrawInfoSum {
	public:
		// [[[ 関数宣言 ]]]
		CDrawInfoSum();
		~CDrawInfoSum();
		void Release(void);
		void Overwrite(CDrawInfoSum* pOvr);

		// [[[ 変数宣言 ]]]
		CDrawInfoBase** ms_drawInfos;
		int             ms_drawInfoNum;
	};

	//----------------------------------------
	// 登録情報情報
	//----------------------------------------
	// 登録情報情報総括
	class CRegistInfoSum {
	public:
		// [[[ 関数宣言 ]]]
		CRegistInfoSum();
		~CRegistInfoSum();

		// [[[ 変数宣言 ]]]
		CPolygon2D::CRegistInfo* m_polygon2DRegistInfos;
		int                      m_polygon2DRegistInfoNum;
		CPolygon3D::CRegistInfo* m_polygon3DRegistInfos; 
		int                      m_polygon3DRegistInfoNum;
		CText2D::CRegistInfo*    m_text2DRegistInfos;
		int                      m_text2DRegistInfoNum;
		CText3D::CRegistInfo*    m_text3DRegistInfos;
		int                      m_text3DRegistInfoNum;
		CModel::CRegistInfo*     m_modelRegistInfos;
		int                      m_modelRegistInfoNum;
	};

	//========== [[[ 関数宣言 ]]]
	static PROCESS_STATE GetProcessState(void) { return ms_processState; }
	CDrawMng();
	~CDrawMng();
	void Init(void);
	void Uninit(void);
	void Release(void);
	bool StartDraw(void);
	void Draw(LPDIRECT3DDEVICE9& device, const bool& isOnScreen);
	CPolygon2D::CRegistInfo* PutPolygon2D(const D3DXVECTOR3& pos, const float& angle, const bool& isOnScreen);
	CPolygon3D::CRegistInfo* PutPolygon3D(const D3DXMATRIX& mtx, const bool& isOnScreen);
	CText2D::CRegistInfo*    PutText2D   (const D3DXVECTOR2& pos, const float& angle, const bool& isOnScreen);
	CText3D::CRegistInfo*    PutText3D   (const D3DXMATRIX& mtx, const bool& isOnScreen);
	CModel::CRegistInfo*     PutModel    (const D3DXMATRIX& mtx, const bool& isOnScreen);

private:
	//========== [[[ 関数宣言 ]]]
	static void MainLoop(void);
	static void PutBasedRegistInfo(CRegistInfoSum& resistInfoSum, const bool& isOnScreen);
	static void ConvRegistInfoToDrawInfo(CRegistInfoSum& resistInfoSum, CDrawInfoSum& drawInfoSum);
	static void SortDrawInfo(CDrawInfoSum& drawInfoSum);
	void AssignVertexInfo(void);
	void ConvDrawInfoToVertex2DInfo(VERTEX_2D* vtxs, CDrawInfoSum& drawInfoSum);
	void ConvDrawInfoToVertex3DInfo(VERTEX_3D* vtxs, CDrawInfoSum& drawInfoSum);
	CPolygon2D::CRegistInfo& RegistPolygon2D(CRegistInfoSum& resistInfo);
	CPolygon3D::CRegistInfo& RegistPolygon3D(CRegistInfoSum& resistInfo);
	CText2D::CRegistInfo&    RegistText2D   (CRegistInfoSum& resistInfo);
	CText3D::CRegistInfo&    RegistText3D   (CRegistInfoSum& resistInfo);
	CModel::CRegistInfo&     RegistModel    (CRegistInfoSum& resistInfo);

	//========== [[[ 変数宣言 ]]]
	static PROCESS_STATE  ms_processState;
	static CRegistInfoSum ms_resistInfoSum;
	static CRegistInfoSum ms_resistInfoSumScreen;
	static CDrawInfoSum   ms_drawInfoSum;			// 描画情報
	static CDrawInfoSum   ms_drawInfoSumOvr;		// 描画情報(上書き)
	static CDrawInfoSum   ms_drawInfoSumScreen;		// スクリーン描画情報
	static CDrawInfoSum   ms_drawInfoSumScreenOvr;	// スクリーン描画情報(上書き)
	static std::thread    ms_mainLoopTh;			// メインループスレッド
};