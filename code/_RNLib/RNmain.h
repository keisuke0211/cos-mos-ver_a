//========================================
// 
// RN���C�u�����̃��C���w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <thread>
#include <mutex>
#include <time.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	// �r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						// ���͏����ɕK�v
#include "Xinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// �T�E���h�����ɕK�v

//****************************************
// ���C�u�����̃����N
//****************************************
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g���g�p����̂ɕK�v
#pragma comment(lib,"dsound.lib")	// DirectSound���g�p����̂ɕK�v
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	// ���͏����ɕK�v
#pragma warning(disable:4091)		// �x��:C4091�𖳎�����
#pragma warning(disable:4244)		// �x��:C4244�𖳎�����

//****************************************
// �}�N����`
//****************************************
// ���_�t�H�[�}�b�g
#define FVF_VERTEX_2D         (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D         (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
// �����l (��D3D�n��)
#define INITD3DXMATRIX        D3DXMATRIX   (1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f)
#define INITD3DVIEWPORT9      D3DVIEWPORT9 {0,0,0,0,0.0f,0.0f}
#define INITD3DXCOLOR         D3DXCOLOR(0.0f,0.0f,0.0f,0.0f)
#define INITD3DCOLOR          D3DCOLOR_RGBA(255,255,255,255)
#define INITD3DXVECTOR3       D3DXVECTOR3  (0.0f,0.0f,0.0f)
#define INITD3DXVECTOR2       D3DXVECTOR2  (0.0f,0.0f)
// �����l
#define INITMATRIX            Matrix       (1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f)
#define INITPOS2D             Pos2D        (0.0f,0.0f)
#define INITROT2D             Rot2D        (0.0f,0.0f)
#define INITVECTOR2D          Vector2D     (0.0f,0.0f)
#define INITNORMAL2D          Normal2D     (0.0f,0.0f)
#define INITSCALE2D           Scale2D      (1.0f,1.0f)
#define INITPOS3D             Pos3D        (0.0f,0.0f,0.0f)
#define INITROT3D             Rot3D        (0.0f,0.0f,0.0f)
#define INITVECTOR3D          Vector3D     (0.0f,0.0f,0.0f)
#define INITNORMAL3D          Normal3D     (0.0f,0.0f,0.0f)
#define INITSCALE3D           Scale3D      (1.0f,1.0f,1.0f)
#define INITBGCOLOR           Color        {0,0,0,255}
#define INITCOLOR             Color        {255,255,255,255}
// �~����
#define D3DX_PI_HALF          (D3DX_PI*0.5f)
#define D3DX_PI_DOUBLE        (D3DX_PI*2.0f)
#define D3DX_PI_UP            (0.0f)
#define D3DX_PI_DOWN          (D3DX_PI)
#define D3DX_PI_RIGHT         (D3DX_PI*0.5f)
#define D3DX_PI_RIGHT_UP      (D3DX_PI*0.75f)
#define D3DX_PI_RIGHT_DOWN    (D3DX_PI*0.25f)
#define D3DX_PI_LEFT          (D3DX_PI*0.5f)
#define D3DX_PI_LEFT_UP       (D3DX_PI*-0.75f)
#define D3DX_PI_LEFT_DOWN     (D3DX_PI*-0.25f)
// �s�N�Z���T�C�Y
#define PIXEL2D_SIZE          (2.0f)
#define PIXEL3D_SIZE          (0.4f)
// �f�[�^����
#define NONEDATA              (-1)
#define NONECOLOR             Color{-1,-1,-1,-1}
// �֐��`��
#define ARRAY_SIZE(a)         (sizeof(a) / sizeof(*a))
#define CHECK_ARRAY_SIZE(a,l) static_assert(ARRAY_SIZE(a) == (l),"aho")
// ���̑�
#define TXT_MAX               (512)

//****************************************
// �񋓌^��`
//****************************************
enum class PROCESS { INIT, UNINIT, UPDATE, };
enum class ANCHOR { NONE, CENTER, TOP, BOTTOM, LEFT, LEFTTOP, LEFTBOTTOM, RIGHT, RIGHTTOP, RIGHTBOTTOM, MAX, };

//****************************************
// �\���̒�`
//****************************************
// ���_���2D�̍\����
struct Vertex2D {
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// ���_���W
	float       rhw = 0.0f;				// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR    col = INITD3DCOLOR;		// ���_�J���[
	D3DXVECTOR2 tex = INITD3DXVECTOR2;	// �e�N�X�`�����W
};

// ���_���3D�̍\����
struct Vertex3D {
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// ���_���W
	D3DXVECTOR3 nor = INITD3DXVECTOR3;	// �@���x�N�g��
	D3DCOLOR    col = INITD3DCOLOR;		// ���_�J���[
	D3DXVECTOR2 tex = INITD3DXVECTOR2;	// �e�N�X�`�����W
};

//****************************************
// �\���̕ϊ�
//****************************************
// unsigned
typedef unsigned short    UShort;
typedef unsigned int      UInt;
typedef unsigned long     ULong;
// Vector2
typedef D3DXVECTOR2       Pos2D;
typedef D3DXVECTOR2       Rot2D;
typedef D3DXVECTOR2       Vector2D;
typedef D3DXVECTOR2       Normal2D;
typedef D3DXVECTOR2       Scale2D;
// Vector3
typedef D3DXVECTOR3       Pos3D;
typedef D3DXVECTOR3       Rot3D;
typedef D3DXVECTOR3       Vector3D;
typedef D3DXVECTOR3       Normal3D;
typedef D3DXVECTOR3       Scale3D;
// Other
typedef float             Angle;
typedef D3DXMATRIX        Matrix;
typedef D3DMATERIAL9      Material;
typedef LPDIRECT3DDEVICE9 Device;

//****************************************
// �N���X��`
//****************************************
// �F�N���X
class Color{
public:
	//========== [[[ �֐��錾 ]]]
	Color operator +(Color ovr) const {
		Color col = *this;
		col.r += ovr.r;
		col.g += ovr.g;
		col.b += ovr.b;
		col.a += ovr.a;
		return col;
	}
	Color operator *(float f) const {
		Color col = *this;
		col.r *= f;
		col.g *= f;
		col.b *= f;
		col.a *= f;
		return col;
	}
	Color operator /(float f) const {
		Color col = *this;
		col.r /= f;
		col.g /= f;
		col.b /= f;
		col.a /= f;
		return col;
	}
	Color operator +=(Color col) {
		this->r += col.r;
		this->g += col.g;
		this->b += col.b;
		this->a += col.a;
		return *this;
	}
	Color operator *=(float f) {
		this->r *= f;
		this->g *= f;
		this->b *= f;
		this->a *= f;
		return *this;
	}
	Color operator /=(float f) {
		this->r /= f;
		this->g /= f;
		this->b /= f;
		this->a /= f;
		return *this;
	}
	bool operator ==(Color col) {
		return (
			(this->r == col.r) &&
			(this->g == col.g) &&
			(this->b == col.b) &&
			(this->a == col.a)
			);
	}
	bool operator !=(Color col) {
		return !(*this == col);
	}

	//========== [[[ �ϐ��錾 ]]]
	int r;	// ��
	int g;	// ��
	int b;	// ��
	int a;	// �s�����x
};