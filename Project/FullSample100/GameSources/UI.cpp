/*!
@file UI.cpp
@brief UI����
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	/***************************************************************************************
								  �^�C�g���V�[����UI
	***************************************************************************************/
	TitleSceneSprite::TitleSceneSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}
	void TitleSceneSprite::OnCreate() {
		Sprite::OnCreate();
	}
	void TitleSceneSprite::SetActive(bool Active) {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		if (Active) {
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	/***************************************************************************************
									  �Z���N�g�V�[����UI
	***************************************************************************************/
	SelectSceneSprite::SelectSceneSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	//--------------------------------------------------------------------------------------
	//	�I�����Ă��鏊��\������X�v���C�g
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
		// �z�u���Ă���X�e�[�W����A���I�����Ă���X�e�[�W�ԍ����擾
		auto stageNum = GetTypeStage<SelectScene>()->GetStageNum();
		// �z�u���Ă���X�e�[�W����A�X�e�[�W�X�v���C�g�̔z����擾
		auto spVec = GetTypeStage<SelectScene>()->GetSpVec();
		// �X�e�[�W�ԍ����獡�I�����Ă���X�e�[�W�X�v���C�g�����
		auto stageSprite = spVec[++stageNum];
		//���肵���X�v���C�g�̈ʒu���擾
		auto nowSpritePos = stageSprite->GetComponent<Transform>()->GetPosition();
		// �X�e�[�W�X�v���C�g�̈ʒu���玩���̈ʒu�������ċ��������߂�
		auto dis = nowSpritePos - pos;
		// �ړ��ʂ��v�Z
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
		// �ʒu�Ɉړ��ʂ𑫂�
		pos.x += moveX;
		pos.y += moveY;

		ptrTrans->SetPosition(pos);


	}

	//--------------------------------------------------------------------------------------
	//	�J�E���g�_�E��
	//--------------------------------------------------------------------------------------
	CountDown::CountDown(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_TotalTime(0.0f),
		m_RemoveTime(5.0f),
		m_Count(0)
	{}

	void CountDown::OnCreate() {
		Sprite::OnCreate();
		SetDrawLayer(20);
	}
	void CountDown::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 3.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else
		{
			dis = (m_TotalTime - removeTimeHalf) / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f - dis));
			m_Count++;
			m_TotalTime = 0;
		}

		switch (m_Count)
		{
		case 1:
			ptrDraw->SetTextureResource(L"Countdown_2");
			break;
		case 2:
			ptrDraw->SetTextureResource(L"Countdown_1");
			break;
		case 3:
			//�X�^�[�g�̕\��
			ptrDraw->SetTextureResource(L"START");
			break;
		case 4:
			GetTypeStage<TestStage>()->SetStart(true);
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			break;
		}
	}

	/***************************************************************************************
									  ���C���V�[����UI
	***************************************************************************************/
	MainSceneSprite::MainSceneSprite(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}

	//--------------------------------------------------------------------------------------
	//	�|�[�Y�p�̃��j���[
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
	//	���Ԍv��
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

		//�C���f�b�N�X�z��
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
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
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
	//	time�̉摜�\��
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
	//	�X�}�b�V���Q�[�W�����܂������Ƃ����m�点
	//--------------------------------------------------------------------------------------
	GaugeMax::GaugeMax(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos)
	{}
	void GaugeMax::OnCreate() {
		Sprite::OnCreate();
		AddTag(L"GaugeMax");

		//�A�N�V�����̓o�^
		auto PtrAction = AddComponent<Action>();
		PtrAction->AddRotateTo(0.5f, Vec3(0, 0, XM_1DIVPI));
		PtrAction->AddRotateBy(0.5f, Vec3(0, 0, -0.7f));
		//���[�v����
		PtrAction->SetLooped(true);
		//�A�N�V�����J�n
		PtrAction->Run();
	}
	void GaugeMax::OnUpdate() {
		if (GameSystems::GetInstans().GetSmashPoint() >= 5) {
			SetDrawActive(true);
		}
		else {
			SetDrawActive(false);
		}
	}
	//--------------------------------------------------------------------------------------
	//	�X�s�[�h���[�^�[��UI
	//--------------------------------------------------------------------------------------
	SpeedMeter::SpeedMeter(const shared_ptr<Stage>&stagePtr) :
		GameObject(stagePtr)
	{}

	void SpeedMeter::OnCreate() {

		float helfSize = 0.5f;
		//���_�z��i�c���T���\���j
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);
		SetDrawLayer(1);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(250, 250, 1.0f);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(450, -200, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"SpeedMeter");
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		GetTypeStage<TestStage>()->AddGameObject<SpeedMeterNeedle>();
	}
	void SpeedMeter::OnUpdate() {


	}

	// �X�s�[�h���[�^�[�̐j
	SpeedMeterNeedle::SpeedMeterNeedle(const shared_ptr<Stage>&stagePtr) :
		GameObject(stagePtr),
		m_speed(0),
		m_rotate(90 * XM_PI / 180)
		
	{}

	void SpeedMeterNeedle::OnCreate() {

		float helfSize = 0.5f;
		//���_�z��i�c���T���\���j
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize,  helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f, -0.0f)) },
			{ VertexPositionColorTexture(Vec3(-helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(-0.0f,  1.0f)) },
			{ VertexPositionColorTexture(Vec3(helfSize, -helfSize, 0), Col4(1.0f, 1.0f, 1.0f, 1.0f), Vec2(1.0f,  1.0f)) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//0  1
		//2  3
		//
		SetAlphaActive(true);
		SetDrawLayer(2);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(100, 500, 1.0f);
		ptrTransform->SetRotation(0, 0, m_rotate);
		ptrTransform->SetPosition(575, -325 , 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetTextureResource(L"SpeedMeterNeedle");
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

	}

	void SpeedMeterNeedle::OnUpdate() {
		auto ptrTrans = GetComponent<Transform>();
		m_speed = GameSystems::GetInstans().GetPlayerSpeed();// �v���C���[�̃X�s�[�h���擾
		float culcSpeed = m_speed *= 11.25f;// �ő呬�x��90�ɂȂ�悤�ɔ{����������
		float angle = 90 - culcSpeed;// �j�̊p�x
		if(angle >= 0) m_rotate = angle * XM_PI / 180;// ���W�A���p�ɕϊ�
		ptrTrans->SetRotation(0, 0, m_rotate);
	}

	//--------------------------------------------------------------------------------------
	//	�X�s�[�h���[�^�[�p�̐���
	//--------------------------------------------------------------------------------------
	SpeedMeterNumber::SpeedMeterNumber(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos, bool resultFlg) :
		GameObject(StagePtr),
		m_NumberOfDigits(NumberOfDigits),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_Speed(0.0f)
	{}

	void SpeedMeterNumber::OnCreate() {
		AddTag(L"SpeedMeterNumber");

		float XPiecesize = 1.0f / (float)m_NumberOfDigits;
		float HelfSize = 0.5f;
		//�C���f�b�N�X�z��
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
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		PtrDraw->SetTextureResource(m_TextureKey);

	}

	void SpeedMeterNumber::OnUpdate() {
		m_Speed = GameSystems::GetInstans().GetPlayerSpeed()*10;
		
		vector<VertexPositionTexture> NewVertices;
		UINT Num;
		int VerNum = 0;
		for (UINT i = m_NumberOfDigits; i > 0; i--) {
			Vec2 UV0;
			UINT Base = (UINT)pow(10, i);
			Num = ((UINT)m_Speed) % Base;
			Num = Num / (Base / 10);
			UV0 = m_BackupVertices[VerNum].textureCoordinate;
			UV0.x = (float)Num / 11.0f;
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


	/***************************************************************************************
									  ���U���g�V�[����UI
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
	//	�^�C�}�[�̌��ʕ\��
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

		//�C���f�b�N�X�z��
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
		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
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

