#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TestStage::~TestStage() {
		//BGMを止める
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
		///生成されたときは止めておく
		TimerPtr->SetUpdateActive(false);
		//timeの画像表示
		auto TimePtr = AddGameObject<TextTime>(L"UI_Time_2", Vec2(120.0f, 50.0f), Vec2(200.0f, 350.0f));
		SetSharedGameObject(L"TextTime", TimePtr);

		//スマッシュゲージ
		auto SmashPtr = AddGameObject<SmashGauge>(L"gray", Vec2(275.0f, 30.0f), Vec2(500.0f, 0.0f));
		SetSharedGameObject(L"Smash", SmashPtr);

		//ポーズ画面の画像
		AddGameObject<StartPause>(L"ResultBG", Vec2(600, 600), Vec2(0, 0));
		AddGameObject<StartPause>(L"Pause", Vec2(256.0f, 64.0f), Vec2(0, 200));
		auto pause = AddGameObject<StartPause>(L"Gameback", Vec2(368.0f, 65.0f), Vec2(0, 50));
		pause->Akarusa(true);
		m_SpVec[0] = pause;
		pause = AddGameObject<StartPause>(L"Titleback", Vec2(427.0f, 59.0f), Vec2(0, -100));
		pause->Akarusa(false);
		m_SpVec[1] = pause;
		pause->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 0.5f));

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

			auto FadePtr = AddGameObject<FadeSprite>(FadeType::FadeIn, 0.01f);
			SetSharedGameObject(L"Fade", FadePtr);

			AddGameObject<CountDown>(L"UI_3", Vec2(512.0f, 512.0f), Vec2(0.0f, 0.0f));
		}
		catch (...) {
			throw;
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

		auto &app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObject = stage->GetGameObjectVec();
		//Timerを動かす
		if (m_StartActive == true) {
			m_cntlrock = true;
			for (auto v : gameObject) {
				if (v->FindTag(L"Timer")) {
					v->SetUpdateActive(true);
				}
			}
		}
	}
	//時を止める処理
	void TestStage::UpdateStage() {
		//停止
		if (!m_updateFlag) {
			Stage::UpdateStage();
		}

		//ポーズメニューに関すること
		auto cntlvec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlvec.bConnected) {
			if (m_Pause) {
				if (!m_cntlrock) {
					if (cntlvec.fThumbLY <= -0.8f) {
						PauseSelect++;
						if (PauseSelect == 2) {
							PauseSelect = 0;
						}
						m_cntlrock = true;
						ChangePause(PauseSelect);
					}
					else if (cntlvec.fThumbLY >= 0.8f) {
						PauseSelect--;
						if (PauseSelect == -1) {
							PauseSelect = 1;
						}
						m_cntlrock = true;
						ChangePause(PauseSelect);
					}
				}
				else {
					if (cntlvec.fThumbLY<0.8f&&cntlvec.fThumbLY>-0.8f) {
						m_cntlrock = false;
					}
				}
			}
		}

		switch (PauseSelect)
		{
			//ゲームに戻る
		case 0:
			if (cntlvec.wPressedButtons&XINPUT_GAMEPAD_A) {
				auto vec = GetGameObjectVec();
				if (m_Pause) {
					for (auto v : vec) {
						v->SetUpdateActive(true);
						if (v->FindTag(L"StartPause")) {
							//ポーズメニューをけす
							v->SetDrawActive(false);
						}
					}
					m_Pause = false;
				}
			}
			break;
			//タイトルへ
		case 1:
			if (cntlvec.wPressedButtons&XINPUT_GAMEPAD_A) {
				auto vec = GetGameObjectVec();
				if (m_Pause) {
					for (auto v : vec) {
						v->SetUpdateActive(true);
						if (v->FindTag(L"StartPause")) {
							//ポーズメニューをけす
							v->SetDrawActive(false);
						}
					}
					m_Pause = false;
					AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"TitleScene");
				}
			}
			break;
		}
		//ポーズ出す
		if (cntlvec.wPressedButtons&XINPUT_GAMEPAD_START) {
			auto vec = GetGameObjectVec();
			if (m_Pause) {
				for (auto v : vec) {
					v->SetUpdateActive(true);
					if (v->FindTag(L"StartPause")) {
						//ポーズメニューをけす
						v->SetDrawActive(false);
					}
				}
				m_Pause = false;
			}
			else {
				for (auto v : vec) {
					if (v->FindTag(L"StartPause")) {
						//ポーズメニューを出す
						v->SetDrawActive(true);
					}
				}
				m_updateFlag = true;
				m_Pause = true;
			}
		}
	}

	//描画処理
	void TestStage::OnDraw() {
		//レイヤーの取得と設定
		set<int> drawLayers;
		auto& ptrCamera = GetView()->GetTargetCamera();

		m_efkInterface->SetViewProj(ptrCamera->GetViewMatrix(), ptrCamera->GetProjMatrix());
		m_efkInterface->OnDraw();

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
	void TestStage::ChangePause(int num) {
		for (int i = 0; i < 2; i++) {
			shared_ptr<StartPause>shptr = m_SpVec[i].lock();
			if (shptr) {
				if (i == num) {
					shptr->Akarusa(true);
				}
				else {
					shptr->Akarusa(false);
					shptr->GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 0.5));
				}
			}
		}
	}
}

