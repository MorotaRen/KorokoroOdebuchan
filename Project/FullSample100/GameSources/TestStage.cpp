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
		auto TimerPtr = AddGameObject<Timer>(8, L"UI_Number_4", true, Vec2(160.0f, 40.0f), Vec3(360.0f, 350.0f, 0.0f));
		SetSharedGameObject(L"Timer", TimerPtr);
		//timeの画像表示
		AddGameObject<TextTime>(L"UI_Time", Vec2(120.0f, 50.0f), Vec2(200.0f, 350.0f));

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

			AddGameObject<FadeSprite>(FadeType::FadeIn);

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
			GameSystems::GetInstans().ActiveNextCollision(0);
			m_IsCreateObject = true;
		}

		//スタート前で止まるようにする
		m_deltTime += App::GetApp()->GetElapsedTime();
		auto &app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObjectVec = stage->GetGameObjectVec();
		/*if (m_StartPos == false) {
			for (auto v : gameObjectVec) {
				if (v->FindTag(L"Player"))
				{
					if (m_deltTime > 3.8f) {
						v->SetUpdateActive(false);
						m_StartPos = true;
						m_deltTime = 0.0f;
					}
				}
				if (v->FindTag(L"Timer"))
				{
					v->SetUpdateActive(false);
				}
			}
		}*/

		if (m_deltTime > 5.0f) {
			m_updateFlag = true;
			
		}
		
		

		//スタートをくぐったら
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (m_StartPos == true) {
				for (auto v : gameObjectVec) {
					if (v->FindTag(L"Player"))
					{
						v->SetUpdateActive(true);
					}
					if (v->FindTag(L"Timer"))
					{
						v->SetUpdateActive(true);
					}
			}

			if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_X) {
				//GetSharedGameObject<Timer>(L"Timer")->SetScore();
				//AddGameObject<ResultTimer>(8, L"UI_Number_4", true, Vec2(160.0f, 40.0f), Vec3(-50.0f, 0.0f, 0.0f));
				//AddGameObject<ResultSprite>(L"gray", Vec2(500.0f, 500.0f), Vec2(0.0f, 0.0f));
				//AddGameObject<ResultSprite>(L"gray", Vec2(500.0f, 500.0f), Vec2(0.0f, 0.0f));
				//AddGameObject<ResultSprite>(L"gray", Vec2(500.0f, 500.0f), Vec2(0.0f, 0.0f));
			}


		}
	}
	void TestStage::UpdateStage() {
		if (!m_updateFlag) {
			Stage::UpdateStage();
		}

		m_stopTime += App::GetApp()->GetElapsedTime();
		if (m_stopTime > 10.0f) {
			m_updateFlag = false;
		}
	}
}

