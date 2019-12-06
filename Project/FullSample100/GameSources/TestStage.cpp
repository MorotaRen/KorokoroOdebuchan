#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -10.0f);
		const Vec3 at(0.0f, 0.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetPlayer(m_ptrPlayer);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void TestStage::CreateUI()
	{
		//�^�C�}�[
		auto TimerPtr = AddGameObject<Timer>(8, L"UI_Number_5", true, Vec2(160.0f, 40.0f), Vec3(360.0f, 350.0f, 0.0f));
		SetSharedGameObject(L"Timer", TimerPtr);
		//�������ꂽ�Ƃ��͎~�߂Ă���
		TimerPtr->SetUpdateActive(false);
		//time�̉摜�\��
		auto TimePtr = AddGameObject<TextTime>(L"UI_Time_2", Vec2(120.0f, 50.0f), Vec2(200.0f, 350.0f));
		SetSharedGameObject(L"TextTime", TimePtr);

		//�X�^�[�g�\��
		AddGameObject<CountDown>(L"START", Vec2(0.0f, 0.0f));

	}

	void TestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			//CreateViewLight();

			//�}���`���C�g�̍쐬
			auto PtrMultiLight = CreateLight<MultiLight>();
			//�f�t�H���g�̃��C�e�B���O���w��
			PtrMultiLight->SetDefaultLighting();

			const Vec3 eye(0.0f, 0.0f, -10.0f);
			const Vec3 at(0.0f, 0.0f, 0.0f);
			auto PtrView = CreateView<SingleView>();
			//�r���[�̃J�����̐ݒ�
			m_camera = ObjectFactory::Create<MyCamera>();
			PtrView->SetCamera(m_camera);
			m_camera->SetEye(eye);
			m_camera->SetAt(at);

			// UI�̍쐬
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

		//�X�^�[�g�O�Ŏ~�܂�悤�ɂ���
		m_deltTime += App::GetApp()->GetElapsedTime();
		if (m_deltTime > 1.8f) {
			m_updateFlag = true;

		}
	}
	//�����~�߂鏈��
	void TestStage::UpdateStage() {
		auto &app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObject = stage->GetGameObjectVec();

		//��~
		if (!m_updateFlag) {
			Stage::UpdateStage();
		}

		//m_stopTime��m_deltTime�Ɠ������v��
		//�ĊJ
		m_stopTime += App::GetApp()->GetElapsedTime();
		if (m_stopTime > 5.0f) {
			m_updateFlag = false;
			//Timer�𓮂���
			for (auto v : gameObject) {
				if (v->FindTag(L"Timer")) {
					v->SetUpdateActive(true);
				}
			}
		}
	}
}

