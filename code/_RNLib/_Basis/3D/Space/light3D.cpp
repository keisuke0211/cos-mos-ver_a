//========================================
// 
// ��3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ light3D.cpp ]]]
//========================================
#include "../../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define AMBIENTLIGHTDATA_PATH "data\\_RNData\\AmbientLight.txt"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CLight3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CLight3D::CLight3D() {
	m_pAmbient = NULL;
	m_col      = INITCOLOR;
	m_nSetNum  = 0;
}

//========================================
// �f�X�g���N�^
// Author:RIKU NISHIMURA
//========================================
CLight3D::~CLight3D() {

}

//========================================
// ����������
// Author:RIKU NISHIMURA
//========================================
void CLight3D::Init(void) {

	if (!RNLib::File()->OpenLoadFile(AMBIENTLIGHTDATA_PATH))
	{// �����f�[�^�t�@�C�����J���Ȃ������ꍇ�A�������I������
		RNLib::Window()->Message("�����f�[�^�t�@�C�����J���܂���ł����B", "���s");
		return;
	}

	// �ǂݍ��݃��[�v
	while (RNLib::File()->SearchLoop("END")) {
		if (false) {}
		else if (RNLib::File()->CheckIdentifier("LIGHTSET{")) {
			// �ݒ萔��ǂݍ��݁A���̕������ݒ���̃��������m�ۂ���
			RNLib::File()->Scan(CFile::SCAN::INT,&m_nSetNum);
			m_pAmbient = new AmbientLight[m_nSetNum];

			// �����̃J�E���g
			int nCntLight = 0;

			while (RNLib::File()->SearchLoop("}")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier("LIGHT{")) {
					m_pAmbient[nCntLight] = {};

					while (RNLib::File()->SearchLoop("}")) {
						if (false) {}
						else if (RNLib::File()->CheckIdentifier("ROT:"))        { RNLib::File()->Scan(CFile::SCAN::POS3D, &m_pAmbient[nCntLight].rot); }
						else if (RNLib::File()->CheckIdentifier("BRIGHTNESS:")) { RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_pAmbient[nCntLight].fBrightness); }
					}

					// �J�E���g�̌���ݒ肷��
					SetLight(nCntLight);

					nCntLight++;	// �J�E���g�����Z
				}
			}
		}
		else if (RNLib::File()->CheckIdentifier("FOGSET{")) {
			while (RNLib::File()->SearchLoop("}")) {
				if (false) {}
				else if (RNLib::File()->CheckIdentifier("DIST_START:")) { 
					float fDistStart = 0.0f;
					RNLib::File()->Scan(CFile::SCAN::FLOAT, &fDistStart);
					RNLib::Fog()->SetDistStart(fDistStart);
				}
				else if (RNLib::File()->CheckIdentifier("DIST_END:"  )) {
					float fDistEnd = 0.0f;
					RNLib::File()->Scan(CFile::SCAN::FLOAT, &fDistEnd);
					RNLib::Fog()->SetDistEnd(fDistEnd);
				}
			}
		}
	}

	// �t�@�C�������
	RNLib::File()->CloseFile();
}

//========================================
// �����ݒ����ۑ�
// Author:RIKU NISHIMURA
//========================================
void CLight3D::SaveAmbientLight(void) {
	
	if (!RNLib::File()->OpenSaveFile(AMBIENTLIGHTDATA_PATH))
	{// �����f�[�^�t�@�C�����J���Ȃ������ꍇ�A�������I������
		RNLib::Window()->Message("�����f�[�^�t�@�C�����J���܂���ł����B", "���s");
		return;
	}

	FILE* pFile = RNLib::File()->GetFile();
	fprintf(pFile, "LIGHTSET{ %d\n", m_nSetNum);
	for (int nCntLight = 0; nCntLight < m_nSetNum; nCntLight++) {
		fprintf(pFile, "	LIGHT{\n");
		fprintf(pFile, "		ROT: %f %f %f\n", m_pAmbient[nCntLight].rot.x, m_pAmbient[nCntLight].rot.y, m_pAmbient[nCntLight].rot.z);
		fprintf(pFile, "		BRIGHTNESS: %f\n", m_pAmbient[nCntLight].fBrightness);
		fprintf(pFile, "	}\n");
	}
	fprintf(pFile, "}\n");

	fprintf(pFile, "FOGSET{\n");
	fprintf(pFile, "	DIST_START: %f\n", RNLib::Fog()->GetDistStart());
	fprintf(pFile, "	DIST_END: %f\n", RNLib::Fog()->GetDistEnd());
	fprintf(pFile, "}\n");

	fprintf(pFile, "END\n");

	// �t�@�C�������
	RNLib::File()->CloseFile();

	// �ۑ��������b�Z�[�W
	RNLib::Window()->Message("�����f�[�^�t�@�C����ۑ����܂����B", "");
}

//========================================
// �I������
// Author:RIKU NISHIMURA
//========================================
void CLight3D::Uninit(void) {
	// �����ݒ���̔j��
	delete[] m_pAmbient;
	m_pAmbient = NULL;
}

//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CLight3D::Update(void) {

}

//========================================
// �F�ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void CLight3D::SetCol(Color col) {
	m_col = col;

	for (int nCntLight = 0; nCntLight < m_nSetNum; nCntLight++) {
		SetLight(nCntLight);
	}
}

//========================================
// ���ݒ�
// Author:RIKU NISHIMURA
//========================================
void CLight3D::SetNum(int nNum) {
	if (m_nSetNum == nNum)
		return;

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();

	// �����g�p����Ȃ�����S�Ė����ɂ���
	for (int nCntLight = nNum; nCntLight < m_nSetNum; nCntLight++) {
		pDevice->LightEnable(nCntLight, FALSE);
	}
	
	// �ߋ��̐��Ƃ��ĕۑ����Ă���
	int nNumOld = m_nSetNum;

	// �ݒ萔����
	m_nSetNum = nNum;

	{// �����̃������Ċm��
		AmbientLight* pNew = new AmbientLight[m_nSetNum];
		int nCopySize = m_nSetNum < nNumOld ? m_nSetNum : nNumOld;
		if (nCopySize > 0) {
			memcpy(pNew, m_pAmbient, sizeof(AmbientLight) * nCopySize);
			delete[] m_pAmbient;
		}
		m_pAmbient = pNew;
	}
}

//========================================
// ����ݒ肷��
// Author:RIKU NISHIMURA
//========================================
void CLight3D::SetLight(int nIdx) {
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();

	// ��3D�̏����N���A���A��ނ�ݒ�
	D3DLIGHT9 light3D;
	ZeroMemory(&light3D, sizeof(D3DLIGHT9));
	light3D.Type = D3DLIGHT_DIRECTIONAL;

	// �g�U���ƕ�����ݒ�
	light3D.Diffuse = ColorToD3DXCOLOR(BrightnessToColor(m_col, m_pAmbient[nIdx].fBrightness));
	light3D.Direction = Find_RotVec(m_pAmbient[nIdx].rot);

	// ���̏���ݒ肵�A�L���ɂ���
	pDevice->SetLight(nIdx, &light3D);
	pDevice->LightEnable(nIdx, TRUE);
}