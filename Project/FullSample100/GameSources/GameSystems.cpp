/// ----------------------------------------<summary>
/// �Q�[���S�̂ŌĂяo����֐��p�\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "Project.h"
namespace basecross {

	void GameSystems::ControllerCheck_Cursor() {
		if (m_Pad.bConnected) {
			::ShowCursor(false);
		}
	}

	void GameSystems::UpdatePadData() {
		//�A�v���P�[�V��������Q�[���R���g���[���[�̏�Ԃ��Ƃ��Ă���
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		m_Pad = device.GetControlerVec()[0];
	}
}