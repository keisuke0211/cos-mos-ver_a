//========================================
// 
// ���f���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../draw-info.h"
#include "../../Mechanical/regist.h"

//****************************************
// �N���X��`
//****************************************
// ���f���N���X
class CModel : public CRegist {
public:
	//========== [[[ �N���X��` ]]]
	// �f�[�^�N���X
	class CData {
	public:
		// [[[ �֐��錾 ]]]
		CData();
		~CData();
		void Release(void);

		// [[[ �ϐ��錾 ]]]
		short*         m_texIdxs;
		LPD3DXMESH     m_mesh;
		LPD3DXMESH     m_outLineMesh;
		LPD3DXBUFFER   m_matBuff;
		unsigned short m_matNum;
		float          m_radiusMax;
	};

	// �`����N���X
	class CDrawInfo : public CDrawInfoBase {
	public:
		// [[[ �֐��錾 ]]]
		CDrawInfo();
		~CDrawInfo();
		void Draw       (Device& device, const Matrix& viewMtx);
		void SetMaterial(Device& device, Material* mat, const Color& col);

		// [[[ �ϐ��錾 ]]]
		Matrix m_mtx;
		Color  m_col;
		short  m_modelIdx;
		short  m_texIdx;
		bool   m_isZTest;
		bool   m_isLighting;
		bool   m_isOutLine;
		float  m_brightnessOfEmissive;
		float  m_distance;
	};

	// �o�^���N���X
	class CRegistInfo {
	public:
		// [[[ �֐��錾 ]]]
		CRegistInfo();
		~CRegistInfo();
		void ClearParameter(void);
		CDrawInfo* ConvToDrawInfo(void);
		CRegistInfo* SetMtx                 (const Matrix& mtx);
		CRegistInfo* SetCol                 (const Color& col);
		CRegistInfo* SetModel               (const short& modelIdx);
		CRegistInfo* SetTex                 (const short& texIdx);
		CRegistInfo* SetZTest               (const bool& isZTest);
		CRegistInfo* SetLighting            (const bool& isLighting);
		CRegistInfo* SetOutLine             (const bool& isOutLine);
		CRegistInfo* SetBrightnessOfEmissive(const float& brightnessOfEmissive);
		CRegistInfo* SetPriority            (const short& priority);

	private:
		// [[[ �ϐ��錾 ]]]
		Matrix m_mtx;
		Color  m_col;
		short  m_modelIdx;
		short  m_texIdx;
		bool   m_isZTest;
		bool   m_isLighting;
		bool   m_isOutLine;
		float  m_brightnessOfEmissive;
		short  m_priority;
	};

	//========== [[[ �֐��錾 ]]]
	CModel();
	~CModel();
	void         Release(void);
	short        Load   (const char* loadPath, short idx = NONEDATA);
	CData&       GetData(const short& idx) { return m_datas[idx]; }
	CRegistInfo* Put    (const Matrix& mtx, const short& modelIdx, const bool& isOnScreen = false);
	CRegistInfo* Put    (const Pos3D& pos, const Rot3D& rot, const short& modelIdx, const bool& isOnScreen = false);

private:
	//========== [[[ �ϐ��錾 ]]]
	CData* m_datas;
};