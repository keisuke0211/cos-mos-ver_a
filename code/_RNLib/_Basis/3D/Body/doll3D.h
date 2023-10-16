//========================================
// 
// 部品セットアップ3Dのヘッダファイル
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
// 部品セットアップ3Dクラス
class CParts3DSetUp {
public:
	//========== [[[ 構造体定義 ]]]
	// 部品情報構造体
	typedef struct Parts_ {
		// 位置関連
		D3DXVECTOR3 pos   = INITD3DXVECTOR3;				// 位置
		D3DXVECTOR3 rot   = INITD3DXVECTOR3;				// 向き
		D3DXVECTOR3 scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// 拡大倍率
		D3DXMATRIX  mtx   = INITD3DXMATRIX;					// マトリックス(最終位置)

		//========== [[[ モーション関連 ]]]
		// 移動アニメ
		EASE        easePos           = EASE_LINEAR;		// 位置補間
		bool        bPosAnim          = false;				// 位置アニメフラグ
		int         nCounterPosAnim   = 0;					// 位置アニメカウンター
		int         nPosAnimTime      = 0;					// 位置アニメにかかる時間
		D3DXVECTOR3 posOld            = INITD3DXVECTOR3;	// 元の位置
		D3DXVECTOR3 targetPos         = INITD3DXVECTOR3;	// 目標位置
		// 向きアニメ			      
		EASE        easeRot           = EASE_LINEAR;		// 向き補間
		bool        bRotAnim          = false;				// 向きアニメフラグ
		int         nCounterRotAnim   = 0;					// 向きアニメカウンター
		int         nRotAnimTime      = 0;					// 向きアニメにかかる時間
		D3DXVECTOR3 rotOld            = INITD3DXVECTOR3;	// 元の角度
		D3DXVECTOR3 targetRot         = INITD3DXVECTOR3;	// 目標角度
		// 足踏
		bool        bStep             = false;				// 足踏フラグ(向きアニメ変数使用)
		int         nStepTime         = 0;					// 足踏時間
		int         nStepResetTime    = 0;					// 足踏戻る時間
		// 拡大縮小
		EASE        easeScale         = EASE_LINEAR;		// 拡大縮小補間
		bool        bScaleAnim        = false;				// 拡大縮小フラグ
		int         nCounterScaleAnim = 0;					// 拡大縮小カウンター
		int         nScaleAnimTime    = 0;					// 拡大縮小にかかる時間
		D3DXVECTOR3 scaleOld          = INITD3DXVECTOR3;	// 元の拡大倍率
		D3DXVECTOR3 targetScale       = INITD3DXVECTOR3;	// 目標拡大倍率
		// 足踏反応
		bool        bStepReaction     = false;				// 足踏反応フラグ
	}PartsState;

	// コリジョン部品情報構造体
	typedef struct CLParts_ {
		D3DXVECTOR3 pos = INITD3DXVECTOR3;	// 位置
		D3DXVECTOR3 rot = INITD3DXVECTOR3;	// 向き
	}CLParts;

	// 部品データ構造体
	typedef struct PartsData_ {
		int         nIdx             = 0;				// 自分の番号
		int         nModelIdx        = DATANONE;		// モデルの番号
		int         nParent          = DATANONE;		// 親番号
		D3DXVECTOR3 fixedRelativePos = INITD3DXVECTOR3;	// 固定の相対位置
		D3DXVECTOR3 fixedRelativeRot = INITD3DXVECTOR3;	// 固定の相対角度
		D3DXVECTOR3 rotRelativePos   = INITD3DXVECTOR3;	// 回転軸の相対位置
		bool        bLighting        = true;			// ライティングフラグ
	}PartsData;

	// データ構造体
	typedef struct Data_ {
		int        nPartsNum  = 0;
		PartsData* pPartsData = NULL;
	}Data;

	//========== [[[ 関数宣言 ]]]
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
	// 取得設定
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
	D3DXVECTOR3  m_pos;				// 位置(本体)
	D3DXVECTOR3  m_rot;				// 向き(本体)
	bool         m_bMotionStop;		// モーション停止フラグ
	bool         m_bDrawCollision;	// 当たり判定描画フラグ
	int          m_nModelSetUp;		// モデルセットアップ番号
	int          m_nMotion;			// モーション番号
	int          m_nMotionOld;		// モーション番号(過去)
	int          m_nMotionCounter;	// モーションカウンター
	Color        m_col;				// 色
	float        m_fBrOfEm;			// 発光部分の明るさ
	float        m_fScale;			// 大きさ
	PartsState*  m_pParts;			// 部品情報のポインタ
	CLParts*     m_pCLParts;		// コリジョン部品情報のポインタ
};