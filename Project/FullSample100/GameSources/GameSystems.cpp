/// ----------------------------------------<summary>
/// �Q�[���S�̂ŌĂяo����֐��p�\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void GameSystems::ControllerCheck_Cursor() {
		if (m_pad.bConnected) {
			::ShowCursor(false);
		}
	}

	void GameSystems::UpdatePadData() {
		//�A�v���P�[�V��������Q�[���R���g���[���[�̏�Ԃ��Ƃ��Ă���
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		m_pad = device.GetControlerVec()[0];
	}
}