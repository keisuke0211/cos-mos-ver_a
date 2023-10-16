//========================================
// 
// モデルセットアップ関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "doll3D.h"
#include "../../Other/regist.h"

//****************************************
// クラス定義
//****************************************
// モデルセットアップクラス
class CModelSetUp : public CRegist{
public:
	//========== [[[ 列挙型定義 ]]]
	// 構成
	typedef enum {
		PLATFORM_NONE,				// 無し
		PLATFORM_FOOTLESS_00,		// 無足[00]
		PLATFORM_BIPEDALISM_00,		// 二足[00]
		PLATFORM_BIPEDALISM_01,		// 二足[01]
		PLATFORM_QUADRUPEDALISM_00,	// 四足[00]
		PLATFORM_HEXAPOD_00,		// 六足[00]
		PLATFORM_OCTAPOD_00,		// 八足[00]
		PLATFORM_MAX,
	}PLATFORM;

	// 部位
	typedef enum {
		PART_HEAD      ,	// 頭
		PART_NECK      ,	// 首
		PART_CHEST     ,	// 胸
		PART_WAIST     ,	// 腰
		PART_UPPERARM_L,	// 上腕[左]
		PART_UPPERARM_R,	// 上腕[右]
		PART_FOREARM_L ,	// 前腕[左]
		PART_FOREARM_R ,	// 前腕[右]
		PART_HAND_L    ,	// 手[左]
		PART_HAND_R    ,	// 手[右]
		PART_FINGER4_L ,	// 指４[左]
		PART_FINGER4_R ,	// 指４[右]
		PART_FINGER1_L ,	// 指１[左]
		PART_FINGER1_R ,	// 指１[右]
		PART_THIGH_L   ,	// 太腿[左]
		PART_THIGH_R   ,	// 太腿[右]
		PART_SHIN_L    ,	// 脛[左]
		PART_SHIN_R    ,	// 脛[右]
		PART_LEGS_L    ,	// 足[左]
		PART_LEGS_R    ,	// 足[右]
		PART_MAX       ,
	}PART;

	//========== [[[ 構造体定義 ]]]
	// データ構造体
	typedef struct Data_ {
		CParts3DSetUp::Data partsSet = {};				// 部品情報
		CCollision3D::Data  collSet  = {};				// コリジョン情報
		PLATFORM            platform = PLATFORM_NONE;	// 構成
	}Data;

	//========== [[[ 関数宣言 ]]]
	CModelSetUp();
	~CModelSetUp();
	void        Uninit             (void);
	int         Load               (const char* pLoadPath, short nIdx = DATANONE);
	void        Save               (char* pPath, int nIdx);
	Data*       GetData            (const int nIdx) { return &m_pData[nIdx]; }
	int         GetPlatformPartIdx (const PLATFORM platform, const CModelSetUp::PART part);
	const char* GetPlatformName    (const PLATFORM platform);
	PLATFORM    GetPlatformFromName(const char* pName);
	void        InitMemory         (const int nNum);

private:
	//========== [[[ 変数宣言 ]]]
	Data* m_pData;
};