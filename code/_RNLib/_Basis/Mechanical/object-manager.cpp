//========================================
// 
// �I�u�W�F�N�g�}�l�[�W���[�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �I�u�W�F�N�g�}�l�[�W���[�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//****************************************
// �ÓI�����o�ϐ���`
//****************************************
CObjectMgr** CObjectMgr::ms_objectMgrs = NULL;
unsigned short CObjectMgr::ms_objectMgrNum = NULL;

//========================================
// [�ÓI] �S�}�l�[�W���[�X�V����
//========================================
void CObjectMgr::UpdateAllMgrs(void) {

	// �S�}�l�[�W���[�̑S�X�V�����ƍX�V�������s��
	for (int cntObjectMgr = 0; cntObjectMgr < ms_objectMgrNum; cntObjectMgr++) {
		ms_objectMgrs[cntObjectMgr]->UpdateAll();
		ms_objectMgrs[cntObjectMgr]->Update();
	}
}

//========================================
// [�ÓI] �}�l�[�W���[��r��
//========================================
void CObjectMgr::SubMgr(CObjectMgr* mgr) {

	bool isSub = false;
	for (int cntObjectMgr = 0; cntObjectMgr < ms_objectMgrNum; cntObjectMgr++) {
		if (isSub) 
		{// �r�����I����
			// 1�O�ɂ��炷
			ms_objectMgrs[cntObjectMgr - 1] = ms_objectMgrs[cntObjectMgr];
			ms_objectMgrs[cntObjectMgr] = NULL;
		}
		else 
		{// �r�����ĂȂ�
			if (mgr == ms_objectMgrs[cntObjectMgr]) 
			{// �J�E���g�ƑΏۃA�h���X����v�������A
				// ���������炵�A�r���t���O��^�ɂ���
				ms_objectMgrNum--;
				isSub = true;
			}
		}
	}

	// �r���o�������A���������Ċm��
	if (isSub)
		RNLib::Memory()->ReAlloc<CObjectMgr*>(&ms_objectMgrs, ms_objectMgrNum + 1, ms_objectMgrNum);
}

//========================================
// �R���X�g���N�^
//========================================
CObjectMgr::CObjectMgr(void) {

	{// �I�u�W�F�N�g�}�l�[�W���[��ɒǉ�����
		int numOld = ms_objectMgrNum++;
		RNLib::Memory()->ReAlloc<CObjectMgr*>(&ms_objectMgrs, numOld, ms_objectMgrNum, false);
		ms_objectMgrs[numOld] = this;
	}

	m_top = NULL;
	m_cur = NULL;
	m_num = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CObjectMgr::~CObjectMgr(void) {

	// �S�J������
	CObjectMgr::ReleaseAll();

	// ���g���}�l�[�W���[�񂩂�r��
	SubMgr(this);
}

//========================================
// �S�J������
//========================================
void CObjectMgr::ReleaseAll(void) {

	// �擪���珇�ԂɍŌ���܂ō폜�t���O�𗧂�����
	// (���p����̗v�f�͉������邪�A
	//    �{�͉̂�������A���S�t���O�𗧂�����)
	CObject* obj = NULL;
	while (ListLoop(&obj)) {

		obj->Delete();
	}

	// �폜�t���O�������Ă���I�u�W�F�N�g���������
	ReleaseDeleteObj();
}

//========================================
// �ꊇ�X�V����
// Author:RIKU NISHIMURAS
//========================================
void CObjectMgr::UpdateAll(void) {

	// �擪���珇�ԂɍŌ���܂ōX�V���Ă���
	CObject* pList = NULL;
	while (ListLoop(&pList)) {

		pList->Update();
	}

	// �폜�t���O�������Ă���I�u�W�F�N�g���������
	ReleaseDeleteObj();
}

//========================================
// �폜�t���O�������Ă���I�u�W�F�N�g���������
//========================================
void CObjectMgr::ReleaseDeleteObj(void) {

	// �擪���珇�ԂɍŌ���܂ŉ�����Ă���
	// (���폜�t���O���^�̎��A�������)
	CObject* obj = m_top;
	while (obj != NULL) {
		CObject* nextObj = obj->GetNext();

		// �폜�t���O���^�̎��A�������
		if (obj->GetDelete())
			Release(obj);

		obj = nextObj;
	}
}

//========================================
// ���X�g���[�v����
//========================================
bool CObjectMgr::ListLoop(CObject** obj) {

	if (*obj == NULL)
		*obj = m_top;
	else
		*obj = (*obj)->GetNext();

	return (*obj != NULL);
}

//========================================
// �I�u�W�F�N�g�������
//========================================
void CObjectMgr::Release(CObject* obj) {

	// ����NULL�ł���ΏI��
	if (obj == NULL)
		return;

	// ���X�g����폜
	SubList(obj);

	// �I�����ĉ��
	obj->Uninit();
	delete obj;
}

//========================================
// ���X�g�ɒǉ�
//========================================
void CObjectMgr::AddList(CObject* obj) {

	if (m_cur == NULL)
	{// �Ō�������݂��Ȃ�(���܂�1���Ȃ�)���A
		// �擪�ƍŌ����V�K�ɐݒ肷��
		m_top = obj;
		m_cur = obj;

		obj->SetPrev(NULL);	// �O ����
		obj->SetNext(NULL);	// �� ����
	}
	else
	{// �Ō�������݂��鎞�A
		// ���Ō���̎���V�K�ɐݒ肷��
		m_cur->SetNext(obj);

		obj->SetPrev(m_cur);	// �O ���Ō��
		obj->SetNext(NULL);		// �� ����

		// �Ō����V�K�ɐݒ肷��
		m_cur = obj;
	}

	m_num++;
}

//========================================
// ���X�g����r��
//========================================
void CObjectMgr::SubList(CObject* obj) {

	if (obj->GetPrev() == NULL)
	{// �O�����݂��Ȃ�(���������擪)���A
		// �擪�����ɐݒ肷��
		m_top = obj->GetNext();

		if (m_top != NULL)
		{// �擪�����݂��鎞�A
			m_top->SetPrev(NULL);	// �O ����
		}
	}

	if (obj->GetNext() == NULL)
	{// �������݂��Ȃ�(���������Ō��)���A
		// �Ō����O�ɐݒ肷��
		m_cur = obj->GetPrev();

		if (m_cur != NULL)
		{// �Ō�������݂��鎞�A
			m_cur->SetNext(NULL);	// �� ����
		}
	}
	else
	{// �������݂��鎞�A
		CObject* prev = obj->GetPrev();
		CObject* next = obj->GetNext();

		// �O�Ǝ����q��
		if (prev != NULL)
			prev->SetNext(next);	// (���O�͑��݂���ۏႪ�����׃`�F�b�N)
		next->SetPrev(prev);
	}

	m_num--;
}