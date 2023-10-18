//========================================
// 
// �h�[��3D�̏���
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
#if 0
// �h�[��3D�N���X
class CDoll3D {
public:
	//========== [[[ �N���X��` ]]]
	// �{�[����ԃN���X
	class CBoneState {
	public:
		// [[[ �\���̐錾 ]]]
		// �ړ��A�j�����
		struct MoveAnimState {
			EASE        posEase   = EASE_LINEAR;
			D3DXVECTOR3 oldPos    = INITD3DXVECTOR3;
			D3DXVECTOR3 targetPos = INITD3DXVECTOR3;
			short       counter   = 0;
			short       time      = 0;
		};

		// ��]�A�j�����
		struct SpinAnimState {
			EASE        rotEase   = EASE_LINEAR;
			D3DXVECTOR3 oldRot    = INITD3DXVECTOR3;
			D3DXVECTOR3 targetRot = INITD3DXVECTOR3;
			int         counter   = 0;
			int         time      = 0;
		};

		// �g�k�A�j�����
		struct ScaleAnimState {
			EASE        scaleEase   = EASE_LINEAR;
			D3DXVECTOR3 oldScale    = INITD3DXVECTOR3;
			D3DXVECTOR3 targetScale = INITD3DXVECTOR3;
			int         counter     = 0;
			int         time        = 0;
		};

		// �A�j����ԑ���
		struct AnimStateSum {
			MoveAnimState*  move   = NULL;
			SpinAnimState*  spin   = NULL;
			ScaleAnimState* scale  = NULL;
		};

		// [[[ �֐��錾 ]]]
		CBoneState();
		~CBoneState();

	private:
		// [[[ �ϐ��錾 ]]]
		D3DXVECTOR3  m_pos;
		D3DXVECTOR3  m_rot;
		D3DXVECTOR3  m_scale;
		D3DXMATRIX   m_resultMtx;
		AnimStateSum m_animeStateSum;
	};

	//========== [[[ �֐��錾 ]]]
	CDoll3D();
	~CDoll3D();
	void SetUp           (const short& setUpIdx);
	void Update          (void);
	void SetMotion       (int nIdx)   { m_nMotion = nIdx; }
	void SetMotionStop   (bool bStop) { m_bMotionStop = bStop; }
	void SetMotionCount  (int nCount) { m_nMotionCounter = nCount; }
	void SetDrawCollision(bool bDraw) { m_bDrawCollision = bDraw; }
	bool GetDrawCollision(void)       { return m_bDrawCollision; }
	// �擾�ݒ�
	D3DXVECTOR3 GetPos            (void)            { return m_pos;                }
	void        SetPos            (D3DXVECTOR3 pos) { m_pos = pos;                 }
	D3DXVECTOR3 GetRot            (void)            { return m_rot;                }
	void        SetRot            (D3DXVECTOR3 rot) { m_rot = rot;                 }
	void        SetScale          (float fScale)    { m_fScale = fScale;           }
	void        SetCol            (Color col)       { m_col = col;                 }
	void        SetBrOfEm         (float fBr)       { m_fBrOfEm = fBr;             }
	float       GetBrOfEm         (void)            { return m_fBrOfEm;            }
	void        InitPartsState    (int nParts)      { m_boneStates[nParts] = {};       }
	CBoneState   GetPartsState     (int nParts)      { return m_boneStates[nParts];     }
	bool        GetPartsState_Idx (int nIdx, CBoneState* pParts);
	bool        GetPartsState_Part(int nPart, CBoneState* pParts);
	CBoneState** GetPartsState_PP  (void)            { return &m_boneStates;            }
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
	D3DXVECTOR3  m_pos;
	D3DXVECTOR3  m_rot;
	CBoneState*   m_boneStates;

	bool         m_bMotionStop;		// ���[�V������~�t���O
	bool         m_bDrawCollision;	// �����蔻��`��t���O
	int          m_nModelSetUp;		// ���f���Z�b�g�A�b�v�ԍ�
	int          m_nMotion;			// ���[�V�����ԍ�
	int          m_nMotionOld;		// ���[�V�����ԍ�(�ߋ�)
	int          m_nMotionCounter;	// ���[�V�����J�E���^�[
	Color        m_col;				// �F
	float        m_fBrOfEm;			// ���������̖��邳
	float        m_fScale;			// �傫��
};
#endif