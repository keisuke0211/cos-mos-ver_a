//========================================
// 
// モーション3Dの処理
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ motion3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// 静的メンバ定数宣言
//****************************************
// コマンドデータ
const CMotion3D::CmdData CMotion3D::CMD_DATA[] = {
	{ "MOVE"         ,5 },	// 移動
	{ "SPIN"         ,5 },	// 回転
	{ "STEP"         ,3 },	// 足踏
	{ "SCALE"        ,5 },	// 拡大縮小
	{ "STEP_REACTION",0 },	// 足踏反応
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMotion3Dクラスのメンバ関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// 終了処理
// Author:RIKU NISHIMURA
//========================================
void CMotion3D::Uninit(void) {
	CRegist::Uninit();	// 基底クラス終了処理

	for (int nCntData = 0; nCntData < m_num; nCntData++) {
		for (int nCntPF = 0; nCntPF < CModelSetUp::PLATFORM_MAX; nCntPF++) {
			for (int nCntParts = 0; nCntParts < m_pData[nCntData].pfData[nCntPF].nPartsNum; nCntParts++) {
				for (int nCntCmd = 0; nCntCmd < m_pData[nCntData].pfData[nCntPF].pPartsCmd[nCntParts].nCmdNum; nCntCmd++) {
					// コマンドの引数を破棄
					RNLib::Memory()->Release(&m_pData[nCntData].pfData[nCntPF].pPartsCmd[nCntParts].pCmd[nCntCmd].pData);
				}
				// コマンド情報を破棄
				RNLib::Memory()->Release(&m_pData[nCntData].pfData[nCntPF].pPartsCmd[nCntParts].pCmd);
			}

			// 部品のコマンド情報を破棄
			RNLib::Memory()->Release(&m_pData[nCntData].pfData[nCntPF].pPartsCmd);
		}
	}

	// データの破棄
	RNLib::Memory()->Release(&m_pData);
}

//========================================
// 読み込み処理
// Author:RIKU NISHIMURA
//========================================
int CMotion3D::Load(const char *pLoadPath, short nIdx) {
	int nNumOld = m_num;	// 過去の総数

	if (!CRegist::Load(pLoadPath, &nIdx)) {
		return nIdx;
	}
	else {
		{// データのメモリ再確保
			Data* pNew = new Data[m_num];
			int nCopySize = m_num < nNumOld ? m_num : nNumOld;
			if (nCopySize > 0) {
				memcpy(pNew, m_pData, sizeof(Data) * nCopySize);
				delete m_pData;
			}
			m_pData = pNew;
		}

		// データ初期化
		m_pData[nIdx] = {};

		if (!RNLib::File()->OpenLoadFile(pLoadPath))
		{// 種類毎の情報のデータファイルが開けなかった場合、処理を終了する
			assert(false);
			return 0;
		}

		// 読み込みループ
		while (RNLib::File()->SearchLoop("END")) {
			if (false) {}
			else if (RNLib::File()->CheckIdentifier(/* ループ時間   */"LOOP_TIME:")) { RNLib::File()->Scan(CFile::SCAN::INT, &m_pData[nIdx].nLoopTime); }
			else if (RNLib::File()->CheckIdentifier(/* ループフラグ */"LOOP:"))      { RNLib::File()->Scan(CFile::SCAN::BOOL, &m_pData[nIdx].bLoop); }
			else if (RNLib::File()->CheckIdentifier(/* 構成毎データ */"PLATFORM_DATA{")) {
				
				CModelSetUp::PLATFORM pf; {
					char aPlatformName[TXT_MAX];
					RNLib::File()->Scan(CFile::SCAN::STRING, aPlatformName);
					pf = RNLib::ModelSetUp()->GetPlatformFromName(aPlatformName);
				}
				RNLib::File()->Scan(CFile::SCAN::INT,&m_pData[nIdx].pfData[pf].nPartsNum);

				// 部品毎のコマンド情報のメモリ確保
				m_pData[nIdx].pfData[pf].pPartsCmd = NULL;
				m_pData[nIdx].pfData[pf].pPartsCmd = new PartsCmd[m_pData[nIdx].pfData[pf].nPartsNum];

				// 部品毎のコマンド情報の読み込み
				int nCntParts = 0;
				while (RNLib::File()->SearchLoop("}")) {
					if (false) {}
					else if (RNLib::File()->CheckIdentifier("PARTS{")) {
						// 部品毎のコマンド情報のポインタ
						m_pData[nIdx].pfData[pf].pPartsCmd[nCntParts] = {};
						PartsCmd* pPartsMotion = &m_pData[nIdx].pfData[pf].pPartsCmd[nCntParts];

						RNLib::File()->Scan(CFile::SCAN::INT,&pPartsMotion->nCmdNum);	// コマンド数取得

						// コマンド情報のメモリ確保
						if (pPartsMotion->nCmdNum > 0) {
							pPartsMotion->pCmd = new Cmd[pPartsMotion->nCmdNum];

							// コマンドのカウント
							int nCntCmd = 0;

							// 部品毎のコマンド情報の読み込みを開始
							while (RNLib::File()->SearchLoop("}")) {
								if (false) {}
								else if (RNLib::File()->CheckIdentifier("TIME")) {
									// コマンド開始時間
									RNLib::File()->Scan(CFile::SCAN::INT,&pPartsMotion->pCmd[nCntCmd].nTime);

									// コマンド番号
									int nCmd = 0;
									// コマンドラベルを読み取る
									char aCommandLabel[TXT_MAX];
									RNLib::File()->Scan(CFile::SCAN::STRING, aCommandLabel);

									// 総当たりでラベルの判定を行う
									for (int nCntLabel = 0; nCntLabel < CMD_LABEL_MAX; nCntLabel++) {
										if (!strcmp(aCommandLabel, CMD_DATA[nCntLabel].pLabelName))
										{// 文字列がラベル名と一致している時、
											// ラベルを設定
											pPartsMotion->pCmd[nCntCmd].command = (CMD_LABEL)nCntLabel;

											// 移動 or 回転フラグを立てる
											pPartsMotion->bMove |= (pPartsMotion->pCmd[nCntCmd].command == CMD_LABEL_MOVE);
											pPartsMotion->bSpin |= (pPartsMotion->pCmd[nCntCmd].command == CMD_LABEL_SPIN);

											// コマンド番号を指定
											nCmd = nCntLabel;
											break;
										}
									}

									// 引数情報のメモリを確保
									pPartsMotion->pCmd[nCntCmd].pData = NULL;
									pPartsMotion->pCmd[nCntCmd].pData = new float[CMD_DATA[nCmd].nDataNum];

									// 引数の読み込みを引数の数分行う
									for (int nCntData = 0; nCntData < CMD_DATA[nCmd].nDataNum; nCntData++) {
										RNLib::File()->Scan(CFile::SCAN::FLOAT, &pPartsMotion->pCmd[nCntCmd].pData[nCntData]);
									}

									// コマンドのカウントを加算
									nCntCmd++;
									assert(nCntCmd <= pPartsMotion->nCmdNum);
								}
							}
						}
						else 
						{// 部品数が0以下だった時、
							pPartsMotion->pCmd = NULL;
							RNLib::File()->NewLine();	// }
						}

						// 部品のカウントを加算
						nCntParts++;
						assert(nCntParts <= m_pData[nIdx].pfData[pf].nPartsNum);
					}
				}
			}
		}

		// データファイルを閉じる
		RNLib::File()->CloseFile();
	}

	// モーション3D番号を返す
	return nIdx;
}

//========================================
// 書き込み処理
// Author:RIKU NISHIMURA
//========================================
void CMotion3D::Save(const char *pPath, const int nIdx) {
	if (RNLib::File()->OpenSaveFile(pPath))
	{// ファイルが開けた場合、
		FILE* pFile = RNLib::File()->GetFile();
		fprintf(pFile, "LOOP_TIME: %d\n", m_pData[nIdx].nLoopTime);
		fprintf(pFile, "LOOP: %d\n", (int)m_pData[nIdx].bLoop);

		// モデル構成毎のモーション情報を書き込み
		for (int nCntPF = 0; nCntPF < CModelSetUp::PLATFORM_MAX; nCntPF++) {
			fprintf(pFile, "PLATFORM_DATA{ %s %d\n",
				RNLib::ModelSetUp()->GetPlatformName((CModelSetUp::PLATFORM)nCntPF),
				m_pData[nIdx].pfData[nCntPF].nPartsNum);

			for (int nCntParts = 0; nCntParts < m_pData[nIdx].pfData[nCntPF].nPartsNum; nCntParts++) {
				// 部品3D毎のコマンド情報のポインタ
				PartsCmd* pPartsMotion = &m_pData[nIdx].pfData[nCntPF].pPartsCmd[nCntParts];

				fprintf(pFile, "	PARTS{ %d\n", pPartsMotion->nCmdNum);
				for (int nCntCmd = 0; nCntCmd < pPartsMotion->nCmdNum; nCntCmd++) {
					Cmd cmd = pPartsMotion->pCmd[nCntCmd];
					fprintf(pFile, "		TIME %d ", cmd.nTime);
					switch (cmd.command) {
					case CMD_LABEL_MOVE:
						fprintf(pFile, "MOVE %f %f %f %d %d\n", cmd.pData[0], cmd.pData[1], cmd.pData[2], (int)cmd.pData[3], (int)cmd.pData[4]);
						break;
					case CMD_LABEL_SPIN:
						fprintf(pFile, "SPIN %f %f %f %d %d\n", cmd.pData[0], cmd.pData[1], cmd.pData[2], (int)cmd.pData[3], (int)cmd.pData[4]);
						break;
					case CMD_LABEL_STEP:
						fprintf(pFile, "STEP %d %d %d\n", (int)cmd.pData[0], (int)cmd.pData[1], (int)cmd.pData[2]);
						break;
					case CMD_LABEL_SCALE:
						fprintf(pFile, "SCALE %f %f %f %d %d\n", cmd.pData[0], cmd.pData[1], cmd.pData[2], (int)cmd.pData[3], (int)cmd.pData[4]);
						break;
					case CMD_LABEL_STEP_REACTION:
						fprintf(pFile, "STEP_REACTION\n");
						break;
					default:
						assert(false);
						break;
					}
				}
				fprintf(pFile, "	}\n");
			}
			fprintf(pFile, "}\n");
		}

		fprintf(pFile, "END\n");

		// ファイルを閉じる
		RNLib::File()->CloseFile();
	}
}

//========================================
// メモリを指定数に初期化
// Author:RIKU NISHIMURA
//========================================
void CMotion3D::InitMemory(const int nNum) {
	Uninit();	// 終了処理
	CRegist::InitMemory(nNum);	// 基底クラスのメモリ初期化処理

	// データのメモリ確保
	if (m_pData != NULL) {
		delete m_pData;
	}
	m_pData = new Data[nNum];

	// 確保した分のデータを全て初期化する
	for (int nCntMotion = 0; nCntMotion < nNum; nCntMotion++) {
		m_pData[nCntMotion] = {};
	}
}