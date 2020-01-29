#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルシーンのクラス
	//--------------------------------------------------------------------------------------
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(0.0f, 0.0f, 0.0f);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleScene::CreateUI() {
		//タイトルBG
		AddGameObject<TitleSceneSprite>(L"TitleLogo", Vec2(512.0f, 512.0f), Vec2(0, 0));
		//pushBottan
		auto PushPtr = AddGameObject<TitleSceneSprite>(L"Press A Button", Vec2(512.0f, 128.0f), Vec2(0, -300));
		SetSharedGameObject(L"A_Button", PushPtr);
	}

	void TitleScene::CreateBackground() {
		//ゲーム画面サイズ
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
	}

	void TitleScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			//UIの作成
			CreateUI();

			CreateBackground();

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);

			AddGameObject<FadeSprite>(FadeType::FadeIn, 0.01f);
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//ボタンの点滅
		//trueの時
		if (Switch <= 0.0f) {
			FalseTime = 0.0f; //falseの時の時間のリセット
			TrueTime += 1.0f; //時間計測開始
			//一定時間経過して透明にさせる
			if (TrueTime >= TrueTimeEnd) {
				Switch += 1.0f;
				GetSharedGameObject<TitleSceneSprite>(L"A_Button")->SetActive(false);
			}
		}
		//falseの時
		else {
			TrueTime = 0.0f;//trueの時の時間のリセット
			FalseTime += TrueTimePlus;//時間計測開始
			//一定時間経過して表示させる
			if (FalseTime >= FalseTimeEnd) {
				Switch += -1.0f;
				GetSharedGameObject<TitleSceneSprite>(L"A_Button")->SetActive(true);
			}
		}


		//Aが押されたら
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (cntlVec.bConnected) {
			if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A||KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				App::GetApp()->GetXAudio2Manager()->Start(L"pushA", 0, 0.5f);
				//点滅スピードを速くする
				FalseTimeEnd *= FlashingSpeed;
				TrueTimeEnd *= FlashingSpeed;
				DecSwitch += 1.0f;

				if (DecSwitch >= 1.0f) {
					DecTime += 1.0f;//ボタンを押してからの時間計測開始
					if (DecTime >= FlashingTime) {
						GetSharedGameObject<TitleSceneSprite>(L"A_Button")->SetActive(false);
						TrueTimePlus = 0.0f;//点滅しなくなる
						if (DecTime >= FlashingEnd) {
						}
					}
				}

				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"SelectScene");
			}
		}
	}
}