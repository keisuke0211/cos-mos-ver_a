//========================================
// 
// 幾何学のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ geometry.h ]]]
//========================================
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

//****************************************
// マクロ定義
//****************************************
// 角度
#define ANGLE_UP         (D3DX_PI* 0.00f)
#define ANGLE_UP_RIGHT   (D3DX_PI* 0.25f)
#define ANGLE_RIGHT      (D3DX_PI* 0.50f)
#define ANGLE_DOWN_RIGHT (D3DX_PI* 0.75f)
#define ANGLE_DOWN       (D3DX_PI* 1.00f)
#define ANGLE_DOWN_LEFT  (D3DX_PI*-0.75f)
#define ANGLE_LEFT       (D3DX_PI*-0.50f)
#define ANGLE_UP_LEFT    (D3DX_PI*-0.25f)

//****************************************
// 関数宣言
//****************************************
/*------------算出------------*/
/* 2点の距離                  */float       Find_Dist              (D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
/* 2点の距離   (見下ろし視点) */float       Find_Dist_LookDown     (D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
/* 2点の角度   (俯瞰視点)     */float       Find_Angle_LookFront   (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 2点の角度   (見下ろし視点) */float       Find_Angle_LookDown    (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 2点の向き                  */D3DXVECTOR3 Find_Rot               (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 2点の向きマトリックス      */D3DXMATRIX  Find_RotMtx            (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 交点座標    (見下ろし視点) */D3DXVECTOR3 Find_Inter_LookDown    (D3DXVECTOR3 posA1, D3DXVECTOR3 posA2, D3DXVECTOR3 posB1, D3DXVECTOR3 posB2);
/* 角度の差                   */float       Find_AngleDiff         (float fAngle, float fTargetAngle);
/* 向きのベクトル             */D3DXVECTOR3 Find_RotVec            (D3DXVECTOR3 rot);
/* ベクトルの向き             */D3DXVECTOR3 Find_VecRot            (D3DXVECTOR3 vec);
/* カメラ面までの垂直距離     */float       Find_DistToCameraPlane (D3DXVECTOR3 pos);
/* ベクトルの法線             */D3DXVECTOR3 Find_VecNor            (D3DXVECTOR3 start1, D3DXVECTOR3 end1, D3DXVECTOR3 start2, D3DXVECTOR3 end2);
/*---------範囲内制御---------*/								    
/* 角度                       */void        Limit_Angle            (float *pAngle);
/*---------ループ制御---------*/								    
/* 向き                       */void        Cycle_Control          (D3DXVECTOR3* pRot);
/*------------変換------------*/								   
/* 角度→分割値               */float       Conv_AngleToDir        (float fAngle, int nDiv);
/* 位置→見下ろし基準(Z⇔Y)   */D3DXVECTOR3 Conv_LookDownPos       (D3DXVECTOR3 pos);
/* 向き→見下ろし基準(Z⇔Y)   */D3DXVECTOR3 Conv_LookDownRot       (D3DXVECTOR3 rot);
/*-----------その他-----------*/
/* ランダムなベクトルを取得   */D3DXVECTOR3 vecRand(void);

#endif