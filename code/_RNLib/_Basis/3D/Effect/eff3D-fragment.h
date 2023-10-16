//========================================
// 
// �G�t�F�N�g3D(����)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ eff3D-polygon.h ]]]
//========================================
#ifndef _EFF3D_FRAGMENT_H_
#define _EFF3D_FRAGMENT_H_

#include "effect3D.h"
#include "../../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
// �G�t�F�N�g3D(����)�N���X
class CEff3D_Fragment : public CEff3D {
public:
	//========== [[[ �֐��錾 ]]]
	CEff3D_Fragment();
	~CEff3D_Fragment();
	void Init(void);
	void Uninit(void);
	void Update(void);
	// �ݒ�擾
	void SetModelIdx(int nModelIdx)     { if (this != NULL)m_nModelIdx = nModelIdx; }
	void SetMove    (D3DXVECTOR3 move)  { m_move = move; }
	void SetSpin    (D3DXVECTOR3 spin)  { m_spin = spin; }
	void SetScale   (float fScale)      { m_fScale = fScale; }
	void SetTex     (int nTex)          { m_nTex = nTex; }
	void SetCol     (Color col)         { m_col = col; }
	static int GetTypeModel(FRAGMENT_TYPE type) { return m_aTypeModel[(int)type]; }

private:
	//========== [[[ �ϐ��錾 ]]]
	static int    m_aTypeModel[(int)FRAGMENT_TYPE::MAX];
	int           m_nModelIdx;
	D3DXVECTOR3   m_move;
	D3DXVECTOR3   m_spin;
	float         m_fScale;
	int           m_nTex;
	Color         m_col;
};

#endif