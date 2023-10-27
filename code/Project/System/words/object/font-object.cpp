//========================================
// 
// �I�u�W�F�N�g����
// 
//========================================
// *** object.cpp ***
//========================================
#include "../../../manager.h"
#include "font-object.h"

// �ÓI�ϐ�
CFontObject *CFontObject::m_apTop[] = {};
CFontObject* CFontObject::m_apCir[] = {};

//========================================
// �R���X�g���N�^
//========================================
CFontObject::CFontObject(int nPriority)
{
	m_pNext = NULL;		// ���̃I�u�W�F�N�g
	m_pPrev = NULL;		// �O�̃I�u�W�F�N�g
	m_bDeath = false;	// ���S�t���O
	m_type = TYPE_NONE;	// ���

	// �擪�I�u�W�F�N�g��NULL��
	if (m_apTop[nPriority] == NULL)
	{
		m_apTop[nPriority] = this;	// �������g����(�擪)
		m_apCir[nPriority] = this;	// �������g����(�Ō��)
	}
	else
	{
		this->m_pPrev = m_apCir[nPriority];	// �Ō���̃I�u�W�F�N�g����
		m_apCir[nPriority]->m_pNext = this;	// �������g����
		m_apCir[nPriority] = this;			// �������g����
	}
	m_nPriority = nPriority;		// �������g�̗D�揇�ʂ���
}

//========================================
// �f�X�g���N�^
//========================================
CFontObject::~CFontObject()
{
	
}

//========================================
// �S�̂̔j��
//========================================
void CFontObject::ReleaseAll(void)
{
	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// �擪�I�u�W�F�N�g
		CFontObject *pObj = m_apTop[nPrio];

		// �I�u�W�F�N�g���̉�
		while (pObj != NULL)
		{
			// ���̃I�u�W�F�N�g
			CFontObject *pObjNext = pObj->m_pNext;

			// ���̃I�u�W�F�N�g�����邩
			if (pObj->m_pNext == NULL)
			{
				pObj->Uninit();		// �I������
				pObj->Release();	// ���S�t���O��^�ɂ���
				pObj = NULL;
				break;
			}
			else
			{
				pObj->Uninit();		// �I������
				pObj->Release();	// ���S�t���O��^�ɂ���
				pObj = NULL;
			}
			pObj = pObjNext;	// ���̃I�u�W�F�N�g�|�C���^����
		}

		// �|�C���^��擪�܂Ŗ߂�
		pObj = m_apTop[nPrio];

		while (pObj != NULL)
		{
			// ���̃I�u�W�F�N�g
			CFontObject *pObjNext = pObj->m_pNext;

			// ���S�t���O���^��
			if (pObj->m_bDeath)
			{
				// �j��
				pObj->ReleaseList();
			}

			pObj = pObjNext;	// ���̃I�u�W�F�N�g�|�C���^����
		}
	}
}

//========================================
// �S�Ĕj��(��ޖ�)
//========================================
void CFontObject::ReleaseAll(TYPE type)
{
	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// �擪�I�u�W�F�N�g
		CFontObject *pObj = m_apTop[nPrio];

		// �I�u�W�F�N�g���̉�
		while (pObj != NULL)
		{
			// ���̃I�u�W�F�N�g
			CFontObject *pObjNext = pObj->m_pNext;

			// �w�肵����ނ��ǂ���
			if (pObj->GetType() == type)
			{
				// ���̃I�u�W�F�N�g�����邩
				if (pObj->m_pNext == NULL)
				{
					pObj->Uninit();		// �I������
					pObj->Release();	// ���S�t���O��^�ɂ���
					pObj = NULL;
					break;
				}
				else
				{
					pObj->Uninit();		// �I������
					pObj->Release();	// ���S�t���O��^�ɂ���
					pObj = NULL;
				}
			}
			pObj = pObjNext;	// ���̃I�u�W�F�N�g�|�C���^����
		}

		// �|�C���^��擪�܂Ŗ߂�
		pObj = m_apTop[nPrio];

		while (pObj != NULL)
		{
			// ���̃I�u�W�F�N�g
			CFontObject *pObjNext = pObj->m_pNext;

			// ���S�t���O���^��
			if (pObj->m_bDeath)
			{
				// �j��
				pObj->ReleaseList();
			}

			pObj = pObjNext;	// ���̃I�u�W�F�N�g�|�C���^����
		}
	}
}

//========================================
// �j�����X�g
//========================================
void CFontObject::Release(void)
{
	// ���S�t���O��^�ɂ���
	m_bDeath = true;
}
//========================================
// �j��
//========================================
void CFontObject::ReleaseList(void)
{
	// �������g
	CFontObject *pObj = this;

	if (pObj == NULL)
	{// �����z���g���Ă��邩�ǂ����A
		return;
	}
	else if (m_pPrev == NULL && m_pNext == NULL)
	{// �I�u�W�F�N�g���P�����Ȃ����A
		m_apTop[m_nPriority] = NULL;
		m_apCir[m_nPriority] = NULL;
	}
	else if (m_pPrev == NULL)
	{// Top�����������A
		m_apTop[m_nPriority] = pObj->m_pNext;	// �擪�̃|�C���^����
		m_apTop[m_nPriority]->m_pPrev = NULL;	// �O�̃|�C���^�� NULL
	}
	else if (m_pNext == NULL)
	{// Cir�����������A
		m_apCir[m_nPriority] = pObj->m_pPrev;	// �Ō���̃|�C���^����
		m_apCir[m_nPriority]->m_pNext = NULL;	// ���̃|�C���^�� NULL
	}
	else
	{// �Ԃ̃I�u�W�F�N�g�����������A
		pObj->m_pPrev->m_pNext = pObj->m_pNext;	// ���̃|�C���^����
		pObj->m_pNext->m_pPrev = pObj->m_pPrev;	// �O�̃|�C���^����
	}

	delete pObj;
	pObj = NULL;
}

//========================================
// �S�̂̍X�V
//========================================
void CFontObject::UpdateAll(void)
{
	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// �擪�I�u�W�F�N�g
		CFontObject *pObj = m_apTop[nPrio];

		// �I�u�W�F�N�g���̉�
		while (pObj != NULL)
		{
			// ���̃I�u�W�F�N�g
			CFontObject *pObjNext = pObj->m_pNext;

			if (!pObj->m_bDeath)
			{
				// �X�V����
				pObj->Update();
			}

			// ���̃I�u�W�F�N�g����
			pObj = pObjNext;
		}

		// �|�C���^��擪�܂Ŗ߂�
		pObj = m_apTop[nPrio];

		// �I�u�W�F�N�g���̉�
		while (pObj != NULL)
		{
			// ���̃I�u�W�F�N�g
			CFontObject *pObjNext = pObj->m_pNext;

			if (pObj->m_bDeath)
			{
				// �j��
				pObj->ReleaseList();
			}

			// ���̃I�u�W�F�N�g����
			pObj = pObjNext;
		}
	}
}

//========================================
// �S�̂̕`��
//========================================

void CFontObject::DrawAll(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window().GetD3DDevice();

	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// �擪�I�u�W�F�N�g
		CFontObject *pObj = m_apTop[nPrio];


		// �I�u�W�F�N�g���̉�
		while (pObj != NULL)
		{
			// ���S�t���O���U��
			if (!pObj->m_bDeath)
			{
				// �`�揈��
				pObj->Draw();
			}
			// ���̃I�u�W�F�N�g�����邩�ǂ����A
			if (pObj->m_pNext == NULL)
			{
				break;
			}
			else
			{
				// ���̃I�u�W�F�N�g����
				pObj = pObj->m_pNext;
			}
		}
	}
}

//========================================
// ��ނ̐ݒ�
//========================================
void CFontObject::SetType(TYPE type)
{
	m_type = type;
}