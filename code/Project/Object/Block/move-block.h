//========================================
// 
// �����u���b�N���� [move-block.h]
// Author:HIROMU KOMURO
// 
//========================================

#ifndef _MOVEBLOCK_H_
#define _MOVEBLOCK_H_

#include "../../../_RNLib/RNlib.h"

//========================================
// �N���X
//========================================
class CMoveBlock : public CStageObject
{
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�O��)
		D3DXVECTOR3 refPos;		// �ʒu(�ߋ�)
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		float frefdef;			// ���˂��鋗��
		int nCntMove;			// �ړ��J�E���g
		int nType;				// ���
		int nID;				// ID
		int nModelIdx;
	};

	//�֐�
	CMoveBlock();
	~CMoveBlock();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ݒ�
	void SetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetRefdef(const float refdef) { m_Info.frefdef = refdef; }
	void SetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	void SetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* ���f���ԍ�	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	//�擾
	D3DXVECTOR3 GetPos(void)	{ return m_Info.pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_Info.posOld; }
	D3DXVECTOR3 GetRot(void)	{ return m_Info.rot; }
	D3DXVECTOR3 GetMove(void)	{ return m_Info.move; }
	D3DXCOLOR GetColor(void)	{ return m_Info.col; }
	D3DXVECTOR3 GetSize(void)	{ return m_Info.size; }

private:

	//�ÓI�ϐ�
	static int m_nNumAll;		// ����

	//�ϐ�
	Info m_Info;		// ���ʏ��

	int nModelIdx;

};
#endif