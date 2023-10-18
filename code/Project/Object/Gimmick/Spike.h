//========================================
// 
// ��
// Author:KEISUKE OTONO
// 
//========================================
// *** spike.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// �N���X
//****************************************
class CSpike : public CStageObject {
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// ���_�J���[
		short nModelIdx;		// ���f���ԍ�
	};

	// *** �֐� ***
	CSpike();
	~CSpike();

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

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};