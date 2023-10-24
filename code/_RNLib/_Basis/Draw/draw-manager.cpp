//========================================
// 
// �`�揈��
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// �ÓI�����o�ϐ���`
//****************************************
CDrawMng::PROCESS_STATE  CDrawMng::ms_processState = PROCESS_STATE::REGIST_ACCEPT;
CDrawMng::CRegistInfoSum CDrawMng::ms_resistInfoSum;
CDrawMng::CRegistInfoSum CDrawMng::ms_resistInfoSumScreen;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSum;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSumOvr;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSumScreen;
CDrawMng::CDrawInfoSum   CDrawMng::ms_drawInfoSumScreenOvr;
std::thread              CDrawMng::ms_mainLoopTh(MainLoop);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �`���񑍊��N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDrawMng::CDrawInfoSum::CDrawInfoSum() {

	ms_drawInfos   = NULL;
	ms_drawInfoNum = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CDrawMng::CDrawInfoSum::~CDrawInfoSum() {

}

//========================================
// �������
//========================================
void CDrawMng::CDrawInfoSum::Release(void) {

	// �`��������
	if (ms_drawInfos != NULL) {
		for (int cnt = 0; cnt < ms_drawInfoNum; cnt++) {
			RNLib::Memory()->Release<CDrawInfoBase>(&ms_drawInfos[cnt]);
		}
		RNLib::Memory()->Release<CDrawInfoBase*>(&ms_drawInfos);
	}
}

//========================================
// �㏑������
//========================================
void CDrawMng::CDrawInfoSum::Overwrite(CDrawInfoSum* pOvr) {

	// �������
	Release();

	// �㏑��
	ms_drawInfos         = pOvr->ms_drawInfos;
	ms_drawInfoNum       = pOvr->ms_drawInfoNum;
	pOvr->ms_drawInfos   = NULL;
	pOvr->ms_drawInfoNum = 0;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �o�^����񑍊��N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDrawMng::CRegistInfoSum::CRegistInfoSum() {

	m_polygon2DRegistInfos   = NULL;
	m_polygon2DRegistInfoNum = 0;
	m_polygon3DRegistInfos   = NULL;
	m_polygon3DRegistInfoNum = 0;
	m_text2DRegistInfos      = NULL;
	m_text2DRegistInfoNum    = 0;
	m_text3DRegistInfos      = NULL;
	m_text3DRegistInfoNum    = 0;
	m_modelRegistInfos       = NULL;
	m_modelRegistInfoNum     = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CDrawMng::CRegistInfoSum::~CRegistInfoSum() {

}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �`��N���X�̃X���b�h�p�ÓI�����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// ���C�����[�v
//========================================
void CDrawMng::MainLoop(void) {
	while (true) {
		if (ms_processState == PROCESS_STATE::REGIST_INFO_APPLY_WAIT)
		{// [ �o�^���K�p�҂� ]�̎��A
			// �o�^�������ɐݒu����
			PutBasedRegistInfo(ms_resistInfoSum, false);
			PutBasedRegistInfo(ms_resistInfoSumScreen, true);

			// �o�^����`����ɕϊ�����
			ConvRegistInfoToDrawInfo(ms_resistInfoSum, ms_drawInfoSumOvr);
			ConvRegistInfoToDrawInfo(ms_resistInfoSumScreen, ms_drawInfoSumScreenOvr);

			// �`������\�[�g����
			SortDrawInfo(ms_drawInfoSumOvr);
			SortDrawInfo(ms_drawInfoSumScreenOvr);

			// [ �`�������ւ��҂� ]�ɂ���
			ms_processState = PROCESS_STATE::DRAW_INFO_SWAP_WAIT;
		}

		// ���S�͂ŉ񂳂Ȃ��悤��0�b�X���[�v
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
	}
}

//========================================
// �o�^�������ɐݒu����
//========================================
void CDrawMng::PutBasedRegistInfo(CRegistInfoSum& resistInfoSum, const bool& isOnScreen) {

	//----------------------------------------
	// �e�L�X�g2D����|���S��2D��ݒu
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_text2DRegistInfoNum; cnt++) {
		resistInfoSum.m_text2DRegistInfos[cnt].PutPolygon2D(isOnScreen);
	}

	// ���
	resistInfoSum.m_text2DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_text2DRegistInfos);

	//----------------------------------------
	// �e�L�X�g3D����|���S��3D��ݒu
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_text3DRegistInfoNum; cnt++) {
		resistInfoSum.m_text3DRegistInfos[cnt].PutPolygon3D(isOnScreen);
	}

	// ���
	resistInfoSum.m_text3DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_text3DRegistInfos);
}

//========================================
// �o�^����`����ɕϊ�����
//========================================
void CDrawMng::ConvRegistInfoToDrawInfo(CRegistInfoSum& resistInfoSum, CDrawInfoSum& drawInfoSum) {

	int cntDrawInfo = 0;

	{// �`����̃������m��
		drawInfoSum.ms_drawInfoNum = 
			resistInfoSum.m_polygon2DRegistInfoNum +	// �|���S��2D
			resistInfoSum.m_polygon3DRegistInfoNum +	// �|���S��3D
			resistInfoSum.m_modelRegistInfoNum +		// ���f��
			0;
		RNLib::Memory()->Alloc<CDrawInfoBase*>(&drawInfoSum.ms_drawInfos, drawInfoSum.ms_drawInfoNum);
	}

	//----------------------------------------
	// �|���S��3D
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_polygon3DRegistInfoNum; cnt++, cntDrawInfo++) {
		drawInfoSum.ms_drawInfos[cntDrawInfo] = resistInfoSum.m_polygon3DRegistInfos[cnt].ConvToDrawInfo();
	}

	// ���
	resistInfoSum.m_polygon3DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_polygon3DRegistInfos);

	//----------------------------------------
	// ���f��
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_modelRegistInfoNum; cnt++, cntDrawInfo++) {
		drawInfoSum.ms_drawInfos[cntDrawInfo] = resistInfoSum.m_modelRegistInfos[cnt].ConvToDrawInfo();
	}

	// ���
	resistInfoSum.m_modelRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_modelRegistInfos);

	//----------------------------------------
	// �|���S��2D
	//----------------------------------------
	for (int cnt = 0; cnt < resistInfoSum.m_polygon2DRegistInfoNum; cnt++, cntDrawInfo++) {
		drawInfoSum.ms_drawInfos[cntDrawInfo] = resistInfoSum.m_polygon2DRegistInfos[cnt].ConvToDrawInfo();
	}

	// ���
	resistInfoSum.m_polygon2DRegistInfoNum = 0;
	RNLib::Memory()->Release(&resistInfoSum.m_polygon2DRegistInfos);
}

//========================================
// �`����\�[�g����
//========================================
void CDrawMng::SortDrawInfo(CDrawInfoSum& drawInfoSum) {

	// �`����̐���0�ȉ��Ȃ�I��
	if (drawInfoSum.ms_drawInfoNum <= 0)
		return;

	//----------------------------------------
	// ���[�J���֐��̒�`
	//----------------------------------------
	struct LocalFunc {
		// [[[ �D�悷�邩���ׂ�(�|���S��3D�ƃ��f��) ]]]
		static bool FindPrioritizePolygon3DAndModel(CPolygon3D::CDrawInfo* base, CModel::CDrawInfo* target) {

			if (base->m_isZTest && !target->m_isZTest) return true;		// ���Z�e�X�g��ON�Ŕ�r�Ώۂ̂�Z�e�X�g��OFF
			if (!base->m_isZTest && target->m_isZTest) return false;	// ���Z�e�X�g��OFF�Ŕ�r�Ώۂ�Z�e�X�g��ON
			if (base->m_distance > target->m_distance) return true;		// ��̕�������������

			return false;
		}

		// [[[ �D�悷�邩���ׂ� ]]]
		static bool FindPrioritize(CDrawInfoBase& base, CDrawInfoBase& target) {

			if (&base == NULL || &target == NULL) return false;		// �Е������݂��Ȃ�

			// �����Ԃ��͕̂`���D�悷�邩�Ȃ̂Œ���
			if (base.m_priority < target.m_priority) return true;	// ��̕����D��x���Ⴂ
			if (base.m_priority > target.m_priority) return false;	// ��̕����D��x������

			if (base.m_type == CDrawInfoBase::TYPE::POLYGON2D) {
				//----------------------------------------
				// [[[ Base:�|���S��2D ]]]
				//----------------------------------------
				if (target.m_type == CDrawInfoBase::TYPE::POLYGON2D)
				{// [[[ Target::�|���S��2D ]]]
					CPolygon2D::CDrawInfo* castedBase   = (CPolygon2D::CDrawInfo*)&base;
					CPolygon2D::CDrawInfo* castedTarget = (CPolygon2D::CDrawInfo*)&target;

					if (castedBase->m_isZTest && !castedTarget->m_isZTest) return true;		// ���Z�e�X�g��ON�Ŕ�r�Ώۂ̂�Z�e�X�g��OFF
					if (!castedBase->m_isZTest && castedTarget->m_isZTest) return false;	// ���Z�e�X�g��OFF�Ŕ�r�Ώۂ�Z�e�X�g��ON
					if (castedBase->m_distance > castedTarget->m_distance) return true;		// ��̕�������������
				}
				else if (target.m_type == CDrawInfoBase::TYPE::POLYGON3D)
				{// [[[ Target::�|���S��3D ]]]
					return true;
				}
				else if (target.m_type == CDrawInfoBase::TYPE::MODEL)
				{// [[[ Target:���f�� ]]]
					return true;
				}
				else assert(false);
			}
			else if (base.m_type == CDrawInfoBase::TYPE::POLYGON3D) {
				//----------------------------------------
				// [[[ Base:�|���S��3D ]]]
				//----------------------------------------
				if (target.m_type == CDrawInfoBase::TYPE::POLYGON2D) 
				{// [[[ Target::�|���S��2D ]]]
					return false;
				}
				else if (target.m_type == CDrawInfoBase::TYPE::POLYGON3D)
				{// [[[ Target::�|���S��3D ]]]
					CPolygon3D::CDrawInfo* castedBase   = (CPolygon3D::CDrawInfo*)&base;
					CPolygon3D::CDrawInfo* castedTarget = (CPolygon3D::CDrawInfo*)&target;

					if (castedBase->m_isZTest && !castedTarget->m_isZTest) return true;		// ���Z�e�X�g��ON�Ŕ�r�Ώۂ̂�Z�e�X�g��OFF
					if (!castedBase->m_isZTest && castedTarget->m_isZTest) return false;	// ���Z�e�X�g��OFF�Ŕ�r�Ώۂ�Z�e�X�g��ON
					if (castedBase->m_distance > castedTarget->m_distance) return true;		// ��̕�������������
				}
				else if (target.m_type == CDrawInfoBase::TYPE::MODEL)
				{// [[[ Target:���f�� ]]]
					return FindPrioritizePolygon3DAndModel((CPolygon3D::CDrawInfo*)&base, (CModel::CDrawInfo*)&target);
				}
				else assert(false);
			}
			else if (base.m_type == CDrawInfoBase::TYPE::MODEL) {
				//----------------------------------------
				// [[[ Base:���f�� ]]]
				//----------------------------------------
				if (target.m_type == CDrawInfoBase::TYPE::POLYGON2D)
				{// [[[ Target::�|���S��2D ]]]
					return false;
				}
				else if (target.m_type == CDrawInfoBase::TYPE::POLYGON3D)
				{// [[[ Target::�|���S��3D ]]]
					return !FindPrioritizePolygon3DAndModel((CPolygon3D::CDrawInfo*)&target, (CModel::CDrawInfo*)&base);
				}
				else if (target.m_type == CDrawInfoBase::TYPE::MODEL)
				{// [[[ Target:���f�� ]]]
					CModel::CDrawInfo* castedBase = (CModel::CDrawInfo*)&base;
					CModel::CDrawInfo* castedTarget = (CModel::CDrawInfo*)&target;
					
					if (castedBase->m_isZTest && !castedTarget->m_isZTest) return true;		// ���Z�e�X�g��ON�Ŕ�r�Ώۂ̂�Z�e�X�g��OFF
					if (!castedBase->m_isZTest && castedTarget->m_isZTest) return false;	// ���Z�e�X�g��OFF�Ŕ�r�Ώۂ�Z�e�X�g��ON
					if (castedBase->m_distance > castedTarget->m_distance) return true;		// ��̕�������������
				}
				else assert(false);
			}
			else assert(false);

			return false;
		}
	};

	//----------------------------------------
	// �\�[�g����
	//      cnt1
	// [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ �c ]
	// �����̏ꍇ2�����r���Ă���
	//----------------------------------------
	int cnt1Num = drawInfoSum.ms_drawInfoNum - 1;
	for (int cnt1 = 0; cnt1 < cnt1Num; cnt1++) {

		// �ŗD��̃J�E���g�𒲂ׂ�
		int cntTop = DATANONE;
		for (int cnt2 = cnt1 + 1; cnt2 < drawInfoSum.ms_drawInfoNum; cnt2++) {
			CDrawInfoBase& drawInfoCnt2 = *drawInfoSum.ms_drawInfos[cnt2];

			//----------------------------------------
			// Cnt2�̕`���� �� ���̍ŗD��`���� ���
			// �D��x���������ǂ������肷��
			//----------------------------------------
			bool isTopPriorityCnt2 = false;

			// �ŗD��̃J�E���g��NONE(�܂�ŏ��̃J�E���g)�̎��ACnt2�̕����D��x�������Ƃ���
			if (cntTop == DATANONE) {
				isTopPriorityCnt2 = true;
			}
			else {
				isTopPriorityCnt2 = LocalFunc::FindPrioritize(drawInfoCnt2, *drawInfoSum.ms_drawInfos[cntTop]);
			}
			
			// ����̌��ʁc
			// Cnt2�̕`���� �̕����D��x�������������A
			// �ŗD��̃J�E���g���㏑������
			if (isTopPriorityCnt2)
				cntTop = cnt2;
		}

		// Cnt1�`���� �̕��� �ŗD��`���� ���D��x���Ⴂ���A����ւ���
		if (!LocalFunc::FindPrioritize(*drawInfoSum.ms_drawInfos[cnt1], *drawInfoSum.ms_drawInfos[cntTop])) {
			CDrawInfoBase* drwInfoTemp = drawInfoSum.ms_drawInfos[cnt1];
			drawInfoSum.ms_drawInfos[cnt1] = drawInfoSum.ms_drawInfos[cntTop];
			drawInfoSum.ms_drawInfos[cntTop] = drwInfoTemp;
		}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �`��N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CDrawMng::CDrawMng() {

}

//========================================
// �f�X�g���N�^
//========================================
CDrawMng::~CDrawMng() {

}

//========================================
// �ݒu����(�|���S��2D)
//========================================
CPolygon2D::CRegistInfo* CDrawMng::PutPolygon2D(const D3DXVECTOR3& pos, const float& angle, const bool& isOnScreen) {

	// �o�^���
	CPolygon2D::CRegistInfo* registInfo = NULL;;

	// �X�N���[����t���O�ɉ����ēo�^
	if (isOnScreen) registInfo = &RegistPolygon2D(ms_resistInfoSumScreen);
	else            registInfo = &RegistPolygon2D(ms_resistInfoSum);

	// ������
	registInfo->SetPos(pos);
	registInfo->SetAngle(angle);

	return registInfo;
}

//========================================
// �ݒu����(�e�L�X�g2D)
//========================================
CText2D::CRegistInfo* CDrawMng::PutText2D(const D3DXVECTOR2& pos, const float& angle, const bool& isOnScreen) {

	// �o�^���
	CText2D::CRegistInfo* registInfo = NULL;;

	// �X�N���[����t���O�ɉ����ēo�^
	if (isOnScreen) registInfo = &RegistText2D(ms_resistInfoSumScreen);
	else            registInfo = &RegistText2D(ms_resistInfoSum);

	// ������
	registInfo->SetPos(pos);
	registInfo->SetAngle(angle);

	return registInfo;
}

//========================================
// �ݒu����(�e�L�X�g3D)
//========================================
CText3D::CRegistInfo* CDrawMng::PutText3D(const D3DXMATRIX& mtx, const bool& isOnScreen) {

	// �o�^���
	CText3D::CRegistInfo* registInfo = NULL;;

	// �X�N���[����t���O�ɉ����ēo�^
	if (isOnScreen) registInfo = &RegistText3D(ms_resistInfoSumScreen);
	else            registInfo = &RegistText3D(ms_resistInfoSum);

	// ������
	registInfo->SetMtx(mtx);

	return registInfo;
}

//========================================
// �ݒu����(�|���S��3D)
//========================================
CPolygon3D::CRegistInfo* CDrawMng::PutPolygon3D(const D3DXMATRIX& mtx, const bool& isOnScreen) {
	
	// �o�^���
	CPolygon3D::CRegistInfo* registInfo = NULL;;

	// �X�N���[����t���O�ɉ����ēo�^
	if (isOnScreen) registInfo = &RegistPolygon3D(ms_resistInfoSumScreen);
	else            registInfo = &RegistPolygon3D(ms_resistInfoSum);

	// ������
	registInfo->SetMtx(mtx);

	return registInfo;
}

//========================================
// �ݒu����(���f��)
//========================================
CModel::CRegistInfo* CDrawMng::PutModel(const D3DXMATRIX& mtx, const bool& isOnScreen) {

	// �o�^��t���łȂ����A�I��
	if (ms_processState != PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	// �o�^���
	CModel::CRegistInfo* registInfo = NULL;;

	// �X�N���[����t���O�ɉ����ēo�^
	if (isOnScreen) registInfo = &RegistModel(ms_resistInfoSumScreen);
	else            registInfo = &RegistModel(ms_resistInfoSum);

	// ������
	registInfo->SetMtx(mtx);

	return registInfo;
}

//========================================
// �o�^����(�|���S��2D)
//========================================
CPolygon2D::CRegistInfo& CDrawMng::RegistPolygon2D(CRegistInfoSum& resistInfo) {

	// �o�^��񐔂����Z
	int numOld = resistInfo.m_polygon2DRegistInfoNum++;

	// �o�^���̃������Ċm��
	RNLib::Memory()->ReAlloc<CPolygon2D::CRegistInfo>(&resistInfo.m_polygon2DRegistInfos, numOld, resistInfo.m_polygon2DRegistInfoNum);

	return resistInfo.m_polygon2DRegistInfos[numOld];
}

//========================================
// �o�^����(�|���S��3D)
//========================================
CPolygon3D::CRegistInfo& CDrawMng::RegistPolygon3D(CRegistInfoSum& resistInfo) {

	// �o�^��񐔂����Z
	int numOld = resistInfo.m_polygon3DRegistInfoNum++;

	// �o�^���̃������Ċm��
	RNLib::Memory()->ReAlloc<CPolygon3D::CRegistInfo>(&resistInfo.m_polygon3DRegistInfos, numOld, resistInfo.m_polygon3DRegistInfoNum);

	return resistInfo.m_polygon3DRegistInfos[numOld];
}

//========================================
// �o�^����(�e�L�X�g2D)
//========================================
CText2D::CRegistInfo& CDrawMng::RegistText2D(CRegistInfoSum& resistInfo) {

	// �o�^��񐔂����Z
	int numOld = resistInfo.m_text2DRegistInfoNum++;

	// �o�^���̃������Ċm��
	RNLib::Memory()->ReAlloc<CText2D::CRegistInfo>(&resistInfo.m_text2DRegistInfos, numOld, resistInfo.m_text2DRegistInfoNum);

	return resistInfo.m_text2DRegistInfos[numOld];
}

//========================================
// �o�^����(�e�L�X�g3D)
//========================================
CText3D::CRegistInfo& CDrawMng::RegistText3D(CRegistInfoSum& resistInfo) {

	// �o�^��񐔂����Z
	int numOld = resistInfo.m_text3DRegistInfoNum++;

	// �o�^���̃������Ċm��
	RNLib::Memory()->ReAlloc<CText3D::CRegistInfo>(&resistInfo.m_text3DRegistInfos, numOld, resistInfo.m_text3DRegistInfoNum);

	return resistInfo.m_text3DRegistInfos[numOld];
}

//========================================
// �o�^����(���f��)
//========================================
CModel::CRegistInfo& CDrawMng::RegistModel(CRegistInfoSum& resistInfo) {

	// �o�^��񐔂����Z
	int numOld = resistInfo.m_modelRegistInfoNum++;

	// �o�^���̃������Ċm��
	RNLib::Memory()->ReAlloc<CModel::CRegistInfo>(&resistInfo.m_modelRegistInfos, numOld, resistInfo.m_modelRegistInfoNum);

	return resistInfo.m_modelRegistInfos[numOld];
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �`��}�l�[�W���[�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// ����������
//========================================
void CDrawMng::Init(void) {
	
}

//========================================
// �I������
//========================================
void CDrawMng::Uninit(void) {

	// ���C�����[�v�X���b�h���a�藣��
	ms_mainLoopTh.detach();

	// �������
	Release();
}

//========================================
// �������
//========================================
void CDrawMng::Release(void) {

	// �`�����j��
	ms_drawInfoSum.Release();
	ms_drawInfoSumOvr.Release();
	ms_drawInfoSumScreen.Release();
	ms_drawInfoSumScreenOvr.Release();
	RNLib::Memory()->Release(&ms_drawInfoSum.ms_drawInfos);
	RNLib::Memory()->Release(&ms_drawInfoSumOvr.ms_drawInfos);
	RNLib::Memory()->Release(&ms_drawInfoSumScreen.ms_drawInfos);
	RNLib::Memory()->Release(&ms_drawInfoSumScreenOvr.ms_drawInfos);

	// ���_�o�b�t�@��j������
	CPolygon2D::CDrawInfo::ReleaseVertexBuffer();
	CPolygon3D::CDrawInfo::ReleaseVertexBuffer();
}

//========================================
// �`��J�n����
//========================================
bool CDrawMng::StartDraw(void) {

	if (ms_processState == PROCESS_STATE::REGIST_ACCEPT)
	{// [ �o�^��t ]�̎��A
		// [ �o�^���K�p�҂� ]�ɂ���
		ms_processState = PROCESS_STATE::REGIST_INFO_APPLY_WAIT;
	}
	else if ((ms_processState == PROCESS_STATE::DRAW_INFO_SWAP_WAIT && !RNLib::GetSpace3DStop()) || RNLib::GetSceneSwap())
	{// [ �`�����ւ��҂� ]�̎��A
		// �`������㏑������
		ms_drawInfoSum.Overwrite(&ms_drawInfoSumOvr);
		ms_drawInfoSumScreen.Overwrite(&ms_drawInfoSumScreenOvr);

		// ���_�o�b�t�@�𐶐�����
		CPolygon2D::CDrawInfo::CreateVertexBuffer();
		CPolygon3D::CDrawInfo::CreateVertexBuffer();

		// ���_������
		AssignVertexInfo();

		// [ �o�^��t ]�ɂ���
		ms_processState = PROCESS_STATE::REGIST_ACCEPT;

		return true;
	}

	return false;
}

//========================================
// ���_���������
//========================================
void CDrawMng::AssignVertexInfo(void) {

	// ���_2D���ɕϊ�
	if (CPolygon2D::CDrawInfo::m_vtxBuff != NULL) {
		VERTEX_2D* vtxs = NULL;
		CPolygon2D::CDrawInfo::m_vtxBuff->Lock(0, 0, (void**)&vtxs, 0);

		ConvDrawInfoToVertex2DInfo(vtxs, ms_drawInfoSum);
		ConvDrawInfoToVertex2DInfo(vtxs, ms_drawInfoSumScreen);

		CPolygon2D::CDrawInfo::m_vtxBuff->Unlock();
	}

	// ���_3D���ɕϊ�
	if (CPolygon3D::CDrawInfo::m_vtxBuff != NULL) {
		VERTEX_3D* vtxs = NULL;
		CPolygon3D::CDrawInfo::m_vtxBuff->Lock(0, 0, (void**)&vtxs, 0);

		ConvDrawInfoToVertex3DInfo(vtxs, ms_drawInfoSum);
		ConvDrawInfoToVertex3DInfo(vtxs, ms_drawInfoSumScreen);

		CPolygon3D::CDrawInfo::m_vtxBuff->Unlock();
	}
}

//========================================
// �`����𒸓_2D���ɕϊ�
//========================================
void CDrawMng::ConvDrawInfoToVertex2DInfo(VERTEX_2D* vtxs, CDrawInfoSum& drawInfoSum) {

	for (int cntDrawInfo = 0; cntDrawInfo < drawInfoSum.ms_drawInfoNum; cntDrawInfo++) {
		if (drawInfoSum.ms_drawInfos[cntDrawInfo]->m_type == CDrawInfoBase::TYPE::POLYGON2D) {
			CPolygon2D::CDrawInfo& drawInfo = (CPolygon2D::CDrawInfo&)*drawInfoSum.ms_drawInfos[cntDrawInfo];
			int vtxStartIdx = 4 * drawInfo.m_idx;

			for (int cntVtx = 0; cntVtx < 4; cntVtx++) {
				int vtxIdx = vtxStartIdx + cntVtx;
				vtxs[vtxIdx] = drawInfo.m_vtxs[cntVtx];
			}
		}
	}
}

//========================================
// �`����𒸓_3D���ɕϊ�
//========================================
void CDrawMng::ConvDrawInfoToVertex3DInfo(VERTEX_3D* vtxs, CDrawInfoSum& drawInfoSum) {

	for (int cntDrawInfo = 0; cntDrawInfo < drawInfoSum.ms_drawInfoNum; cntDrawInfo++) {
		if (drawInfoSum.ms_drawInfos[cntDrawInfo]->m_type == CDrawInfoBase::TYPE::POLYGON3D) {
			CPolygon3D::CDrawInfo& drawInfo = (CPolygon3D::CDrawInfo&)*drawInfoSum.ms_drawInfos[cntDrawInfo];
			int vtxStartIdx = 4 * drawInfo.m_idx;

			for (int cntVtx = 0; cntVtx < 4; cntVtx++) {
				int vtxIdx = vtxStartIdx + cntVtx;
				vtxs[vtxIdx] = drawInfo.m_vtxs[cntVtx];
			}
		}
	}
}

//========================================
// �`�揈��
//========================================
void CDrawMng::Draw(LPDIRECT3DDEVICE9& device, const bool& isOnScreen) {

	// �r���[�}�g���b�N�X���擾
	D3DXMATRIX viewMtx;
	device->GetTransform(D3DTS_VIEW, &viewMtx);

	// �`�悵�Ă���
	if (isOnScreen) {
		for (int cntDrawInfo = 0; cntDrawInfo < ms_drawInfoSumScreen.ms_drawInfoNum; cntDrawInfo++) {
			if (ms_drawInfoSumScreen.ms_drawInfos[cntDrawInfo] != NULL)
				ms_drawInfoSumScreen.ms_drawInfos[cntDrawInfo]->Draw(device, viewMtx);
		}
	}
	else {
		for (int cntDrawInfo = 0; cntDrawInfo < ms_drawInfoSum.ms_drawInfoNum; cntDrawInfo++) {
			if (ms_drawInfoSum.ms_drawInfos[cntDrawInfo] != NULL)
				ms_drawInfoSum.ms_drawInfos[cntDrawInfo]->Draw(device, viewMtx);
		}
	}
}