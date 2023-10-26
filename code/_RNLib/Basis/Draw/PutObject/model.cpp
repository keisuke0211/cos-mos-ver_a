//========================================
// 
// ���f���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../../RNLib.h"

//****************************************
// �萔��`
//****************************************
#define OUTLINE_ADD_DIST (0.2f)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]���f���N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CModel::CModel() {

	m_datas = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CModel::~CModel() {

	// �������
	Release();
}

//========================================
// �������
//========================================
void CModel::Release(void) {

	// �f�[�^�̉��
	for (int cntData = 0; cntData < m_num; cntData++) {
		m_datas[cntData].Release();
	}
	RNLib::Memory().Release(&m_datas);
}

//========================================
// �ǂݍ��ݏ���
//========================================
short CModel::Load(const char* loadPath, short idx) {

	const unsigned short oldNum(m_num);
	const short idxOld(idx);

	if (CRegist::Load(loadPath, idx)) 
	{// �ǂݍ��ݐ���
		// �f�[�^�̃������Ċm��
		RNLib::Memory().ReAlloc(&m_datas, oldNum, m_num);

		// �f�[�^�̔j��(�ԍ��w��̏ꍇ)
		if (idxOld != NONEDATA)
			m_datas[idx].Release();

		// X�t�@�C���̓ǂݍ���
		Device device(RNLib::Window().GetD3DDevice());
		if (FAILED(D3DXLoadMeshFromX(loadPath, D3DXMESH_SYSTEMMEM, device, NULL, &m_datas[idx].m_matBuff, NULL, (DWORD*)&m_datas[idx].m_matNum, &m_datas[idx].m_mesh))) 
		{// �ǂݍ��ݎ��s
			// �G���[���b�Z�[�W
			RNLib::Window().Message_ERROR(CreateText("���f���̓ǂݍ��݂Ɏ��s���܂����B\n%s", loadPath));

			// �f�[�^�̃��������Z�b�g
			RNLib::Memory().ReAlloc(&m_datas, m_num, oldNum);

			// �ǂݍ��ݍσp�X�̃��������Z�b�g
			ReAllocLoadPath(oldNum);

			// �������Z�b�g
			m_num = oldNum;

			return NONEDATA;
		}
		else 
		{// �ǂݍ��݂ɐ����������A
			//----------------------------------------
			// �֊s�����b�V���̐��� & ���a�̍ő�𒲂ׂ�
			//----------------------------------------
			{
				// �֊s���p�ɂ�����x�ǂݍ���
				D3DXLoadMeshFromX(loadPath, D3DXMESH_SYSTEMMEM, device, NULL, NULL, NULL, NULL, &m_datas[idx].m_outLineMesh);

				// ���_�t�H�[�}�b�g�̃T�C�Y���擾
				const DWORD dwSizeFVF(D3DXGetFVFVertexSize(m_datas[idx].m_outLineMesh->GetFVF()));

				// ���_�o�b�t�@�����b�N
				BYTE* vtxBuff;
				m_datas[idx].m_outLineMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vtxBuff);

				// �@�������ɉ��Z
				int nVtxNum((int)m_datas[idx].m_outLineMesh->GetNumVertices());
				for (int nCntVtx = 0; nCntVtx < nVtxNum; nCntVtx++) {
					D3DXVECTOR3* pos( (D3DXVECTOR3*)(vtxBuff + (dwSizeFVF * nCntVtx)));
					D3DXVECTOR3  nor(*(D3DXVECTOR3*)(vtxBuff + (dwSizeFVF * nCntVtx) + D3DXGetFVFVertexSize(D3DFVF_XYZ)));

					{// ���a�̍ő�𒲂ׂ�
						float dist(CGeometry::FindDistance(INITD3DXVECTOR3, *pos));

						if (m_datas[idx].m_radiusMax < dist) {
							m_datas[idx].m_radiusMax = dist;
						}
					}

					*pos += nor * OUTLINE_ADD_DIST;
				}

				// ���_�o�b�t�@���A�����b�N
				m_datas[idx].m_outLineMesh->UnlockVertexBuffer();
			}// <<< >>>

			// �}�e���A�����ɑ΂���|�C���^���擾
			const D3DXMATERIAL* mats((D3DXMATERIAL*)m_datas[idx].m_matBuff->GetBufferPointer());

			// �e�N�X�`���ԍ��̃������m��
			RNLib::Memory().Alloc(&m_datas[idx].m_texIdxs, m_datas[idx].m_matNum);

			// �e�N�X�`���̓ǂݍ���
			for (int nCntMat(0); nCntMat < m_datas[idx].m_matNum; nCntMat++)
				m_datas[idx].m_texIdxs[nCntMat] = (mats[nCntMat].pTextureFilename != NULL) ? RNLib::Texture().Load(mats[nCntMat].pTextureFilename) : NONEDATA;
		}
	}

	return idx;
}

//========================================
// �ݒu����
//========================================
CModel::CRegistInfo* CModel::Put(const Matrix& mtx, const short& modelIdx, const bool& isOnScreen) {

	// �o�^��t���łȂ����A�I��
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng().PutModel(mtx, isOnScreen)
		->SetModel(modelIdx);
}

//========================================
// �ݒu����(�ʒu�ƌ����Ŏw��)
//========================================
CModel::CRegistInfo* CModel::Put(const Pos3D& pos, const Rot3D& rot, const short& modelIdx, const bool& isOnScreen) {
	
	return Put(CMatrix::ConvPosRotToMtx(pos, rot), modelIdx, isOnScreen);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �f�[�^�N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CModel::CData::CData() {

	m_texIdxs     = NULL;
	m_mesh        = NULL;
	m_outLineMesh = NULL;
	m_matBuff     = NULL;
	m_matNum      = 0;
	m_radiusMax   = 0.0f;
}

//========================================
// �f�X�g���N�^
//========================================
CModel::CData::~CData() {

}

//========================================
// �������
//========================================
void CModel::CData::Release(void) {

	// �e�N�X�`���ԍ��̔j��
	RNLib::Memory().Release(&m_texIdxs);

	// ���b�V���̔j��
	if (m_mesh != NULL) {
		m_mesh->Release();
		m_mesh = NULL;
	}

	// �֊s�����b�V���̔j��
	if (m_outLineMesh != NULL) {
		m_outLineMesh->Release();
		m_outLineMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_matBuff != NULL) {
		m_matBuff->Release();
		m_matBuff = NULL;
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �`����N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CModel::CDrawInfo::CDrawInfo() {

	m_mtx                  = INITD3DXMATRIX;
	m_col                  = INITCOLOR;
	m_modelIdx             = NONEDATA;
	m_texIdx               = NONEDATA;
	m_isZTest              = true;
	m_isLighting           = false;
	m_isOutLine            = false;
	m_brightnessOfEmissive = 1.0f;
	m_distance             = 0.0f;
}

//========================================
// �f�X�g���N�^
//========================================
CModel::CDrawInfo::~CDrawInfo() {

}

//========================================
// �`�揈��
//========================================
void CModel::CDrawInfo::Draw(Device& device, const Matrix& viewMtx) {

	//----------------------------------------
	// ���O����
	//----------------------------------------
	// ���f���f�[�^���擾
	const CData& modelData(RNLib::Model().GetData(m_modelIdx));

	// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &m_mtx);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* mats((D3DXMATERIAL*)modelData.m_matBuff->GetBufferPointer());

	//----------------------------------------
	// �ꎞ�I�ȕ`�惂�[�h�ݒ���J�n
	//----------------------------------------
	RNLib::DrawStateMng().StartTemporarySetMode();

	for (int cntMat(0); cntMat < modelData.m_matNum; cntMat++) {
		
		//----------------------------------------
		// �p�����[�^�[�ɉ������ݒ�
		//----------------------------------------
		{// [[[ �}�e���A���̐ݒ� ]]]
			Color setCol = m_col;

			// ���������̖��邳���ݒ肳��Ă��鎞�A
			if (m_brightnessOfEmissive < 1.0f) {

				// �����v�f������ΓK�p
				if (0.0f < mats[cntMat].MatD3D.Emissive.r + mats[cntMat].MatD3D.Emissive.g + mats[cntMat].MatD3D.Emissive.b) {
					setCol = BrightnessToColor(setCol, m_brightnessOfEmissive);
				}
			}
			
			// �}�e���A����ݒ�
			SetMaterial(device, &mats[cntMat].MatD3D, setCol);
		}

		// [[[ �e�N�X�`���̐ݒ� ]]]
		RNLib::Texture().Set(device, (m_texIdx == NONEDATA) ? modelData.m_texIdxs[cntMat] : m_texIdx);

		//----------------------------------------
		// �`��
		//----------------------------------------
		// �\�ʂ�`��
		RNLib::DrawStateMng().SetCullingMode(CDrawState::CULLING_MODE::FRONT_SIDE, device);
		modelData.m_mesh->DrawSubset(cntMat);

		//----------------------------------------
		// �֊s���̕`��
		//----------------------------------------
		if (m_isOutLine) {

			// �}�e���A���̐ݒ�
			SetMaterial(device, &mats[cntMat].MatD3D, COLOR_BLACK);

			// ���ʂ�`��
			RNLib::DrawStateMng().SetCullingMode(CDrawState::CULLING_MODE::BACK_SIDE, device);
			modelData.m_outLineMesh->DrawSubset(cntMat);
		}
	}

	//----------------------------------------
	// �ꎞ�I�ȕ`�惂�[�h�ݒ���I��
	//----------------------------------------
	RNLib::DrawStateMng().EndTemporarySetMode(device);
}

//========================================
// �}�e���A���ݒ菈��
//========================================
void CModel::CDrawInfo::SetMaterial(Device& device, Material* mat, const Color& col) {

	// �}�e���A���̍ގ��p�����[�^��ۑ�
	const D3DXCOLOR diffuseTemp (mat->Diffuse);
	const D3DXCOLOR emissiveTemp(mat->Emissive);

	// �}�e���A���̍ގ��p�����[�^��ݒ�
	const float r = (float)col.r / 255;
	const float g = (float)col.g / 255;
	const float b = (float)col.b / 255;
	const float a = (float)col.a / 255;
	mat->Diffuse.r  = diffuseTemp .r * r;
	mat->Diffuse.g  = diffuseTemp .g * g;
	mat->Diffuse.b  = diffuseTemp .b * b;
	mat->Diffuse.a  = diffuseTemp .a * a;
	mat->Emissive.r = emissiveTemp.r * r;
	mat->Emissive.g = emissiveTemp.g * g;
	mat->Emissive.b = emissiveTemp.b * b;
	mat->Emissive.a = emissiveTemp.a * a;

	// �}�e���A���̐ݒ�
	device->SetMaterial(mat);

	// �}�e���A���̍ގ��p�����[�^�����ɖ߂�
	mat->Diffuse  = diffuseTemp;
	mat->Emissive = emissiveTemp;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| [���J]�o�^���N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CModel::CRegistInfo::CRegistInfo() {

	m_mtx                  = INITD3DXMATRIX;
	m_col                  = INITCOLOR;
	m_modelIdx             = NONEDATA;
	m_texIdx               = NONEDATA;
	m_isZTest              = false;
	m_isLighting           = false;
	m_isOutLine            = false;
	m_brightnessOfEmissive = 1.0f;
	m_priority             = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CModel::CRegistInfo::~CRegistInfo() {

}

//========================================
// �p�����[�^�[�̃N���A����
//========================================
void CModel::CRegistInfo::ClearParameter(void) {

	m_mtx                  = INITD3DXMATRIX;
	m_col                  = INITCOLOR;
	m_modelIdx             = NONEDATA;
	m_texIdx               = NONEDATA;
	m_isZTest              = false;
	m_isLighting           = false;
	m_isOutLine            = false;
	m_brightnessOfEmissive = 1.0f;
	m_priority             = 0;
}

//========================================
// �`����ɕϊ�
//========================================
CModel::CDrawInfo* CModel::CRegistInfo::ConvToDrawInfo(void) {

	// �`����̃������m��
	CDrawInfo* drawInfo(NULL);
	RNLib::Memory().Alloc(&drawInfo);

	// ������
	// (���)
	drawInfo->m_type                 = CDrawInfoBase::TYPE::MODEL;
	drawInfo->m_priority             = m_priority;
	// (�p��)
	drawInfo->m_mtx                  = m_mtx;
	drawInfo->m_col                  = m_col;
	drawInfo->m_modelIdx             = m_modelIdx;
	drawInfo->m_texIdx               = m_texIdx;
	drawInfo->m_isZTest              = m_isZTest;
	drawInfo->m_isLighting           = m_isLighting;
	drawInfo->m_isOutLine            = m_isOutLine;
	drawInfo->m_brightnessOfEmissive = m_brightnessOfEmissive;
	{// �������Z�o
		// �g��{���̍ő���Z�o
		float scaleMax = 0.0f; {
			Scale3D scale = CMatrix::ConvMtxToScale(m_mtx);

			scaleMax = scale.x;
			if (scaleMax < scale.y)
				scaleMax = scale.y;
			if (scaleMax < scale.z)
				scaleMax = scale.z;
		}
		drawInfo->m_distance = CGeometry::FindDistanceToCameraPlane(CMatrix::ConvMtxToPos(m_mtx), RNLib::Camera3D()) - (RNLib::Model().GetData(m_modelIdx).m_radiusMax * scaleMax);
	}

	return drawInfo;
}


//========================================
// �}�g���b�N�X��ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetMtx(const D3DXMATRIX& mtx) {

	if (this == NULL)
		return NULL;

	m_mtx = mtx;

	return this;
}

//========================================
// �F��ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetCol(const Color& col) {

	if (this == NULL)
		return NULL;

	m_col = col;

	return this;
}

//========================================
// ���f����ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetModel(const short& modelIdx) {

	if (this == NULL)
		return NULL;

	m_modelIdx = modelIdx;

	return this;
}

//========================================
// �e�N�X�`����ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetTex(const short& texIdx) {

	if (this == NULL)
		return NULL;

	m_texIdx = texIdx;

	return this;
}

//========================================
// Z�e�X�g��ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetZTest(const bool& isZTest) {

	if (this == NULL)
		return NULL;

	m_isZTest = isZTest;

	return this;
}

//========================================
// ���C�e�B���O��ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetLighting(const bool& isLighting) {

	if (this == NULL)
		return NULL;

	m_isLighting = isLighting;

	return this;
}

//========================================
// �֊s����ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetOutLine(const bool& isOutLine) {

	if (this == NULL)
		return NULL;

	m_isOutLine = isOutLine;

	return this;
}

//========================================
// ���������̖��邳��ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetBrightnessOfEmissive(const float& brightnessOfEmissive) {

	if (this == NULL)
		return NULL;

	m_brightnessOfEmissive = brightnessOfEmissive;

	return this;
}

//========================================
// �D��x�ݒ�
//========================================
CModel::CRegistInfo* CModel::CRegistInfo::SetPriority(const short& priority) {

	if (this == NULL)
		return NULL;

	m_priority = priority;

	return this;
}
