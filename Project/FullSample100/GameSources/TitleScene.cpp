/// ----------------------------------------<summary>
/// タイトル用のステージのソース
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleScene::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}
	void TitleScene::CreateBackground() {
		//ゲーム画面サイズ
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(),(float)App::GetApp()->GetGameHeight());
	}
	void TitleScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//CreateBackground();
			auto player = AddGameObject<Player>(Vec3(250, 100, 0), Vec3(1, 1, 1));
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		auto pad = GameSystems::GetInstans().GetPad();
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		//Padの何かしらでもボタンが押されたらStage移動
		if (pad.wPressedButtons) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameScene");
		}
	}
}