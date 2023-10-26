//========================================
// 
// �f�t�H���g�f�[�^�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// �f�t�H���g�f�[�^�N���X
class CDefaultData {
public:
	//========== [[[ �񋓌^��` ]]]
	enum class MODEL { PRUFEN_HEAD, MAX, };

	//========== [[[ �֐��錾 ]]]
	CDefaultData();
	~CDefaultData();
	void Init(void);
	UShort& GetModelIdx(const MODEL& model) { return m_modelIdxes[(int)model]; }

private:
	//========== [[[ �萔�錾 ]]]
	static const char* MODEL_PATH[(int)MODEL::MAX];

	//========== [[[ �ϐ��錾 ]]]
	UShort m_modelIdxes[(int)MODEL::MAX];
};
