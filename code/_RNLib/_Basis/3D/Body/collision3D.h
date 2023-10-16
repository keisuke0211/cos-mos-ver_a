//========================================
// 
// �R���W����3D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// ���f���Z�b�g�A�b�v�N���X
class CCollision3D {
public:
	//========== [[[ �񋓌^��` ]]]
	// �`
	typedef enum {
		FORM_SPHERE,	// ��
		FORM_CUBE,		// ������
		FORM_CYLINDER,	// ��
		FORM_MAX,
	}FORM;

	//========== [[[ �\���̒�` ]]]
	// ���i���\����
	typedef struct Parts_ {
		FORM        form    = (FORM)0;			// �`
		float       fWidth  = 0.0f;				// ��
		float       fHeight = 0.0f;				// ����
		float       fDepth  = 0.0f;				// ���s��
		int         nParent = DATANONE;			// �e
		D3DXVECTOR3 pos     = INITD3DXVECTOR3;	// �ʒu
		D3DXVECTOR3 rot     = INITD3DXVECTOR3;	// ����
	}Parts;
	// �f�[�^�\����
	typedef struct Data_{
		Parts* pParts    = NULL;	// ���i���
		int    nPartsNum = 0;		// ���i��
	}Data;

	//========== [[[ �֐��錾 ]]]
	static void LoadData(Data* pData);
	static void SaveData(Data* pData);
};