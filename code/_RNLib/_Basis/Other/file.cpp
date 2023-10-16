//========================================
// 
// �t�@�C���֘A�̏���
// 
//========================================
#include "../../RNlib.h"

//****************************************
// �萔��`
//****************************************
namespace {
	const char* c_anchorNames[] = {
		"NONE" ,
		"CENTER","TOP"     ,"BOTTOM"     ,
		"LEFT"  ,"LEFTTOP" ,"LEFTBOTTOM" ,
		"RIGHT" ,"RIGHTTOP","RIGHTBOTTOM",
	};
}
CHECK_ARRAY_SIZE(c_anchorNames, (int)ANCHOR::MAX);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| CFile�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CFile::CFile() {
	files = NULL;
	fileNum = 0;
	strcpy(searchString, "");
}

//========================================
// �f�X�g���N�^
//========================================
CFile::~CFile() {

}

//========================================
// �I�������J���t�@�C�����擾
//========================================
bool CFile::GetSelectOpenFileName(char* resultFileName, const char* initDir, const char* fileType) {

	TCHAR        fileName[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lpstrTitle      = "�J��";				// �E�B���h�E�̃^�C�g���w��
	ofn.lStructSize     = sizeof(ofn);			// �\���̂̃T�C�Y�w��
	ofn.lpstrFile       = fileName;				// �I�����ꂽ�t�@�C�������i�[�����z��w��
	ofn.lpstrFile[0]    = '\0';					// �t�@�C����������
	ofn.nMaxFile        = sizeof(fileName);		// lpstrFile �z��̍ő�T�C�Y���t�@�C�����i�[�p������̃T�C�Y�Ŏw��
	ofn.lpstrFilter     = fileType;				// �I���ł���t�@�C���̎�ނ��w��
	ofn.nFilterIndex    = 1;					// �����I������Ă���t�B���^�̃C���f�b�N�X���w��
	ofn.lpstrFileTitle  = NULL;					// �I�����ꂽ�t�@�C���̃^�C�g�����w��(�g�p����Ȃ��ꍇ��NULL)
	ofn.nMaxFileTitle   = 0;					// lpstrFileTitle �̍ő�T�C�Y(�g�p����Ȃ��ꍇ��0)
	ofn.lpstrInitialDir = initDir;				// �����\������f�B���N�g��(�g�p����Ȃ��ꍇ��NULL)
	// �_�C�A���O�̃I�v�V�������w��
	// OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST �́A�I�����ꂽ�p�X�����݂��邱�ƂƁA�I�����ꂽ�t�@�C�������݂��邱�Ƃ��m�F�������
	// OFN_NOCHANGEDIR �́A�f�B���N�g����ύX���Ȃ��悤�ɂ������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	// �J�����t�@�C�������擾�o�������A
	if (GetOpenFileName(&ofn)) {
		if (!strcmp(fileName, ""))
			return false;
		sprintf(resultFileName, fileName);
		RNLib::Input()->Clear();
	}
	else {
		RNLib::Input()->Clear();
		return false;
	}

	return true;
}

//========================================
// �I�������J���t�@�C�����擾
//========================================
bool CFile::GetSelectSaveFileName(char* resultFileName, const char* initDir, const char* fileType) {

	TCHAR        fileName[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lpstrTitle      = "���O��t���ĕۑ�";	// �E�B���h�E�̃^�C�g���w��
	ofn.lStructSize     = sizeof(ofn);			// �\���̂̃T�C�Y�w��
	ofn.lpstrFile       = fileName;				// �I�����ꂽ�t�@�C�������i�[�����z��w��
	ofn.lpstrFile[0]    = '\0';					// �t�@�C����������
	ofn.nMaxFile        = sizeof(fileName);		// lpstrFile �z��̍ő�T�C�Y���t�@�C�����i�[�p������̃T�C�Y�Ŏw��
	ofn.lpstrFilter     = fileType;				// �I���ł���t�@�C���̊g���q���w��
	ofn.nFilterIndex    = 1;					// �����I������Ă���t�B���^�̃C���f�b�N�X���w��
	ofn.lpstrFileTitle  = NULL;					// �I�����ꂽ�t�@�C���̃^�C�g�����w��(�g�p����Ȃ��ꍇ��NULL)
	ofn.nMaxFileTitle   = 0;					// lpstrFileTitle �̍ő�T�C�Y(�g�p����Ȃ��ꍇ��0)
	ofn.lpstrInitialDir = initDir;				// �����\������f�B���N�g��(�g�p����Ȃ��ꍇ��NULL)
	// �_�C�A���O�̃I�v�V�������w��
	// OFN_NOCHANGEDIR �́A�f�B���N�g����ύX���Ȃ��悤�ɂ������
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn))
	{// �J�����t�@�C�������擾�o�������A
		// �t�@�C�����̃|�C���^�ɓǂݍ��񂾃t�@�C�����������邪�A
		// �������g���q�ŏI����Ă��Ȃ����A����ɉ����Ċg���q��A��������
		int len = strlen(fileName);
		int extlen = strlen(fileType);
		if (len < extlen || strcmp(fileName + len - extlen, fileType) != 0)
			sprintf(resultFileName, "%s%s", fileName, fileType);
		else
			strcpy(resultFileName, fileName);

		RNLib::Input()->Clear();
		return true;
	}
	else {
		RNLib::Input()->Clear();
		return false;
	}
}

//========================================
// "data"���N�_�Ƃ����p�X������𐶐�����
//========================================
char* CFile::ConvPathToDataStartPath(const char* path) {

	static char dataStartPath[TXT_MAX] = "";

	// �p�X��data�f�B���N�g�����܂܂Ȃ��ꍇ�̓G���[
	if (strstr(path, "data\\") == NULL) {
		RNLib::Window()->Message(CreateText("\"%s\" does not contain \"data\\\" directory.\n", path), "Error");
		return NULL;
	}

	// data�f�B���N�g���̒���̕�������R�s�[����
	const char *start = strstr(path, "data\\");
	strncpy(dataStartPath, start, TXT_MAX);
	dataStartPath[TXT_MAX - 1] = '\0'; // NULL�I�[��t��

	return dataStartPath;
}

//========================================
// �f�[�^�t�@�C�����J��(�ǂݍ���)
//========================================
bool CFile::OpenLoadFile(const char* path) {

	int fileNumOld = fileNum++;
	RNLib::Memory()->ReAlloc<FILE*>(&files, fileNumOld, fileNum);
	files[fileNumOld] = fopen(path, "r");
	if (files[fileNumOld] == NULL) {
		assert(false);
		RNLib::Memory()->ReAlloc<FILE*>(&files, fileNum, fileNumOld);
		return false;
	}

	return true;
}

//========================================
// �f�[�^�t�@�C�����J��(�����o��)
//========================================
bool CFile::OpenSaveFile(const char* path) {

	int fileNumOld = fileNum++;
	RNLib::Memory()->ReAlloc<FILE*>(&files, fileNumOld, fileNum);
	files[fileNumOld] = fopen(path, "w");
	if (files[fileNumOld] == NULL) {
		assert(false);
		RNLib::Memory()->ReAlloc<FILE*>(&files, fileNum, fileNumOld);
		return false;
	}

	return true;
}

//========================================
// �f�[�^�t�@�C�������
//========================================
void CFile::CloseFile(void) {

	if (fileNum <= 0)
		return;

	if (files[fileNum-1] != NULL) {
		fclose(files[fileNum-1]);
		fileNum--;
		RNLib::Memory()->ReAlloc<FILE*>(&files, fileNum + 1, fileNum);
	}
}

//========================================
// �������[�v
//========================================
bool CFile::SearchLoop(const char* endIdentifier) {

	if (files == NULL)
		return false;

	strcpy(searchString, "");
	fscanf(files[fileNum-1], "%s", searchString);

	return (strcmp(searchString, endIdentifier) != 0);
}

//========================================
// �ǂݎ�菈��
//========================================
void CFile::Scan(const SCAN scan, void* data, const char* identifier) {

	// ���ʎq���݂鎞�A���ʎq�ƕs��v�Ȃ�I��
	if (identifier != NULL) {
		if (strcmp(searchString, identifier))
			return;
	}

	// �ǂݎ����s
	ScanExecution(scan, data, false, false);
}

//========================================
// �ǂݎ�菈��(CSV)
//========================================
void CFile::ScanCSV(const SCAN scan, void* data, bool isEnd) {

	// �ǂݎ����s
	ScanExecution(scan, data, true, isEnd);
}

//========================================
// �ǂݎ�菈��(���s����)
//========================================
void CFile::ScanExecution(const SCAN scan, void* data, bool isCSV, bool isEnd) {

	searchString;

	switch (scan) {
	case SCAN::INT: {
		int* castData = (int*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%d ", castData);
		else
			fscanf(files[fileNum-1], "%d,", castData);
	}break;
	case SCAN::FLOAT: {
		float* castData = (float*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%f ", castData);
		else
			fscanf(files[fileNum-1], "%f,", castData);
	}break;
	case SCAN::FLOAT2D: {
		float* castData = (float*)data;
		ScanExecution(SCAN::FLOAT, castData, isCSV, isEnd);
		*castData *= PIXEL2D_SIZE;
	}break;
	case SCAN::CAHR: {
		char scanString[TXT_MAX];
		ScanExecution(SCAN::STRING, scanString, isCSV, isEnd);
		char* castData = (char*)data;
		*castData = scanString[0];
	}break;
	case SCAN::STRING: {
		char* castData = (char*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%s ", castData);
		else
			fscanf(files[fileNum-1], "%[^,],", castData);
	}break;
	case SCAN::STRING_DYNAMIC: {
		char scanString[TXT_MAX];
		ScanExecution(SCAN::STRING, scanString, isCSV, isEnd);
		StrCpyDynamicMemory((char**)data, scanString);
	}break;
	case SCAN::BOOL: {
		int temp;
		ScanExecution(SCAN::INT, &temp, isCSV, isEnd);
		bool* castData = (bool*)data;
		*castData = (temp != 0);
	}break;
	case SCAN::POS2D: {
		D3DXVECTOR3* castData = (D3DXVECTOR3*)data;
		fscanf(files[fileNum-1], "%f %f %f", &castData->x, &castData->y, &castData->z);
		*castData *= PIXEL2D_SIZE;

		// �A���J�[�ɉ����Ĉʒu�␳
		char aAnchor[TXT_MAX];
		ScanExecution(SCAN::STRING, aAnchor, isCSV, isEnd);
		int cntAnchor;
		for (cntAnchor = 0; cntAnchor < (int)ANCHOR::MAX; cntAnchor++) {
			if (strcmp(aAnchor, c_anchorNames[cntAnchor]))
				continue;

			switch ((ANCHOR)cntAnchor) {
			case ANCHOR::CENTER: {
				*castData += RNLib::Window()->GetCenterPos();
			}break;
			case ANCHOR::TOP: {
				castData->x += RNLib::Window()->GetCenterX();
			}break;
			case ANCHOR::BOTTOM: {
				castData->x += RNLib::Window()->GetCenterX();
				castData->y += RNLib::Window()->GetHeight();
			}break;
			case ANCHOR::LEFT: {
				castData->y += RNLib::Window()->GetCenterY();
			}break;
			case ANCHOR::LEFTTOP: {
			}break;
			case ANCHOR::LEFTBOTTOM: {
				castData->y += RNLib::Window()->GetHeight();
			}break;
			case ANCHOR::RIGHT: {
				castData->x += RNLib::Window()->GetWidth();
				castData->y += RNLib::Window()->GetCenterY();
			}break;
			case ANCHOR::RIGHTTOP: {
				castData->x += RNLib::Window()->GetWidth();
			}break;
			case ANCHOR::RIGHTBOTTOM: {
				castData->x += RNLib::Window()->GetWidth();
				castData->y += RNLib::Window()->GetHeight();
			}break;
			}

			break;
		}

		assert(cntAnchor < (int)ANCHOR::MAX);
	}break;
	case SCAN::POS3D: {
		D3DXVECTOR3* castData = (D3DXVECTOR3*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%f %f %f ", &castData->x, &castData->y, &castData->z);
		else
			fscanf(files[fileNum-1], "%f %f %f,", &castData->x, &castData->y, &castData->z);
	}break;
	case SCAN::ROT: {
		D3DXVECTOR3* castData = (D3DXVECTOR3*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%f %f %f ", &castData->x, &castData->y, &castData->z);
		else
			fscanf(files[fileNum-1], "%f %f %f,", &castData->x, &castData->y, &castData->z);
	}break;
	case SCAN::ROT_CORRECT: {
		D3DXVECTOR3* castData = (D3DXVECTOR3*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%f %f %f ", &castData->x, &castData->y, &castData->z);
		else
			fscanf(files[fileNum-1], "%f %f %f,", &castData->x, &castData->y, &castData->z);
		*castData *= D3DX_PI;
	}break;
	case SCAN::COLOR: {
		Color* castData = (Color*)data;
		if (!isCSV || isEnd)
			fscanf(files[fileNum-1], "%d %d %d %d ", &castData->r, &castData->g, &castData->b, &castData->a);
		else
			fscanf(files[fileNum-1], "%d %d %d %d,", &castData->r, &castData->g, &castData->b, &castData->a);
	}break;
	case SCAN::TEXIDX: {
		char texPath[TXT_MAX];
		ScanExecution(SCAN::STRING, texPath, isCSV, isEnd);
		int* castData = (int*)data;
		*castData = RNLib::Texture()->Load(texPath);
	}break;
	case SCAN::MODELIDX: {
		char modelPath[TXT_MAX];
		ScanExecution(SCAN::STRING, modelPath, isCSV, isEnd);
		int* castData = (int*)data;
		*castData = RNLib::Model()->Load(modelPath);
	}break;
	case SCAN::MODELSUIDX: {
		char modelSUPath[TXT_MAX];
		ScanExecution(SCAN::STRING, modelSUPath, isCSV, isEnd);
		int* castData = (int*)data;
		*castData = RNLib::ModelSetUp()->Load(modelSUPath);
	}break;
	case SCAN::MOTION3DIDX: {
		char motion3DPath[TXT_MAX];
		ScanExecution(SCAN::STRING, motion3DPath, isCSV, isEnd);
		int* castData = (int*)data;
		*castData = RNLib::Motion3D()->Load(motion3DPath);
	}break;
	}
}