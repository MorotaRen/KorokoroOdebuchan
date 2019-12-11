#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TestStage::~TestStage() {
		StopBGM();
	}
	void TestStage::CreateViewLight() {
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
	}

	//エフェクトの作成
	void TestStage::CreateEffect()
	{
		m_efkInterface = ObjectFactory::Create<EfkInterface>();

		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		
	}


	void TestStage::CreateUI()
	{
		//タイマー
		auto TimerPtr = AddGameObject<Timer>(8, L"UI_Number_5", true, Vec2(160.0f, 40.0f), Vec3(360.0f, 350.0f, 0.0f));
		SetSharedGameObject(L"Timer", TimerPtr);
		//生成されたときは止めておく
		TimerPtr->SetUpdateActive(false);
		//timeの画像表示
		auto TimePtr = AddGameObject<TextTime>(L"UI_Time_2", Vec2(120.0f, 50.0f), Vec2(200.0f, 350.0f));
		SetSharedGameObject(L"TextTime", TimePtr);

		//スタート表示
		AddGameObject<CountDown>(L"START", Vec2(0.0f, 0.0f));

	}
	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			// UIの作成
			CreateUI();
			//エフェクトの作成
			CreateEffect();

			PlayBGM(L"MainBGM", 0.5f);

			AddGameObject<FadeSprite>(FadeType::FadeIn);

		}
		catch (...) {		throw;
		}
	}

	void TestStage::OnUpdate() {
		m_efkInterface->OnUpdate();

		if (!m_IsCreateObject) {
			GameSystems::GetInstans().LoadStageCSV();
			m_ptrPlayer = GameSystems::GetInstans().CreateStage();
			m_camera->SetPlayer(m_ptrPlayer);
			GameSystems::GetInstans().ActiveNextCollision(0);
			m_IsCreateObject = true;
		}
		//スタート前で止まるようにする
		m_deltTime += App::GetApp()->GetElapsedTime();
		if (m_deltTime > 1.8f) {
			m_updateFlag = true;
		}

	}

	//時を止める処理
	void TestStage::UpdateStage() {
		auto &app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObject = stage->GetGameObjectVec();

		//停止
		if (!m_updateFlag) {
			Stage::UpdateStage();
		}

		//m_stopTimeはm_deltTimeと同じく計測
		//再開
		m_stopTime += App::GetApp()->GetElapsedTime();
		if (m_stopTime > 5.0f) {
			m_updateFlag = false;
			//Timerを動かす
			for (auto v : gameObject) {
				if (v->FindTag(L"Timer")) {
					v->SetUpdateActive(true);
				}
			}
		}
	}

	//BGMの再生
	void TestStage::PlayBGM(wstring key, float vol) {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(key, XAUDIO2_LOOP_INFINITE, vol);
	}
	//BGMの停止
	void TestStage::StopBGM() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//描画処理
	void TestStage::OnDraw() {
		//レイヤーの取得と設定
		set<int> drawLayers;
		auto& ptrCamera = GetView()->GetTargetCamera();

		m_efkInterface->SetViewProj(ptrCamera->GetViewMatrix(), ptrCamera->GetProjMatrix());
		m_efkInterface->OnDraw();

	}
}

