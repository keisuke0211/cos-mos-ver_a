//========================================
// 
// �u���b�N����
// Author:KEISUKE OTONO
// 
//========================================
// *** block.h ***
//========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../main.h"

//****************************************
// �N���X
//****************************************
class CBlock
{
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nID;				// ID
	};

private:

	// *** �֐� ***
	CBlock();
	~CBlock();

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* �ǂݍ���	*/static void Load(void);
	/* ����		*/static CBlock *Create(void);

	// -- �ݒ� ---------------------------------------------
	/* �ʒu		*/void SetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* ����		*/void SetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F		*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* �傫��	*/void SetSize(const D3DXVECTOR3 size) { m_Info.size = size; }

	// -- ���� ---------------------------------------------
	/* �ʒu		*/D3DXVECTOR3 GetPos(void) { return m_Info.pos; }
	/* ����		*/D3DXVECTOR3 GetRot(void) { return m_Info.rot; }
	/* �F		*/D3DXCOLOR GetColor(void) { return m_Info.col; }
	/* �傫��	*/D3DXVECTOR3 GetSize(void) { return m_Info.size; }

	// *** �ÓI�ϐ� ***
	static int m_nNumAll;		// ����

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};
#endif