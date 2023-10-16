//========================================
// 
// �T�E���h����
// Author :AKIRA TANAKA
// Arrange:RIKU NISHIMURA
// 
//========================================
// [[[ sound.cpp ]]]
//========================================
#include "../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define DATAFILE_PATH "data\\_RNData\\SoundList.txt"	// �T�E���h�̃f�[�^�t�@�C���p�X

//****************************************
// �萔��`
//****************************************
namespace {
	// �T�E���h��
	const char* c_aSoundName[] = {
		"DIGBUG",
		"DIGBUG_BOSS",
		"MENU_SELECT",
		"MENU_DECIDE",
		"MENU_BACK",
		"SCORE_COUNT",
		"GOLD_COUNT",
		"ITEM_GET",
		"GAMECLEAR",
		"GAMEOVER",
		"TAKE_AIM",
		"BLOW_DAMAGE_LOW",
		"BLOW_DAMAGE_MID",	
		"BLOW_DAMAGE_HIGH",
		"SLASH_DAMAGE_LOW",
		"SLASH_DAMAGE_MID",
		"SLASH_DAMAGE_HIGH",
		"SPC_DAMAGE_LOW",	
		"SPC_DAMAGE_MID",	
		"ELEM_DAMAGE_FIRE",
		"ELEM_DAMAGE_WATER",
		"ELEM_DAMAGE_ICE",	
		"ELEM_DAMAGE_WIND",
		"ELEM_DAMAGE_ELEC",
		"ELEM_DAMAGE_SOIL",
		"ELEM_DAMAGE_DARK",
		"ELEM_DAMAGE_LIGHT",
		"IMPACT_MID",
		"BREATH_LOW",
		"BREATH_MID",
		"BREATH_HIGH",
		"BREATH_SHOT",
		"LANDING_GRASS",
		"LANDING_SOIL",
		"LANDING_STONE",
		"LANDING_SAND",
		"LANDING_IMPACT",
		"EARTHQUAKE",
		"BREAK_SOIL",
		"BREAK_STONE",
		"EXPLOSION_MID",
		"SWING_LOW",
		"SWING_MID",
		"SWING_HIGH",
		"METAL_STRIKE",
		"MOTOR",
	};

	// ����
	const float c_aDistance[] = {
		0.0f,
		50.0f,
		250.0f,
		500.0f,
		1000.0f,
	};
}
CHECK_ARRAY_SIZE(c_aSoundName, CSound::MAX);
CHECK_ARRAY_SIZE(c_aDistance , CSound::DISTANCE_MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| Sound�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CSound::CSound() {
	m_pXAudio2        = NULL;
	m_pMasteringVoice = NULL;
	m_mic3DPos        = INITD3DXVECTOR3;
	
	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
		for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
			m_apSourceVoice[nCntSound][nCntPlay] = NULL;
			m_aState       [nCntSound][nCntPlay] = {};
		}

		m_apDataAudio[nCntSound] = NULL;
		m_aSizeAudio [nCntSound] = NULL;							
	}

	for (int nCntCategory = 0; nCntCategory < (int)CATEGORY::MAX; nCntCategory++) {
		m_aCategoryVolume[nCntCategory] = 0.0f;
		m_aSettingVolume [nCntCategory] = 0.0f;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CSound::~CSound() {

}

//========================================
// ����������
//========================================
HRESULT CSound::Init(void) {
	HWND hWnd = RNLib::Window()->GetHandle();

	for (int nCntCategory = 0; nCntCategory < (int)CATEGORY::MAX; nCntCategory++) {
		m_aCategoryVolume[nCntCategory] = 1.0f;
		m_aSettingVolume [nCntCategory] = 1.0f;
	}

	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr)) {
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr)) {
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// XAudio2�I�u�W�F�N�g�̊J��
		if (m_pXAudio2 != NULL) {
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
		HANDLE hFile;
		DWORD dwChunkSize     = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFilecategory;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aData[nCntSound].aFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			char aString[TXT_MAX];
			sprintf(aString, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1) (�J�E���g%d)", nCntSound);
			MessageBox(hWnd, aString, "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		hr = ReadChunkData(hFile, &dwFilecategory, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		if (dwFilecategory != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr)) {
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr)) {
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr)) {
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr)) {
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
			// �\�[�X�{�C�X�̐���
			hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound][nCntPlay], &(wfx.Format));
			if (FAILED(hr)) {
				MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
				return S_FALSE;
			}

			// �I�[�f�B�I�o�b�t�@�̓o�^
			m_apSourceVoice[nCntSound][nCntPlay]->SubmitSourceBuffer(&buffer);
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aData[nCntSound].nCntLoop;

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//========================================
// �I������
//========================================
void CSound::Uninit(void) {
	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
		for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
			if (m_apSourceVoice[nCntSound][nCntPlay] != NULL) {
				m_apSourceVoice[nCntSound][nCntPlay]->Stop(0);

				// �\�[�X�{�C�X�̔j��
				m_apSourceVoice[nCntSound][nCntPlay]->DestroyVoice();
				m_apSourceVoice[nCntSound][nCntPlay] = NULL;
			}

			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	// XAudio2�I�u�W�F�N�g�̊J��
	if (m_pXAudio2 != NULL) {
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//========================================
// �X�V����
//========================================
void CSound::Update(void) {
	XAUDIO2_VOICE_STATE xa2state;

	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
		for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
			State& state = m_aState[nCntSound][nCntPlay];

			if (!state.bPlay)
				continue;
			
			m_apSourceVoice[nCntSound][nCntPlay]->GetState(&xa2state);

			if (xa2state.BuffersQueued == 0)
			{// �Đ����łȂ����A
				state.bPlay = false;

				// ��~���A�I�[�f�B�I�o�b�t�@�̍폜
				m_apSourceVoice[nCntSound][nCntPlay]->Stop(0);
				m_apSourceVoice[nCntSound][nCntPlay]->FlushSourceBuffers();

				continue;
			}

			switch (state.space) {
			case SPACE_3D: {
				float fRate = 1.0f - (Find_Dist(state.pos, m_mic3DPos) / c_aDistance[state.dist]);
				if (fRate <= 0.0f) {
					m_apSourceVoice[nCntSound][nCntPlay]->SetVolume(0.0f);
					break;
				}
				else if (fRate > 1.0f)
					fRate = 1.0f;

				m_apSourceVoice[nCntSound][nCntPlay]->SetVolume(
					m_aData[nCntSound].fVolume *
					m_aCategoryVolume[(int)m_aData[nCntSound].category] *
					m_aSettingVolume [(int)m_aData[nCntSound].category] *
					fRate);
			}break;
			}
		}
	}
}

//========================================
// �ǂݍ��ݏ���
//========================================
void CSound::Load(void) {
	if (!RNLib::File()->OpenLoadFile(DATAFILE_PATH))
		return;

	// �ǂݍ��݃��[�v
	while (RNLib::File()->SearchLoop("END")) {
		if (RNLib::File()->CheckIdentifier("BGM{")) {
			while (RNLib::File()->SearchLoop("}")) {
				for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
					if (RNLib::File()->CheckIdentifier(CreateText("%s:", c_aSoundName[nCntSound]))) {
						m_aData[nCntSound].category = CATEGORY::BGM;
						RNLib::File()->Scan(CFile::SCAN::STRING,  m_aData[nCntSound].aFileName);
						RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_aData[nCntSound].fVolume);
						RNLib::File()->Scan(CFile::SCAN::INT, &m_aData[nCntSound].nCntLoop);
						break;
					}
				}
			}
		}
		else if (RNLib::File()->CheckIdentifier("SE{")) {
			while (RNLib::File()->SearchLoop("}")) {
				for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
					if (RNLib::File()->CheckIdentifier(CreateText("%s:", c_aSoundName[nCntSound]))) {
						m_aData[nCntSound].category = CATEGORY::SE;
						RNLib::File()->Scan(CFile::SCAN::STRING,  m_aData[nCntSound].aFileName);
						RNLib::File()->Scan(CFile::SCAN::FLOAT, &m_aData[nCntSound].fVolume);
						RNLib::File()->Scan(CFile::SCAN::INT, &m_aData[nCntSound].nCntLoop);
						break;
					}
				}
			}
		}
	}

	RNLib::File()->CloseFile();
}

//========================================
// �`�����N�̃`�F�b�N
//========================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition) {
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK) {
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType) {
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format) {
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize) {
			return S_FALSE;
		}
	}

	return S_OK;
}

//========================================
// �`�����N�f�[�^�̓ǂݍ���
//========================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset) {
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//========================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//========================================
int CSound::Play(int nSoundIdx, SPACE space, D3DXVECTOR3 pos, DISTANCE dist) {
	if (nSoundIdx < 0 || nSoundIdx >= MAX)
		return DATANONE;

	// BGM���������ABGM���ꊇ��~����
	if (m_aData[nSoundIdx].category == CATEGORY::BGM)
		Stop(CATEGORY::BGM);

	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER      buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[nSoundIdx];
	buffer.pAudioData = m_apDataAudio[nSoundIdx];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aData[nSoundIdx].nCntLoop;
	
	int nCntPlay = 0;
	for (; nCntPlay < PLAY_MAX; nCntPlay++) {
		State& state = m_aState[nSoundIdx][nCntPlay];

		// �Đ����̎��A������܂�Ԃ�
		if (state.bPlay)
			continue;

		state.bPlay = true;
		state.space = space;
		state.pos   = pos;
		state.dist  = dist;

		// ��Ԏ擾
		m_apSourceVoice[nSoundIdx][nCntPlay]->GetState(&xa2state);

		if (xa2state.BuffersQueued != 0)
		{// �Đ����̎��A��~���A�I�[�f�B�I�o�b�t�@���폜
			m_apSourceVoice[nSoundIdx][nCntPlay]->Stop(0);
			m_apSourceVoice[nSoundIdx][nCntPlay]->FlushSourceBuffers();
		}

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nSoundIdx][nCntPlay]->SubmitSourceBuffer(&buffer);

		// ���ʂ�ݒ�
		if (state.space == SPACE_NONE) {
			m_apSourceVoice[nSoundIdx][nCntPlay]->SetVolume(
				m_aData[nSoundIdx].fVolume *
				m_aCategoryVolume[(int)m_aData[nSoundIdx].category] *
				m_aSettingVolume [(int)m_aData[nSoundIdx].category]);
		}
		else {
			m_apSourceVoice[nSoundIdx][nCntPlay]->SetVolume(0.0f);
		}

		// �Đ�
		m_apSourceVoice[nSoundIdx][nCntPlay]->Start(0);

		break;
	}

	if (nCntPlay >= PLAY_MAX)
		return DATANONE;

	return (nSoundIdx * PLAY_MAX) + nCntPlay;
}

//========================================
// �ʒu�ݒ�
//========================================
void CSound::SetPos(int nID, D3DXVECTOR3 pos) {
	int nSoundIdx = nID / PLAY_MAX;
	int nPlayIdx  = nID % PLAY_MAX;

	m_aState[nSoundIdx][nPlayIdx].pos = pos;
}

//========================================
// �Z�O�����g��~(���x���w��)
//========================================
int CSound::Stop(int nID) {
	int nSoundIdx = nID / PLAY_MAX;
	int nPlayIdx  = nID % PLAY_MAX;

	if (m_apSourceVoice[nSoundIdx][nPlayIdx] == NULL)
		return DATANONE;

	// ��Ԏ擾
	XAUDIO2_VOICE_STATE xa2state;
	m_apSourceVoice[nSoundIdx][nPlayIdx]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_apSourceVoice[nSoundIdx][nPlayIdx]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[nSoundIdx][nPlayIdx]->FlushSourceBuffers();
	}

	return DATANONE;
}

//========================================
// �Z�O�����g��~(��ގw��)
//========================================
void CSound::Stop(TYPE type) {
	for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
		if (m_apSourceVoice[type][nCntPlay] == NULL)
			return;

		// ��Ԏ擾
		XAUDIO2_VOICE_STATE xa2state;
		m_apSourceVoice[type][nCntPlay]->GetState(&xa2state);
		if (xa2state.BuffersQueued != 0)
		{// �Đ���
			// �ꎞ��~
			m_apSourceVoice[type][nCntPlay]->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			m_apSourceVoice[type][nCntPlay]->FlushSourceBuffers();
		}
	}
}

//========================================
// �Z�O�����g��~(���J�e�S���[�w��)
//========================================
void CSound::Stop(CATEGORY category) {
	XAUDIO2_VOICE_STATE xa2state;

	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
		if (m_aData[nCntSound].category == category)
		{// �T�E���h�̕��ނ���v�������A
			for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
				// ��Ԏ擾
				m_apSourceVoice[nCntSound][nCntPlay]->GetState(&xa2state);

				if (xa2state.BuffersQueued != 0)
				{// �Đ����̎��A��~���A�I�[�f�B�I�o�b�t�@���폜
					m_apSourceVoice[nCntSound][nCntPlay]->Stop(0);
					m_apSourceVoice[nCntSound][nCntPlay]->FlushSourceBuffers();
				}
			}
		}
	}
}

//========================================
// �Z�O�����g��~(�S��)
//========================================
void CSound::Stop(void) {
	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {
		for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
			if (m_apSourceVoice[nCntSound][nCntPlay] != NULL) {
				m_apSourceVoice[nCntSound][nCntPlay]->Stop(0);
			}
		}
	}
}

//========================================
// ���ޖ��ɉ��ʕύX
//========================================
void CSound::TypeVolumeChange(CATEGORY category, float fVolume) {
	// ���ʂ𐧌�
	if (fVolume <= 0.0f) {
		fVolume = 0.0f;
	}
	else if (fVolume >= 1.0f) {
		fVolume = 1.0f;
	}

	// ���ʂ�ݒ�
	m_aCategoryVolume[(int)category] = fVolume;

	for (int nCntSound = 0; nCntSound < MAX; nCntSound++) {

		if (m_aData[nCntSound].category == category)
		{// �T�E���h�̕��ނ���v�������A
			for (int nCntPlay = 0; nCntPlay < PLAY_MAX; nCntPlay++) {
				// ���ʂ�ݒ�
				m_apSourceVoice[nCntSound][nCntPlay]->SetVolume(m_aData[nCntSound].fVolume * m_aCategoryVolume[(int)category] * m_aSettingVolume[(int)category]);
			}
		}
	}
}

//========================================
// �ݒ艹�ʂ�ݒ�
//========================================
void CSound::SetSettingVolume(CATEGORY category) {
	// ���ނɉ������ݒ艹�ʂ��擾
	if (category == CATEGORY::BGM) {
		m_aSettingVolume[(int)category] = 1.0f;	// ToDo:�ݒ菈���ǉ������炻������擾����悤�ɂ��� (float)GetSetting()->nBGMVolume / (float)VOLUME_STAGE;
	}
	else if (category == CATEGORY::SE) {
		m_aSettingVolume[(int)category] = 1.0f;	// ToDo:�ݒ菈���ǉ������炻������擾����悤�ɂ���
	}

	// ���ޖ��ɉ��ʂ�K�p
	TypeVolumeChange(category, m_aCategoryVolume[(int)category]);
}