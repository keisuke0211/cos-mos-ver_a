//========================================
// 
// �u���b�N����
// Author:KEISUKE OTONO
// 
//========================================
// *** block.cpp ***
//========================================
#include "effect.h"
#include "../main.h"

//========================================
// �ÓI�ϐ�
//========================================
int CEffect::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CEffect::CEffect(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CEffect::~CEffect()
{
	m_nNumAll--;
}

//========================================
// ������
//========================================
HRESULT CEffect::Init(void)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.nType = 0;

	return S_OK;
}

//========================================
// �I��
//========================================
void CEffect::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CEffect::Update(void)
{
	// �ߋ��̈ʒu
	RNLib::Polygon3D()->Put(INITD3DXVECTOR3, INITD3DXVECTOR3)
		->SetTex(1)
		->SetBillboard(true);
}

//========================================
// �`��
//========================================
void CEffect::Draw(void)
{

}