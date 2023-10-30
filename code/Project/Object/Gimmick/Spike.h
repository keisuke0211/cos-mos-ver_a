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
	/* ���f���ԍ�	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	// -- ���� ---------------------------------------------

private:

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};