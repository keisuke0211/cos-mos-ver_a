//========================================
// 
// ���X�g�}�l�[�W���[�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ list-manager.cpp ]]]
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CListMng�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CListMgr::CListMgr(void) {
	m_pTop = NULL;	// �擪�@��CHR�|�C���^
	m_pCur = NULL;	// �Ō����CHR�|�C���^
	m_nNum = 0;
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CListMgr::~CListMgr(void) {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CListMgr::Init(void) {

}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CListMgr::ReleaseAll(void) {
	CList* pList = m_pTop;
	while (pList != NULL) {
		CList* pListNext = pList->GetNext();

		pList->Release();

		pList = pListNext;
	}

	pList = m_pTop;
	while (pList != NULL) {
		CList* pListNext = pList->GetNext();

		// �폜�t���O���^�̎��A�������
		if (pList->GetDelete())
			Release(pList);

		pList = pListNext;
	}
}

//========================================
// �X�V����
// Author:RIKU NISHIMURAS
//========================================
void CListMgr::Update(void) {
	UpdateAll();
}

//========================================
// �ꊇ�X�V����
// Author:RIKU NISHIMURAS
//========================================
void CListMgr::UpdateAll(void) {
	CList* pList = NULL;
	while (ListLoop(&pList)) {
		pList->Update();
	}

	pList = m_pTop;
	while (pList != NULL) {
		CList* pListNext = pList->GetNext();

		// �폜�t���O���^�̎��A�������
		if (pList->GetDelete())
			Release(pList);

		pList = pListNext;
	}
}

//========================================
// ���X�g���[�v����
// Author:RIKU NISHIMURAS
//========================================
bool CListMgr::ListLoop(CList** ppList) {
	if (*ppList == NULL) {
		*ppList = m_pTop;
	}
	else {
		*ppList = (*ppList)->GetNext();
	}

	return (*ppList != NULL);
}

//========================================
// ���X�g�������
// Author:RIKU NISHIMURA
//========================================
void CListMgr::Release(CList* pRel) {
	if (pRel == NULL)
		return;

	SubList(pRel);

	pRel->Uninit();
	delete pRel;
}

//========================================
// ���X�g�ɒǉ�
// Author:RIKU NISHIMURA
//========================================
void CListMgr::AddList(CList* pAdd) {
	if (m_pCur == NULL)
	{// �Ō�������݂��Ȃ�(���܂�1���Ȃ�)���A
		// �擪�ƍŌ����V�K�ɐݒ肷��
		m_pTop = pAdd;
		m_pCur = pAdd;

		pAdd->SetPrev(NULL);	// �O ����
		pAdd->SetNext(NULL);	// �� ����
	}
	else
	{// �Ō�������݂��鎞�A
		// ���Ō���̎���V�K�ɐݒ肷��
		m_pCur->SetNext(pAdd);

		pAdd->SetPrev(m_pCur);	// �O ���Ō��
		pAdd->SetNext(NULL);	// �� ����

		// �Ō����V�K�ɐݒ肷��
		m_pCur = pAdd;
	}

	m_nNum++;
}

//========================================
// ���X�g����폜
// Author:RIKU NISHIMURA
//========================================
void CListMgr::SubList(CList* pSub) {
	if (pSub->GetPrev() == NULL)
	{// �O�����݂��Ȃ�(���������擪)���A
		// �擪�����ɐݒ肷��
		m_pTop = pSub->GetNext();

		if (m_pTop != NULL)
		{// �擪�����݂��鎞�A
			m_pTop->SetPrev(NULL);	// �O ����
		}
	}

	if (pSub->GetNext() == NULL)
	{// �������݂��Ȃ�(���������Ō��)���A
		// �Ō����O�ɐݒ肷��
		m_pCur = pSub->GetPrev();

		if (m_pCur != NULL)
		{// �Ō�������݂��鎞�A
			m_pCur->SetNext(NULL);	// �� ����
		}
	}
	else
	{// �������݂��鎞�A
		CList* pPrev = pSub->GetPrev();
		CList* pNext = pSub->GetNext();

		// �O�Ǝ����q��
		if (pPrev != NULL)
			pPrev->SetNext(pNext);	// (���O�͑��݂���ۏႪ�����׃`�F�b�N)
		pNext->SetPrev(pPrev);
	}

	m_nNum--;
}