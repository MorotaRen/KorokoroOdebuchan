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
		//生成されたときは止めておく
		TimerPtr->SetUpdateActive(false);
		//timeの画像表示
		auto TimePtr = AddGameObject<TextTime>(L"UI_Time", Vec2(120.0f, 50.0f), Vec2(200.0f, 350.0f));
		SetSharedGameObject(L"TextTime", TimePtr);

		//スタート表示
		AddGameObject<CountDown>(L"START", Vec2(0.0f, 0.0f));

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

		//スタート前で止まるようにする
		m_deltTime += App::GetApp()->GetElapsedTime();
		if (m_deltTime > 1.8f) {
			m_updateFlag = true;

		}


		//ゴールした時
		if (m_ptrPlayer.lock()->GetGoolFlg()) {
			GetSharedGameObject<Timer>(L"Timer")->SetScore();
			AddGameObject<ResultTimer>(8, L"UI_Number_4", true, Vec2(160.0f, 40.0f), Vec3(-60.0f, 60.0f, 0.0f));
			AddGameObject<ResultSprite>(L"gray", Vec2(500.0f, 500.0f), Vec2(0.0f, 0.0f));
			m_SpVec[0] = AddGameObject<ResultSprite>(L"Title_1", Vec2(128.0f, 64.0f), Vec2(-100.0f, -50.0f));
			m_SpVec[1] = AddGameObject<ResultSprite>(L"Title_2", Vec2(128.0f, 64.0f), Vec2(100.0f, -50.0f));

			GetSharedGameObject<Timer>(L"Timer")->SetDrawActive(false);
			GetSharedGameObject<TextTime>(L"TextTime")->SetDrawActive(false);

			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			//シーン遷移
			//if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A) {
				//AddGameObject<FadeSprite>(FadeType::FadeOut, L"TitleScene");
			//}

			if (cntlVec.bConnected) {
				//1回スティック倒したら戻すまでロックする
				if (!m_CntrolLock) {
					if (cntlVec.fThumbLX >= 0.8f) {
							m_StageNum++;
							m_CntrolLock = true;

					}
					else if (cntlVec.fThumbLX <= -0.8f) {
						m_StageNum--;
						m_CntrolLock = true;
					}
				}
				else {
					if (cntlVec.fThumbLX<0.8f&&cntlVec.fThumbLX>-0.8f) {
						m_CntrolLock = false;
					}
				}
				//上限
				if (m_StageNum == 2) {
					m_StageNum = 0;
				}
				else if (m_StageNum == -1) {
					m_StageNum = 1;
				}

				//
				if (m_StageNum == 0) {
					m_SpVec[0]->Transluc(true);
					m_SpVec[1]->Transluc(false);
				}
				else if (m_StageNum == 1) {
					m_SpVec[0]->Transluc(false);
					m_SpVec[1]->Transluc(true);
				}
			}
			m_ptrPlayer.lock()->SetGoolFlg(false);
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
}

