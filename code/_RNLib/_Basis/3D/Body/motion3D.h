//========================================
// 
// ���[�V����3D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ motion3D.h ]]]
//========================================
#ifndef _MOTION3D_H_
#define _MOTION3D_H_

#include "setup3D.h"
#include "../../Other/regist.h"

//****************************************
// �N���X��`
//****************************************
class CMotion3D : public CRegist {
public:
	//========== [[[ �񋓌^��` ]]]
	// �R�}���h
	typedef enum {
		CMD_LABEL_MOVE,				// �ړ�
		CMD_LABEL_SPIN,				// ��]
		CMD_LABEL_STEP,				// ����
		CMD_LABEL_SCALE,			// �g��k��
		CMD_LABEL_STEP_REACTION,	// ��������
		CMD_LABEL_MAX,
	}CMD_LABEL;

	//========== [[[ �\���̒�` ]]]
	// �R�}���h�f�[�^�\����
	typedef struct CmdData_ {
		const char* pLabelName;	// ���x����
		int         nDataNum;	// �����̐�
	}CmdData;
	// �R�}���h���\����
	typedef struct Cmd_ {
		int       nTime   = 0;				// ����
		CMD_LABEL command = (CMD_LABEL)0;	// �R�}���h�̎��
		float*    pData   = NULL;			// ����
	}Cmd;
	// ���i���̃R�}���h���\����
	typedef struct PartsCmd_ {
		bool bMove   = false;	// �ړ��t���O
		bool bSpin   = false;	// ��]�t���O
		int  nCmdNum = 0;		// �R�}���h��
		Cmd* pCmd    = NULL;	// �R�}���h���
	}PartsCmd;

	// ���f���\�����̃f�[�^�\����
	typedef struct PlatformData_{
		int       nPartsNum = 0;	// ���i��
		PartsCmd* pPartsCmd = NULL;	// ���i���̃R�}���h���
	}PlatformData;
	// �f�[�^�\����
	typedef struct Data_ {
		int  nLoopTime = 0;		// ���[�v����
		bool bLoop     = false;	// ���[�v���邩�t���O
		PlatformData pfData[CModelSetUp::PLATFORM_MAX] = {};
	}Data;

	//========== [[[ �֐��錾 ]]]
	/* �I������             */void      Uninit(void);
	/* �ǂݍ��ݏ���         */int       Load(const char* pPath, short nIdx = DATANONE);
	/* �������ݏ���         */void      Save(const char* pPath, const int nIdx);
	/* �f�[�^�擾           */Data*     GetData(void)                                               { return m_pData; }
	/* ���i���̃R�}���h�擾 */PartsCmd* GetPartsCmd(int nIdx, CModelSetUp::PLATFORM pf, int nParts) { return &m_pData[nIdx].pfData[pf].pPartsCmd[nParts]; }
	/* �R�}���h�f�[�^�擾   */CmdData   GetCmdData(CMD_LABEL cmd)                                   { return CMD_DATA[cmd]; }
	/* ����������������     */void      InitMemory(const int nNum);

	//========== [[[ �ϐ��錾 ]]]
	Data* m_pData;	// �f�[�^

private:
	//========== [[[ �ÓI�萔�錾 ]]]
	static const CmdData CMD_DATA[CMD_LABEL_MAX];	// �R�}���h�f�[�^
};

#endif