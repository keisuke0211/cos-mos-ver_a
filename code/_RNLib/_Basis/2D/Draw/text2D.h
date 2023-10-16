//========================================
// 
// �e�L�X�g2D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ text2D.h ]]]
//========================================
#ifndef _TEXT2D_H_
#define _TEXT2D_H_

#include "../../Draw/text.h"

//****************************************
// �N���X��`
//****************************************
// �e�L�X�g2D�N���X
class CText2D {
public:
	// �ݒ菈��
	void Set(
		const char*       pString,
		const float       fScaleX,
		const float       fScaleY,
		const D3DXVECTOR3 pos   = INITD3DXVECTOR3,
	    const D3DXVECTOR3 rot   = INITD3DXVECTOR3,
		const CText::ALIGNMENT disp  = CText::ALIGNMENT::CENTER,
		const int         nFont = 0,
		const Color       col   = INITCOLOR);
};

#endif