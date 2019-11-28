/// ----------------------------------------<summary>
/// �^�C�g���p�̃X�e�[�W�̃\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(0.0f,0.0f,0.0f);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void TitleScene::CreateUI() {

	}

	void TitleScene::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();


			//��Փx�̃X�v���C�g���쐬
			m_Spvec[0] = AddGameObject<Sprite>(L"Title", Vec2(1000.0f, 1000.0f),Vec2(0,0));
			//m_Spvec[1] = AddGameObject<Sprite>(L"Summer", Vec2(640.0f, 400.0f), Vec2(640.0f, -400.0f));
			//m_Spvec[2] = AddGameObject<Sprite>(L"Autumn", Vec2(640.0f, 400.0f), Vec2(-640.0f, 400.0f));
			//m_Spvec[3] = AddGameObject<Sprite>(L"Winter", Vec2(640.0f, 400.0f), Vec2(-640.0f, 400.0f));

			//m_Spvec[0]->SetDrawActive(true);
			//m_Spvec[1]->SetDrawActive(true);
			//m_Spvec[2]->SetDrawActive(true);
			//m_Spvec[3]->SetDrawActive(true);

			//UI�̍쐬
			CreateUI();
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {

	}
}