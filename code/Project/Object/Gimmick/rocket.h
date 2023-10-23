//========================================
// 
// ���P�b�g
// Author:KEISUKE OTONO
// 
//========================================
// *** rocket.h ***
//========================================
#pragma once

#include "../../../_RNLib/RNlib.h"
#include "../stage-object.h"

//****************************************
// �N���X
//****************************************
class CRocket : public CStageObject {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class ANIME_STATE {
		NONE = -1,// �����Ȃ�
		FLY,	  // ���
		MAX,
	};
	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// ���_�J���[
		ANIME_STATE Animstate;	// �A�j���[�V�����̏��
		short nModelIdx;		// ���f���ԍ�
		int	nFlyAnimeCounter;	// ��s�A�j���[�V�����J�E���^�[
	};

	// *** �֐� ***
	CRocket();
	~CRocket();

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ---------------------------------------------
	/* �F			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* ���f���ԍ�	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }
	/* �A�j���[�V�����̏�Ԃ̐ݒ�*/void SetState(const ANIME_STATE state) { m_Info.Animstate = state; }
	// -- ���� ---------------------------------------------
	/* �F		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

};