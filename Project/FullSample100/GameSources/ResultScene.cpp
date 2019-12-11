/*!
@file Result.cpp
@brief リザルトクラス実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトスプライト
	//--------------------------------------------------------------------------------------
	ResultSprite::ResultSprite(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void ResultSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(13);
	}
	void ResultSprite::Transluc(bool Active) {
		if (Active) {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else {
			auto ptrDraw = GetComponent<PCTSpriteDraw>();
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.4f));
		}
	}
	//--------------------------------------------------------------------------------------
	//	タイマーの結果表示
	//--------------------------------------------------------------------------------------
	ResultTimer::ResultTimer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos)
	{}

	void ResultTimer::OnCreate() {
		float XPiecesize = 2.0f / (float)m_NumberOfDigits;
		float HelfSize = 0.5f;

		//インデックス配列
		vector<uint16_t> indices;
		for (UINT i = 0; i < m_NumberOfDigits; i++) {
			float Vertex0 = -HelfSize + XPiecesize * (float)i;
			float Vertex1 = Vertex0 + XPiecesize;
			//0
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex0, HelfSize, 0), Vec2(0.0f, 0.0f))
			);
			//1
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex1, HelfSize, 0), Vec2(0.1f, 0.0f))
			);
			//2
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex0, -HelfSize, 0), Vec2(0.0f, 1.0f))
			);
			//3
			m_BackupVertices.push_back(
				VertexPositionTexture(Vec3(Vertex1, -HelfSize, 0), Vec2(0.1f, 1.0f))
			);
			indices.push_back(i * 4 + 0);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 2);
			indices.push_back(i * 4 + 1);
			indices.push_back(i * 4 + 3);
			indices.push_back(i * 4 + 2);
		}

		SetAlphaActive(m_Trace);
		SetDrawLayer(15);
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		PtrDraw->SetTextureResource(m_TextureKey);

		//文字列をつける
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(1000.0f, 16.0f, 1200.0f, 480.0f));
	}

	void ResultTimer::OnUpdate() {
		m_TimerScore = App::GetApp()->GetScene<Scene>()->GetRecodeTime();


		vector<VertexPositionTexture> NewVertices;
		UINT Num;
		int VerNum = 0;
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			Vec2 UV0;
			if (i < 3) {
				int num = int((m_TimerScore - (int(m_TimerScore) / 1)) * 100);
				UINT Base = (UINT)pow(10, i);
				Num = ((UINT)num) % Base;
				Num = Num / (Base / 10);
				UV0 = m_BackupVertices[VerNum].textureCoordinate;
				UV0.x = (float)Num / 11.0f;
			}
			else if (i > 3 && i < 6) {
				int num = int(m_TimerScore) % 60 * 1000;
				UINT Base = (UINT)pow(10, i);
				Num = ((UINT)num) % Base;
				Num = Num / (Base / 10);
				UV0 = m_BackupVertices[VerNum].textureCoordinate;
				UV0.x = (float)Num / 11.0f;
			}
			else if (i > 6) {
				int num = int(m_TimerScore) / 60 * 1000000;
				UINT Base = (UINT)pow(10, i);
				Num = ((UINT)num) % Base;
				Num = Num / (Base / 10);
				UV0 = m_BackupVertices[VerNum].textureCoordinate;
				UV0.x = (float)Num / 11.0f;
			}
			else {
				UV0 = m_BackupVertices[VerNum].textureCoordinate;
				UV0.x = 10.0f / 11.0f;
			}
			auto v = VertexPositionTexture(
				m_BackupVertices[VerNum].position,
				UV0
			);
			NewVertices.push_back(v);

			Vec2 UV1 = m_BackupVertices[VerNum + 1].textureCoordinate;
			UV1.x = UV0.x + 0.1f;
			v = VertexPositionTexture(
				m_BackupVertices[VerNum + 1].position,
				UV1
			);
			NewVertices.push_back(v);

			Vec2 UV2 = m_BackupVertices[VerNum + 2].textureCoordinate;
			UV2.x = UV0.x;

			v = VertexPositionTexture(
				m_BackupVertices[VerNum + 2].position,
				UV2
			);
			NewVertices.push_back(v);

			Vec2 UV3 = m_BackupVertices[VerNum + 3].textureCoordinate;
			UV3.x = UV0.x + 0.1f;

			v = VertexPositionTexture(
				m_BackupVertices[VerNum + 3].position,
				UV3
			);
			NewVertices.push_back(v);

			VerNum += 4;
		}
		auto PtrDraw = GetComponent<PTSpriteDraw>();
		PtrDraw->UpdateVertices(NewVertices);

		//wstringstream ss;
		//ss << L"Timer : " << m_Timer << std::endl;
		//ss << L"TimeScore : " << m_TimeScore << std::endl;

		//文字列コンポーネントの取得
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(ss.str());
	}

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
			AddGameObject<ResultSprite>(L"Result1", Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
			AddGameObject<ResultSprite>(L"UI_Time_2", Vec2(256.0f, 128.0f), Vec2(0.0f, 150.0f));
			AddGameObject<ResultSprite>(L"Result", Vec2(256.0f, 128.0f), Vec2(0.0f, 300.0f));
			m_SpVec[0] = AddGameObject<ResultSprite>(L"ritorai", Vec2(160.0f, 100.0f), Vec2(-150.0f, -250.0f));
			m_SpVec[1] = AddGameObject<ResultSprite>(L"title", Vec2(160.0f, 100.0f), Vec2(150.0f, -250.0f));

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

