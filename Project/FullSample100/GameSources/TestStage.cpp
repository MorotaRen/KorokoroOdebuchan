#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 1.0f, 0.0f);
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
		AddGameObject<Timer>(L"TestNumber",
			Vec2(640.0f, 128.0f),
			Vec2(0.0f, 0.0f));
	}

	void TestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			//CreateViewLight();

			//�}���`���C�g�̍쐬
			auto PtrMultiLight = CreateLight<MultiLight>();
			//�f�t�H���g�̃��C�e�B���O���w��
			PtrMultiLight->SetDefaultLighting();

			const Vec3 eye(0.0f, 0.0f, -2.0f);
			const Vec3 at(0.0f, 0.01f, 0.0f);
			auto PtrView = CreateView<SingleView>();
			//�r���[�̃J�����̐ݒ�
			m_camera = ObjectFactory::Create<MyCamera>();
			PtrView->SetCamera(m_camera);
			m_camera->SetEye(eye);
			m_camera->SetAt(at);

			//AddGameObject<TestBlock>(Vec3(0, 0, 0), Vec3(20, 1, 1200), Vec3(10, 0, 0));
			//m_ptrPlayer = AddGameObject<Player>(Vec3(0, 12, -15), Vec3(1, 1, 1));



			//auto stageobject = AddGameObject<TestBlock>(Vec3(0, 0, 0), Vec3(20, 1, 500), Vec3(0, 90, 0));
			//SetSharedGameObject(L"StageObject", stageobject);
			//auto player = AddGameObject<Player>(Vec3(250, 100, 0), Vec3(1, 1, 1));
			//SetSharedGameObject(L"Player",player);

			// UI�̍쐬
			CreateUI();

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
			m_IsCreateObject = true;
		}
	}

}
