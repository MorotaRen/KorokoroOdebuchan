/// ----------------------------------------<summary>
/// ゲーム全体で呼び出せる関数用ソース
/// 管理者：諸田
/// </summary>----------------------------------------

#include "Project.h"
namespace basecross {

	void GameSystems::ControllerCheck_Cursor() {
		if (m_Pad.bConnected) {
			::ShowCursor(false);
		}
	}

	void GameSystems::UpdatePadData() {
		//アプリケーションからゲームコントローラーの状態をとってくる
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		m_Pad = device.GetControlerVec()[0];
	}
}