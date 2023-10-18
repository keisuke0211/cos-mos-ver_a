//========================================
// 
// �h�[��3D�̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNlib.h"

//****************************************
// �}�N����`
//****************************************
#define PAUSE_RESET_TIME (10)

#if 0
//================================================================================
//----------|---------------------------------------------------------------------
//==========| �{�[����ԃN���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDoll3D::CBoneState::CBoneState() {

	m_pos			= INITD3DXVECTOR3;
	m_rot			= INITD3DXVECTOR3;
	m_scale			= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_resultMtx		= INITD3DXMATRIX;
	m_animeStateSum = {};
}

//========================================
// �f�X�g���N�^
//========================================
CDoll3D::CBoneState::~CBoneState() {

}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �h�[��3D�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDoll3D::CDoll3D(void) {

	m_pos			 = INITD3DXVECTOR3;
	m_rot			 = INITD3DXVECTOR3;
	m_boneStates     = NULL;

	m_bMotionStop	 = false;
	m_bDrawCollision = false;		
	m_nModelSetUp	 = 0;			
	m_nMotion		 = 0;			
	m_nMotionOld	 = 0;			
	m_nMotionCounter = 0;			
	m_col			 = CLEARCOLOR;	
	m_fBrOfEm        = 1.0f;
	m_fScale         = 1.0f;
}

//========================================
// �f�X�g���N�^
//========================================
CDoll3D::~CDoll3D(void) {

	// ���i���̃��������
	RNLib::Memory()->Release(&m_boneStates);
}

//========================================
// ����������
//========================================
void CDoll3D::SetUp(const short& setUpIdx) {

	// �Z�b�g�A�b�v�f�[�^�擾
	CSetUp3D::CData& setUp = RNLib::ModelSetUp()->GetData(setUpIdx);

	//----------------------------------------
	// �{�[����ԃ�����
	// ���i����0���z���Ă��� > �������m��
	//----------------------------------------
	if (setUp.m_boneDataSum.boneDataNum > 0)
		RNLib::Memory()->Alloc<CBoneState>(&m_boneStates, setUp.m_boneDataSum.boneDataNum);
	else
		RNLib::Memory()->Release<CBoneState>(&m_boneStates);
}

//========================================
// ���f���ݒ菈��
//========================================
void CDoll3D::ModelSet(Data *pPartsSet) {

	// ���i��0�ȉ��̎��A�������I������
	if (pPartsSet->nPartsNum <= 0)return;

	LPDIRECT3DDEVICE9 pDevice = RNLib::Window()->GetD3DDevice();	// �f�o�C�X���擾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxSelf;				// �{�̂̃}�g���b�N�X
	D3DXMATRIX *pMtxParts = NULL;	// ���i���̃}�g���b�N�X�̃|�C���^

	// ���i���̃}�g���b�N�X�̃������𕔕i�����m��
	pMtxParts = new D3DXMATRIX[pPartsSet->nPartsNum];

	// �{�̂̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxSelf);

	// �{�̂̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

	// �{�̂̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

	// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++) {
		CBoneState *pParts = &m_boneStates[nCntParts];	// ���i�̏��̃|�C���^
		PartsData *pPartsType = &pPartsSet->pPartsData[nCntParts];	// ���i�̎�ޖ��̏��̃|�C���^
		D3DXVECTOR3 posResult;	// �ʒu(����)
		D3DXVECTOR3 rotResult;	// ����(����)

		{//========== [[[ �ʒu(����)���X�V ]]]
			if (pParts->bPosAnim)
			{// �ʒu�A�j���t���O���^�̎��A�J�E���^�[�̐i�s���ɉ����Ĉʒu���X�V
				float fRate = Easing(pParts->easePos, pParts->nCounterPosAnim, pParts->nPosAnimTime - 1);
				pParts->pos = (pParts->oldPos * (1.0f - fRate)) + (pParts->targetPos * fRate);
			}

			// ���ʈʒu�����߂�
			posResult = pParts->pos + pPartsType->fixedRelativePos;

			// �e�ԍ���-1�̎��A���ʈʒu�Ɋg��{������Z
			if (pPartsType->nParent == -1) {
				posResult *= m_fScale;
			}
		}

		float fStepRate = 0.0f;	// ��������

		{//========== [[[ ����(����)���X�V ]]]
			if (pParts->bStep) 
			{// �����t���O���^�̎��A
				int nCounter = pParts->nCounterRotAnim;
				if (nCounter > pParts->nRotAnimTime) {
					nCounter = pParts->nRotAnimTime;
				}
				int nCounterReset = pParts->nCounterRotAnim - (pParts->nStepTime - pParts->nStepResetTime);
				if (nCounterReset < 0) {
					nCounterReset = 0;
				}
				fStepRate = Easing(EASE_LINEAR, nCounter, pParts->nRotAnimTime) * (1.0f - Easing(EASE_LINEAR, nCounterReset, pParts->nStepResetTime));
			}
			else if (pParts->bRotAnim)
			{// �����A�j���t���O���^�̎��A�J�E���^�[�̐i�s���ɉ����Č������X�V
				float fRate = Easing(pParts->easeRot, pParts->nCounterRotAnim, pParts->nRotAnimTime - 1);
				pParts->rot = (pParts->oldRot * (1.0f - fRate)) + (pParts->targetRot * fRate);
			}

			// ���ʈʒu�����߂�
			rotResult = pParts->rot + pPartsType->fixedRelativeRot;
		}

		{//========== [[[ �g��{��(����)���X�V ]]]
			if (pParts->bScaleAnim)
			{// �g��{���A�j���t���O���^�̎��A�J�E���^�[�̐i�s���ɉ����Ċg��{�����X�V
				float fRate = Easing(pParts->easeScale, pParts->nCounterScaleAnim, pParts->nScaleAnimTime - 1);
				pParts->scale = (pParts->scaleOld * (1.0f - fRate)) + (pParts->targetScale * fRate);
			}
		}

		{// ���i�̃��[���h�}�g���b�N�X�̎Z�o
			// ���i�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pMtxParts[nCntParts]);

			if (pPartsType->nParent == -1)
			{// �e�ԍ���-1�̎��A���f���̃T�C�Y��K�p
				D3DXMatrixScaling(
					&pMtxParts[nCntParts],
					m_fScale * pParts->scale.x, 
					m_fScale * pParts->scale.y, 
					m_fScale * pParts->scale.z);
			}
			else 
			{// �e�����鎞�A���g�̊g��{���̂ݓK�p
				D3DXMatrixScaling(
					&pMtxParts[nCntParts],
					pParts->scale.x,
					pParts->scale.y,
					pParts->scale.z);
			}

			D3DXMATRIX mtxOvl = pMtxParts[nCntParts];	// ����}�g���b�N�X��ۑ�

			// ���i�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rotResult.y, rotResult.x, rotResult.z);
			D3DXMatrixMultiply(&pMtxParts[nCntParts], &pMtxParts[nCntParts], &mtxRot);

			// ���i�̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, posResult.x, posResult.y, posResult.z);
			D3DXMatrixMultiply(&pMtxParts[nCntParts], &pMtxParts[nCntParts], &mtxTrans);

			// �e�̕��i�̃}�g���b�N�X
			D3DXMATRIX mtxParent;

			// ���i�̐e�ԍ���-1(�e����)�łȂ����A�e�}�g���b�N�X��ݒ�B�e�����ł���Ύ��g�̃}�g���b�N�X��ݒ�
			if (pPartsType->nParent != -1) { mtxParent = pMtxParts[pPartsType->nParent]; }
			else                           { mtxParent = mtxSelf; }

			// �Z�o�������i�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(
				&pMtxParts[nCntParts],
				&pMtxParts[nCntParts],
				&mtxParent);

			if (pParts->bStep) {
				// �T�C�Y��ύX
				D3DXMatrixScaling(&mtxOvl, m_fScale, m_fScale, m_fScale);

				// �{�̂̌����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
				D3DXMatrixMultiply(&mtxOvl, &mtxOvl, &mtxRot);

				// ���i�̈ʒu����
				mtxOvl._41 = pMtxParts[nCntParts]._41;
				mtxOvl._42 = pMtxParts[nCntParts]._42;
				mtxOvl._43 = pMtxParts[nCntParts]._43;

				// �����Ń}�g���b�N�X�����߂�
				pMtxParts[nCntParts] = (pMtxParts[nCntParts] * (1.0f - fStepRate)) + (mtxOvl * fStepRate);
			}
		}

		// ���f���̐ݒ菈��
		RNLib::Model()->Put(pMtxParts[nCntParts], pPartsType->nModelIdx)
			->SetCol(m_col)
			->SetLighting(pPartsType->bLighting)
			->SetOutLine(true)
			->SetBrightnessOfEmissive(m_fBrOfEm);

		// �}�g���b�N�X�𕔕i�ɕۑ�
		pParts->resultMtx = pMtxParts[nCntParts];
	}

	// ���i���̃}�g���b�N�X�̃��������
	delete pMtxParts;

	if (m_pCLParts != NULL) 
	{// �R���W�������i�����݂��鎞�A�R���W�������i�̈ʒu�v�Z
		CSetUp3D::Data* pModelSetUp = RNLib::ModelSetUp()->GetData(m_nModelSetUp);
		for (int nCntCLParts = 0; nCntCLParts < pModelSetUp->collSet.nPartsNum; nCntCLParts++) {
			CCollision3D::Parts collParts = pModelSetUp->collSet.pParts[nCntCLParts];
			D3DXVECTOR3 pos = INITD3DXVECTOR3;
			D3DXVECTOR3 rot = INITD3DXVECTOR3;

			if (pModelSetUp->collSet.pParts[nCntCLParts].nParent == DATANONE) {
				pos = m_pos;
				rot = m_rot;
			}
			else {
				CDoll3D::CBoneState parts = {};	// ���i���

				if (GetPartsState_Idx(pModelSetUp->collSet.pParts[nCntCLParts].nParent, &parts)) {
					pos = ConvMatrixToPos(parts.resultMtx);
					rot = ConvMatrixToRot(parts.resultMtx);
				}
				else {
					pos = m_pos;
					rot = m_rot;
				}
			}

			D3DXMATRIX mtx = MultiplyMatrix(
				ConvPosRotToMatrix(collParts.pos, collParts.rot),
				ConvPosRotToMatrix(pos, rot));
			m_pCLParts[nCntCLParts].pos = ConvMatrixToPos(mtx);
			m_pCLParts[nCntCLParts].rot = ConvMatrixToRot(mtx);
		}
	}
}


//========================================
// �X�V����
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::Update(void) {
	// ���f���Z�b�g�A�b�v���
	CSetUp3D::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	if (m_nModelSetUp != DATANONE)
	{// ���f���Z�b�g�A�b�v�ԍ���-1 or �̎��A
		if (!m_bMotionStop)
		{// ��~���Ă��Ȃ����A
			// ���[�V�����ݒ�
			MotionSet(setUp.boneDataSum);

			// ���[�V�����̍X�V����
			MotionUpdate(m_nMotion, setUp.boneDataSum);
		}

		// ���f���̐ݒ菈��
		ModelSet(&setUp.boneDataSum);

		if (m_bDrawCollision)
			DrawCollision();
	}

	// �e��ݒ�
	RNLib::Shadow3D()->Set(m_pos);
}

//========================================
// ���[�V�����I���擾
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetMotionEnd(void) {
	return m_nMotionCounter >= RNLib::Motion3D()->GetData()[m_nMotion].nLoopTime;
}

//========================================
// ���[�V�������ݎ擾
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetMotionStep(void) {
	CSetUp3D::Data modelSetUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);
	CMotion3D  ::Data motion     =  RNLib::Motion3D  ()->GetData()[m_nMotion];

	for (int nCntParts = 0; nCntParts < modelSetUp.boneDataSum.nPartsNum; nCntParts++) {
		if (m_boneStates[nCntParts].bStepReaction)
		{// ���������t���O���^�̎��A
			return true;
		}
		else if (m_boneStates[nCntParts].bStep)
		{// �����t���O���^�̎��A
			if (m_boneStates[nCntParts].nCounterRotAnim == m_boneStates[nCntParts].nRotAnimTime) {
				return true;
			}
		}
	}

	return false;
}

//========================================
// ���i���擾(�ԍ��w��)
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetPartsState_Idx(int nIdx, CBoneState* pParts) {
	// ���f���Z�b�g�A�b�v���
	CSetUp3D::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntParts = 0; nCntParts < setUp.boneDataSum.nPartsNum; nCntParts++) {
		if (setUp.boneDataSum.pPartsData[nCntParts].nIdx == nIdx) {
			*pParts = m_boneStates[nCntParts];
			return true;
		}
	}

	return false;
}

//========================================
// ���i���擾(���ʎw��)
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::GetPartsState_Part(int nPart, CBoneState* pParts) {
	// ���f���Z�b�g�A�b�v���
	CSetUp3D::Data setUp = *RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	// ���f���\���ɉ��������ʔԍ��擾
	int nIdx = RNLib::ModelSetUp()->GetPlatformPartIdx(setUp.platform, (CSetUp3D::PART)nPart);

	for (int nCntParts = 0; nCntParts < setUp.boneDataSum.nPartsNum; nCntParts++) {
		if (setUp.boneDataSum.pPartsData[nCntParts].nIdx == nIdx) {
			*pParts = m_boneStates[nCntParts];
			return true;
		}
	}

	*pParts = m_boneStates[0];

	return false;
}

//========================================
// ���[�V����3D�̐ݒ菈��
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::MotionSet(Data partsSet) {
	if (m_nMotion == m_nMotionOld)
	{// ���ɂ��̃��[�V�����ԍ��ɐݒ肳��Ă��鎞�A
		return;	// �������I������
	}

	// ���[�V�����N���A
	MotionClear(partsSet, m_nMotion);
	
	// �ߋ��̃��[�V�����ԍ��Ƃ��ĕۑ�
	m_nMotionOld = m_nMotion;

	// ���[�V�����J�E���^�[��������
	m_nMotionCounter = 0;
}

//========================================
// ���[�V����3D�̍X�V����
// Author:RIKU NISHIMURA
//========================================
bool CDoll3D::MotionUpdate(int nMotion, Data partsSet) {
	if (nMotion == DATANONE) {
		return false;
	}

	CMotion3D::Data motion = RNLib::Motion3D()->GetData()[nMotion];	// ���[�V�������

	if (motion.nLoopTime == DATANONE)
	{// ���[�V�����̃��[�v���Ԃ������̎��A
		// �������I������
		return false;
	}

	// ���[�V�����̃A�j��3D�ǂݍ��ݏ���
	LoadMotionAnim(partsSet);

	// ���[�V�����̃A�j������
	MotionAnim(partsSet);

	// ���[�V���������[�v�������t���O
	bool bMotionLoop = false;

	if (++m_nMotionCounter > motion.nLoopTime)
	{// ���[�V�����J�E���^�[�����Z�������ʃ��[�v���ԂɒB�������A
		bMotionLoop = true;	// ���[�V���������[�v�������t���O��^�ɂ���

		if (motion.bLoop)
		{// ���[�v���邩�t���O���^�̎��A
			// ���[�V�����J�E���^�[�����[�v����
			IntLoopControl(&m_nMotionCounter, motion.nLoopTime + 1, 0);
		}
		else
		{// ���[�v���邩�t���O���U�̎��A
			// ���[�V�����J�E���^�[�𐧌�
			IntControl(&m_nMotionCounter, motion.nLoopTime + 1, 0);
		}
	}

	// ���[�V���������[�v�������t���O��Ԃ�
	return bMotionLoop;
}


//========================================
// ���[�V����3D�̃A�j���ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::LoadMotionAnim(Data partsSet) {
	CSetUp3D::PLATFORM platform = RNLib::ModelSetUp()->GetData(m_nModelSetUp)->platform;
	CMotion3D::Data       motion   = RNLib::Motion3D()->GetData()[m_nMotion];

	// ���i�S�Ă̈ꕔ��񏉊���
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		m_boneStates[nCntParts].bStepReaction = false;
	}

	// ���i���̃A�j���̓ǂݍ���
	for (int nCntPartsAnim = 0; nCntPartsAnim < motion.pfData[platform].nPartsNum; nCntPartsAnim++) {
		// ���i���̃��[�V����3D�̏��
		CMotion3D::PartsCmd partsMotion3D = motion.pfData[platform].pPartsCmd[nCntPartsAnim];

		for (int nCntCmd = 0; nCntCmd < partsMotion3D.nCmdNum; nCntCmd++) {
			CMotion3D::Cmd cmd = partsMotion3D.pCmd[nCntCmd];	// �R�}���h���
			CBoneState *pParts = m_boneStates;	// ���i3D�̏��

			{// ��v�������i�ԍ��܂Ń|�C���^��i�߂�
				bool bFind = false;	// ��v���i�m�F�t���O
				for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++, pParts++) {
					if (partsSet.pPartsData[nCntParts].nIdx == nCntPartsAnim)
					{// ���i���̃A�j���J�E���g�ƕ��i�ԍ�����v�������A
						bFind = true;
						break;
					}
				}

				if ((m_nMotionCounter != cmd.nTime) || (!bFind))
				{// �J�E���^�[�����s���Ԃƈ�v���Ă��Ȃ� or ��v���i���m�F�A
					continue;
				}
			}

			// �R�}���h���x���ɉ���������
			switch (cmd.command) {
			case CMotion3D::CMD_LABEL_MOVE: {
				D3DXVECTOR3 pos       = D3DXVECTOR3(cmd.pData[0], cmd.pData[1], cmd.pData[2]);	// �ʒu
				int         nMoveTime = (int)cmd.pData[3];			// �ړ��ɂ����鎞��
				EASE        ease      = (EASE)((int)cmd.pData[4]);	// ���

				if (nMoveTime == 0)
				{// �ړ��ɂ����鎞�Ԃ�0�̎��A
					pParts->pos = pos;	// �ʒu�𒼐ڑ��
				}
				else
				{// �ړ��ɂ����鎞�Ԃ�0�łȂ����A
					pParts->easePos         = ease;			// �ʒu��Ԃ�ݒ�
					pParts->oldPos          = pParts->pos;	// ���̈ʒu��ݒ�
					pParts->targetPos       = pos;			// �ڕW�ʒu����
					pParts->nPosAnimTime    = nMoveTime;	// �ʒu�A�j���ɂ����鎞�Ԃ���
					pParts->nCounterPosAnim = 0;			// �ʒu�A�j���J�E���^�[��������
					pParts->bPosAnim        = true;			// �ʒu�A�j���t���O��^�ɂ���
				}
			}
			break;
			case CMotion3D::CMD_LABEL_SPIN: {
				D3DXVECTOR3 rot       = D3DXVECTOR3(cmd.pData[0], cmd.pData[1], cmd.pData[2]);	// ����
				int         nSpinTime = (int)cmd.pData[3];			// ��]�ɂ����鎞��
				EASE        ease      = (EASE)((int)cmd.pData[4]);	// ���

				if (nSpinTime == 0)
				{// ��]�ɂ����鎞�Ԃ�0�̎��A
					pParts->rot = rot;	// �����𒼐ڑ��
				}
				else
				{// ��]�ɂ����鎞�Ԃ�0�łȂ����A
					pParts->easeRot         = ease;			// ������Ԃ�ݒ�
					pParts->oldRot          = pParts->rot;	// ���̌�����ݒ�
					pParts->targetRot       = rot;			// �ڕW��������
					pParts->nRotAnimTime    = nSpinTime;	// �����A�j���ɂ����鎞�Ԃ���
					pParts->nCounterRotAnim = 0;			// �����A�j���J�E���^�[��������
					pParts->bRotAnim        = true;			// �����A�j���t���O��^�ɂ���
				}
			}
			break;
			case CMotion3D::CMD_LABEL_STEP: {
				pParts->nRotAnimTime    = (int)cmd.pData[0];	// �����A�j���ɂ����鎞�Ԃ���
				pParts->nCounterRotAnim = 0;					// �����A�j���J�E���^�[��������
				pParts->bRotAnim        = false;				// �����A�j���t���O���U�ɂ���
				pParts->bStep           = true;					// �����t���O�^
				pParts->nStepTime       = (int)cmd.pData[1];	// ��������
				pParts->nStepResetTime  = (int)cmd.pData[2];	// �����߂鎞��
			}
			break;
			case CMotion3D::CMD_LABEL_SCALE: {
				D3DXVECTOR3 scale      = D3DXVECTOR3(cmd.pData[0], cmd.pData[1], cmd.pData[2]);	// �g��{��
				int         nScaleTime = (int)cmd.pData[3];			// �ړ��ɂ����鎞��
				EASE        ease       = (EASE)((int)cmd.pData[4]);	// ���

				if (nScaleTime == 0)
				{// �ړ��ɂ����鎞�Ԃ�0�̎��A
					pParts->scale = scale;	// �g��{���𒼐ڑ��
				}
				else
				{// �ړ��ɂ����鎞�Ԃ�0�łȂ����A
					pParts->easeScale         = ease;			// �g��{����Ԃ�ݒ�
					pParts->scaleOld          = pParts->scale;	// ���̊g��{����ݒ�
					pParts->targetScale       = scale;			// �ڕW�g��{������
					pParts->nScaleAnimTime    = nScaleTime;		// �g��k���A�j���ɂ����鎞�Ԃ���
					pParts->nCounterScaleAnim = 0;				// �g��k���A�j���J�E���^�[��������
					pParts->bScaleAnim        = true;			// �g��k���A�j���t���O��^�ɂ���
				}
			}
			break;
			case CMotion3D::CMD_LABEL_STEP_REACTION: {
				pParts->bStepReaction = true;	// ���������t���O�^
			}
			break;
			default:
				assert(false);
				break;
			}
		}
	}
}

//========================================
// ���[�V����3D�̃A�j������
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::MotionAnim(Data partsSet) {
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		// ���i�̏��̃|�C���^
		CBoneState *pParts = &m_boneStates[nCntParts];

		if (pParts->bPosAnim)
		{// �ʒu�A�j���t���O���^�̎��A
			if (++pParts->nCounterPosAnim >= pParts->nPosAnimTime)
			{// �ʒu�A�j���J�E���^�[�����Z�������ʈʒu�A�j���ɂ����鎞�Ԃ����������A
				pParts->bPosAnim = false;	// �ʒu�A�j���t���O���U�ɂ���
			}
		}

		if (pParts->bStep) 
		{// �����t���O���^�̎��A
			if (++pParts->nCounterRotAnim >= pParts->nStepTime)
			{// �����A�j���J�E���^�[�����Z�������ʑ������Ԃ����������A
				pParts->bStep = false;	// �����t���O���U�ɂ���
			}
		}
		else if (pParts->bRotAnim)
		{// �p�x�A�j���t���O���^�̎��A
			if (++pParts->nCounterRotAnim >= pParts->nRotAnimTime)
			{// �����A�j���J�E���^�[�����Z�������ʌ����A�j���ɂ����鎞�Ԃ����������A
				pParts->bRotAnim = false;	// �����A�j���t���O���U�ɂ���
			}
		}

		if (pParts->bScaleAnim)
		{// �g��k���A�j���t���O���^�̎��A
			if (++pParts->nCounterScaleAnim >= pParts->nScaleAnimTime)
			{// �g��k���A�j���J�E���^�[�����Z�������ʊg��k���A�j���ɂ����鎞�Ԃ����������A
				pParts->bScaleAnim = false;	// �g��k���A�j���t���O���U�ɂ���
			}
		}
	}
}

//========================================
// ���[�V�����̃N���A����
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::MotionClear(Data partsSet, int nMotion) {
	if (nMotion == DATANONE)
		return;

	CMotion3D::Data motion = RNLib::Motion3D()->GetData()[nMotion];
	CSetUp3D::PLATFORM platform = RNLib::ModelSetUp()->GetData(m_nModelSetUp)->platform;

	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++) {
		m_boneStates[nCntParts].bScaleAnim = false;
		m_boneStates[nCntParts].bStep      = false;

		if (motion.pfData[platform].pPartsCmd == NULL) {
			m_boneStates[nCntParts].bPosAnim = false;
		}
		else if (motion.pfData[platform].pPartsCmd[nCntParts].bMove) {
			m_boneStates[nCntParts].bPosAnim = false;
		}
		else {
			m_boneStates[nCntParts].easePos         = EASE_LINEAR;
			m_boneStates[nCntParts].bPosAnim        = true;
			m_boneStates[nCntParts].nCounterPosAnim = 0;
			m_boneStates[nCntParts].nPosAnimTime    = PAUSE_RESET_TIME;
			m_boneStates[nCntParts].oldPos          = m_boneStates[nCntParts].pos;	
			m_boneStates[nCntParts].targetPos       = INITD3DXVECTOR3;
		}

		if (motion.pfData[platform].pPartsCmd == NULL) {
			m_boneStates[nCntParts].bRotAnim = false;
		}
		else if (motion.pfData[platform].pPartsCmd[nCntParts].bSpin) {
			m_boneStates[nCntParts].bRotAnim = false;
		}
		else {
			m_boneStates[nCntParts].easeRot         = EASE_LINEAR;
			m_boneStates[nCntParts].bRotAnim        = true;
			m_boneStates[nCntParts].nCounterRotAnim = 0;
			m_boneStates[nCntParts].nRotAnimTime    = PAUSE_RESET_TIME;
			m_boneStates[nCntParts].oldRot          = m_boneStates[nCntParts].rot;	
			m_boneStates[nCntParts].targetRot       = INITD3DXVECTOR3;
		}
	}
}

//========================================
// �R���W�����`�揈��
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::DrawCollision(void) {
	CSetUp3D::Data* pModelSetUp = RNLib::ModelSetUp()->GetData(m_nModelSetUp);

	for (int nCntCollParts = 0; nCntCollParts < pModelSetUp->collSet.nPartsNum; nCntCollParts++) {
		CCollision3D::Parts collParts = pModelSetUp->collSet.pParts[nCntCollParts];
		D3DXVECTOR3 pos = INITD3DXVECTOR3;
		D3DXVECTOR3 rot = INITD3DXVECTOR3;

		if (pModelSetUp->collSet.pParts[nCntCollParts].nParent == DATANONE) {
			pos = m_pos;
			rot = m_rot;
		}
		else {
			CDoll3D::CBoneState parts = {};	// ���i���

			if (GetPartsState_Idx(pModelSetUp->collSet.pParts[nCntCollParts].nParent, &parts)) {
				pos = ConvMatrixToPos(parts.resultMtx);
				rot = ConvMatrixToRot(parts.resultMtx);
			}
			else {
				pos = m_pos;
				rot = m_rot;
			}
		}

		D3DXMATRIX mtx = MultiplyMatrix(
			ConvPosRotToMatrix(collParts.pos, collParts.rot),
			ConvPosRotToMatrix(pos, rot));
		pos = ConvMatrixToPos(mtx);
		rot = ConvMatrixToRot(mtx);

		// �`�ɉ��������C���ݒ�
		switch (pModelSetUp->collSet.pParts[nCntCollParts].form) {
		case CCollision3D::FORM_SPHERE: {
			RNLib::Line3D()->Set_Sphere(
				pos,
				rot,
				collParts.fWidth,
				{ 255,0,0,255 },
				false
			);
			break;
		}
		case CCollision3D::FORM_CUBE: {
			RNLib::Line3D()->Set_Cube(
				pos,
				rot,
				collParts.fWidth,
				collParts.fHeight,
				collParts.fDepth,
				{ 255,0,0,255 },
				false
			);
			break;
		}
		case CCollision3D::FORM_CYLINDER: {
			RNLib::Line3D()->Set_Cylinder(
				pos,
				rot,
				collParts.fWidth,
				collParts.fHeight,
				{ 255,0,0,255 },
				false
			);
			break;
		}
		}
	}
}

//========================================
// ���i�ݒ���3D�̓ǂݍ��ݏ���
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::LoadData(Data *pPartsSet) {

	
}

//========================================
// ���i�ݒ���3D�̏������ݏ���
// Author:RIKU NISHIMURA
//========================================
void CDoll3D::SaveData(Data *pPartsSet) {
	FILE* pFile = RNLib::File()->GetFile();
	fprintf(pFile, "PARTSSET{ %d\n", pPartsSet->nPartsNum);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++) {
		PartsData *pPartsType = &pPartsSet->pPartsData[nCntParts];

		fprintf(pFile, "	PARTS{\n");
		fprintf(pFile, "		INDEX: %d\n", pPartsType->nIdx);
		fprintf(pFile, "		MODEL_PATH: %s\n", RNLib::Model()->GetLoadPath(pPartsType->nModelIdx));
		fprintf(pFile, "		PARENT: %d\n", pPartsType->nParent == DATANONE ? DATANONE : pPartsSet->pPartsData[pPartsType->nParent].nIdx);
		fprintf(pFile, "		RELATIVE_POS: %f %f %f\n",
				pPartsType->fixedRelativePos.x,
				pPartsType->fixedRelativePos.y,
				pPartsType->fixedRelativePos.z);
		fprintf(pFile, "		RELATIVE_ROT: %f %f %f\n",
				pPartsType->fixedRelativeRot.x,
				pPartsType->fixedRelativeRot.y,
				pPartsType->fixedRelativeRot.z);
		fprintf(pFile, "		LIGHTING: %d\n", (int)pPartsType->bLighting);
		fprintf(pFile, "	}\n");
	}
	fprintf(pFile, "}\n");
}
#endif