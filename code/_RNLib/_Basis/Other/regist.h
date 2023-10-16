//========================================
// 
// �o�^�����̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ regist.h ]]]
//========================================
#ifndef _REGIST_H_
#define _REGIST_H_

//****************************************
// �N���X��`
//****************************************
// �o�^�N���X
class CRegist {
public:
	//========== [[[ �֐��錾 ]]]
	/* �R���X�g���N�^     */CRegist();
	/* �f�X�g���N�^       */virtual ~CRegist();
	/* �I������           */virtual void Uninit(void);
	/* �ǂݍ��ݏ���       */virtual bool Load(const char *pPath, short *pIdx);
	/* ����������������   */virtual void InitMemory(const int nNum);
	/*=====[�ݒ�擾]=====*/
	/* �ǂݍ��ݍσp�X�擾 */char* GetLoadPath(int nIdx) {
		if (nIdx < 0) { return NULL; }
		return m_ppLoadPath[nIdx];
	}

protected:
	//========== [[[ �ϐ��錾 ]]]
	char** m_ppLoadPath;	// �ǂݍ��ݍσp�X
	unsigned short m_num;	// ����
};

#endif