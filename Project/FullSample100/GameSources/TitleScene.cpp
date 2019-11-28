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

			//難易度のスプライトを作成
			m_Spvec[1] = AddGameObject<Sprite>(L"Title_1", Vec2(640.0f, 400.0f),Vec2(-320,200));
			m_Spvec[2] = AddGameObject<Sprite>(L"Title_2", Vec2(640.0f, 400.0f), Vec2(320.0f, 200.0f));
			m_Spvec[3] = AddGameObject<Sprite>(L"Title_3", Vec2(640.0f, 400.0f), Vec2(-320.0f, -200.0f));
			m_Spvec[4] = AddGameObject<Sprite>(L"Title_4", Vec2(640.0f, 400.0f), Vec2(320.0f, -200.0f));

			//マスクスプライト
			//m_SpotSprite = AddGameObject<SelectSpotSprite>(L"TestWall", Vec2(3840.0f, 1920.0f), Vec2(-320.0f, 200.0f));
			m_SpotSprite = AddGameObject<SelectSpotSprite>(L"TitleLogo", Vec2(640.0f, 400.0f), Vec2(-320.0f, 200.0f));

			//描画処理が有効
			m_Spvec[1]->SetDrawActive(true);
			m_Spvec[2]->SetDrawActive(true);
			m_Spvec[3]->SetDrawActive(true);
			m_Spvec[4]->SetDrawActive(true);

			//UIの作成
			CreateUI();

			CreateBackground();
			//auto player = AddGameObject<Player>(Vec3(250, 100, 0), Vec3(1, 1, 1));
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//
		bool SelectSpotFlag = m_SpotSprite->GetSelectSpotFlag();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
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
			if (m_StageNum == 4) {
				m_StageNum = 3;
			}
			else if (m_StageNum == -1) {
				m_StageNum = 0;
			}
		}

		//シーン遷移
		if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A&&SelectSpotFlag == true) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTestStage");
		}
	}
}