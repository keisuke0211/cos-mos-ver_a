//========================================
// 
// �t�@�C���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#ifndef _FILE_H_
#define _FILE_H_

//****************************************
// �N���X��`
//****************************************
class CFile {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class SCAN {
		INT,
		FLOAT,
		FLOAT2D,
		CAHR,
		STRING,
		STRING_DYNAMIC,
		BOOL,
		POS2D,
		POS3D,
		ROT,
		ROT_CORRECT,
		COLOR,
		TEXIDX,
		MODELIDX,
		MODELSUIDX,
		MOTION3DIDX,
	};

	//========== [[[ �֐��錾 ]]]
	      CFile                   ();
		  ~CFile                  ();
	FILE* GetFile                 (void) { return files[fileNum-1]; }
	char* GetSearchString         (void) { return searchString; }
	bool  GetSelectOpenFileName   (char* fileName, const char* initDir, const char* fileType);
	bool  GetSelectSaveFileName   (char* fileName, const char* initDir, const char* fileType);
	char* ConvPathToDataStartPath (const char* path);
	bool  OpenLoadFile            (const char* path);
	bool  OpenSaveFile            (const char* path);
	void  CloseFile               (void);
	bool  SearchLoop              (const char* endIdentifier);
	void  Scan                    (const SCAN scan, void* data, const char* identifier = NULL);
	void  ScanCSV                 (const SCAN scan, void* data, bool isEnd = false);
	bool  CheckIdentifier         (const char* identifier) { return (strcmp(searchString, identifier) == 0); }
	bool  CheckIdentifierPartial  (const char* identifier) { return (strncmp(searchString, identifier, strlen(identifier)) == 0); }
	void  NewLine                 (void)                   { fscanf(files[fileNum-1], "%s\n", searchString); }

private:
	//========== [[[ �֐��錾 ]]]
	void ScanExecution(const SCAN scan, void* data, bool isCSV, bool isEnd);

	//========== [[[ �ϐ��錾 ]]]
	FILE** files;
	int    fileNum;
	char   searchString[TXT_MAX];
};

#endif