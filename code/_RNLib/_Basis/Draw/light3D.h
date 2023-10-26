//========================================
// 
// ��3D�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ light3D.h ]]]
//========================================
#ifndef _LIGHT3D_H_
#define _LIGHT3D_H_

//****************************************
// �N���X��`
//****************************************
// ��3D�N���X
class CLight3D {
public:
	//========== [[[ �֐��錾 ]]]
	CLight3D();
	~CLight3D();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCol(Color col);
	Color GetCol(void) { return m_col; }
	// ��������
	void         SetNum          (int nNum);
	int          GetNum          (void)                        { return m_nSetNum; }
	void         SetVec          (int nIdx, D3DXVECTOR3 rot)   { m_pAmbient[nIdx].rot = rot; SetLight(nIdx); }
	D3DXVECTOR3& GetVec          (int nIdx)                    { return m_pAmbient[nIdx].rot; }
	void         SetBrightness   (int nIdx, float fBrightness) { m_pAmbient[nIdx].fBrightness = fBrightness; SetLight(nIdx); }
	float&       GetBrightness   (int nIdx)                    { return m_pAmbient[nIdx].fBrightness; }
	void         SaveAmbientLight(void);
	void         SetLight        (int nIdx);

private:
	//========== [[[ �\���̒�` ]]]
	// �������\����
	typedef struct AmbientLight_ {
		D3DXVECTOR3 rot         = INITD3DXVECTOR3;
		float       fBrightness = 1.0f;
	}AmbientLight;

	//========== [[[ �ϐ��錾 ]]]
	AmbientLight* m_pAmbient;
	Color         m_col;
	int           m_nSetNum;
};

#endif