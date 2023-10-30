//========================================
// 
// �G�t�F�N�g����
// Author:RYUKI FUJIWARA
// 
//========================================
// *** block.cpp ***
//========================================
#include "particle.h"
#include "../main.h"

#define MAX_COUNT		(60)		//�J�E���g
#define PI				(628)		//�~��
#define HARF_PI			(314)		//���~��
#define MAGNI			(100.0f)	//�{��
#define RANDOM_MAGNI	(16)		//�����_���{��
#define ATTEN_RATE		(0.3f)		//������

//========================================
// �ÓI�ϐ�
//========================================
int CParticle::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CParticle::CParticle(void)
{
	m_Info.pos = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.scale = INITD3DXVECTOR3;
	m_Info.col = INITCOLOR;
	m_Info.nCount = MAX_COUNT;
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CParticle::~CParticle()
{
	m_nNumAll--;
}

//========================================
// ������
//========================================
HRESULT CParticle::Init(int nTex)
{
	m_Info.move = D3DXVECTOR3(
	sinf((float)(rand() % PI - HARF_PI) / MAGNI) * (float)(rand() % RANDOM_MAGNI - RANDOM_MAGNI * 0.5f),	//x�̈ړ���
	cosf((float)(rand() % PI - HARF_PI) / MAGNI) * (float)(rand() % RANDOM_MAGNI - RANDOM_MAGNI * 0.5f),	//y�̈ړ���
	INITD3DXVECTOR3.z);

	m_Info.col = INITCOLOR;
	m_Info.nTex = nTex;
	m_Info.nCount = MAX_COUNT;

	return S_OK;
}

//========================================
// �I��
//========================================
void CParticle::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CParticle::Update(void)
{
	//�ړ��ʉ��Z
	m_Info.pos += m_Info.move;

	RNLib::Polygon3D().Put(m_Info.pos, INITD3DXVECTOR3)
		->SetTex(m_Info.nTex)
		->SetBillboard(true)
		->SetCol(m_Info.col)
		->SetSize(m_Info.scale.x, m_Info.scale.y)
		->SetAlphaBlendMode(CDrawState::ALPHA_BLEND_MODE::ADD)
		->SetPriority(1);

	//�ړ��ʌ���
	m_Info.move.x += (0.0f - m_Info.move.x) * ATTEN_RATE;
	m_Info.move.y += (0.0f - m_Info.move.y) * ATTEN_RATE;

	//�����v�Z
	float fCountRate = CEase::Easing(CEase::TYPE::IN_SINE, m_Info.nCount, MAX_COUNT);

	//�����ɂ��Ă���
	m_Info.col.a = m_Info.col.a * fCountRate;

	//�������炷
	m_Info.nCount--;

	if (m_Info.nCount <= 0)
	{
		CObject::Delete();
	}
}

//========================================
// �`��
//========================================
void CParticle::Draw(void)
{

}