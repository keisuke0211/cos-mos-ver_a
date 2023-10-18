//========================================
// 
// ���f���̏���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//****************************************
// �萔��`
//****************************************
#define OUTLINE_ADD_DIST (0.2f)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| ���f���N���X�̃����o�֐�
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

}

//========================================
// �I������
//========================================
void CModel::Uninit(void) {
	CRegist::Uninit();

	// �������
	Release();
}

//========================================
// �������
//========================================
void CModel::Release(void) {

	// �f�[�^�̔j��
	for (int nCnt = 0; nCnt < m_num; nCnt++) {
		m_datas[nCnt].Release();
	}
	RNLib::Memory()->Release<CData>(&m_datas);
}

//========================================
// �ǂݍ��ݏ���
//========================================
short CModel::Load(const char *loadPath, short idx) {

	unsigned short numOld = m_num;

	if (CRegist::Load(loadPath, &idx)) 
	{// �ǂݍ��ݐ���
		// �f�[�^�̃������Ċm��
		RNLib::Memory()->ReAlloc<CData>(&m_datas, numOld, m_num);

		// �f�[�^�̔j��(�ԍ��w��̏ꍇ)
		if (idx != DATANONE) {
			m_datas[idx].Release();
		}

		// X�t�@�C���̓ǂݍ���
		LPDIRECT3DDEVICE9 device = RNLib::Window()->GetD3DDevice();
		if (FAILED(D3DXLoadMeshFromX(loadPath, D3DXMESH_SYSTEMMEM, device, NULL, &m_datas[idx].m_matBuff, NULL, (DWORD*)&m_datas[idx].m_matNum, &m_datas[idx].m_mesh))) 
		{// �ǂݍ��ݎ��s
			// �f�[�^�̃��������Z�b�g
			RNLib::Memory()->ReAlloc<CData>(&m_datas, m_num, numOld);

			// �ǂݍ��ݍσp�X�̃��������Z�b�g
			RNLib::Memory()->ReAlloc<char*>(&m_ppLoadPath, m_num, numOld);

			// �������Z�b�g
			m_num = numOld;

			return DATANONE;
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
				DWORD dwSizeFVF = D3DXGetFVFVertexSize(m_datas[idx].m_outLineMesh->GetFVF());

				// ���_�o�b�t�@�����b�N
				BYTE* vtxBuff;
				m_datas[idx].m_outLineMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vtxBuff);

				// �@�������ɉ��Z
				int nVtxNum = (int)m_datas[idx].m_outLineMesh->GetNumVertices();
				for (int nCntVtx = 0; nCntVtx < nVtxNum; nCntVtx++) {
					D3DXVECTOR3* pos =  (D3DXVECTOR3*)(vtxBuff + (dwSizeFVF * nCntVtx));
					D3DXVECTOR3  nor = *(D3DXVECTOR3*)(vtxBuff + (dwSizeFVF * nCntVtx) + D3DXGetFVFVertexSize(D3DFVF_XYZ));

					{// ���a�̍ő�𒲂ׂ�
						float dist = Find_Dist(INITD3DXVECTOR3, *pos);

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
			D3DXMATERIAL* mats = (D3DXMATERIAL*)m_datas[idx].m_matBuff->GetBufferPointer();

			// �e�N�X�`���ԍ��̃������m��
			RNLib::Memory()->Alloc<short>(&m_datas[idx].m_texIdxs, m_datas[idx].m_matNum);

			// �e�N�X�`���̓ǂݍ���
			for (int nCntMat = 0; nCntMat < m_datas[idx].m_matNum; nCntMat++) {
				if (mats[nCntMat].pTextureFilename != NULL) {
					m_datas[idx].m_texIdxs[nCntMat] = RNLib::Texture()->Load(mats[nCntMat].pTextureFilename);
				}
				else {
					m_datas[idx].m_texIdxs[nCntMat] = DATANONE;
				}
			}
		}
	}

	return idx;
}

//========================================
// �ݒu����
//========================================
CModel::CRegistInfo* CModel::Put(const D3DXMATRIX& mtx, const short& modelIdx, const bool& isOnScreen) {

	// �o�^��t���łȂ����A�I��
	if (CDrawMng::GetProcessState() != CDrawMng::PROCESS_STATE::REGIST_ACCEPT)
		return NULL;

	return RNLib::DrawMng()->PutModel(mtx, isOnScreen)
		->SetModel(modelIdx);
}

//========================================
// �ݒu����(�ʒu�ƌ����Ŏw��)
//========================================
CModel::CRegistInfo* CModel::Put(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const short& modelIdx, const bool& isOnScreen) {
	
	return Put(ConvPosRotToMatrix(pos, rot), modelIdx, isOnScreen);
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
	RNLib::Memory()->Release<short>(&m_texIdxs);

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
	m_modelIdx             = DATANONE;
	m_texIdx               = DATANONE;
	m_isZTest              = true;
	m_isLighting           = true;
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
void CModel::CDrawInfo::Draw(LPDIRECT3DDEVICE9& device, const D3DXMATRIX& viewMtx) {

	//----------------------------------------
	// ���O����
	//----------------------------------------
	// ���f���f�[�^���擾
	CData& modelData = RNLib::Model()->GetData(m_modelIdx);

	// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &m_mtx);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	D3DXMATERIAL* mats = (D3DXMATERIAL*)modelData.m_matBuff->GetBufferPointer();

	//----------------------------------------
	// �ꎞ�I�ȕ`�惂�[�h�ݒ���J�n
	//----------------------------------------
	RNLib::DrawStateMng()->StartTemporarySetMode();

	RNLib::DrawStateMng()->SetLightingMode(m_isLighting, device);

	for (int cntMat = 0; cntMat < modelData.m_matNum; cntMat++) {
		
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
		if (m_texIdx == DATANONE)
			RNLib::Texture()->Set(device, modelData.m_texIdxs[cntMat]);
		else
			RNLib::Texture()->Set(device, m_texIdx);

		//----------------------------------------
		// �`��
		//----------------------------------------
		// �\�ʂ�`��
		RNLib::DrawStateMng()->SetCullingMode(CDrawState::CULLING_MODE::FRONT_SIDE, device);
		modelData.m_mesh->DrawSubset(cntMat);

		//----------------------------------------
		// �֊s���̕`��
		//----------------------------------------
		if (m_isOutLine) {

			// �}�e���A���̐ݒ�
			SetMaterial(device, &mats[cntMat].MatD3D, COLOR_BLACK);

			// ���ʂ�`��
			RNLib::DrawStateMng()->SetCullingMode(CDrawState::CULLING_MODE::BACK_SIDE, device);
			modelData.m_outLineMesh->DrawSubset(cntMat);
		}
	}

	//----------------------------------------
	// �ꎞ�I�ȕ`�惂�[�h�ݒ���I��
	//----------------------------------------
	RNLib::DrawStateMng()->EndTemporarySetMode(device);
}

//========================================
// �}�e���A���ݒ菈��
//========================================
void CModel::CDrawInfo::SetMaterial(LPDIRECT3DDEVICE9& device, D3DMATERIAL9* mat, const Color& col) {

	// �}�e���A���̍ގ��p�����[�^��ۑ�
	D3DXCOLOR DiffuseTemp  = mat->Diffuse;
	D3DXCOLOR EmissiveTemp = mat->Emissive;

	// �}�e���A���̍ގ��p�����[�^��ݒ�
	mat->Diffuse.r  = DiffuseTemp.r * ((float)col.r / 255);
	mat->Diffuse.g  = DiffuseTemp.g * ((float)col.g / 255);
	mat->Diffuse.b  = DiffuseTemp.b * ((float)col.b / 255);
	mat->Diffuse.a  = DiffuseTemp.a * ((float)col.a / 255);
	mat->Emissive.r = EmissiveTemp.r * ((float)col.r / 255);
	mat->Emissive.g = EmissiveTemp.g * ((float)col.g / 255);
	mat->Emissive.b = EmissiveTemp.b * ((float)col.b / 255);
	mat->Emissive.a = EmissiveTemp.a * ((float)col.a / 255);

	// �}�e���A���̐ݒ�
	device->SetMaterial(mat);

	// �}�e���A���̍ގ��p�����[�^�����ɖ߂�
	mat->Diffuse  = DiffuseTemp;
	mat->Emissive = EmissiveTemp;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �o�^���N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// �R���X�g���N�^
//========================================
CModel::CRegistInfo::CRegistInfo() {

	m_mtx                  = INITD3DXMATRIX;
	m_col                  = INITCOLOR;
	m_modelIdx             = DATANONE;
	m_texIdx               = DATANONE;
	m_isZTest              = false;
	m_isLighting           = true;
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
// �`����ɕϊ�
//========================================
CModel::CDrawInfo* CModel::CRegistInfo::ConvToDrawInfo(void) {

	// �`����̃������m��
	CDrawInfo* drawInfo = NULL;
	RNLib::Memory()->Alloc<CDrawInfo>(&drawInfo);

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
			float scaleX = FindMatrixScaleX(m_mtx);
			float scaleY = FindMatrixScaleY(m_mtx);
			float scaleZ = FindMatrixScaleZ(m_mtx);

			scaleMax = scaleX;
			if (scaleMax < scaleY)
				scaleMax = scaleY;
			if (scaleMax < scaleZ)
				scaleMax = scaleZ;
		}
		drawInfo->m_distance = Find_DistToCameraPlane(ConvMatrixToPos(m_mtx)) - (RNLib::Model()->GetData(m_modelIdx).m_radiusMax * scaleMax);
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
