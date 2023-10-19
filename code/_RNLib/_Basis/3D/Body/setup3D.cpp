//========================================
// 
// �Z�b�g�A�b�v3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �Z�b�g�A�b�v3D�N���X�̃����o�֐�
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
	RNLib::Memory()->Release<CData>(&m_datas);
}

//========================================
// �ǂݍ��ݏ���
//========================================
int CSetUp3D::Load(const char* loadPath, short idx) {

	unsigned short numOld  = m_num;

	if (CRegist::Load(loadPath, idx))
	{// �ǂݍ��ݐ���
		// �f�[�^�̃������Ċm��
		RNLib::Memory()->ReAlloc<CData>(&m_datas, numOld, m_num);

		// �f�[�^�̔j��(�ԍ��w��̏ꍇ)
		if (idx != DATANONE)
			m_datas[idx].Release();

		// �t�@�C�����J��
		if (RNLib::File()->OpenLoadFile(loadPath)) {
			while (RNLib::File()->SearchLoop("END")) {
				if (RNLib::File()->CheckIdentifier("boneDataSum{")) {
					BoneDataSum& boneDataSum = m_datas[idx].m_boneDataSum;
					BoneData*&   boneDatas   = boneDataSum.boneDatas;
					
					// �{�[���f�[�^�Q�����
					RNLib::Memory()->Release<BoneData>(&boneDatas);

					// �{�[���f�[�^���ǂݍ���
					RNLib::File()->Scan(CFile::SCAN::INT, &boneDataSum.boneDataNum);

					// �{�[���f�[�^�Q�̃������m��
					RNLib::Memory()->Alloc<BoneData>(&boneDatas, boneDataSum.boneDataNum);

					// �{�[���f�[�^�Q�̓ǂݍ���
					int cntBoneData = 0;
					while (RNLib::File()->SearchLoop("}")) {
						if (RNLib::File()->CheckIdentifier("boneData{")) {

							// �{�[���f�[�^������
							BoneData& boneData = boneDatas[cntBoneData];
							boneData = {};

							// ���i���̓ǂݍ��݂��J�n
							while (RNLib::File()->SearchLoop("}")) {
								RNLib::File()->Scan(CFile::SCAN::INT, &boneData.idx, "idx");
								RNLib::File()->Scan(CFile::SCAN::MODELIDX, &boneData.modelIdx, "modelIdx");
								RNLib::File()->Scan(CFile::SCAN::INT, &boneData.parentIdx, "parentIdx");
								RNLib::File()->Scan(CFile::SCAN::POS3D, &boneData.relativePos, "relativePos");
								RNLib::File()->Scan(CFile::SCAN::POS3D, &boneData.relativeRot, "relativeRot");
							}

							// �J�E���g�����Z
							cntBoneData++;
							assert(cntBoneData <= boneDataSum.boneDataNum);
						}
					}// �{�[���f�[�^�Q�̓ǂݍ��ݏI���c
					
					// �{�[���f�[�^1��1�̐e�ԍ����J�E���g�ɕϊ����Ă���
					for (int cntBoneData = 0; cntBoneData < boneDataSum.boneDataNum; cntBoneData++) {
						BoneData& boneData = boneDatas[cntBoneData];

						// �e��DATANONE�̎��A�܂�Ԃ�
						if (boneData.parentIdx == DATANONE)
							continue;

						// �e�ԍ��ƈ�v�����{�[���f�[�^��e�Ƃ��A
						// �{�[���f�[�^�̐e�ԍ����J�E���g�ɕϊ�����
						int cntBoneData2;
						for (cntBoneData2 = 0; cntBoneData2 < boneDataSum.boneDataNum; cntBoneData2++) {
							if (boneData.parentIdx == boneDatas[cntBoneData2].idx) {
								boneData.parentIdx = cntBoneData2;
								break;
							}
						}

						// �e��������Ȃ��������A�e�ԍ���DATANONE�ɂ���
						if (cntBoneData2 == boneDataSum.boneDataNum)
							boneData.parentIdx = DATANONE;
					}
				}
			}

			// �t�@�C�������
			RNLib::File()->CloseFile();
		}
	}

	return idx;
}

//========================================
// �������ݏ���
//========================================
void CSetUp3D::Save(const char* path, short idx) {

	//if (RNLib::File()->OpenSaveFile(pPath))
	//{// �t�@�C�����J�����ꍇ�A
	//	// ���i���̏������ݏ���
	//	CParts3DSetUp::SaveData(&m_datas[nIdx].boneDataSum);
	//
	//	FILE* file = RNLib::File()->GetFile();
	//	
	//	fprintf(file, "PLATFORM: %s\n", c_aModelPlatformName[m_datas[nIdx].platform]);
	//	fprintf(file, "END");
	//
	//	RNLib::File()->CloseFile();
	//}
}

//========================================
// ���������w�萔�ɏ�����
//========================================
void CSetUp3D::InitMemory(const unsigned short& num) {
	CRegist::InitMemory(num);

	// �f�[�^�̃������m��
	RNLib::Memory()->Alloc<CData>(&m_datas, num);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �f�[�^�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CSetUp3D::CData::CData() {

	m_boneDataSum = {};
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

	RNLib::Memory()->Release(&m_boneDataSum.boneDatas);
}