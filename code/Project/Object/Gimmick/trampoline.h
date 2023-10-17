//========================================
// 
// �M�~�b�N�̏���
// Author:RYUKI FUJIWARA
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"

//****************************************
// �N���X��`
//****************************************
// ���[�h�̏��\����
class CTrampoline : public CList {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class TYPE {
		NONE = 0,	//����Ă��Ȃ�
		GETON,		//����Ă���
		LAND,		//���n����
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CTrampoline();
	virtual        ~CTrampoline();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);
	virtual void   Draw(void);
	void   SetType(TYPE type) { m_type = type; }			//��ސݒ�
	TYPE   GetType(void) { return m_type; }					//��ގ擾
	void   SetPos(D3DXVECTOR3 pos) { m_pos = pos; }			//�ʒu�ݒ�
	void   SetScale(D3DXVECTOR3 scale) { m_scale = scale; }	//�g�k�ݒ�

protected:
	
private:
	//========== [[[ �ϐ��錾 ]]]
	TYPE m_type;			//���
	int m_modelIdx;			//���f���ԍ�
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_scale;	//�傫��
};
