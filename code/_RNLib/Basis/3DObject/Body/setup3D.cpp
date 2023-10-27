//========================================
// 
// �Z�b�g�A�b�v3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNLib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�Z�b�g�A�b�v3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CSetUp3D::CSetUp3D() {

	m_datas = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CSetUp3D::~CSetUp3D() {

	// �f�[�^�̉��
	RNLib::Memory().Release<CData>(&m_datas);
}

//========================================
// �ǂݍ��ݏ���
//========================================
short CSetUp3D::Load(const char* loadPath, short idx) {

	const unsigned short numOld(m_num);

	if (CRegist::Load(loadPath, idx))
	{// �ǂݍ��ݐ���
		// �f�[�^�̃������Ċm��
		RNLib::Memory().ReAlloc(&m_datas, numOld, m_num);

		// �f�[�^�̔j��(�ԍ��w��̏ꍇ)
		if (idx != NONEDATA)
			m_datas[idx].Release();

		// �t�@�C�����J��
		if (RNLib::File().OpenLoadFile(loadPath)) {
			while (RNLib::File().SearchLoop("END")) {
				if (RNLib::File().CheckIdentifier("boneDataSum{")) {
					BoneData*& boneDatas = m_datas[idx].m_boneDatas;
					
					// �{�[���f�[�^�Q�����
					RNLib::Memory().Release(&boneDatas);

					// �{�[���f�[�^���ǂݍ���
					RNLib::File().Scan(CFile::SCAN::INT, &m_datas[idx].m_boneDataNum);

					// �{�[���f�[�^�Q�̃������m��
					RNLib::Memory().Alloc(&boneDatas, m_datas[idx].m_boneDataNum);

					// �{�[���f�[�^�Q�̓ǂݍ���
					int cntBoneData(0);
					while (RNLib::File().SearchLoop("}")) {
						if (RNLib::File().CheckIdentifier("boneData{")) {

							// �G���[���b�Z�[�W
							if (cntBoneData >= m_datas[idx].m_boneDataNum) {
								RNLib::Window().Message_ERROR(CreateText("�{�[���f�[�^�̐����w�萔���I�[�o�[���Ă��܂��B\n%s", loadPath));
								break;
							}

							// �{�[���f�[�^������
							BoneData& boneData(boneDatas[cntBoneData]);
							boneData = {};

							// ���i���̓ǂݍ��݂��J�n
							while (RNLib::File().SearchLoop("}")) {
								RNLib::File().Scan(CFile::SCAN::INT, &boneData.idx, "idx");
								RNLib::File().Scan(CFile::SCAN::MODELIDX, &boneData.modelIdx, "modelIdx");
								RNLib::File().Scan(CFile::SCAN::INT, &boneData.parentIdx, "parentIdx");
								RNLib::File().Scan(CFile::SCAN::POS3D, &boneData.relativePos, "relativePos");
								RNLib::File().Scan(CFile::SCAN::POS3D, &boneData.relativeRot, "relativeRot");
							}

							// �J�E���g�����Z
							cntBoneData++;
						}
					}// �{�[���f�[�^�Q�̓ǂݍ��ݏI���c

					// �G���[���b�Z�[�W
					if (cntBoneData < m_datas[idx].m_boneDataNum) {
						RNLib::Window().Message_ERROR(CreateText("�{�[���f�[�^�̐����w�萔�ɑ΂��ĕs�����Ă��܂��B\n%s", loadPath));
					}
					
					// �{�[���f�[�^1��1�̐e�ԍ����J�E���g�ɕϊ����Ă���
					for (int cntBoneData = 0; cntBoneData < m_datas[idx].m_boneDataNum; cntBoneData++) {
						BoneData& boneData(boneDatas[cntBoneData]);

						// �e��DATANONE�̎��A�܂�Ԃ�
						if (boneData.parentIdx == NONEDATA)
							continue;

						// �e�ԍ��ƈ�v�����{�[���f�[�^��e�Ƃ��A
						// �{�[���f�[�^�̐e�ԍ����J�E���g�ɕϊ�����
						int cntBoneData2;
						for (cntBoneData2 = 0; cntBoneData2 < m_datas[idx].m_boneDataNum; cntBoneData2++) {
							if (boneData.parentIdx == boneDatas[cntBoneData2].idx) {
								boneData.parentIdx = cntBoneData2;
								break;
							}
						}

						// �e��������Ȃ��������A�e�ԍ���DATANONE�ɂ���
						if (cntBoneData2 == m_datas[idx].m_boneDataNum)
							boneData.parentIdx = NONEDATA;
					}
				}
			}

			// �t�@�C�������
			RNLib::File().CloseFile();
		}
		else 
		{// �ǂݍ��ݎ��s
			// �G���[���b�Z�[�W
			RNLib::Window().Message_ERROR(CreateText("�Z�b�g�A�b�v3D�f�[�^�t�@�C�������݂��܂���B\n%s", loadPath));

			return NONEDATA;
		}
	}

	return idx;
}

//========================================
// �����o������
//========================================
void CSetUp3D::Save(const char* path, short idx) {

}

//========================================
// ���������w�萔�ɏ�����
//========================================
void CSetUp3D::InitMemory(const unsigned short& num) {
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
CSetUp3D::CData::CData() {

	m_boneDatas   = NULL;
	m_boneDataNum = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CSetUp3D::CData::~CData() {

	// �������
	Release();
}

//========================================
// �������
//========================================
void CSetUp3D::CData::Release(void) {

	RNLib::Memory().Release(&m_boneDatas);
}