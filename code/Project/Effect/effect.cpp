//========================================
// 
// �G�t�F�N�g����
// Author:RYUKI FUJIWARA
// 
//========================================
// *** block.cpp ***
//========================================
#include "effect.h"
#include "../main.h"

#define MAX_COUNT (60)	//�J�E���g

//========================================
// �ÓI�ϐ�
//========================================
int CEffect::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CEffect::CEffect(void)
{
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITCOLOR;
	m_Info.nCount = MAX_COUNT;
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
HRESULT CEffect::Init(int nTex)
{
	m_Info.move = INITD3DXVECTOR3;
	m_Info.col = INITCOLOR;
	m_Info.nTex = nTex;
	m_Info.nCount = MAX_COUNT;

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
	RNLib::Polygon3D().Put(m_Info.pos + m_Info.move, INITD3DXVECTOR3)
		->SetTex(m_Info.nTex)
		->SetBillboard(true)
		->SetCol(m_Info.col);

	m_Info.nCount--;

	//�����v�Z
	float fCountRate = CEase::Easing(CEase::TYPE::IN_SINE, m_Info.nCount, MAX_COUNT);

	m_Info.col.a = m_Info.col.a * fCountRate;

	if (m_Info.nCount <= 0)
	{
		CObject::Delete();
	}
}

//========================================
// �`��
//========================================
void CEffect::Draw(void)
{

}