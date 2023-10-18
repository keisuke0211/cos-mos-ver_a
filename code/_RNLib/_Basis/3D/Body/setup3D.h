//========================================
// 
// �Z�b�g�A�b�v3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "doll3D.h"
#include "../../Mechanical/regist.h"

//****************************************
// �N���X��`
//****************************************
// �Z�b�g�A�b�v3D�N���X
class CSetUp3D : public CRegist {
public:
	//========== [[[ �\���̒�` ]]]
	//----- �{�[�� -----
	// �{�[���f�[�^�\����
	struct BoneData {
		int         idx = 0;
		int         modelIdx = DATANONE;
		int         parentIdx = DATANONE;
		D3DXVECTOR3 relativePos = INITD3DXVECTOR3;
		D3DXVECTOR3 relativeRot = INITD3DXVECTOR3;
		D3DXVECTOR3 rotRelativePos = INITD3DXVECTOR3;
	};

	// �{�[���f�[�^�����\����
	struct BoneDataSum {
		BoneData* boneDatas = NULL;
		int       boneDataNum = 0;
	};
	//----------

	// �f�[�^�\����
	class CData {
	public:
		// [[[ �֐��錾 ]]]
		CData();
		~CData();
		void Release(void);

		// [[[ �ϐ��錾 ]]]
		BoneDataSum m_boneDataSum;	// ���i���
	};

	//========== [[[ �֐��錾 ]]]
	CSetUp3D();
	~CSetUp3D();
	int    Load(const char* loadPath, short idx = DATANONE);
	void   Save(const char* path, short idx);
	CData& GetData(const short& idx) { return m_datas[idx]; }
	void   InitMemory(const unsigned short& num);

private:
	//========== [[[ �ϐ��錾 ]]]
	CData* m_datas;
};