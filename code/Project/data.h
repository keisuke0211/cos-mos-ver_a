//========================================
// 
// �f�[�^�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// [[[ data.h ]]]
//========================================
#ifndef _DATA_H_
#define _DATA_H_

//****************************************
// �N���X��`
//****************************************
// �f�[�^�N���X
class CData {
public:
	//========== [[[ �֐��錾 ]]]
	CData() {
		m_highCoin = 0;
	}
	~CData() {}
	bool SetHighCoin(int coin) {
		if (m_highCoin < coin) {
			m_highCoin = coin;
			return true;
		}
		return false;
	}
	int  GetHighCoin(void) { return m_highCoin; }

private:
	//========== [[[ �ϐ��錾 ]]]
	int m_highCoin;
};

#endif