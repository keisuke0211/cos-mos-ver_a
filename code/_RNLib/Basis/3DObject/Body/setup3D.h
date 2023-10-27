//========================================
// 
// �Z�b�g�A�b�v3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "../../Mechanical/regist.h"
#include "../../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
// �Z�b�g�A�b�v3D�N���X
class CSetUp3D : public CRegist {
public:
	//========== [[[ �\���̒�` ]]]
	// �{�[���f�[�^�\����
	struct BoneData {
		short idx         = NONEDATA;
		short modelIdx    = NONEDATA;
		short parentIdx   = NONEDATA;
		Pos3D relativePos = INITPOS3D;
		Pos3D relativeRot = INITPOS3D;
	};

	// �f�[�^�\����
	class CData {
	public:
		// [[[ �֐��錾 ]]]
		CData();
		~CData();
		void Release(void);

		// [[[ �ϐ��錾 ]]]
		BoneData* m_boneDatas;
		short     m_boneDataNum;
	};

	//========== [[[ �֐��錾 ]]]
	CSetUp3D();
	~CSetUp3D();
	short  Load      (const char* loadPath, short idx = NONEDATA);
	void   Save      (const char* savePath, short idx);
	CData& GetData   (const short& idx) { return m_datas[idx]; }
	void   InitMemory(const unsigned short& num);

private:
	//========== [[[ �ϐ��錾 ]]]
	CData* m_datas;
};