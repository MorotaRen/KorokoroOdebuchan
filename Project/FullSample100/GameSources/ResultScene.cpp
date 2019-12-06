/*!
@file Result.cpp
@brief ���U���g�N���X����
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�v���C�g
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

		//�����������
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

		//������R���|�[�l���g�̎擾
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(ss.str());
	}

	//--------------------------------------------------------------------------------------
	//	���U���g�V�[���̃N���X
	//--------------------------------------------------------------------------------------
	void ResultScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(0.0f, 0.0f, 0.0f);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void ResultScene::CreateBackground() {
	}

	void ResultScene::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			CreateBackground();

			//�S�[��������
			//App::GetApp()->GetScene<TestStage>()->GetSharedGameObject<Timer>(L"Timer")->SetScore();
			AddGameObject<ResultTimer>(8, L"UI_Number_4", true, Vec2(160.0f, 40.0f), Vec3(-60.0f, 60.0f, 0.0f));
			AddGameObject<ResultSprite>(L"gray", Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f));
			m_SpVec[0] = AddGameObject<ResultSprite>(L"Title_1", Vec2(128.0f, 64.0f), Vec2(-100.0f, -50.0f));
			m_SpVec[1] = AddGameObject<ResultSprite>(L"Title_2", Vec2(128.0f, 64.0f), Vec2(100.0f, -50.0f));

			AddGameObject<FadeSprite>(FadeType::FadeIn);
		}
		catch (...) {
			throw;
		}
	}
	void ResultScene::OnUpdate() {

		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		//�V�[���J��
		//if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A) {
			//AddGameObject<FadeSprite>(FadeType::FadeOut, L"TitleScene");
		//}

		if (cntlVec.bConnected) {
			//1��X�e�B�b�N�|������߂��܂Ń��b�N����
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
			//���
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
	}

}

//end basecross

