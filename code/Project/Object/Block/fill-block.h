//========================================
// 
// �u���b�N(���� ����)
// Author:KEISUKE OTONO
// 
//========================================
// *** fill-block.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// �N���X
//****************************************
class CFillBlock : public CStageObject {
public:

	// ���ʏ��
	struct Info
	{
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		short nModelIdx;		// ���f���ԍ�
	};

	// �����߃u���b�N���
	enum class FILL_TYPE
	{
		FILL_1x1 = 0,
		FILL_2x2,
		FILL_3x3,
		FILL_4x4,
		FILL_MAX,
	};

	// *** �֐� ***
	CFillBlock();
	~CFillBlock();

	/* ������	*/HRESULT Init(FILL_TYPE type);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ---------------------------------------------
	/* �F			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* ���f���ԍ�	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	// -- ���� ---------------------------------------------
	/* �F		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};