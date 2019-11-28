/// ----------------------------------------<summary>
/// タイトル用のステージのソース
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(0.0f,0.0f,0.0f);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleScene::CreateUI() {

	}

	void TitleScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();


			//難易度のスプライトを作成
			m_Spvec[0] = AddGameObject<Sprite>(L"Title", Vec2(1000.0f, 1000.0f),Vec2(0,0));
			//m_Spvec[1] = AddGameObject<Sprite>(L"Summer", Vec2(640.0f, 400.0f), Vec2(640.0f, -400.0f));
			//m_Spvec[2] = AddGameObject<Sprite>(L"Autumn", Vec2(640.0f, 400.0f), Vec2(-640.0f, 400.0f));
			//m_Spvec[3] = AddGameObject<Sprite>(L"Winter", Vec2(640.0f, 400.0f), Vec2(-640.0f, 400.0f));

			//m_Spvec[0]->SetDrawActive(true);
			//m_Spvec[1]->SetDrawActive(true);
			//m_Spvec[2]->SetDrawActive(true);
			//m_Spvec[3]->SetDrawActive(true);

			//UIの作成
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {

	}
}