#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�^�C�g���V�[���̃N���X
	//--------------------------------------------------------------------------------------
	void TitleScene::CreateViewLight() {
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

	void TitleScene::CreateUI() {
		//�^�C�g��BG
		AddGameObject<TitleSceneSprite>(L"TitleLogo", Vec2(256.0f, 256.0f), Vec2(0, 0));
		//pushBottan
	}

	void TitleScene::CreateBackground() {
		//�Q�[����ʃT�C�Y
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(), (float)App::GetApp()->GetGameHeight());
	}

	void TitleScene::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//UI�̍쐬
			CreateUI();

			CreateBackground();

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);

			AddGameObject<FadeSprite>(FadeType::FadeIn, 0.01f);
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (cntlVec.bConnected) {
			if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A||KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"SelectScene");
			}
		}
	}
}