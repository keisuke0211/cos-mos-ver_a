//========================================
// 
// �X�e�[�W�I�u�W�F�N�g�}�l�[�W���[�̏���
// Author:KEISUKE OTONO
// Arrange:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../_RNLib/RNlib.h"
#include "Block/block.h"
#include "Block\fill-block.h"
#include "Gimmick\Spike.h"
#include "Block/move-block.h"
#include "Gimmick/trampoline.h"
#include "Gimmick/meteor.h"
#include "Gimmick\rocket.h"
#include "Item/Parts.h"
#include "BackGround/Planet.h"
#include "BackGround/Star.h"
//****************************************
// �N���X
//****************************************
class CStageObjectMgr : public CObjectMgr {
public:
	//========== [[[ �ÓI�ϐ��錾 ]]]
	static const char* BLOCK_INFO_FILE;		// �u���b�N���̃t�@�C���p�X

	//========== [[[ �֐��錾 ]]]
	CStageObjectMgr();
	virtual~CStageObjectMgr();
	virtual void Update(void);	void Load(void);
	CBlock      *BlockCreate     (D3DXVECTOR3 pos);
	CFillBlock  *FillBlockCreate(D3DXVECTOR3 pos,CFillBlock::FILL_TYPE type);
	CSpike      *SpikeCreate	 (D3DXVECTOR3 pos);
	CTrampoline *TrampolineCreate(D3DXVECTOR3 pos);
	CMeteor     *MeteorCreate    (D3DXVECTOR3 pos, D3DXVECTOR3 move);
	CMoveBlock  *MoveBlockCreate (D3DXVECTOR3 pos, D3DXVECTOR3 move,float fRefdef);
	CParts      *PartsCreate	 (D3DXVECTOR3 pos);
	CRocket     *RocketCreate    (D3DXVECTOR3 pos);
	CPlanet		*PlanetCreate	 (D3DXVECTOR3 pos, D3DXVECTOR3 rot,CPlanet::STAR_TYPE type,Color col);
	CStar		*StarCreate		 (D3DXVECTOR3 pos, D3DXVECTOR3 rot);
private:

	// *** �\���� ***

	// ��ޏ��
	struct BlockType
	{
		char			aFileName[0xff];	// X�t�@�C���̃p�X
		int				nModelIdx;			// ���f���ԍ�
	};

	// *** �ÓI�ϐ� ***
	static int *m_nMaxType;

	// *** �ϐ� ***
	static BlockType *m_pBlockType;	// ��ޏ��
};