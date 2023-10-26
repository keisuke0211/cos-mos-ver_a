//========================================
// 
// �e�L�X�g�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ text.h ]]]
//========================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "../../RNmain.h"

//****************************************
// �N���X��`
//****************************************
// �e�L�X�g�N���X
class CText {
public:
	//========== [[[ �񋓌^��` ]]]
	// �\���`��
	enum class ALIGNMENT {
		CENTER,	// ��������
		LEFT,	// ������
		RIGHT,	// �E����
		MAX,
	};

	//========== [[[ �\���̒�` ]]]
	// �t�H���g���̏��\����
	typedef struct Font_ {
		int   nStartCode = 0;			// �J�n����
		int   nPtnWidth  = 0;			// �p�^�[����
		int   nPtnHeight = 0;			// �p�^�[������
		float fSpaceRate = 0.0f;		// �Ԋu�䗦
		int   nTexIdx    = NONEDATA;	// �e�N�X�`���ԍ�
	}FontData;

	//========== [[[ �֐��錾 ]]]
	/* �R���X�g���N�^         */CText();
	/* �f�X�g���N�^           */~CText();
	/* �I������               */void Uninit(void);
	/* �t�H���g�̓ǂݍ��ݏ��� */void LoadFont(void);
	/* �t�H���g���݃`�F�b�N   */bool CheckFontExists(int nFont) {
		if (nFont < 0 || nFont >= m_nFontNum) {
			return false;
		}
		return true;
	}
	/* �t�H���g�̏����擾   */FontData GetFont(const int nFont) {
		if (nFont < 0 || nFont >= m_nFontNum) {
			FontData defFont = {};
			return defFont;
		}
		return m_pFont[nFont];
	};
	/* �t�H���g�̐����擾    */int GetFontNum(void) { return m_nFontNum; }
	/* �t�H���g�̕��擾      */float GetFontWidth   (int nFont);
	/* �t�H���g�̕��擾      */float GetFontWidth2D (int nFont);
	/* �t�H���g�̍����擾    */float GetFontHeight  (int nFont);
	/* �t�H���g�̍����擾    */float GetFontHeight2D(int nFont);

	//========== [[[ �ϐ��錾 ]]]
	FontData* m_pFont;	// �t�H���g���̃|�C���^
	int m_nFontNum;	// �t�H���g��
};

#endif