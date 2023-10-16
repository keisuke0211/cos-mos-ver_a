//========================================
// 
// ���X�g�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list.h ]]]
//========================================
#ifndef _LIST_H_
#define _LIST_H_

//****************************************
// �N���X��`
//****************************************
// ���X�g�N���X
class CList {
public:
	//========== [[[ �֐��錾 ]]]
	CList();
	virtual ~CList();
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Release(void);
	// �ݒ�擾
	void   SetNext  (CList* pNext) { m_pNext = pNext; }
	CList* GetNext  (void)         { return m_pNext; }
	void   SetPrev  (CList* pPrev) { m_pPrev = pPrev; }
	CList* GetPrev  (void)         { return m_pPrev; }
	bool   GetDelete(void)         { return m_bDelete; }

private:
	//========== [[[ �ϐ��錾 ]]]
	CList* m_pPrev;
	CList* m_pNext;
	bool   m_bDelete;
};

#endif