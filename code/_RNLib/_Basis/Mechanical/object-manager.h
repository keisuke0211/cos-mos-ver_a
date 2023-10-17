//========================================
// 
// �I�u�W�F�N�g�}�l�[�W���[�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include "object.h"

//****************************************
// �N���X��`
//****************************************
// �I�u�W�F�N�g�}�l�[�W���[�N���X
class CObjectMgr {
public:
	//========== [[[ �֐��錾 ]]]
	static void  UpdateAllMgrs(void);
	static void  SubMgr(CObjectMgr* mgr);
	             CObjectMgr();
	virtual      ~CObjectMgr();
	virtual void Update(void) = 0;
	void         UpdateAll(void);
	virtual void ReleaseAll(void);
	void         Release(CObject* obj);
	void         AddList(CObject* obj);
	void         SubList(CObject* obj);
	int          GetNum(void) { return m_num; }
	CObject*     GetTop(void) { return m_top; }
	bool         ListLoop(CObject** obj);

private:
	//========== [[[ �֐��錾 ]]]
	void ReleaseDeleteObj(void);

	//========== [[[ �ϐ��錾 ]]]
	CObject* m_top;	// �擪
	CObject* m_cur;	// �Ō��
	int m_num;
	static CObjectMgr** ms_objectMgrs;
	static unsigned short ms_objectMgrNum;
};