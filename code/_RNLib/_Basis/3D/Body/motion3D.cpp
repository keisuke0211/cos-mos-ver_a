//========================================
// 
// ���[�V����3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ motion3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// �ÓI�����o�萔�錾
//****************************************
// �R�}���h�f�[�^
const CMotion3D::CmdData CMotion3D::CMD_DATA[] = {
	{ "MOVE"         ,5 },	// �ړ�
	{ "SPIN"         ,5 },	// ��]
	{ "STEP"         ,3 },	// ����
	{ "SCALE"        ,5 },	// �g��k��
	{ "STEP_REACTION",0 },	// ��������
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CMotion3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CMotion3D::Uninit(void) {
	CRegist::Uninit();	// ���N���X�I������

	for (int nCntData = 0; nCntData < m_num; nCntData++) {
		for (int nCntPF = 0; nCntPF < CModelSetUp::PLATFORM_MAX; nCntPF++) {
			for (int nCntParts = 0; nCntParts < m_pData[nCntData].pfData[nCntPF].nPartsNum; nCntParts++) {
				for (int nCntCmd = 0; nCntCmd < m_pData[nCntData].pfData[nCntPF].pPartsCmd[nCntParts].nCmdNum; nCntCmd++) {
					// �R�}���h�̈�����j��
					RNLib::Memory()->Release(&m_pData[nCntData].pfData[nCntPF].pPartsCmd[nCntParts].pCmd[nCntCmd].pData);
				}
				// �R�}���h����j��
				RNLib::Memory()->Release(&m_pData[nCntData].pfData[nCntPF].pPartsCmd[nCntParts].pCmd);
			}

			// ���i�̃R�}���h����j��
			RNLib::Memory()->Release(&m_pData[nCntData].pfData[nCntPF].pPartsCmd);
		}
	}

	// �f�[�^�̔j��
	RNLib::Memory()->Release(&m_pData);
}

//========================================
// �ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
int CMotion3D::Load(const char *pLoadPath, short nIdx) {
	int nNumOld = m_num;	// �ߋ��̑���

	if (!CRegist::Load(pLoadPath, &nIdx)) {
		return nIdx;
	}
	else {
		{// �f�[�^�̃������Ċm��
			Data* pNew = new Data[m_num];
			int nCopySize = m_num < nNumOld ? m_num : nNumOld;
			if (nCopySize > 0) {
				memcpy(pNew, m_pData, sizeof(Data) * nCopySize);
				delete m_pData;
			}
			m_pData = pNew;
		}

		// �f�[�^������
		m_pData[nIdx] = {};

		if (!RNLib::File()->OpenLoadFile(pLoadPath))
		{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A�������I������
			assert(false);
			return 0;
		}

		// �ǂݍ��݃��[�v
		while (RNLib::File()->SearchLoop("END")) {
			if (false) {}
			else if (RNLib::File()->CheckIdentifier(/* ���[�v����   */"LOOP_TIME:")) { RNLib::File()->Scan(CFile::SCAN::INT, &m_pData[nIdx].nLoopTime); }
			else if (RNLib::File()->CheckIdentifier(/* ���[�v�t���O */"LOOP:"))      { RNLib::File()->Scan(CFile::SCAN::BOOL, &m_pData[nIdx].bLoop); }
			else if (RNLib::File()->CheckIdentifier(/* �\�����f�[�^ */"PLATFORM_DATA{")) {
				
				CModelSetUp::PLATFORM pf; {
					char aPlatformName[TXT_MAX];
					RNLib::File()->Scan(CFile::SCAN::STRING, aPlatformName);
					pf = RNLib::ModelSetUp()->GetPlatformFromName(aPlatformName);
				}
				RNLib::File()->Scan(CFile::SCAN::INT,&m_pData[nIdx].pfData[pf].nPartsNum);

				// ���i���̃R�}���h���̃������m��
				m_pData[nIdx].pfData[pf].pPartsCmd = NULL;
				m_pData[nIdx].pfData[pf].pPartsCmd = new PartsCmd[m_pData[nIdx].pfData[pf].nPartsNum];

				// ���i���̃R�}���h���̓ǂݍ���
				int nCntParts = 0;
				while (RNLib::File()->SearchLoop("}")) {
					if (false) {}
					else if (RNLib::File()->CheckIdentifier("PARTS{")) {
						// ���i���̃R�}���h���̃|�C���^
						m_pData[nIdx].pfData[pf].pPartsCmd[nCntParts] = {};
						PartsCmd* pPartsMotion = &m_pData[nIdx].pfData[pf].pPartsCmd[nCntParts];

						RNLib::File()->Scan(CFile::SCAN::INT,&pPartsMotion->nCmdNum);	// �R�}���h���擾

						// �R�}���h���̃������m��
						if (pPartsMotion->nCmdNum > 0) {
							pPartsMotion->pCmd = new Cmd[pPartsMotion->nCmdNum];

							// �R�}���h�̃J�E���g
							int nCntCmd = 0;

							// ���i���̃R�}���h���̓ǂݍ��݂��J�n
							while (RNLib::File()->SearchLoop("}")) {
								if (false) {}
								else if (RNLib::File()->CheckIdentifier("TIME")) {
									// �R�}���h�J�n����
									RNLib::File()->Scan(CFile::SCAN::INT,&pPartsMotion->pCmd[nCntCmd].nTime);

									// �R�}���h�ԍ�
									int nCmd = 0;
									// �R�}���h���x����ǂݎ��
									char aCommandLabel[TXT_MAX];
									RNLib::File()->Scan(CFile::SCAN::STRING, aCommandLabel);

									// ��������Ń��x���̔�����s��
									for (int nCntLabel = 0; nCntLabel < CMD_LABEL_MAX; nCntLabel++) {
										if (!strcmp(aCommandLabel, CMD_DATA[nCntLabel].pLabelName))
										{// �����񂪃��x�����ƈ�v���Ă��鎞�A
											// ���x����ݒ�
											pPartsMotion->pCmd[nCntCmd].command = (CMD_LABEL)nCntLabel;

											// �ړ� or ��]�t���O�𗧂Ă�
											pPartsMotion->bMove |= (pPartsMotion->pCmd[nCntCmd].command == CMD_LABEL_MOVE);
											pPartsMotion->bSpin |= (pPartsMotion->pCmd[nCntCmd].command == CMD_LABEL_SPIN);

											// �R�}���h�ԍ����w��
											nCmd = nCntLabel;
											break;
										}
									}

									// �������̃��������m��
									pPartsMotion->pCmd[nCntCmd].pData = NULL;
									pPartsMotion->pCmd[nCntCmd].pData = new float[CMD_DATA[nCmd].nDataNum];

									// �����̓ǂݍ��݂������̐����s��
									for (int nCntData = 0; nCntData < CMD_DATA[nCmd].nDataNum; nCntData++) {
										RNLib::File()->Scan(CFile::SCAN::FLOAT, &pPartsMotion->pCmd[nCntCmd].pData[nCntData]);
									}

									// �R�}���h�̃J�E���g�����Z
									nCntCmd++;
									assert(nCntCmd <= pPartsMotion->nCmdNum);
								}
							}
						}
						else 
						{// ���i����0�ȉ����������A
							pPartsMotion->pCmd = NULL;
							RNLib::File()->NewLine();	// }
						}

						// ���i�̃J�E���g�����Z
						nCntParts++;
						assert(nCntParts <= m_pData[nIdx].pfData[pf].nPartsNum);
					}
				}
			}
		}

		// �f�[�^�t�@�C�������
		RNLib::File()->CloseFile();
	}

	// ���[�V����3D�ԍ���Ԃ�
	return nIdx;
}

//========================================
// �������ݏ���
// Author:RIKU NISHIMURA
//========================================
void CMotion3D::Save(const char *pPath, const int nIdx) {
	if (RNLib::File()->OpenSaveFile(pPath))
	{// �t�@�C�����J�����ꍇ�A
		FILE* pFile = RNLib::File()->GetFile();
		fprintf(pFile, "LOOP_TIME: %d\n", m_pData[nIdx].nLoopTime);
		fprintf(pFile, "LOOP: %d\n", (int)m_pData[nIdx].bLoop);

		// ���f���\�����̃��[�V����������������
		for (int nCntPF = 0; nCntPF < CModelSetUp::PLATFORM_MAX; nCntPF++) {
			fprintf(pFile, "PLATFORM_DATA{ %s %d\n",
				RNLib::ModelSetUp()->GetPlatformName((CModelSetUp::PLATFORM)nCntPF),
				m_pData[nIdx].pfData[nCntPF].nPartsNum);

			for (int nCntParts = 0; nCntParts < m_pData[nIdx].pfData[nCntPF].nPartsNum; nCntParts++) {
				// ���i3D���̃R�}���h���̃|�C���^
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

		// �t�@�C�������
		RNLib::File()->CloseFile();
	}
}

//========================================
// ���������w�萔�ɏ�����
// Author:RIKU NISHIMURA
//========================================
void CMotion3D::InitMemory(const int nNum) {
	Uninit();	// �I������
	CRegist::InitMemory(nNum);	// ���N���X�̃���������������

	// �f�[�^�̃������m��
	if (m_pData != NULL) {
		delete m_pData;
	}
	m_pData = new Data[nNum];

	// �m�ۂ������̃f�[�^��S�ď���������
	for (int nCntMotion = 0; nCntMotion < nNum; nCntMotion++) {
		m_pData[nCntMotion] = {};
	}
}