//========================================
// 
// �q���[�}��3D�x�[�X�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ human-base3D.h ]]]
//========================================
#pragma once

#include "../../Mechanical/regist.h"
#include "../../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
// �q���[�}��3D�x�[�X�N���X
class CHuman3DBase :public CRegist{
public:
	//========== [[[ �\���̒�` ]]]
	// �f�[�^�\����
	typedef struct Data_ {
		//----- ��{��� -----
		int         nSetUpIdx  = 0;					// ���f���Z�b�g�A�b�v�ԍ�
		//----- �� -----
		D3DXVECTOR3 eyePos     = INITD3DXVECTOR3;	// �ڂ̈ʒu
		D3DXVECTOR3 eyeRot     = INITD3DXVECTOR3;	// �ڂ̌���
		int         nEyeParent = -1;				// �ڂ̐e���i�ԍ�
		float       fEyeSpace  = 0.0f;				// �ڂ̊Ԋu
		float       fEyeRotDia = 0.0f;				// �ڂ̉�]�{��
	}Data;

	//========== [[[ �֐��錾 ]]]
	/* �R���X�g���N�^   */CHuman3DBase();
	/* �f�X�g���N�^     */~CHuman3DBase();
	/* �I������         */void Uninit(void);
	/* �ǂݍ��ݏ���     */int  Load(const char* pLoadPath, short nIdx = DATANONE);
	/* �������ݏ���     */void Save(char* pPath, int nIdx);
	/* �f�[�^�擾       */Data* GetData(const int nIdx) { return &m_pData[nIdx]; }
	/* ���������������� */void InitMemory(const int nNum);

private:
	//========== [[[ �ϐ��錾 ]]]
	Data* m_pData;	// �f�[�^
};