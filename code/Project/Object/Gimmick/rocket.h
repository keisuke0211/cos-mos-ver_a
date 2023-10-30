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
		RIDE,	  // ���
		FLY,	  // ���
		MAX,
	};
	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 move;		// �ړ���
		D3DXCOLOR col;			// ���_�J���[
		ANIME_STATE Animstate;	// �A�j���[�V�����̏��
		Scale3D scale;			// �X�P�[��
		Scale3D Maxscale;		// �ő�X�P�[��
		float SmallSpeed;		// �������Ȃ鑬�x
		float fScaleMag;		// �X�P�[���̔{��
		short nModelIdx;		// ���f���ԍ�
		int	nRideAnimeCounter;	// ���C�h�A�j���[�V�����J�E���^�[
		int	nFlyAnimeCounter;	// ��s�A�j���[�V�����J�E���^�[
	};
	
	// *** �֐� ***
	CRocket();
	~CRocket();

	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* ����Ԃ̍X�V		*/void UpdateState_Ride(void);
	/* ��ԏ�Ԃ̍X�V		*/void UpdateState_Fly(void);
	/* �`��		*/void Draw(void);

	// -- �ݒ� ---------------------------------------------
	/* �F			*/void SetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* ���f���ԍ�	*/void SetModelIdx(const int nIdx) { m_Info.nModelIdx = nIdx; }
	/* �A�j���[�V�����̏�Ԃ̐ݒ�*/void SetState(const ANIME_STATE state) { m_Info.Animstate = state; }
	/* ����Ă���		*/void Ride(void);

	// -- ���� ---------------------------------------------
	/* �F		*/D3DXCOLOR GetColor(void) { return m_Info.col; }

private:

	// *** �ϐ� ***
	Info m_Info;		// ���ʏ��

	static const int   s_AnimeMax;
	static const int   s_RideAnimeMax;
	static const float s_RideAnimeMag;
	static const float s_RideAnimeShrink;
	static const float s_RotAdd;
	static const int   s_RotAnimeMax;
	static const float s_MoveMag;
	static const float s_MoveAdd;
};