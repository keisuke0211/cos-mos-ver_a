//========================================
// 
// �����u���b�N���� [move-block.h]
// Author:HIROMU KOMURO
// 
//========================================
#include "../../manager.h"
#include "move-block.h"
#include "../../main.h"

#define ROT_MAG		(0.05f)	// �{��
//========================================
// �ÓI�ϐ�
//========================================
int CMoveBlock::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CMoveBlock::CMoveBlock(void)
{
	Manager::BlockMgr()->AddList(this);

	m_type = TYPE::MOVE_BLOCK;	// ��ނ̐ݒ�

	// �傫���̐ݒ�
	m_width = SIZE_OF_1_SQUARE * 2.0f;
	m_height = SIZE_OF_1_SQUARE * 0.5f;

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = INITD3DXVECTOR3;
	m_Info.refPos = INITD3DXVECTOR3;
	m_Info.move = INITD3DXVECTOR3;
	m_Info.rot = INITD3DXVECTOR3;
	m_Info.size = INITD3DXVECTOR3;
	m_Info.col = INITD3DCOLOR;
	m_Info.frefdef = 0.0f;
	m_Info.nType = 0;
	m_Info.nID = m_nNumAll;
	m_Info.nModelIdx = RNLib::Model().Load("data\\MODEL\\Lift.x");
	nModelIdx = RNLib::Model().Load("data\\MODEL\\Lift_Gear.x");
	m_nNumAll++;

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================================
// �f�X�g���N�^
//========================================
CMoveBlock::~CMoveBlock()
{
	m_nNumAll--;
}

//========================================
// ������
//========================================
HRESULT CMoveBlock::Init(void)
{

	return S_OK;
}

//========================================
// �I��
//========================================
void CMoveBlock::Uninit(void)
{
	
}

//========================================
// �X�V
//========================================
void CMoveBlock::Update(void)
{
	m_Info.posOld = m_Info.pos;	// �O��ʒu�X�V
	m_Info.pos += m_Info.move;	// �ړ��ʂ̑���

	if (m_Info.move.y != 0.0f)
	{
		float fConv = m_Info.move.y;
		if (fConv < 0.0f)
			fConv -= 1.0f;
		else
			fConv += 1.0f;

		m_rot.z += fConv * ROT_MAG * -1;
	}

	if (m_Info.move.x != 0.0f)
	{
		float f = m_Info.move.x;
		if (f < 0.0f)
			f -= 1.0f;
		else
			f += 1.0f;

		m_rot.z += f * ROT_MAG * -1;
	}

	// x�̈ړ��ʂ̔��]
	if (m_Info.refPos.x + m_Info.frefdef <= m_Info.pos.x || m_Info.refPos.x - m_Info.frefdef >= m_Info.pos.x)
	{
		m_Info.move.x *= -1;
	}
	// y�̈ړ��ʂ̔��]
	if (m_Info.refPos.y + m_Info.frefdef <= m_Info.pos.y || m_Info.refPos.y - m_Info.frefdef >= m_Info.pos.y)
	{
		m_Info.move.y *= -1;
	}

	CStageObject::SetPos(m_Info.pos);
	RNLib::Model().Put(m_Info.pos, m_Info.rot, m_Info.nModelIdx);
	RNLib::Model().Put(m_Info.pos, m_rot, nModelIdx);
}

//========================================
// �`��
//========================================
void CMoveBlock::Draw(void)
{

}