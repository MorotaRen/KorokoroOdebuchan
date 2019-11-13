#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5000.0f);
		const Vec3 at(0.0f, 0.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void TestStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			auto stageobject = AddGameObject<TestBlock>(Vec3(0, 0, 0), Vec3(20, 1, 500), Vec3(0, 90, 0));
			SetSharedGameObject(L"StageObject", stageobject);
			auto player = AddGameObject<Player>(Vec3(250, 100, 0), Vec3(1, 1, 1));
			SetSharedGameObject(L"Player",player);
			GameSystems::GetInstans().LoadStageCSV();

		}
		catch (...) {
			throw;
		}
	}

}
