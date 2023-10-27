//========================================
// 
// ���[�V����3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]���[�V����3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//****************************************
// �萔��`
//****************************************
const UShort CMotion3D::COMMAND_DATA_NUM[] = {
	5,	// �ړ� ( �ڕW�ʒuX,Y,Z,�ړ�����,��Ԕԍ� )
	5,	// ��] ( �ڕW����X,Y,Z,��]����,��Ԕԍ� )
	5,	// �g�k ( �g��{��X,Y,Z.�g�k����,��Ԕԍ� )
	0,	// ����
};

//========================================
// �R���X�g���N�^
//========================================
CMotion3D::CMotion3D() {

	m_datas = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CMotion3D::~CMotion3D() {

	// �f�[�^�����
	RNLib::Memory().Release(&m_datas);
}

//========================================
// �ǂݍ��ݏ���
//========================================
short CMotion3D::Load(const char* loadPath, short idx) {

	const UShort numOld = m_num;
	const short  idxOld = idx;

	if (CRegist::Load(loadPath, idx))
	{// �ǂݍ��ݐ���
		// �f�[�^�̃������Ċm��
		RNLib::Memory().ReAlloc(&m_datas, numOld, m_num);

		// �f�[�^�̔j��(�ԍ��w��̏ꍇ)
		if (idxOld != NONEDATA)
			m_datas[idx].Release();

		// �t�@�C�����J��
		if (!RNLib::File().OpenLoadFile(loadPath)) {
			while (RNLib::File().SearchLoop("END")) {
				RNLib::File().Scan(CFile::SCAN::INT, &m_datas[idx].loopTime, "loopTime");
				RNLib::File().Scan(CFile::SCAN::BOOL, &m_datas[idx].isLoop, "isLoop");

				// �{�[�����[�V�����f�[�^��ǂݍ���
				if (RNLib::File().CheckIdentifier("boneMotionDatas{")) {

					// �{�[���̐���ǂݍ��݁A
					// �{�[�����[�V�����f�[�^�̃������m��
					RNLib::File().Scan(CFile::SCAN::INT, &m_datas[idx].boneNum);
					RNLib::Memory().Alloc<BoneMotionData>(&m_datas[idx].boneMotionDatas, m_datas[idx].boneNum);

					int cntBone = 0;
					while (RNLib::File().SearchLoop("}")) {
						if (RNLib::File().CheckIdentifier("boneMotionData{")) {

							// �G���[���b�Z�[�W
							if (cntBone >= m_datas[idx].boneNum) {
								RNLib::Window().Message_ERROR(CreateText("�{�[�����[�V�����f�[�^�̐����{�[�������I�[�o�[���Ă��܂��B\n%s", loadPath));
								break;
							}

							// �{�[�����[�V�����f�[�^������
							BoneMotionData& boneMotionData = m_datas[idx].boneMotionDatas[cntBone];
							boneMotionData = {};

							// �R�}���h���ǂݍ���
							RNLib::File().Scan(CFile::SCAN::INT, &boneMotionData.commandDataNum);

							// �R�}���h����0���z���Ă��鎞�A
							if (boneMotionData.commandDataNum > 0) {
								boneMotionData.commandDatas = new CommandData[boneMotionData.commandDataNum];

								// �R�}���h�̃J�E���g
								int cntCommand = 0;

								// �R�}���h�̓ǂݍ��݂��J�n
								while (RNLib::File().SearchLoop("}")) {
									if (RNLib::File().CheckIdentifier("time")) {

										// �G���[���b�Z�[�W
										if (cntCommand >= boneMotionData.commandDataNum) {
											RNLib::Window().Message_ERROR(CreateText("�R�}���h�f�[�^�̐����w�萔���I�[�o�[���Ă��܂��B\n%s", loadPath));
											break;
										}

										// �R�}���h�J�n���ԓǂݍ���
										RNLib::File().Scan(CFile::SCAN::INT, &boneMotionData.commandDatas[cntCommand].time);

										// �R�}���h��ǂݎ��
										COMMAND command = COMMAND::NONE;
										RNLib::File().Scan(CFile::SCAN::INT, &command);
										
										// �ړ�/��]/�g�k�t���O�𗧂Ă�
										if (boneMotionData.commandDatas[cntCommand].command == COMMAND::MOVE)
											boneMotionData.isMove = true;
										else if (boneMotionData.commandDatas[cntCommand].command == COMMAND::SPIN)
											boneMotionData.isSpin = true;
										else if (boneMotionData.commandDatas[cntCommand].command == COMMAND::SCALING)
											boneMotionData.isScale = true;

										// �����̃��������m��
										boneMotionData.commandDatas[cntCommand].datas = NULL;
										boneMotionData.commandDatas[cntCommand].datas = new float[COMMAND_DATA_NUM[(int)command]];

										// �����̓ǂݍ���
										for (int cntData = 0; cntData < COMMAND_DATA_NUM[(int)command]; cntData++)
											RNLib::File().Scan(CFile::SCAN::FLOAT, &boneMotionData.commandDatas[cntCommand].datas[cntData]);

										// �R�}���h�̃J�E���g
										cntCommand++;	
									}
								}

								// �G���[���b�Z�[�W
								if (cntCommand < boneMotionData.commandDataNum) {
									RNLib::Window().Message_ERROR(CreateText("�R�}���h�f�[�^�̐����w�萔�ɑ΂��ĕs�����Ă��܂��B\n%s", loadPath));
								}
							}
							else
							{// �R�}���h����0�ȉ����������A
								boneMotionData.commandDatas = NULL;
								RNLib::File().NewLine();	// }
							}

							// �{�[���̃J�E���g
							cntBone++;
						}
					}
				}
			}

			// �t�@�C�������
			RNLib::File().CloseFile();
		}
		else
		{// �ǂݍ��ݎ��s
			// �G���[���b�Z�[�W
			RNLib::Window().Message_ERROR(CreateText("���[�V�����f�[�^�t�@�C�������݂��܂���B\n%s", loadPath));

			return NONEDATA;
		}
	}

	return idx;
}

//========================================
// �����o������
//========================================
void CMotion3D::Save(const char* savePath, const short& idx) {

	// �t�@�C�����J���̂Ɏ��s�������A�������I��
	if (!RNLib::File().OpenSaveFile(savePath))
		return;

	// �t�@�C���|�C���^���擾
	FILE* file = RNLib::File().GetFile();

	fprintf(file, "loopTime: %d\n", m_datas[idx].loopTime);
	fprintf(file, "loop: %d\n", (int)m_datas[idx].isLoop);

	// �{�[�����[�V�����f�[�^�̏����o��
	for (int cntBone = 0; cntBone < m_datas[idx].boneNum; cntBone++) {
		BoneMotionData& boneMotionData = m_datas[idx].boneMotionDatas[cntBone];

		fprintf(file, "boneMotionDatas{ %d\n", boneMotionData.commandDataNum);

		// �R�}���h�f�[�^�����o��
		for (int cntCmd = 0; cntCmd < boneMotionData.commandDataNum; cntCmd++) {
			CommandData& cmd = boneMotionData.commandDatas[cntCmd];

			fprintf(file, "		time %d ", cmd.time);
			switch (cmd.command) {
			case COMMAND::MOVE: {
				fprintf(file, "%d %f %f %f %d %d\n",
					(int)COMMAND::MOVE, cmd.datas[0], cmd.datas[1], cmd.datas[2], (int)cmd.datas[3], (int)cmd.datas[4]);
			}break;
			case COMMAND::SPIN: {
				fprintf(file, "%d %f %f %f %d %d\n",
					(int)COMMAND::SPIN, cmd.datas[0], cmd.datas[1], cmd.datas[2], (int)cmd.datas[3], (int)cmd.datas[4]);
			}break;
			case COMMAND::SCALING: {
				fprintf(file, "%d %f %f %f %d %d\n",
					(int)COMMAND::SCALING, cmd.datas[0], cmd.datas[1], cmd.datas[2], (int)cmd.datas[3], (int)cmd.datas[4]);
			}break;
			case COMMAND::STEP: {
				fprintf(file, "%d %d\n",
					(int)COMMAND::STEP, (int)cmd.datas[0]);
			}break;
			default: {
				// �G���[���b�Z�[�W
				RNLib::Window().Message_ERROR(CreateText("�R�}���h���w�肳��Ă��܂���B\n%s", savePath));
			}break;
			}
		}
		fprintf(file, "}\n");
	}

	fprintf(file, "END\n");

	// �t�@�C�������
	RNLib::File().CloseFile();
}

//========================================
// ���������w�萔�ɏ�����
//========================================
void CMotion3D::InitMemory(const UShort& num) {
	CRegist::InitMemory(num);

	// �f�[�^�̃������m��
	RNLib::Memory().Alloc(&m_datas, num);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�f�[�^�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CMotion3D::CData::CData() {

	loopTime        = 0;
	isLoop          = false;
	boneNum         = 0;
	boneMotionDatas = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CMotion3D::CData::~CData() {

	// �������
	Release();
}

//========================================
// �������
//========================================
void CMotion3D::CData::Release(void) {

	// �{�[���R�}���h�f�[�^�����
	for (int cntParts = 0; cntParts < boneNum; cntParts++) {
		for (int cntCmd = 0; cntCmd < boneMotionDatas[cntParts].commandDataNum; cntCmd++) {
			RNLib::Memory().Release(&boneMotionDatas[cntParts].commandDatas[cntCmd].datas);
		}
		RNLib::Memory().Release(&boneMotionDatas[cntParts].commandDatas);
	}
	RNLib::Memory().Release(&boneMotionDatas);
}
