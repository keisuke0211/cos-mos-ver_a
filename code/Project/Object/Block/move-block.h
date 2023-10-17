//========================================
// 
// �����u���b�N���� [move-block.h]
// Author:HARUTO KIKUCHI
// 
//========================================

#ifndef _MOVEBLOCK_H_
#define _MOVEBLOCK_H_

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//========================================
// �N���X
//========================================
class CMoveBlock : public CStageObject
{
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
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
	void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	void SetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }

	//�擾
	D3DXCOLOR GetColor(void) { return m_Info.col; }
	D3DXVECTOR3 GetSize(void) { return m_Info.size; }

private:

	//�ÓI�ϐ�
	static int m_nNumAll;		// ����

	//�ϐ�
	Info m_Info;		// ���ʏ��

};
#endif