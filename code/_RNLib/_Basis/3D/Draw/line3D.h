//========================================
// 
// ���C��3D�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ line3D.h ]]]
//========================================
#ifndef _LINE3D_H_
#define _LINE3D_H_

#include "../../Other/color.h"

//****************************************
// �N���X��`
//****************************************
// ���C��3D�N���X
class CLine3D {
public:
	//========= [[[ �֐��錾 ]]]
	CLine3D();
	~CLine3D();
	void Init(void);
	void Uninit(void);
	void Draw(bool bZTest);
	void Set         (D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, Color col = INITCOLOR, bool bZTest = true);
	void Set_Circle  (D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col = INITCOLOR, bool bZTest = true);
	void Set_Sphere  (D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, Color col = INITCOLOR, bool bZTest = true);
	void Set_Cube    (D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, Color col = INITCOLOR, bool bZTest = true);
	void Set_Cylinder(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, float fHeight, Color col = INITCOLOR, bool bZTest = true);
	void SetReset(void);

private:
	//========= [[[ �\���̒�` ]]]
	// �`��ݒ���\����
	typedef struct DrawSet_ {
		bool bZTest = false;	// Z�e�X�g�t���O
	}DrawSet;

	//========= [[[ �ϐ��錾 ]]]
	DrawSet* m_pDrawSet;	// �`��ݒ���
	int      m_nDrawSetNum;	// �`��ݒ萔
	LPDIRECT3DVERTEXBUFFER9* m_ppVtxBuff;	// ���_�o�b�t�@�ւ̃_�u���|�C���^
};

#endif