//========================================
// 
// �Q�[�����[�h�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ game-mode.h ]]]
//========================================
#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_

//****************************************
// �N���X��`
//****************************************
// �Q�[�����[�h�N���X
class CGameMode {
public:
	//========== [[[ �֐��錾 ]]]
	CGameMode();
	virtual ~CGameMode();
	virtual void Init  (void) = 0;
	virtual void Uninit(void) = 0;
	virtual void UninitScene(void) = 0;
	virtual void Update(void) = 0;
	virtual void Load  (void) = 0;
	virtual void Save  (void) = 0;
};

#endif