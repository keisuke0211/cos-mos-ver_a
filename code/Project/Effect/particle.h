//========================================
// 
// �p�[�e�B�N������
// Author:RYUKI FUJIWARA
// 
//========================================
#pragma once
#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X
//****************************************
class CParticle : public CObject {
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 move;		// �ړ���
		Color col;			// ���_�J���[
		int nCount;
		int nTex;
	};

	// *** �֐� ***
	CParticle();
	~CParticle();

	/* ������	*/HRESULT Init(int nTex);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ---------------------------------------------
	/* �F		*/void SetColor(const Color col) { m_Info.col = col; }
	/* �ʒu		*/void SetPos(const D3DXVECTOR3 pos) { m_Info.pos = pos; }

	// -- ���� ---------------------------------------------
	/* �F		*/Color GetColor(void) { return m_Info.col; }
	/* �ʒu		*/D3DXVECTOR3 GetPos(void) { return m_Info.pos; }

private:

	// *** �ÓI�ϐ� ***
	static int m_nNumAll;		// ����

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��
};
