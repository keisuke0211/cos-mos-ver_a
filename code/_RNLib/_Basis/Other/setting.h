//========================================
// 
// �ݒ�̏����̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ setting.h ]]]
//========================================
#ifndef _SETTING_H_
#define _SETTING_H_

//****************************************
// �}�N����`
//****************************************
// ���ʂ̒i�K
#define VOLUME_STAGE	(20)

//****************************************
// �\���̒�`
//****************************************
// �ݒ�̏��\����
typedef struct
{
	int nBGMVolume;		// BGM����
	int nSEVolume;		// SE����
	bool bVibration;	// �U���t���O
	bool bFullScreen;	// �S��ʃt���O
}Setting;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== [[[ ��{�ڑ� ]]]
// �ݒ�̏���������
void InitSetting(void);
// �ݒ�̏I������
void UninitSetting(void);
// �ݒ�̍X�V����
void UpdateSetting(void);
// �ݒ胁�j���[�̍X�V����
void UpdateSettingMenu(void);
//========== [[[ ���o�� ]]]
// �ݒ�̓ǂݍ��ݏ���
void LoadSetting(void);
// �ݒ�̏������ݏ���
void SaveSetting(void);
//========== [[[ �擾 ]]]
// �ݒ�̏����擾
Setting *GetSetting(void);
// �ݒ蒆�t���O���擾
bool *GetSettingNow(void);
//========== [[[ �ݒ� ]]]
// �ݒ胁�j���[�̐ݒ菈��
void SetSettingMenu(void);

#endif