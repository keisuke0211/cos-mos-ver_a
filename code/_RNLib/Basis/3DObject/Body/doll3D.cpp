//========================================
// 
// �h�[��3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNLib.h"

//****************************************
// �}�N����`
//****************************************
#define PAUSE_RESET_TIME (10)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�h�[��3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDoll3D::CDoll3D(void) {

	m_pos			       = INITPOS3D;
	m_rot			       = INITROT3D;
	m_scale                = INITSCALE3D;
	m_col                  = INITCOLOR;
	m_brightnessOfEmission = 1.0f;
	m_boneStates           = NULL;
	m_setUpIdx             = NONEDATA;
	m_motionInfo           = {};
}

//========================================
// �f�X�g���N�^
//========================================
CDoll3D::~CDoll3D(void) {

	// �{�[����Ԃ̃��������
	RNLib::Memory().Release(&m_boneStates);
}

//========================================
// �X�V����
//========================================
void CDoll3D::Update(void) {

	if (m_setUpIdx != NONEDATA)
	{// �Z�b�g�A�b�v���ݒ肳��Ă��鎞�A
		// �Z�b�g�A�b�v�f�[�^�擾
		const CSetUp3D::CData& setUp = RNLib::SetUp3D().GetData(m_setUpIdx);

		// ���[�V�����̍X�V����
		UpdateMotion();

		// �{�[���̍X�V����
		UpdateBone(setUp);
	}
}

//========================================
// �Z�b�g�A�b�v����
//========================================
void CDoll3D::SetUp(const short& setUpIdx) {

	// �Z�b�g�A�b�v�f�[�^�擾
	const CSetUp3D::CData& setUp = RNLib::SetUp3D().GetData(setUpIdx);

	//----------------------------------------
	// �{�[����ԃ�����
	// ���i����0���z���Ă��� > �������m��
	// ���i����0�ȉ�         > ���������
	//----------------------------------------
	if (setUp.m_boneDataNum > 0)
		RNLib::Memory().Alloc<CBoneState>(&m_boneStates, setUp.m_boneDataNum);
	else
		RNLib::Memory().Release<CBoneState>(&m_boneStates);
}

//========================================
// ���[�V�����ݒ菈��
//========================================
void CDoll3D::SetMotion(const short& motionIdx) {

	// �ԍ�����
	m_motionInfo.idx     =
	m_motionInfo.oldIdx  = motionIdx;

	// �J�E���^�[��������
	m_motionInfo.counter = 0;

	// ���[�V������������
	PrepareMotion();
}

//========================================
// ���[�V�����㏑������
//========================================
void CDoll3D::OverwriteMotion(const short& motionIdx) {

	// �ԍ����ߋ��̔ԍ��ƈقȂ鎞�A
	if (m_motionInfo.oldIdx != motionIdx)
		SetMotion(motionIdx);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [����J]�h�[��3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// ���[�V�����̍X�V����
//========================================
void CDoll3D::UpdateMotion(void) {

	// ���[�V�������ݒ肳��Ă��Ȃ����A�I��
	if (m_motionInfo.idx == NONEDATA)
		return;

	// ���[�V�����f�[�^�擾
	const CMotion3D::CData& motionData = RNLib::Motion3D().GetData(m_motionInfo.idx);

	// ���[�V�����J�E���^�[��i�߂�
	if (++m_motionInfo.counter >= motionData.loopTime)
		m_motionInfo.counter = motionData.isLoop ? 0 : m_motionInfo.counter = motionData.loopTime;
}

//========================================
// �{�[���̍X�V����
//========================================
void CDoll3D::UpdateBone(const CSetUp3D::CData& setUp) {

	// ���i��0�ȉ��̎��A�������I������
	if (setUp.m_boneDataNum <= 0)
		return;

	// �{�̃}�g���b�N�X
	const Matrix selfMtx = CMatrix::ConvPosRotScaleToMtx(m_pos, m_rot, m_scale);

	for (int cntBone = 0; cntBone < setUp.m_boneDataNum; cntBone++) {

		CBoneState& boneState = m_boneStates[cntBone];
		Pos3D       resultPos = INITPOS3D;
		Rot3D       resultRot = INITROT3D;

		// ���[�V�����̍X�V����
		boneState.UpdateMotion(m_motionInfo.counter);

		// ���[���h�}�g���b�N�X�𒲂ׂ�
		const Matrix worldMtx = FindBoneWorldMtx(boneState, setUp.m_boneDatas[cntBone], selfMtx);

		// ���f���̐ݒu����
		RNLib::Model().Put(worldMtx, setUp.m_boneDatas[cntBone].modelIdx)
			->SetCol(m_col)
			->SetOutLine(true)
			->SetBrightnessOfEmissive(m_brightnessOfEmission);
	}
}

//========================================
// �{�[���̃��[���h�}�g���b�N�X�𒲂ׂ�
//========================================
Matrix CDoll3D::FindBoneWorldMtx(CBoneState& boneState, const CSetUp3D::BoneData& boneData, const Matrix& selfMtx) {

	Matrix  worldMtx    = INITMATRIX;
	Pos3D   resultPos   = boneState.GetPos() + boneData.relativePos;
	Rot3D   resultRot   = boneState.GetRot() + boneData.relativeRot;
	Scale3D resultScale = boneState.GetScale();
	Matrix  parentMtx   = INITMATRIX;

	// �e�{�[�����Ȃ����A
	if (boneState.GetParentBoneState() == NULL) {

		// �h�[�����̂̊g��{������Z
		resultScale.x *= m_scale.x;
		resultScale.y *= m_scale.y;
		resultScale.z *= m_scale.z;

		// �e�}�g���b�N�X���h�[�����̂̃}�g���b�N�X�ɐݒ�
		parentMtx = selfMtx;
	}
	else 
	{// �e�{�[�������鎞�A
		// �e�}�g���b�N�X��e�{�[���̃}�g���b�N�X�ɐݒ�
		parentMtx = boneState.GetParentBoneState()->GetWorldMtx();
	}

	// ���[���h�}�g���b�N�X���Z�o
	worldMtx = CMatrix::MultiplyMtx(CMatrix::ConvPosRotScaleToMtx(resultPos, resultRot, resultScale), parentMtx);

	// ���[���h�}�g���b�N�X�ݒ�
	boneState.SetWorldMtx(worldMtx);

	return worldMtx;
}

//========================================
// ���[�V�����̏�������
//========================================
void CDoll3D::PrepareMotion(void) {

	const CMotion3D::CData& motionData(RNLib::Motion3D().GetData(m_motionInfo.idx));	// ���[�V�����f�[�^
	const CSetUp3D::CData&  setUpData(RNLib::SetUp3D().GetData(m_setUpIdx));			// �Z�b�g�A�b�v�f�[�^

	// �{�[�����ɏ�������
	for (int cntBone = 0; cntBone < setUpData.m_boneDataNum; cntBone++) {

		// �{�[�����̃��[�V�����f�[�^�|�C���^��n��
		for (int cntMotionBone = 0; cntMotionBone < motionData.boneNum; cntMotionBone++) {
			if (setUpData.m_boneDatas[cntBone].idx == cntMotionBone){
				m_boneStates[cntBone].SetMotionData(&motionData.boneMotionDatas[cntMotionBone]);
				break;
			}
		}

		// ��������
		m_boneStates[cntBone].PrepareMotion(motionData.boneMotionDatas[cntBone]);
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�{�[����ԃN���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDoll3D::CBoneState::CBoneState() {

	m_pos			  = INITPOS3D;
	m_rot			  = INITROT3D;
	m_scale			  = Scale3D(1.0f, 1.0f, 1.0f);
	m_worldMtx		  = INITMATRIX;
	m_animeStateSum   = {};
	m_motionData      = NULL;
	m_parentBoneState = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CDoll3D::CBoneState::~CBoneState() {

}

//========================================
// ���[�V�����X�V����
//========================================
void CDoll3D::CBoneState::UpdateMotion(const short& counter) {

	// �����t���O���U�ɂ��Ă���
	m_animeStateSum.isStep = false;

	//----------------------------------------
	// �R�}���h�ǂݎ��
	//----------------------------------------
	for (int cntCommand = 0; cntCommand < m_motionData->commandDataNum; cntCommand++) {

		// �J�E���^�[�����s���Ԃƈ�v���Ă��Ȃ����A�܂�Ԃ�
		if (counter != m_motionData->commandDatas[cntCommand].time)
			continue;

		CMotion3D::CommandData& commandData(m_motionData->commandDatas[cntCommand]);

		// �R�}���h�ɉ���������
		switch (commandData.command) {
			// [[[ �ړ� ]]]
		case CMotion3D::COMMAND::MOVE: {
			const Pos3D       targetPos = Pos3D(commandData.datas[0], commandData.datas[1], commandData.datas[2]);
			const int         moveTime  = (int)commandData.datas[3];
			const CEase::TYPE ease      = (CEase::TYPE)((int)commandData.datas[4]);

			if (moveTime == 0)
			{// �ړ��ɂ����鎞�Ԃ�0�̎��A
				// �ʒu�𒼐ڑ��
				m_pos = targetPos;
			}
			else
			{// �ړ��ɂ����鎞�Ԃ�0�łȂ����A
				// �ړ��A�j����ԃ��������m��
				RNLib::Memory().Alloc(&m_animeStateSum.move);

				// �ړ��A�j����Ԃ�ݒ�
				m_animeStateSum.move->posEase   = ease;
				m_animeStateSum.move->oldPos    = m_pos;
				m_animeStateSum.move->targetPos = targetPos;
				m_animeStateSum.move->time      = moveTime;
			}
		}break;
			// [[[ ��] ]]]
		case CMotion3D::COMMAND::SPIN: {
			const Rot3D       targetRot = Rot3D(commandData.datas[0], commandData.datas[1], commandData.datas[2]);
			const int         spinTime  = (int)commandData.datas[3];
			const CEase::TYPE ease      = (CEase::TYPE)((int)commandData.datas[4]);

			if (spinTime == 0)
			{// ��]�ɂ����鎞�Ԃ�0�̎��A
				// �����𒼐ڑ��
				m_rot = targetRot;
			}
			else
			{// ��]�ɂ����鎞�Ԃ�0�łȂ����A
				// ��]�A�j����ԃ��������m��
				RNLib::Memory().Alloc(&m_animeStateSum.spin);

				// ��]�A�j����Ԃ�ݒ�
				m_animeStateSum.spin->rotEase   = ease;
				m_animeStateSum.spin->oldRot    = m_rot;
				m_animeStateSum.spin->targetRot = targetRot;
				m_animeStateSum.spin->time      = spinTime;
			}
		}break;
			// [[[ �g�k ]]]
		case CMotion3D::COMMAND::SCALING: {
			const Scale3D     targetScale = Scale3D(commandData.datas[0], commandData.datas[1], commandData.datas[2]);
			const int         scalingTime = (int)commandData.datas[3];
			const CEase::TYPE ease        = (CEase::TYPE)((int)commandData.datas[4]);

			if (scalingTime == 0)
			{// �g�k�ɂ����鎞�Ԃ�0�̎��A
				// �g��{���𒼐ڑ��
				m_scale = targetScale;
			}
			else
			{// �g�k�ɂ����鎞�Ԃ�0�łȂ����A
				// �g�k�A�j����ԃ��������m��
				RNLib::Memory().Alloc(&m_animeStateSum.scaling);

				// �g�k�A�j����Ԃ�ݒ�
				m_animeStateSum.scaling->scaleEase   = ease;
				m_animeStateSum.scaling->oldScale    = m_scale;
				m_animeStateSum.scaling->targetScale = targetScale;
				m_animeStateSum.scaling->time        = scalingTime;
			}
		}break;
			// [[[ ���� ]]]
		case CMotion3D::COMMAND::STEP: {

			// �����t���O��^�ɂ��Ă���
			m_animeStateSum.isStep = true;
		}break;
		}
	}

	//----------------------------------------
	// �A�j����ԍX�V����
	//----------------------------------------
	// [[[ �ړ� ]]]
	if (m_animeStateSum.move != NULL) {

		// �����𒲂ׂ�
		const float rate = CEase::Easing(m_animeStateSum.move->posEase, m_animeStateSum.move->counter, m_animeStateSum.move->time);

		// �ʒu���X�V
		m_pos = (m_animeStateSum.move->oldPos * (1.0f - rate)) + (m_animeStateSum.move->targetPos * rate);

		// �J�E���^�[���B���A���������
		if (++m_animeStateSum.move->counter >= m_animeStateSum.move->time) {
			RNLib::Memory().Release(&m_animeStateSum.move);
		}
	}

	// [[[ ��] ]]]
	if (m_animeStateSum.spin != NULL) {

		// �����𒲂ׂ�
		const float rate = CEase::Easing(m_animeStateSum.spin->rotEase, m_animeStateSum.spin->counter, m_animeStateSum.spin->time);

		// �������X�V
		m_rot = (m_animeStateSum.spin->oldRot * (1.0f - rate)) + (m_animeStateSum.spin->targetRot * rate);

		// �J�E���^�[���B���A���������
		if (++m_animeStateSum.spin->counter >= m_animeStateSum.spin->time) {
			RNLib::Memory().Release(&m_animeStateSum.spin);
		}
	}

	// [[[ �g�k ]]]
	if (m_animeStateSum.scaling != NULL) {

		// �����𒲂ׂ�
		const float rate = CEase::Easing(m_animeStateSum.scaling->scaleEase, m_animeStateSum.scaling->counter, m_animeStateSum.scaling->time);

		// �g��{�����X�V
		m_scale = (m_animeStateSum.scaling->oldScale * (1.0f - rate)) + (m_animeStateSum.scaling->targetScale * rate);

		// �J�E���^�[���B���A���������
		if (++m_animeStateSum.scaling->counter >= m_animeStateSum.scaling->time) {
			RNLib::Memory().Release(&m_animeStateSum.scaling);
		}
	}
}

//========================================
// ���[�V������������
//========================================
void CDoll3D::CBoneState::PrepareMotion(const CMotion3D::BoneMotionData& boneMotionData) {

	// ���������
	RNLib::Memory().Release(&m_animeStateSum.move);
	RNLib::Memory().Release(&m_animeStateSum.spin);
	RNLib::Memory().Release(&m_animeStateSum.scaling);

	// �ړ����Ȃ����[�V�����̎��A�ʒu�ύX���Ă���̂ł���΁A
	if (!boneMotionData.isMove && m_pos != INITPOS3D) {
		
		// �ړ����̃��������m�ۂ��A
		RNLib::Memory().Alloc(&m_animeStateSum.move);

		// �����ʒu�Ɉړ�������
		m_animeStateSum.move->oldPos    = m_pos;
		m_animeStateSum.move->targetPos = INITPOS3D;
		m_animeStateSum.move->time      = PAUSE_RESET_TIME;
		m_animeStateSum.move->posEase   = CEase::TYPE::LINEAR;
	}

	// ��]���Ȃ����[�V�����̎��A�����ύX���Ă���̂ł���΁A
	if (!boneMotionData.isSpin && m_rot != INITROT3D) {
		
		// ��]���̃��������m�ۂ��A
		RNLib::Memory().Alloc(&m_animeStateSum.spin);

		// ���������ɉ�]������
		m_animeStateSum.spin->oldRot    = m_rot;
		m_animeStateSum.spin->targetRot = INITROT3D;
		m_animeStateSum.spin->time      = PAUSE_RESET_TIME;
		m_animeStateSum.spin->rotEase   = CEase::TYPE::LINEAR;
	}

	// �g�k���Ȃ����[�V�����̎��A�g��{���ύX���Ă���̂ł���΁A
	if (!boneMotionData.isScale && m_scale != INITSCALE3D) {
		
		// �g�k���̃��������m�ۂ��A
		RNLib::Memory().Alloc(&m_animeStateSum.scaling);

		// �����g��{���Ɋg�k������
		m_animeStateSum.scaling->oldScale    = m_scale;
		m_animeStateSum.scaling->targetScale = INITSCALE3D;
		m_animeStateSum.scaling->time        = PAUSE_RESET_TIME;
		m_animeStateSum.scaling->scaleEase   = CEase::TYPE::LINEAR;
	}
}