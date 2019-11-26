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
		AddGameObject<Timer>(8, L"Number", true,
			Vec2(320.0f, 80.0f),
			Vec3(450.0f, 300.0f, 0.0f));
	}

	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			//CreateViewLight();

			//マルチライトの作成
			auto PtrMultiLight = CreateLight<MultiLight>();
			//デフォルトのライティングを指定
			PtrMultiLight->SetDefaultLighting();

			const Vec3 eye(0.0f, 0.0f, -1.0f);
			const Vec3 at(0.0f, 0.0f, 0.0f);
			auto PtrView = CreateView<SingleView>();
			//ビューのカメラの設定
			m_camera = ObjectFactory::Create<MyCamera>();
			PtrView->SetCamera(m_camera);
			m_camera->SetEye(eye);
			m_camera->SetAt(at);

			/*AddGameObject<TestBlock>(Vec3(0, 0, 0), Vec3(10, 10, 100), Vec3(10, 0, 0));
			m_ptrPlayer = AddGameObject<Player>(Vec3(0, 12, -15), Vec3(1, 1, 1));*/



			//auto stageobject = AddGameObject<TestBlock>(Vec3(0, 0, 0), Vec3(20, 1, 500), Vec3(0, 90, 0));
			//SetSharedGameObject(L"StageObject", stageobject);
			//auto player = AddGameObject<Player>(Vec3(250, 100, 0), Vec3(1, 1, 1));
			//SetSharedGameObject(L"Player",player);

			// UIの作成
			CreateUI();

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
			m_IsCreateObject = true;
		}
	}

}
