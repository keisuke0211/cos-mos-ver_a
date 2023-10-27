//========================================
// 
// ��Ԋ֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#pragma once

//****************************************
// �N���X��`
//****************************************
// ��ԃN���X
class CEase {
public:
	//========== [[[ �񋓌^��` ]]]
	// ���
	enum class TYPE {
		LINEAR,
		IN_SINE,
		OUT_SINE,
		INOUT_SINE,
		MAX,
	};

	//========== [[[ �֐��錾 ]]]
	static float Easing(const TYPE& ease, const int& base, const int& max);
	static float Easing(const TYPE& ease, const float& base, const float& max);
};