//========================================
// 
// �`�揈��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "draw-info.h"
#include "PutObject/polygon2D.h"
#include "PutObject/polygon3D.h"
#include "PutObject/model.h"
#include "PutObject/text2D.h"
#include "PutObject/text3D.h"
#include "../../RNmain.h"
#include "../Mechanical/memory.h"

//****************************************
// �N���X��`
//****************************************
// �`��N���X
class CDrawMng {
public:
	//----------------------------------------
	// �萔�錾
	//----------------------------------------
	static const unsigned short POLYGON2D_ALLOC_BASE_POWER = 8;
	static const unsigned short POLYGON3D_ALLOC_BASE_POWER = 8;
	static const unsigned short REGIST_ALLOC_BASE_POWER    = 8;	// 2�̉������Ƃ��邩

	//----------------------------------------
	// �񋓌^��`
	//----------------------------------------
	// �������
	enum class PROCESS_STATE {
		REGIST_ACCEPT,			// �o�^��t
		REGIST_INFO_APPLY_WAIT,	// �o�^���K�p�҂�
		DRAW_INFO_SWAP_WAIT,	// �`�������ւ��҂�
	};

	//----------------------------------------
	// �N���X��`
	//----------------------------------------
	// �`���񑍊��N���X
	class CDrawInfoSum {
	public:
		// [[[ �֐��錾 ]]]
		CDrawInfoSum();
		~CDrawInfoSum();
		void Release(void);
		void Overwrite(CDrawInfoSum* pOvr);

		// [[[ �ϐ��錾 ]]]
		CDrawInfoBase** ms_drawInfos;
		int             ms_drawInfoNum;
	};

	//----------------------------------------
	// �o�^�����
	//----------------------------------------
	// �o�^����񑍊�
	class CRegistInfoSum {
	public:
		// [[[ �֐��錾 ]]]
		CRegistInfoSum();
		~CRegistInfoSum();
		void InitAlloc(void);
		void ReAlloc(void);
		void Release(void);

		// [[[ �ϐ��錾 ]]]
		CPolygon2D::CRegistInfo* m_polygon2DRegistInfos;
		unsigned short           m_polygon2DRegistInfoNum;
		unsigned short           m_polygon2DRegistInfoAllocPower;
		unsigned short           m_polygon2DRegistInfoAllocNum;
		CPolygon3D::CRegistInfo* m_polygon3DRegistInfos;
		unsigned short           m_polygon3DRegistInfoNum;
		unsigned short           m_polygon3DRegistInfoAllocPower;
		unsigned short           m_polygon3DRegistInfoAllocNum;
		CText2D::CRegistInfo*    m_text2DRegistInfos;
		unsigned short           m_text2DRegistInfoNum;
		unsigned short           m_text2DRegistInfoAllocPower;
		unsigned short           m_text2DRegistInfoAllocNum;
		CText3D::CRegistInfo*    m_text3DRegistInfos;
		unsigned short           m_text3DRegistInfoNum;
		unsigned short           m_text3DRegistInfoAllocPower;
		unsigned short           m_text3DRegistInfoAllocNum;
		CModel::CRegistInfo*     m_modelRegistInfos;
		unsigned short           m_modelRegistInfoNum;
		unsigned short           m_modelRegistInfoAllocPower;
		unsigned short           m_modelRegistInfoAllocNum;
	};

	//========== [[[ �֐��錾 ]]]
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
	CText2D::CRegistInfo*    PutText2D   (const D3DXVECTOR3& pos, const float& angle, const bool& isOnScreen);
	CText3D::CRegistInfo*    PutText3D   (const D3DXMATRIX& mtx, const bool& isOnScreen);
	CModel::CRegistInfo*     PutModel    (const D3DXMATRIX& mtx, const bool& isOnScreen);

private:
	//========== [[[ �֐��錾 ]]]
	static void MainLoop(void);
	static void PutBasedRegistInfo(CRegistInfoSum& resistInfoSum, const bool& isOnScreen);
	static void ConvRegistInfoToDrawInfo(CRegistInfoSum& resistInfoSum, CDrawInfoSum& drawInfoSum);
	static void SortDrawInfo(CDrawInfoSum& drawInfoSum);
	void AssignVertexInfo(void);
	void ConvDrawInfoToVertex2DInfo(Vertex2D*& vtxs, CDrawInfoSum& drawInfoSum);
	void ConvDrawInfoToVertex3DInfo(Vertex3D*& vtxs, CDrawInfoSum& drawInfoSum);
	CPolygon2D::CRegistInfo* RegistPolygon2D(CRegistInfoSum& resistInfo);
	CPolygon3D::CRegistInfo* RegistPolygon3D(CRegistInfoSum& resistInfo);
	CText2D::CRegistInfo*    RegistText2D   (CRegistInfoSum& resistInfo);
	CText3D::CRegistInfo*    RegistText3D   (CRegistInfoSum& resistInfo);
	CModel::CRegistInfo*     RegistModel    (CRegistInfoSum& resistInfo);

	//========== [[[ �ϐ��錾 ]]]
	static PROCESS_STATE  ms_processState;
	static CRegistInfoSum ms_resistInfoSum;
	static CRegistInfoSum ms_resistInfoSumScreen;
	static CDrawInfoSum   ms_drawInfoSum;			// �`����
	static CDrawInfoSum   ms_drawInfoSumOvr;		// �`����(�㏑��)
	static CDrawInfoSum   ms_drawInfoSumScreen;		// �X�N���[���`����
	static CDrawInfoSum   ms_drawInfoSumScreenOvr;	// �X�N���[���`����(�㏑��)
	static std::thread    ms_mainLoopTh;			// ���C�����[�v�X���b�h
	unsigned short        m_reAllocCount;
};