//========================================
// 
// �e�L�X�g3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "text.h"

//****************************************
// �N���X��`
//****************************************
// �e�L�X�g3D�N���X
class CText3D {
public:
	//========== [[[ �N���X��` ]]]
	// �o�^���
	class CRegistInfo {
	public:
		// [[[ �֐��錾 ]]]
		CRegistInfo();
		~CRegistInfo();
		void PutPolygon3D(const bool& isOnScreen);
		CRegistInfo* SetMtx              (const D3DXMATRIX& mtx);
		CRegistInfo* SetString           (const char* string);
		CRegistInfo* SetAlignment        (const CText::ALIGNMENT& alignment);
		CRegistInfo* SetFontIdx          (const short& fontIdx);
		CRegistInfo* SetCol              (const Color& col);
		CRegistInfo* SetSize             (const float& width, const float& height);
		CRegistInfo* SetSize_TexBaseScale(const float& scaleX, const float& scaleY);
		CRegistInfo* ExtendFixedTexX     (const float& rateX);
		CRegistInfo* ExtendFixedTexY     (const float& rateY);
		CRegistInfo* SetZTest            (const bool& isZTest);
		CRegistInfo* SetLighting         (const bool& isLighting);
		CRegistInfo* SetBillboard        (const bool& isBillboard);
		CRegistInfo* SetPriority         (const short& priority);

	private:
		// [[[ �ϐ��錾 ]]]
		char*            m_string;
		CText::ALIGNMENT m_alignment;
		short            m_fontIdx;
		float            m_scaleX;
		float            m_scaleY;
		bool             m_isFactScale;
		D3DXMATRIX       m_mtx;
		Color            m_col;
		bool             m_isZtest;
		bool             m_isLighting;
		bool             m_isBillboard;
		short            m_priority;
	};

	//========== [[[ �֐��錾 ]]]
	CRegistInfo* Put(const D3DXMATRIX& mtx, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen = false);
	CRegistInfo* Put(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const char* string, const CText::ALIGNMENT alignment, const short& fontIdx, const bool& isOnScreen = false);
};