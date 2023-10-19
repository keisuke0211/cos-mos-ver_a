//========================================
// 
// ドール3Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "setup3D.h"
#include "../../Calculation/matrix.h"
#include "../../Calculation/easing.h"

//****************************************
// クラス定義
//****************************************
#if 0
// ドール3Dクラス
class CDoll3D {
public:
	//========== [[[ クラス定義 ]]]
	// ボーン状態クラス
	class CBoneState {
	public:
		// [[[ 構造体宣言 ]]]
		// 移動アニメ状態
		struct MoveAnimState {
			EASE        posEase   = EASE_LINEAR;
			D3DXVECTOR3 oldPos    = INITD3DXVECTOR3;
			D3DXVECTOR3 targetPos = INITD3DXVECTOR3;
			short       counter   = 0;
			short       time      = 0;
		};

		// 回転アニメ状態
		struct SpinAnimState {
			EASE        rotEase   = EASE_LINEAR;
			D3DXVECTOR3 oldRot    = INITD3DXVECTOR3;
			D3DXVECTOR3 targetRot = INITD3DXVECTOR3;
			int         counter   = 0;
			int         time      = 0;
		};

		// 拡縮アニメ状態
		struct ScaleAnimState {
			EASE        scaleEase   = EASE_LINEAR;
			D3DXVECTOR3 oldScale    = INITD3DXVECTOR3;
			D3DXVECTOR3 targetScale = INITD3DXVECTOR3;
			int         counter     = 0;
			int         time        = 0;
		};

		// アニメ状態総括
		struct AnimStateSum {
			MoveAnimState*  move   = NULL;
			SpinAnimState*  spin   = NULL;
			ScaleAnimState* scale  = NULL;
		};

		// [[[ 関数宣言 ]]]
		CBoneState();
		~CBoneState();

	private:
		// [[[ 変数宣言 ]]]
		D3DXVECTOR3  m_pos;
		D3DXVECTOR3  m_rot;
		D3DXVECTOR3  m_scale;
		D3DXMATRIX   m_resultMtx;
		AnimStateSum m_animeStateSum;
	};

	//========== [[[ 関数宣言 ]]]
	CDoll3D();
	~CDoll3D();
	void SetUp           (const short& setUpIdx);
	void Update          (void);
	void SetMotion       (int nIdx)   { m_nMotion = nIdx; }
	void SetMotionStop   (bool bStop) { m_bMotionStop = bStop; }
	void SetMotionCount  (int nCount) { m_nMotionCounter = nCount; }
	void SetDrawCollision(bool bDraw) { m_bDrawCollision = bDraw; }
	bool GetDrawCollision(void)       { return m_bDrawCollision; }
	// 取得設定
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

	//========== [[[ 静的関数宣言 ]]]
	static void LoadData(Data* pPartsSet);
	static void SaveData(Data* pPartsSet);

private:
	//========== [[[ 関数宣言 ]]]
	void ModelSet      (Data *pPartsSet);
	void MotionSet     (Data partsSet);
	bool MotionUpdate  (int nMotion, Data partsSet);
	void LoadMotionAnim(Data partsSet);
	void MotionAnim    (Data partsSet);
	void MotionClear   (Data partsSet, int nMotion);
	void DrawCollision (void);

	//========== [[[ 変数宣言 ]]]
	D3DXVECTOR3  m_pos;
	D3DXVECTOR3  m_rot;
	CBoneState*   m_boneStates;

	bool         m_bMotionStop;		// モーション停止フラグ
	bool         m_bDrawCollision;	// 当たり判定描画フラグ
	int          m_nModelSetUp;		// モデルセットアップ番号
	int          m_nMotion;			// モーション番号
	int          m_nMotionOld;		// モーション番号(過去)
	int          m_nMotionCounter;	// モーションカウンター
	Color        m_col;				// 色
	float        m_fBrOfEm;			// 発光部分の明るさ
	float        m_fScale;			// 大きさ
};
#endif