//========================================
// 
// �J�����̏�ԏ���
// Author:RIKU NISHIMURA
// 
//========================================
#include "../../RNlib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| �J�����N���X�̃����o�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// ��ԏ���
//========================================
void CCamera::ProcessState(const PROCESS process) {

	switch (m_state) {
		//----------------------------------------
		// �}�E�X�Œ���͂�
		//----------------------------------------
	case STATE::GRAB_AIR_MOUSE: {
		static const D3DXVECTOR3 SPIN_RATE = D3DXVECTOR3(-0.0004f, 0.0004f, 0.0f);

		switch (process) {
			// [[[ �������� ]]]
		case PROCESS::INIT: {
			RNLib::Memory()->Alloc<GrabAirMouseInfo>((GrabAirMouseInfo**)&m_stateInfo);
		}break;
			// [[[ �I������ ]]]
		case PROCESS::UNINIT: {
			RNLib::Memory()->Release<GrabAirMouseInfo>((GrabAirMouseInfo**)&m_stateInfo);
		}break;
			// [[[ �X�V���� ]]]
		case PROCESS::UPDATE: {
			GrabAirMouseInfo* info = (GrabAirMouseInfo*)m_stateInfo;

			// ImGui�̃E�B���h�E�Ƀt�H�[�J�X���������Ă��鎞�A�������I��
			if (ImGui_GetWindowFocused())
				return;
			
			// [[[ �J�[�\���̈ړ��ʂɉ����ĉ�]������ ]]]
			if (RNLib::Input()->GetMousePress(CInput::MOUSEBUTTON::RIGHT)) {
				D3DXVECTOR2 cursorMove = RNLib::Input()->GetCursorMove();
				m_spin.x += cursorMove.y * SPIN_RATE.x * info->spinForce;
				m_spin.y += cursorMove.x * SPIN_RATE.y * info->spinForce;
			}

			{
				// ����X�̊���
				float rotXRate = m_rot.x / D3DX_PI_HALF;

				// [[[ �J�[�\���̈ړ��ʂɉ����Ĉړ������� ]]]
				if (RNLib::Input()->GetMousePress(CInput::MOUSEBUTTON::LEFT)) {
					D3DXVECTOR3 move = INITD3DXVECTOR3;					// �ړ���
					D3DXVECTOR2 cursorMove = RNLib::Input()->GetCursorMove();	// �J�[�\���̈ړ���
					float       moveAngleX = m_rot.y - D3DX_PI_HALF;			// �ړ�����X

					move.x = sinf(moveAngleX) * cursorMove.x;
					move.z = cosf(moveAngleX) * cursorMove.x;
					move.y = cursorMove.y * (1.0f - fabsf(rotXRate));

					// �c�������XZ��Y�̈ړ��ʉ��Z
					move.x += sinf(m_rot.y) * cursorMove.y * -rotXRate;
					move.z += cosf(m_rot.y) * cursorMove.y * -rotXRate;

					// �����_�Ɉړ��ʂ𔽉f
					m_posR += move * info->moveForce;
				}

				// [[[ �z�C�[���̉�]�ɉ����ăY�[���C��/�A�E�g ]]]
				if (RNLib::Input()->GetWheelSpin() == CInput::WHEELSPIN::FRONT) {
					float XZPlaneRate = 1.0f - fabsf(rotXRate);
					
					m_posR.x += sinf(m_rot.y) * info->zoomForce * XZPlaneRate;
					m_posR.z += cosf(m_rot.y) * info->zoomForce * XZPlaneRate;
					m_posR.y += info->zoomForce * rotXRate;
				}
				else if (RNLib::Input()->GetWheelSpin() == CInput::WHEELSPIN::BACK) {
					float XZPlaneRate = 1.0f - fabsf(rotXRate);

					m_posR.x -= sinf(m_rot.y) * info->zoomForce * XZPlaneRate;
					m_posR.z -= cosf(m_rot.y) * info->zoomForce * XZPlaneRate;
					m_posR.y -= info->zoomForce * rotXRate;
				}
			}
		}break;
		}
	}break;
		//----------------------------------------
		// ������]
		//----------------------------------------
	case STATE::RECIPROCATE_SPIN: {
		switch (process) {
			// [[[ �������� ]]]
		case PROCESS::INIT: {
			RNLib::Memory()->Alloc<ReciprocateSpinInfo>((ReciprocateSpinInfo**)&m_stateInfo);
		}break;
			// [[[ �I������ ]]]
		case PROCESS::UNINIT: {
			RNLib::Memory()->Release<ReciprocateSpinInfo>((ReciprocateSpinInfo**)&m_stateInfo);
		}break;
			// [[[ �X�V���� ]]]
		case PROCESS::UPDATE: {
			ReciprocateSpinInfo* info = (ReciprocateSpinInfo*)m_stateInfo;

			// �J�E���g
			info->count = (info->count + 1) % (info->time * 2);
			int count = info->count;
			if (count > info->time)
				count = info->time - (count - info->time);

			// ����
			float rate = Easing(EASE_INOUT, count, info->time);

			// ���ۂ̌������Z�o
			m_rot = (info->rotA * (1.0f - rate)) + (info->rotB * rate);
		}break;
		}
	}break;
	}
}

//========================================
// ��Ԑݒ�
//========================================
void CCamera::SetState(const STATE state) {

	// ���̏�Ԃ̏I������
	ProcessState(PROCESS::UNINIT);

	// ��Ԃ���
	m_state = state;

	// �V������Ԃ̏�������
	ProcessState(PROCESS::INIT);
}

//========================================
// �}�E�X�Œ���͂�
//========================================
void CCamera::GrabAirMouse(const float moveForce, const float spinForce, const float zoomForce) {
	
	SetState(STATE::GRAB_AIR_MOUSE);
	GrabAirMouseInfo* info = (GrabAirMouseInfo*)m_stateInfo;
	info->moveForce = moveForce;
	info->spinForce = spinForce;
	info->zoomForce = zoomForce;
}

//========================================
// ������]
//========================================
void CCamera::ReciprocateSpin(const D3DXVECTOR3 posR, const float dist, const D3DXVECTOR3 rotA, const D3DXVECTOR3 rotB, const int time) {

	SetState(STATE::RECIPROCATE_SPIN);
	m_posR = posR;
	m_dist = dist;
	m_rot  = rotA;
	ReciprocateSpinInfo* info = (ReciprocateSpinInfo*)m_stateInfo;
	info->rotA   = rotA;
	info->rotB   = rotB;
	info->time  = time;
	info->count = 0;
}