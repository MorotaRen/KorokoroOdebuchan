/// ----------------------------------------<summary>
/// �^�C�g���p�̃X�e�[�W�̃\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleScene::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}
	void TitleScene::CreateBackground() {
		//�Q�[����ʃT�C�Y
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(),(float)App::GetApp()->GetGameHeight());
	}
	void TitleScene::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//CreateBackground();
			auto player = AddGameObject<Player>(Vec3(250, 100, 0), Vec3(1, 1, 1));
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		auto pad = GameSystems::GetInstans().GetPad();
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		//Pad�̉�������ł��{�^���������ꂽ��Stage�ړ�
		if (pad.wPressedButtons) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), ptrScene, L"ToGameScene");
		}
	}
}