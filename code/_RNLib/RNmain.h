//========================================
// 
// RNlibのメイン処理のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ RNmain.h ]]]
//========================================
#ifndef _RNMAIN_H_
#define _RNMAIN_H_

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <thread>
#include <mutex>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	// ビルド時の警告対処用マクロ
#include "dinput.h"						// 入力処理に必要
#include "Xinput.h"						// 入力処理に必要
#include "xaudio2.h"					// サウンド処理に必要

//****************************************
// ライブラリのリンク
//****************************************
#pragma comment(lib,"d3d9.lib")		// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	// DirectXコンポーネントを使用するのに必要
#pragma comment(lib,"dsound.lib")	// DirectSoundを使用するのに必要
#pragma comment(lib,"winmm.lib")	// システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")	// 入力処理に必要
#pragma comment(lib,"xinput.lib")	// 入力処理に必要
#pragma warning(disable:4091)		// 警告:C4091を無視する
#pragma warning(disable:4244)		// 警告:C4244を無視する

//****************************************
// マクロ定義
//****************************************
//========== [[[ フォーマット指定 ]]]
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)			// 頂点フォーマット2D
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// 頂点フォーマット3D

//========== [[[ 値 ]]]
#define INITD3DXVECTOR3 D3DXVECTOR3(0.0f,0.0f,0.0f)	// D3DXVECTOR3の初期値
#define INITD3DXVECTOR2 D3DXVECTOR2(0.0f,0.0f)		// D3DXVECTOR2の初期値
#define INITD3DCOLOR    D3DCOLOR_RGBA(255,255,255,255)
#define INITD3DVIEWPORT9 D3DVIEWPORT9{0,0,0,0,0.0f,0.0f}
#define INITBGCOLOR     Color{0  ,0  ,0  ,255}		// 背景色の初期値
#define INITCOLOR       Color{255,255,255,255}		// Colorの初期値
#define CLEARCOLOR      Color{0  ,0  ,0  ,0  }		// Colorのクリア値
#define COLORNONE       Color{-1 ,-1 ,-1 ,-1 }		// Colorのクリア値
#define D3DX_PI_HALF    (D3DX_PI*0.5f)
#define D3DX_PI_DOUBLE  (D3DX_PI*2.0f)
#define COUNT_MAX       (INT_MAX*0.5f)
#define PIXEL2D_SIZE    (2.0f)
#define PIXEL3D_SIZE    (0.4f)

//========== [[[ その他定数 ]]]
#define TXT_MAX  (1024)	// 文字列の最大数(汎用)
#define DATANONE (-1)	// データ無し番号

//========== [[[ 関数形式 ]]]
#define ARRAY_SIZE(a)         (sizeof(a) / sizeof(*a))
#define CHECK_ARRAY_SIZE(a,l) static_assert(ARRAY_SIZE(a) == (l),"aho")

//****************************************
// 列挙型定義
//****************************************
enum class PROCESS { 
	INIT, 
	UNINIT, 
	UPDATE, 
};

enum class ANCHOR {
	NONE ,
	CENTER, TOP     , BOTTOM     ,
	LEFT  , LEFTTOP , LEFTBOTTOM ,
	RIGHT , RIGHTTOP, RIGHTBOTTOM,
	MAX,
};

//****************************************
// 構造体定義
//****************************************
// 頂点情報2Dの構造体
struct VERTEX_2D {
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// 頂点座標
	float       rhw = 0.0f;				// 座標変換用係数(1.0fで固定)
	D3DCOLOR    col = INITD3DCOLOR;		// 頂点カラー
	D3DXVECTOR2 tex = INITD3DXVECTOR2;	// テクスチャ座標
};

// 頂点情報3Dの構造体
struct VERTEX_3D {
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// 頂点座標
	D3DXVECTOR3 nor = INITD3DXVECTOR3;	// 法線ベクトル
	D3DCOLOR    col = INITD3DCOLOR;		// 頂点カラー
	D3DXVECTOR2 tex = INITD3DXVECTOR2;	// テクスチャ座標
};

// 拡大倍率構造体
typedef struct {
	float fWidth;	// 幅
	float fHeight;	// 高さ
	float fDepth;	// 奥行き
}Scale;

//****************************************
// クラス定義
//****************************************
// 色クラス
class Color{
public:
	//========== [[[ 関数宣言 ]]]
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

	//========== [[[ 変数宣言 ]]]
	int r;	// 赤
	int g;	// 緑
	int b;	// 青
	int a;	// 不透明度
};

#endif