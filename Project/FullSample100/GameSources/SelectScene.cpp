/// ----------------------------------------<summary>
/// タイトル用のステージのソース
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	タイトルシーンのクラス
	//--------------------------------------------------------------------------------------
	void SelectScene::CreateViewLight() {
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

	void SelectScene::CreateUI() {
		//難易度のスプライトを作成
		m_Spvec[1] = AddGameObject<SelectSceneSprite>(L"Title_SpringStage", Vec2(640.0f, 400.0f), Vec2(-320, 200));
		m_Spvec[2] = AddGameObject<SelectSceneSprite>(L"Title_AkiStage", Vec2(640.0f, 400.0f), Vec2(320.0f, 200.0f));
		m_Spvec[3] = AddGameObject<SelectSceneSprite>(L"Title_SummerStage2", Vec2(640.0f, 400.0f), Vec2(-320.0f, -200.0f));
		m_Spvec[4] = AddGameObject<SelectSceneSprite>(L"Title_WinterStage", Vec2(640.0f, 400.0f), Vec2(320.0f, -200.0f));

		//マスクスプライト
		m_SpotSprite = AddGameObject<SelectSpotSprite>(L"Title_Mask", Vec2(1921.0f, 1201.0f), Vec2(-320.0f, 200.0f));
		m_SpotSprite->SetDrawLayer(10);


		m_Spvec[1]->SetDrawLayer(1);
		m_Spvec[2]->SetDrawLayer(1);
		m_Spvec[3]->SetDrawLayer(1);
		m_Spvec[4]->SetDrawLayer(1);

	}
	void SelectScene::CreateAnimSp() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		//春
		wstring srtmodel = dataDir + L"SpriteStudio\\TitleSpring\\";
		auto Spring_SS = AddGameObject<SelectSS>(srtmodel, L"TitleSpring.ssae", L"Clause", Vec2(32.0f, 32.0f), Vec2(-320, 200));
		SetSharedGameObject(L"Spring", Spring_SS);
		//秋
		srtmodel = dataDir + L"SpriteStudio\\TitleAutumn\\";
		auto Summer_SS = AddGameObject<SelectSS>(srtmodel, L"TitleAutumn.ssae", L"Clause", Vec2(32.0f, 32.0f), Vec2(320.0f, 200.0f));
		SetSharedGameObject(L"Summer", Summer_SS);
		//夏
		srtmodel = dataDir + L"SpriteStudio\\TitleSummer\\";
		auto Autumn_SS = AddGameObject<SelectSS>(srtmodel, L"TitleSummer.ssae", L"Clause", Vec2(32.0f, 32.0f), Vec2(-320.0f, -200.0f));
		SetSharedGameObject(L"Autumn", Autumn_SS);
		//冬
		srtmodel = dataDir + L"SpriteStudio\\TitleWinter\\";
		auto Winter_SS = AddGameObject<SelectSS>(srtmodel, L"TitleWinter.ssae", L"Clause", Vec2(32.0f, 32.0f), Vec2(320.0f, -200.0f));
		SetSharedGameObject(L"Winter", Winter_SS);
	}
	void SelectScene::CreateBackground() {
		//ゲーム画面サイズ
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
	}

	void SelectScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			//ステージモデルの解放
			GameSystems::GetInstans().ReleaseModelData();

			//UIの作成
			CreateUI();

			//アニメーションスプライト
			CreateAnimSp();

			CreateBackground();

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);


			AddGameObject<FadeSprite>(FadeType::FadeIn, 0.01f);
		}
		catch (...) {
			throw;
		}
	}
	void SelectScene::OnUpdate() {
		//コントローラーの入力
		bool SelectSpotFlag = m_SpotSprite->GetSelectSpotFlag();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (cntlVec.bConnected) {
			//1回スティック倒したら戻すまでロックする
			if (SelectSpotFlag == true) {
				if (!m_CntrolLock) {
					if (cntlVec.fThumbLX >= 0.8f) {
						if (m_StageNum != 3) {
							m_StageNum++;
							m_CntrolLock = true;

						}
					}
					else if (cntlVec.fThumbLX <= -0.8f) {
						m_StageNum--;
						m_CntrolLock = true;
					}

					if (cntlVec.fThumbLY >= 0.8f) {
						m_StageNum -= 2;
						m_CntrolLock = true;

					}
					else if (cntlVec.fThumbLY <= -0.8f) {
						m_StageNum += 2;
						m_CntrolLock = true;
					}
				}
				else {
					if (cntlVec.fThumbLX<0.8f&&cntlVec.fThumbLX>-0.8f) {
						m_CntrolLock = false;
					}
				}
			}
			//上限
			if (m_StageNum > 3) {
				m_StageNum = 3;
			}
			else if (m_StageNum < 0) {
				m_StageNum = 0;
			}
		}

		//アニメーションスプライト出すか引っ込めるか
		//春
		auto Spring = GetSharedGameObject<SelectSS>(L"Spring");
		if (m_StageNum == 0) {
			Spring->ChangeAnimation(L"Open",1);
		}
		else {
			Spring->ChangeAnimation(L"Clause", 1);
		}
		//夏
		auto Summer = GetSharedGameObject<SelectSS>(L"Summer");
		if (m_StageNum == 1) {
			Summer->ChangeAnimation(L"Open",1);
		}
		else {
			Summer->ChangeAnimation(L"Clause", 1);
		}
		//秋
		auto Autumn = GetSharedGameObject<SelectSS>(L"Autumn");
		if (m_StageNum == 2) {
			Autumn->ChangeAnimation(L"Open",1);
		}
		else {
			Autumn->ChangeAnimation(L"Clause", 1);
		}
		//冬
		auto Winter = GetSharedGameObject<SelectSS>(L"Winter");
		if (m_StageNum == 3) {
			Winter->ChangeAnimation(L"Open",1);
		}
		else {
			Winter->ChangeAnimation(L"Clause", 1);
		}


		//シーン遷移
		if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A&&SelectSpotFlag == true || KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Stop(m_BGM);
			App::GetApp()->GetXAudio2Manager()->Start(L"pushA", 0, 0.5f);
			if (m_StageNum == 0) {
				//春
				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"ToWaitScene");
				GameSystems::GetInstans().SetGameStageNum(1);
			}
			else if (m_StageNum == 1) {
				//秋
				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"ToWaitScene");
			}
			else if (m_StageNum == 2) {
				//夏
				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"ToWaitScene");
				GameSystems::GetInstans().SetGameStageNum(2);

			}
			else if (m_StageNum == 3) {
				//冬
				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"ToWaitScene");
			}

		}
	}
}