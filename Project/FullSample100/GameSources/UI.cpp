/*!
@file UI.cpp
@brief UI実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	/***************************************************************************************
									  タイトルシーンのUI
	***************************************************************************************/
	TitleSceneSprite::TitleSceneSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

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
		else if (moveY > -Pickdis && moveY <= 0.0f) {
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

	/***************************************************************************************
									  メインシーンのUI
	***************************************************************************************/
	MainSceneSprite::MainSceneSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}
	//--------------------------------------------------------------------------------------
	//	2Dのスプライト
	//--------------------------------------------------------------------------------------
	CountDown::CountDown(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_TotalTime(0.0f),
		m_RemoveTime(5.0f)
	{}

	void CountDown::OnCreate() {
		Sprite::OnCreate();
		SetAlphaActive(50);
	}
	void CountDown::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 2.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else
		{
			dis = (m_TotalTime - removeTimeHalf) / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f - dis));
		}

		if (m_TotalTime > m_RemoveTime) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}


	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	StartPause::StartPause(const shared_ptr<Stage>& StagePtr,
		const wstring&textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(StagePtr, textureKey, startScale, startPos)
	{}

	void StartPause::OnCreate()
	{
		Sprite::OnCreate();
		AddTag(L"StartPause");
		SetDrawLayer(100);
		SetDrawActive(false);
	}

	void StartPause::OnUpdate()
	{

	}
	void StartPause::Akarusa(bool flg)
	{
		GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 1.0f));
	}

	//--------------------------------------------------------------------------------------
	//	時間計測
	//--------------------------------------------------------------------------------------
	Timer::Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos, bool resultFlg) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Timer(0.0f)
	{}

	void Timer::OnCreate() {
		AddTag(L"Timer");

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
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		PtrTransform->SetRotation(0, 0, 0);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		PtrDraw->SetTextureResource(m_TextureKey);


	}

	void Timer::OnUpdate() {
		m_Timer += App::GetApp()->GetElapsedTime();

		vector<VertexPositionTexture> NewVertices;
		UINT Num;
		int VerNum = 0;
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			Vec2 UV0;
			if (i < 3) {
				int num = int((m_Timer - (int(m_Timer) / 1)) * 100);
				UINT Base = (UINT)pow(10, i);
				Num = ((UINT)num) % Base;
				Num = Num / (Base / 10);
				UV0 = m_BackupVertices[VerNum].textureCoordinate;
				UV0.x = (float)Num / 11.0f;
			}
			else if (i > 3 && i < 6) {
				int num = int(m_Timer) % 60 * 1000;
				UINT Base = (UINT)pow(10, i);
				Num = ((UINT)num) % Base;
				Num = Num / (Base / 10);
				UV0 = m_BackupVertices[VerNum].textureCoordinate;
				UV0.x = (float)Num / 11.0f;
			}
			else if (i > 6) {
				int num = int(m_Timer) / 60 * 1000000;
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

	}

	//--------------------------------------------------------------------------------------
	//	timeの画像表示
	//--------------------------------------------------------------------------------------
	TextTime::TextTime(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void TextTime::OnCreate() {
		Sprite::OnCreate();
	}

	//--------------------------------------------------------------------------------------
	//	スマッシュゲージのUI
	//--------------------------------------------------------------------------------------
	SmashGauge::SmashGauge(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	void SmashGauge::OnCreate() {
		float helfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-0, helfSize, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-0, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize*2.0f, -helfSize, 0), Col4(1.0f, 01.0f, 1.0f, 1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(0.0f, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, XM_PIDIV2);
		ptrTrans->SetPosition(Vec3(m_StartPos.x, m_StartPos.y, 0.0f));
		// ピボットを右端にする
		ptrTrans->SetPivot(0.0f, 0.0f, 0.0f);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		ptrDraw->SetTextureResource(m_TextureKey);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(1000.0f, 100.0f, 1200.0f, 480.0f));

	}
	void SmashGauge::OnUpdate() {
		if (m_Active) {
				UseSmashPoint();
		}
		else {

		}

		wstringstream ss;
		ss << L"m_SmashPoint : " << m_SmashPoint << std::endl;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(ss.str());

	}
	void SmashGauge::CargeSmashPoint(float f) {
		if (m_UsePoint == false) {
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();

			m_SmashPoint += f * 1.0f;
			if (m_SmashPoint >= m_MaxSmashPoint) {
				m_SmashPoint = m_MaxSmashPoint;
				m_IsUsable = true;
			}

			scale.x = 27.5f *m_SmashPoint;
			ptrTrans->SetScale(scale);
		}
	}

	void SmashGauge::UseSmashPoint() {
		if (m_IsUsable == true) {
			auto ptrTrans = GetComponent<Transform>();
			auto scale = ptrTrans->GetScale();
			m_rate = m_MaxSmashPoint / m_SmashPoint;
			m_UsePoint = true;
			ElapsedTime = App::GetApp()->GetElapsedTime();
			m_SmashPoint -= ElapsedTime*6;
			if (m_SmashPoint <= m_MinSmashPoint) {
				m_SmashPoint = m_MinSmashPoint;
				m_Active = false;
				m_UsePoint = false;
				m_IsUsable = false;
			}

			scale.x = m_StartScale.x / m_rate;
			ptrTrans->SetScale(scale);
		}
	}

	/***************************************************************************************
									  リザルトシーンのUI
	***************************************************************************************/
	ResultSceneSprite::ResultSceneSprite(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_TextureKey(textureKey),
		m_StartScale(startScale),
		m_StartPos(startPos)
	{}

	void ResultSceneSprite::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(13);
	}
	void ResultSceneSprite::Transluc(bool Active) {
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

	}

}


//end basecross

