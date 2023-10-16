//========================================
// 
// ���X�g�}�l�[�W���[�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list-manager.h ]]]
//========================================
#ifndef _LIST_MANAGER_H_
#define _LIST_MANAGER_H_

#include "list.h"

//****************************************
// �N���X��`
//****************************************
// ���X�g�}�l�[�W���[�N���X
class CListMgr {
public:
	//========== [[[ �֐��錾 ]]]
	CListMgr();
	virtual ~CListMgr();
	virtual void Init(void);
	virtual void ReleaseAll(void);
	virtual void Update(void);
	void   Release(CList* pList);
	void   AddList(CList* pAdd);
	void   SubList(CList* pSub);
	int    GetNum(void) { return m_nNum; }
	CList* GetTop(void) { return m_pTop; }
	bool ListLoop(CList** ppList);

private:
	//========== [[[ �֐��錾 ]]]
	void UpdateAll(void);

	//========== [[[ �ϐ��錾 ]]]
	CList* m_pTop;	// �擪�@��CHR�|�C���^
	CList* m_pCur;	// �Ō����CHR�|�C���^
	int    m_nNum;
};

#endif