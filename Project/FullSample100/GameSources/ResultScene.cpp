/*!
@file Result.cpp
@brief リザルトクラス実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	playerプレビュー
	//--------------------------------------------------------------------------------------
	WinPlayer::WinPlayer(const shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{}
	void WinPlayer::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(Vec3(0.08f, 0.08f, 0.08f));
		ptrTrans->SetRotation(Vec3(0, 0.3f, 0));
		ptrTrans->SetPosition(Vec3(1.2f, 0.1f, 0));
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.15f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.7f, 0.0f)
		);
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"M_PlayerNomal");
		ptrDraw->AddAnimation(L"Win", 110, 145, true, 45.0f);
		ptrDraw->ChangeCurrentAnimation(L"Win");
		SetDrawLayer(100);
	}
	void WinPlayer::OnUpdate() {
		auto ptrDraw = AddComponent<PNTBoneModelDraw>();
		ptrDraw->SetMeshResource(L"M_PlayerNomal");
		float elapsedTime = App::GetApp()->GetElapsedTime();
		ptrDraw->UpdateAnimation(elapsedTime);

	}
	//--------------------------------------------------------------------------------------
	//	リザルトシーンのクラス
	//--------------------------------------------------------------------------------------
	void ResultScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 0.0f, -3.0f));
		PtrCamera->SetAt(0.0f, 0.0f, 0.0f);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void ResultScene::CreateBackground() {
	}

	void ResultScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			CreateBackground();

			AddGameObject<ResultTimer>(8, L"UI_Number_4", true, Vec2(380.0f, 120.0f), Vec3(-180.0f, -40.0f, 0.0f));
			AddGameObject<ResultSceneSprite>(L"ResultBG", Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
			AddGameObject<ResultSceneSprite>(L"UI_Time_2", Vec2(384.0f, 128.0f), Vec2(0.0f, 150.0f));
			AddGameObject<ResultSceneSprite>(L"Result", Vec2(256.0f, 64.0f), Vec2(0.0f, 300.0f));
			m_SpVec[0] = AddGameObject<ResultSceneSprite>(L"ritorai", Vec2(160.0f, 100.0f), Vec2(-150.0f, -250.0f));
			m_SpVec[1] = AddGameObject<ResultSceneSprite>(L"Title", Vec2(256.0f, 64.0f), Vec2(150.0f, -250.0f));

			AddGameObject<WinPlayer>();

			AddGameObject<FadeSprite>(FadeType::FadeIn);
		}
		catch (...) {
			throw;
		}
	}
	void ResultScene::OnUpdate() {

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

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

		//シーン遷移
		if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A || KeyState.m_bPushKeyTbl[VK_SPACE]) {
			if (m_StageNum == 0) {
				AddGameObject<FadeSprite>(FadeType::FadeOut, L"ToTestStage");
			}
			else if (m_StageNum == 1) {
				AddGameObject<FadeSprite>(FadeType::FadeOut, L"TitleScene");
			}
		}
	}
}

//end basecross

