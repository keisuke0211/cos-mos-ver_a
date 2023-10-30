//========================================
// 
// 覐΂̏���
// Author:KOMURO HIROMU  Hirasawa Shion
// 
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include"../stage-object.h"
//****************************************
// �N���X��`
//****************************************
// ���e�I�̏��\����
class CMeteor : public CStageObject {
public:
	//========== [[[ �֐��錾 ]]]
	CMeteor();
	virtual        ~CMeteor();
	virtual void   Init(void);
	virtual void   Uninit(void);
	virtual void   Update(void);

	void	SetModelIdx(int idx) { ModelIdx = idx; }
	void	SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void	SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	static const D3DXVECTOR3 METEOR_ADDROT;    // 覐΂̉�]�̈ړ���
	static const D3DXVECTOR3 METEOR_MINPOS;    // �ŏ��̈ʒu
	static const D3DXVECTOR3 METEOR_MAXPOS;    // �ő�̈ʒu
	static const int         METEOR_ANIME_MAG; // �_�ŃA�j���[�V�����̔{��
	static const int         METEOR_BLINK_MAX; // �_�ŃA�j���[�V�����̍ő吔
	static const float       METEOR_BLINK_MIN; // �_�ł̍ŏ���
	static const float       METEOR_BLINK_ADJ; // �_�ŃA�j���[�V�����̒���

	void BlinkAnimation(void);	//�_�ŃA�j���[�V��������

	//========== [[[ �ϐ��錾 ]]]
	D3DXVECTOR3 m_move;	// �ړ���
	float m_fBlink;		// �_��
	int	  m_nBlinkAnim;	// �_�ŃA�j���[�V����

	int ModelIdx;
};
