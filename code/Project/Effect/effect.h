//========================================
// 
// �G�t�F�N�g����
// Author:RYUKI FUJIWARA
// 
//========================================

#include "../../_RNLib/RNlib.h"

//****************************************
// �N���X
//****************************************
class CEffect : CObject{
public:

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nID;				// ID
	};

	// *** �֐� ***
	CEffect();
	~CEffect();

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ---------------------------------------------
	/* �F			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }

	// -- ���� ---------------------------------------------
	/* �F		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** �ÓI�ϐ� ***
	static int m_nNumAll;		// ����

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};
