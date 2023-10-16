//========================================
// 
// �􉽊w�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ geometry.h ]]]
//========================================
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

//****************************************
// �}�N����`
//****************************************
// �p�x
#define ANGLE_UP         (D3DX_PI* 0.00f)
#define ANGLE_UP_RIGHT   (D3DX_PI* 0.25f)
#define ANGLE_RIGHT      (D3DX_PI* 0.50f)
#define ANGLE_DOWN_RIGHT (D3DX_PI* 0.75f)
#define ANGLE_DOWN       (D3DX_PI* 1.00f)
#define ANGLE_DOWN_LEFT  (D3DX_PI*-0.75f)
#define ANGLE_LEFT       (D3DX_PI*-0.50f)
#define ANGLE_UP_LEFT    (D3DX_PI*-0.25f)

//****************************************
// �֐��錾
//****************************************
/*------------�Z�o------------*/
/* 2�_�̋���                  */float       Find_Dist              (D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
/* 2�_�̋���   (�����낵���_) */float       Find_Dist_LookDown     (D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
/* 2�_�̊p�x   (���Վ��_)     */float       Find_Angle_LookFront   (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 2�_�̊p�x   (�����낵���_) */float       Find_Angle_LookDown    (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 2�_�̌���                  */D3DXVECTOR3 Find_Rot               (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* 2�_�̌����}�g���b�N�X      */D3DXMATRIX  Find_RotMtx            (D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
/* ��_���W    (�����낵���_) */D3DXVECTOR3 Find_Inter_LookDown    (D3DXVECTOR3 posA1, D3DXVECTOR3 posA2, D3DXVECTOR3 posB1, D3DXVECTOR3 posB2);
/* �p�x�̍�                   */float       Find_AngleDiff         (float fAngle, float fTargetAngle);
/* �����̃x�N�g��             */D3DXVECTOR3 Find_RotVec            (D3DXVECTOR3 rot);
/* �x�N�g���̌���             */D3DXVECTOR3 Find_VecRot            (D3DXVECTOR3 vec);
/* �J�����ʂ܂ł̐�������     */float       Find_DistToCameraPlane (D3DXVECTOR3 pos);
/* �x�N�g���̖@��             */D3DXVECTOR3 Find_VecNor            (D3DXVECTOR3 start1, D3DXVECTOR3 end1, D3DXVECTOR3 start2, D3DXVECTOR3 end2);
/*---------�͈͓�����---------*/								    
/* �p�x                       */void        Limit_Angle            (float *pAngle);
/*---------���[�v����---------*/								    
/* ����                       */void        Cycle_Control          (D3DXVECTOR3* pRot);
/*------------�ϊ�------------*/								   
/* �p�x�������l               */float       Conv_AngleToDir        (float fAngle, int nDiv);
/* �ʒu�������낵�(Z��Y)   */D3DXVECTOR3 Conv_LookDownPos       (D3DXVECTOR3 pos);
/* �����������낵�(Z��Y)   */D3DXVECTOR3 Conv_LookDownRot       (D3DXVECTOR3 rot);
/*-----------���̑�-----------*/
/* �����_���ȃx�N�g�����擾   */D3DXVECTOR3 vecRand(void);

#endif