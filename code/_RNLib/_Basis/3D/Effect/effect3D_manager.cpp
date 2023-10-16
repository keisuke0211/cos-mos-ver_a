//========================================
// 
// エフェクト3Dマネージャーの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ effect3D_manager.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// マクロ定義
//****************************************
#define EFFECT3DLIST_PATH     "data\\_RNData\\Effect3DList.txt"
#define SCALE_MIN             (0.5f)
#define SCALE_ADD             (1.0f)
#define MOVEFORCE_RATE_MIN    (0.5f)
#define MOVEFORCE_RATE_ADD    (1.0f)
#define FRAGMENT_MOVE_XZ_RATE (0.25f)
#define FRAGMENT_MOVE_Y_RATE  (0.5f)

//****************************************
// 定数定義
//****************************************
namespace {
	// ポリゴン種類名
	const char* c_aPolygonTypeName[] = {
		"NONE",
		// UI
		"CALLOUT_TAKEAIM",
		"CALLOUT_SILENCE",
		// 状態異常
		"SLEEP",
		// 三次元空間
		"RING",
		"LIGHT_M",
		"SMOKE_M",
		"SMOKE_L",
		"LIQUID_S",
		"LIQUID_M",
		"FRAME_M",
		"LAVABALL_XS",
		"SPARK_ORANGE",
		"EXPLOSION_DESTROY_M",
	};

	// 力毎のパラメータ
	const int c_aPowerLife[] = {
		0,
		30,
		60,
		90,
	};
	const float c_aPowerMoveForce[] = {
		0.0f,
		1.0f,
		2.0f,
		4.0f,
	};
	const float c_aPowerSpin[] = {
		0.0f,
		D3DX_PI * 0.2f,
		D3DX_PI * 0.4f,
		D3DX_PI * 0.6f,
	};
}
CHECK_ARRAY_SIZE(c_aPolygonTypeName, (int)CEff3D::POLYGON_TYPE::MAX);
CHECK_ARRAY_SIZE(c_aPowerSpin      , (int)CEff3D::POWER       ::MAX);
CHECK_ARRAY_SIZE(c_aPowerLife      , (int)CEff3D::POWER       ::MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CEff3DMngクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// コンストラクタ
// Author:RIKU NISHIMURA
//========================================
CEff3DMng::CEff3DMng(void) {
	for (int nCntType = 0; nCntType < (int)CEff3D::POLYGON_TYPE::MAX; nCntType++) {
		m_aTypePolygon[nCntType] = {};
	}
}

//========================================
// デストラクタ
// Author:RIKU NISHIMURA
//========================================
CEff3DMng::~CEff3DMng(void) {

}

//========================================
// 初期化処理
// Author:RIKU NISHIMURA
//========================================
void CEff3DMng::Init(void) {
	CListMgr::Init();
}

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CEff3DMng::Uninit(void) {
	CListMgr::ReleaseAll();

	for (int nCntType = 0; nCntType < (int)CEff3D::POLYGON_TYPE::MAX; nCntType++) {
		RNLib::Memory()->Release(&m_aTypePolygon[nCntType].pScalingStart);
		RNLib::Memory()->Release(&m_aTypePolygon[nCntType].pScalingEnd);
		RNLib::Memory()->Release(&m_aTypePolygon[nCntType].pFadeOut);
	}
}

//========================================
// 更新処理
// Author:RIKU NISHIMURAS
//========================================
void CEff3DMng::Update(void) {
	CListMgr::Update();
}

//========================================
// 読み込み処理
// Author:RIKU NISHIMURAS
//========================================
void CEff3DMng::Load(void) {
	if (!RNLib::File()->OpenLoadFile(EFFECT3DLIST_PATH))
		return;

	// 読み込みループ
	while (RNLib::File()->SearchLoop("END")) {
		if (RNLib::File()->CheckIdentifier("POLYGON{")) {
			while (RNLib::File()->SearchLoop("}")) {
				for (int nCntType = 0; nCntType < (int)CEff3D::POLYGON_TYPE::MAX; nCntType++) {
					if (nCntType == 11) {
						int n = 0;
					}

					if (!RNLib::File()->CheckIdentifier(CreateText("%s{", c_aPolygonTypeName[nCntType]))) {
						continue;
					}

					while (RNLib::File()->SearchLoop("}")) {
						RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].nLife, "LIFE:");
						RNLib::File()->Scan(CFile::SCAN::TEXIDX,&m_aTypePolygon[nCntType].nTexIdx, "TEXTURE_PATH:");
						RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].nPtnX, "PTN_X:");
						RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].nPtnY, "PTN_Y:");
						RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].nPtnSwapTime, "PTNSWAP_TIME:");
						RNLib::File()->Scan(CFile::SCAN::BOOL, &m_aTypePolygon[nCntType].bZTest, "Z_TEST:");
						RNLib::File()->Scan(CFile::SCAN::BOOL, &m_aTypePolygon[nCntType].bLighting, "LIGHTING:");
						RNLib::File()->Scan(CFile::SCAN::BOOL, &m_aTypePolygon[nCntType].bBillboard, "BILLBOARD:");
						RNLib::File()->Scan(CFile::SCAN::BOOL, &m_aTypePolygon[nCntType].bGravity, "GRAVITY:");

						if (RNLib::File()->CheckIdentifierPartial("SCALING")) {
							CEff3D_Polygon::Scaling* pScaling = new CEff3D_Polygon::Scaling;
							if (RNLib::File()->CheckIdentifier("SCALING_START{"))
								m_aTypePolygon[nCntType].pScalingStart = pScaling;
							else
								m_aTypePolygon[nCntType].pScalingEnd = pScaling;

							while (RNLib::File()->SearchLoop("}")) {
								RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].pScalingStart->nTime, "TIME:");
								RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_aTypePolygon[nCntType].pScalingStart->fScaleXStart, "SCALE_X_START:");
								RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_aTypePolygon[nCntType].pScalingStart->fScaleXEnd, "SCALE_X_END:");
								RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_aTypePolygon[nCntType].pScalingStart->fScaleYStart, "SCALE_Y_START:");
								RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_aTypePolygon[nCntType].pScalingStart->fScaleYEnd, "SCALE_Y_END:");
								RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].pScalingStart->ease, "EASE:");
							}
						}
						else if (RNLib::File()->CheckIdentifier("FADEOUT{")) {
							m_aTypePolygon[nCntType].pFadeOut = new CEff3D_Polygon::FadeOut;

							while (RNLib::File()->SearchLoop("}")) {
								RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].pFadeOut->nTime, "TIME:");
								RNLib::File()->Scan(CFile::SCAN::INT, &m_aTypePolygon[nCntType].pFadeOut->ease, "EASE:");
							}
						}
					}
				}
			}
		}
	}

	RNLib::File()->CloseFile();
}

//========================================
// 生成処理(ポリゴン)
// Author:RIKU NISHIMURA
//========================================
CEff3D_Polygon* CEff3DMng::Create_Polygon(CEff3D::POLYGON_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CEff3D::POWER power, Color col) {
	CEff3D_Polygon* pEff = new CEff3D_Polygon;

	// メモリが確保出来た時、
	if (pEff != NULL) {
		pEff->Init();
		pEff->SetType(type);
		pEff->SetLife(m_aTypePolygon[(int)type].nLife);
		pEff->SetPos(pos);
		pEff->SetRot(rot);
		pEff->SetCol(col);
		pEff->SetMoveForce(c_aPowerMoveForce[(int)power] * (MOVEFORCE_RATE_MIN + MOVEFORCE_RATE_ADD * fRand()));
	}

	return pEff;
}

//========================================
// 生成処理(欠片)
// Author:RIKU NISHIMURA
//========================================
CEff3D_Fragment* CEff3DMng::Create_Fragment(CEff3D::FRAGMENT_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, CEff3D::POWER power, Color col, int nTexIdx) {
	CEff3D_Fragment* pEff = new CEff3D_Fragment;

	// メモリが確保出来た時、
	if (pEff != NULL) {
		float fAngle  = -D3DX_PI + (fRand() * D3DX_PI * 2);
		float fMoveXZ = c_aPowerMoveForce[(int)power] * (MOVEFORCE_RATE_MIN + MOVEFORCE_RATE_ADD * fRand()) * FRAGMENT_MOVE_XZ_RATE;
		float fMoveY  = c_aPowerMoveForce[(int)power] * (MOVEFORCE_RATE_MIN + MOVEFORCE_RATE_ADD * fRand()) * FRAGMENT_MOVE_Y_RATE;
		D3DXVECTOR3 move;
		move.x = sinf(fAngle) * fMoveXZ;
		move.z = cosf(fAngle) * fMoveXZ;
		move.y = fMoveY;

		pEff->Init();
		pEff->SetLife(c_aPowerLife[(int)power]);
		pEff->SetModelIdx(CEff3D_Fragment::GetTypeModel(type));
		pEff->SetPos(pos);
		pEff->SetRot(rot);
		pEff->SetCol(col);
		pEff->SetTex(nTexIdx);
		if (type == CEff3D::FRAGMENT_TYPE::NONE)
			pEff->SetScale(1.0f);
		else
			pEff->SetScale(SCALE_MIN + (SCALE_ADD * fRand()));
		pEff->SetMove(move);
		pEff->SetSpin(vecRand() * c_aPowerSpin[(int)power]);
	}

	return pEff;
}