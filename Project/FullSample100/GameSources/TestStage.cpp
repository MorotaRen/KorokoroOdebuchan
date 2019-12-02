#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -10.0f);
		const Vec3 at(0.0f, 0.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetPlayer(m_ptrPlayer);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void TestStage::CreateUI()
	{
		//タイマー
		AddGameObject<Timer>(8, L"UI_Number_4", true, Vec2(320.0f, 80.0f), Vec3(150.0f, 300.0f, 0.0f));
		//timeの画像表示
		AddGameObject<TextTime>(L"UI_Time", Vec2(250.0f, 100.0f), Vec2(-140.0f, 300.0f));

	}

	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			//CreateViewLight();

			//マルチライトの作成
			auto PtrMultiLight = CreateLight<MultiLight>();
			//デフォルトのライティングを指定
			PtrMultiLight->SetDefaultLighting();

			const Vec3 eye(0.0f, 0.0f, -10.0f);
			const Vec3 at(0.0f, 0.0f, 0.0f);
			auto PtrView = CreateView<SingleView>();
			//ビューのカメラの設定
			m_camera = ObjectFactory::Create<MyCamera>();
			PtrView->SetCamera(m_camera);
			m_camera->SetEye(eye);
			m_camera->SetAt(at);
			// UIの作成
			CreateUI();
			AddGameObject<FadeSprite>(FadeType::FadeIn);

		}
		catch (...) {
			throw;
		}
	}

	void TestStage::OnUpdate() {
		if (!m_IsCreateObject) {
			GameSystems::GetInstans().LoadStageCSV();
			m_ptrPlayer = GameSystems::GetInstans().CreateStage();
			m_camera->SetPlayer(m_ptrPlayer);
			GameSystems::GetInstans().ActiveNextCollision(0);
			m_IsCreateObject = true;
		}
	}

}
