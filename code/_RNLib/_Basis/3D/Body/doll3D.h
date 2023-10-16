//========================================
// 
// ���i�Z�b�g�A�b�v3D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "setup3D.h"
#include "../../Calculation/matrix.h"
#include "../../Calculation/easing.h"

//****************************************
// �N���X��`
//****************************************
// ���i�Z�b�g�A�b�v3D�N���X
class CParts3DSetUp {
public:
	//========== [[[ �\���̒�` ]]]
	// ���i���\����
	typedef struct Parts_ {
		// �ʒu�֘A
		D3DXVECTOR3 pos   = INITD3DXVECTOR3;				// �ʒu
		D3DXVECTOR3 rot   = INITD3DXVECTOR3;				// ����
		D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �g��{��
		D3DXMATRIX  mtx   = INITD3DXMATRIX;					// �}�g���b�N�X(�ŏI�ʒu)

		//========== [[[ ���[�V�����֘A ]]]
		// �ړ��A�j��
		EASE        easePos           = EASE_LINEAR;		// �ʒu���
		bool        bPosAnim          = false;				// �ʒu�A�j���t���O
		int         nCounterPosAnim   = 0;					// �ʒu�A�j���J�E���^�[
		int         nPosAnimTime      = 0;					// �ʒu�A�j���ɂ����鎞��
		D3DXVECTOR3 posOld            = INITD3DXVECTOR3;	// ���̈ʒu
		D3DXVECTOR3 targetPos         = INITD3DXVECTOR3;	// �ڕW�ʒu
		// �����A�j��			      
		EASE        easeRot           = EASE_LINEAR;		// �������
		bool        bRotAnim          = false;				// �����A�j���t���O
		int         nCounterRotAnim   = 0;					// �����A�j���J�E���^�[
		int         nRotAnimTime      = 0;					// �����A�j���ɂ����鎞��
		D3DXVECTOR3 rotOld            = INITD3DXVECTOR3;	// ���̊p�x
		D3DXVECTOR3 targetRot         = INITD3DXVECTOR3;	// �ڕW�p�x
		// ����
		bool        bStep             = false;				// �����t���O(�����A�j���ϐ��g�p)
		int         nStepTime         = 0;					// ��������
		int         nStepResetTime    = 0;					// �����߂鎞��
		// �g��k��
		EASE        easeScale         = EASE_LINEAR;		// �g��k�����
		bool        bScaleAnim        = false;				// �g��k���t���O
		int         nCounterScaleAnim = 0;					// �g��k���J�E���^�[
		int         nScaleAnimTime    = 0;					// �g��k���ɂ����鎞��
		D3DXVECTOR3 scaleOld          = INITD3DXVECTOR3;	// ���̊g��{��
		D3DXVECTOR3 targetScale       = INITD3DXVECTOR3;	// �ڕW�g��{��
		// ��������
		bool        bStepReaction     = false;				// ���������t���O
	}PartsState;

	// �R���W�������i���\����
	typedef struct CLParts_ {
		D3DXVECTOR3 pos = INITD3DXVECTOR3;	// �ʒu
		D3DXVECTOR3 rot = INITD3DXVECTOR3;	// ����
	}CLParts;

	// ���i�f�[�^�\����
	typedef struct PartsData_ {
		int         nIdx             = 0;				// �����̔ԍ�
		int         nModelIdx        = DATANONE;		// ���f���̔ԍ�
		int         nParent          = DATANONE;		// �e�ԍ�
		D3DXVECTOR3 fixedRelativePos = INITD3DXVECTOR3;	// �Œ�̑��Έʒu
		D3DXVECTOR3 fixedRelativeRot = INITD3DXVECTOR3;	// �Œ�̑��Ίp�x
		D3DXVECTOR3 rotRelativePos   = INITD3DXVECTOR3;	// ��]���̑��Έʒu
		bool        bLighting        = true;			// ���C�e�B���O�t���O
	}PartsData;

	// �f�[�^�\����
	typedef struct Data_ {
		int        nPartsNum  = 0;
		PartsData* pPartsData = NULL;
	}Data;

	//========== [[[ �֐��錾 ]]]
	CParts3DSetUp();
	~CParts3DSetUp();
	void Init            (int nModelSetUp);
	void Uninit          (void);
	void Update          (void);
	void SetMotion       (int nIdx)   { m_nMotion = nIdx; }
	void SetMotionStop   (bool bStop) { m_bMotionStop = bStop; }
	void SetMotionCount  (int nCount) { m_nMotionCounter = nCount; }
	void SetDrawCollision(bool bDraw) { m_bDrawCollision = bDraw; }
	bool GetDrawCollision(void)       { return m_bDrawCollision; }
	void InitPause       (void);
	// �擾�ݒ�
	D3DXVECTOR3 GetPos            (void)            { return m_pos;                }
	void        SetPos            (D3DXVECTOR3 pos) { m_pos = pos;                 }
	D3DXVECTOR3 GetRot            (void)            { return m_rot;                }
	void        SetRot            (D3DXVECTOR3 rot) { m_rot = rot;                 }
	void        SetScale          (float fScale)    { m_fScale = fScale;           }
	void        SetCol            (Color col)       { m_col = col;                 }
	void        SetBrOfEm         (float fBr)       { m_fBrOfEm = fBr;             }
	float       GetBrOfEm         (void)            { return m_fBrOfEm;            }
	void        InitPartsState    (int nParts)      { m_pParts[nParts] = {};       }
	PartsState  GetPartsState     (int nParts)      { return m_pParts[nParts];     }
	bool        GetPartsState_Idx (int nIdx, PartsState* pParts);
	bool        GetPartsState_Part(int nPart, PartsState* pParts);
	PartsState**GetPartsState_PP  (void)            { return &m_pParts;            }
	D3DXVECTOR3 GetCLPartsPos     (int nIdx)        { return m_pCLParts[nIdx].pos; }
	D3DXVECTOR3 GetCLPartsRot     (int nIdx)        { return m_pCLParts[nIdx].rot; }
	int         GetMotionIdx      (void)            { return m_nMotion;            }
	int         GetMotionCounter  (void)            { return m_nMotionCounter;     }
	bool        GetMotionEnd      (void);
	bool        GetMotionStep     (void);

	//========== [[[ �ÓI�֐��錾 ]]]
	static void LoadData(Data* pPartsSet);
	static void SaveData(Data* pPartsSet);

private:
	//========== [[[ �֐��錾 ]]]
	void ModelSet      (Data *pPartsSet);
	void MotionSet     (Data partsSet);
	bool MotionUpdate  (int nMotion, Data partsSet);
	void LoadMotionAnim(Data partsSet);
	void MotionAnim    (Data partsSet);
	void MotionClear   (Data partsSet, int nMotion);
	void DrawCollision (void);

	//========== [[[ �ϐ��錾 ]]]
	D3DXVECTOR3  m_pos;				// �ʒu(�{��)
	D3DXVECTOR3  m_rot;				// ����(�{��)
	bool         m_bMotionStop;		// ���[�V������~�t���O
	bool         m_bDrawCollision;	// �����蔻��`��t���O
	int          m_nModelSetUp;		// ���f���Z�b�g�A�b�v�ԍ�
	int          m_nMotion;			// ���[�V�����ԍ�
	int          m_nMotionOld;		// ���[�V�����ԍ�(�ߋ�)
	int          m_nMotionCounter;	// ���[�V�����J�E���^�[
	Color        m_col;				// �F
	float        m_fBrOfEm;			// ���������̖��邳
	float        m_fScale;			// �傫��
	PartsState*  m_pParts;			// ���i���̃|�C���^
	CLParts*     m_pCLParts;		// �R���W�������i���̃|�C���^
};