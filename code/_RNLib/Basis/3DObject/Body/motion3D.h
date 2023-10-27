//========================================
// 
// ���[�V����3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "setup3D.h"
#include "../../Mechanical/regist.h"

//****************************************
// �N���X��`
//****************************************
class CMotion3D : public CRegist {
public:
	//========== [[[ �񋓌^��` ]]]
	// �R�}���h
	enum class COMMAND {
		NONE = -1,
		MOVE,		// �ړ�
		SPIN,		// ��]
		SCALING,	// �g�k
		STEP,		// ����
		MAX,
	};

	//========== [[[ �\���̒�` ]]]
	// �R�}���h�\����
	struct CommandData {
		short   time    = 0;
		COMMAND command = (COMMAND)0;
		float*  datas   = NULL;
	};

	// �{�[�����[�V�����f�[�^�\����
	struct BoneMotionData {
		bool         isMove         = false;
		bool         isSpin         = false;
		bool         isScale        = false;
		UShort       commandDataNum = 0;
		CommandData* commandDatas   = NULL;
	};

	// �f�[�^�\����
	class CData {
	public:
		// [[[ �֐��錾 ]]]
		CData();
		~CData();
		void Release(void);

		// [[[ �ϐ��錾 ]]]
		short           loopTime        = 0;
		bool            isLoop          = false;
		UShort          boneNum         = 0;
		BoneMotionData* boneMotionDatas = NULL;
	};

	//========== [[[ �֐��錾 ]]]
	CMotion3D();
	~CMotion3D();
	short  Load      (const char* loadPath, short idx = NONEDATA);
	void   Save      (const char* savePath, const short& idx);
	CData& GetData   (const short& idx) { return m_datas[idx]; }
	void   InitMemory(const UShort& num);

	//========== [[[ �ϐ��錾 ]]]
	CData* m_datas;

private:
	//========== [[[ �萔�錾 ]]]
	static const UShort COMMAND_DATA_NUM[(int)COMMAND::MAX];
};