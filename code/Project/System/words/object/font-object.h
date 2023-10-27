//========================================
// 
// �t�H���g�F�I�u�W�F�N�g
// 
//========================================
// *** font-objext.h ***
//========================================
#pragma once

#include "../../../../_RNLib/RNlib.h"

//****************************************
// �N���X
//****************************************
class CFontObject
{
public:

	// ***** �񋓌^ *****

	// �D�揇�ʎ��
	enum PRIO
	{
		PRIO_NONE = 0,	// ����
		PRIO_OBJECT,	// �I�u�W�F�N�g
		PRIO_TEXT,		// �e�L�X�g
		PRIO_MAX
	};

	// �I�u�W�F�N�g���
	enum TYPE
	{
		TYPE_NONE = 0,	// ����
		TYPE_FONT,		// �t�H���g
		TYPE_TEXT,		// �e�L�X�g
		TYPE_MAX
	};

	// ***** �ÓI�֐� *****
	/* �S�Ă̔j��			*/static void ReleaseAll(void);
	/* �S�Ă̔j��(��ޖ�)	*/static void ReleaseAll(TYPE type);	// [�I�[�o�[���[�h]
	/* �S�Ă̍X�V			*/static void UpdateAll(void);
	/* �S�Ă̕`��			*/static void DrawAll(void);

	// ***** �֐� *****
	CFontObject(int nPriority = 0);
	virtual~CFontObject();

	/* ������	*/virtual HRESULT Init(void) = 0;
	/* �I��		*/virtual void Uninit(void) = 0;
	/* �X�V		*/virtual void Update(void) = 0;
	/* �`��		*/virtual void Draw(void) = 0;

	// -- �ݒ� ------------------------------------------
	/* ��ސݒ�*/void SetType(TYPE type);

	// -- �擾 ------------------------------------------
	/* �擪�̏��				*/static CFontObject *GetTop(int nPriority) { return m_apTop[nPriority]; }
	/* �Ō���̏��				*/static CFontObject *GetCur(int nPriority) { return m_apCir[nPriority]; }
	/* �O�̃I�u�W�F�N�g���		*/CFontObject *GetPrev(void) { return m_pPrev; }
	/* �O�̃I�u�W�F�N�g���		*/CFontObject *GetNext(void) { return m_pNext; }
	/* ��						*/virtual float GetWidth(void) { return 0.0f; }
	/* ����						*/virtual float GetHeight(void) { return 0.0f; }
	/* ���s��					*/virtual float GetDepth(void) { return 0.0f; }
	/* �T�C�Y					*/virtual D3DXVECTOR3 GetSize(void) { return INITD3DXVECTOR3; }
	/* �ʒu						*/virtual D3DXVECTOR3 GetPos(void) { return INITD3DXVECTOR3; }
	/* �ʒu(�ߋ�)				*/virtual D3DXVECTOR3 GetPosOld(void) { return INITD3DXVECTOR3; }
	/* ����						*/virtual D3DXVECTOR3 GetRot(void) { return INITD3DXVECTOR3; }
	/* ����(�ߋ�)				*/virtual D3DXVECTOR3 GetRotOld(void) { return INITD3DXVECTOR3; }
	/* ���						*/TYPE GetType(void) { return m_type; }

protected:
	
	// ***** �֐� ****
	/* ������� */void Release(void);

	// ***** �ϐ� *****
	CFontObject *m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CFontObject *m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^

private:
	// ***** �֐� *****
	/* �������	*/void ReleaseList(void);

	// ***** �ϐ� *****
	static CFontObject *m_apTop[PRIO_MAX];	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CFontObject *m_apCir[PRIO_MAX];	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nPriority;					// �D�揇�ʂ̈ʒu
	TYPE m_type;						// �������g�̎��
	bool m_bDeath;						// ���S�t���O

};