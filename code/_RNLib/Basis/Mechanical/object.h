//========================================
// 
// �I�u�W�F�N�g�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// �I�u�W�F�N�g�N���X
class CObject {
public:
	//========== [[[ �֐��錾 ]]]
	CObject();
	virtual ~CObject();
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	void Delete(void) { m_isDelete = true; }
	// �ݒ�擾
	void     SetNext  (CObject* next) { m_next = next; }
	CObject* GetNext  (void)          { return m_next; }
	void     SetPrev  (CObject* prev) { m_prev = prev; }
	CObject* GetPrev  (void)          { return m_prev; }
	bool     GetDelete(void)          { return m_isDelete; }

private:
	//========== [[[ �ϐ��錾 ]]]
	CObject* m_prev;
	CObject* m_next;
	bool     m_isDelete;
};