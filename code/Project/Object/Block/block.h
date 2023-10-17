//========================================
// 
// �u���b�N����
// Author:KEISUKE OTONO
// 
//========================================
// *** block.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// �N���X
//****************************************
class CBlock : public CStageObject {
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nModelIdx;			// ���f���ԍ�
		int nID;				// ID
	};

	// *** �֐� ***
	CBlock();
	~CBlock();

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ---------------------------------------------
	/* �F			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* ���f���ԍ�	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	// -- ���� ---------------------------------------------
	/* �F		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** �ÓI�ϐ� ***
	static int m_nNumAll;		// ����

	short m_modelIdx;

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};