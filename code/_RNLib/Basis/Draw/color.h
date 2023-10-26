//========================================
// 
// �F�̏����̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ color.h ]]]
//========================================
#ifndef _COLOR_H_
#define _COLOR_H_

//****************************************
// �}�N����`
//****************************************
#define COLOR_RED       Color{255,0  ,0  ,255}
#define COLOR_GREEN     Color{0  ,255,0  ,255}
#define COLOR_BLUE      Color{0  ,0  ,255,255}
#define COLOR_YELLOW    Color{255,255,0  ,255}
#define COLOR_MAGENTA   Color{255,0  ,255,255}
#define COLOR_CYAN      Color{0  ,255,255,255}
#define COLOR_WHITE     Color{255,255,255,255}
#define COLOR_WHITE_TRA Color{255,255,255,127}
#define COLOR_BLACK     Color{0  ,0  ,0  ,255}

//****************************************
// �\���̒�`
//****************************************
// �F�Ǘ����\����
struct ColorInfo {
	// �w�i�F
	Color bgCol = INITBGCOLOR;
};

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== [[[ �擾 ]]]
// �F�Ǘ����̎擾
ColorInfo *GetColorInfo(void);
//========== [[[ �ݒ� ]]]
// �w�i�F��ݒ�
void SetBGColor(Color bgCol);
//========== [[[ ���o�� ]]]
// �F�̓ǂݍ��ݏ���
void LoadColor(FILE *pFile, Color *pCol);
//========== [[[ �ϊ� ]]]
// Color�`���̐F��D3DXCOLOR�`���ɕϊ�
D3DXCOLOR ColorToD3DXCOLOR(Color col);
// Color�`���̐F��D3DCOLOR�`���ɕϊ�
D3DCOLOR ColorToD3DCOLOR(Color col);
// D3DCOLOR�`���̐F��Color�`���ɕϊ�
Color D3DCOLORToColor(D3DCOLORVALUE col);
//========== [[[ ���̑� ]]]
// �F�ɖ��邳�𔽉f
Color BrightnessToColor(Color col, float fBrightness);
// Color�`���̐F�̒l�������ŕԂ�
Color ColorRate(Color col, float fRate);
// Color�`���̐F�����Z
Color ColorAdd(Color col1, Color col2);
// Color�`���̐F��������
Color ColorMix(Color col1, Color col2);

#endif