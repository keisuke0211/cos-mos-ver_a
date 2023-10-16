//========================================
// 
// �r�W���A���̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ visual.h ]]]
//========================================
#ifndef _VISUAL_H_
#define _VISUAL_H_

//****************************************
// �N���X��`
//****************************************
// �r�W���A���N���X
class CVisual {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class TEXTURE {
		// UI�n
		TRANSITION_HOLE,
		// �ގ��n
		LAVA,
		RUGGET,	// �S�c�S�c
		MAX,
	};
	enum class MODEL {
		CLOD_S,		// ��(��)
		CLOD_M,		// ��(��)
		NEEDLE_M,	// �j(��)
		MAX,
	};
	enum class MOTION3D {
		// ��{
		STAND_NORMAL,

		// �������
		SPC_EFF_SLEEP,	// ����

		// �\������
		ANTICIPATION_ARMCROSS,		// �r������
		ANTICIPATION_RIGHTHOOK,		// �E���\��

		// �U��
		BITE_MID,			// ���ݕt��	(��)
		BREATH_FORWARD,		// �f��     (�O)
		DRILL_MID,			// �@��		(��)
		PUNCH_RIGHT_MID,	// ����		(�E���)
		PUNCH_GROUND_RIGHT,	// ����		(�n�ʥ�E)
		TACKLE_MID,			// �^�b�N��	(��)
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	CVisual();
	~CVisual();
	void Load(void);
	int GetTextureIdx (TEXTURE  tex)    { return m_aTextureIdx[(int)tex]; }
	int GetModelIdx   (MODEL    model)  { return m_aModelIdx[(int)model]; }
	int GetMotion3DIdx(MOTION3D motion) { return m_aMotion3DIdx[(int)motion]; }

private:
	//========== [[[ �ϐ��錾 ]]]
	int m_aTextureIdx[(int)TEXTURE::MAX];
	int m_aModelIdx[(int)MODEL::MAX];
	int m_aMotion3DIdx[(int)MOTION3D::MAX];
};

#endif