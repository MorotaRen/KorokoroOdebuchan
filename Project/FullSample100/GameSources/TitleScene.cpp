/// ----------------------------------------<summary>
/// タイトル用のステージのソース
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	選択している所を表示するスプライト
	//--------------------------------------------------------------------------------------
	SelectSpotSprite::SelectSpotSprite(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}
	void SelectSpotSprite::OnCreate() {
		Sprite::OnCreate();
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0, 1.0, 1.0, 0.6f));
	}
	void SelectSpotSprite::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		// 配置してあるステージから、今選択しているステージ番号を取得
		auto stageNum = GetTypeStage<TitleScene>()->GetStageNum();
		// 配置してあるステージから、ステージスプライトの配列を取得
		auto spVec = GetTypeStage<TitleScene>()->GetSpVec();
		// ステージ番号から今選択しているステージスプライトを特定
		auto stageSprite = spVec[++stageNum];
		//特定したスプライトの位置を取得
		auto nowSpritePos = stageSprite->GetComponent<Transform>()->GetPosition();
		// ステージスプライトの位置から自分の位置を引いて距離を求める
		auto dis = nowSpritePos - pos;
		// 移動量を計算
		float moveX = dis.x / 10.0f;
		float moveY = dis.y / 10.0f;

		float Pickdis = 7.0f;
		if (moveY < Pickdis&&moveY >= 0.0f) {
			SelectSpotFlag = true;
		}
		else if (moveY > -Pickdis&&moveY <= 0.0f) {
			SelectSpotFlag = true;
		}
		else {
			SelectSpotFlag = false;
		}
		// 位置に移動量を足す
		pos.x += moveX;
		pos.y += moveY;

		ptrTrans->SetPosition(pos);

		
	}

	//--------------------------------------------------------------------------------------
	//	タイトルシーンのクラス
	//--------------------------------------------------------------------------------------
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

	void TitleScene::CreateBackground() {
		//ゲーム画面サイズ
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(),(float)App::GetApp()->GetGameHeight());
	}

	void TitleScene::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			//タイトルロゴ
			m_Spvec[0] = AddGameObject<Sprite>(L"TitleLogo", Vec2(256.0f, 256.0f), Vec2(0, 0));
			//難易度のスプライトを作成
			m_Spvec[1] = AddGameObject<Sprite>(L"Title_SpringStage", Vec2(640.0f, 400.0f),Vec2(-320,200));
			m_Spvec[2] = AddGameObject<Sprite>(L"Preparation", Vec2(640.0f, 400.0f), Vec2(320.0f, 200.0f));
			m_Spvec[3] = AddGameObject<Sprite>(L"Preparation", Vec2(640.0f, 400.0f), Vec2(-320.0f, -200.0f));
			m_Spvec[4] = AddGameObject<Sprite>(L"Preparation", Vec2(640.0f, 400.0f), Vec2(320.0f, -200.0f));

			//マスクスプライト
			m_SpotSprite = AddGameObject<SelectSpotSprite>(L"Title_Mask", Vec2(1921.0f, 1201.0f), Vec2(-320.0f, 200.0f));
			m_SpotSprite->SetDrawLayer(10);

			//描画処理が有効
			m_Spvec[0]->SetDrawActive(true);
			m_Spvec[1]->SetDrawActive(true);
			m_Spvec[2]->SetDrawActive(true);
			m_Spvec[3]->SetDrawActive(true);
			m_Spvec[4]->SetDrawActive(true);
			
			m_Spvec[0]->SetDrawLayer(9);
			m_Spvec[1]->SetDrawLayer(1);
			m_Spvec[2]->SetDrawLayer(1);
			m_Spvec[3]->SetDrawLayer(1);
			m_Spvec[4]->SetDrawLayer(1);

			//UIの作成
			CreateUI();

			CreateBackground();

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);

			AddGameObject<FadeSprite>(FadeType::FadeIn);
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//
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
				}
				else {
					if (cntlVec.fThumbLX<0.8f&&cntlVec.fThumbLX>-0.8f) {
						m_CntrolLock = false;
					}
				}
			}
			//上限
			if (m_StageNum == 4) {
				m_StageNum = 3;
			}
			else if (m_StageNum == -1) {
				m_StageNum = 0;
			}
		}

		//シーン遷移
		if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A&&SelectSpotFlag == true || KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Stop(m_BGM);
			AddGameObject<FadeSprite>(FadeType::FadeOut, L"ToTestStage");
		}
	}
}