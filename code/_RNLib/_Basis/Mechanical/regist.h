//========================================
// 
// �o�^�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// �o�^�N���X
class CRegist {
public:
	//========== [[[ �֐��錾 ]]]
	CRegist();
	virtual ~CRegist();
	virtual bool Load(const char* loadPath, short& idx);
	virtual void InitMemory(const unsigned short& num);

protected:
	//========== [[[ �ϐ��錾 ]]]
	char** m_loadPaths;
	unsigned short m_num;
};