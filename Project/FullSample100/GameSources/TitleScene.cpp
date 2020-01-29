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
		AddGameObject<TitleSceneSprite>(L"TitleLogo", Vec2(512.0f, 512.0f), Vec2(0, 0));
		//pushBottan
		auto PushPtr = AddGameObject<TitleSceneSprite>(L"Press A Button", Vec2(512.0f, 128.0f), Vec2(0, -300));
		SetSharedGameObject(L"A_Button", PushPtr);
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
		//�{�^���̓_��
		//true�̎�
		if (Switch <= 0.0f) {
			FalseTime = 0.0f; //false�̎��̎��Ԃ̃��Z�b�g
			TrueTime += 1.0f; //���Ԍv���J�n
			//��莞�Ԍo�߂��ē����ɂ�����
			if (TrueTime >= TrueTimeEnd) {
				Switch += 1.0f;
				GetSharedGameObject<TitleSceneSprite>(L"A_Button")->SetActive(false);
			}
		}
		//false�̎�
		else {
			TrueTime = 0.0f;//true�̎��̎��Ԃ̃��Z�b�g
			FalseTime += TrueTimePlus;//���Ԍv���J�n
			//��莞�Ԍo�߂��ĕ\��������
			if (FalseTime >= FalseTimeEnd) {
				Switch += -1.0f;
				GetSharedGameObject<TitleSceneSprite>(L"A_Button")->SetActive(true);
			}
		}


		//A�������ꂽ��
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (cntlVec.bConnected) {
			if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A||KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				auto XAPtr = App::GetApp()->GetXAudio2Manager();
				XAPtr->Stop(m_BGM);
				App::GetApp()->GetXAudio2Manager()->Start(L"pushA", 0, 0.5f);
				//�_�ŃX�s�[�h�𑬂�����
				FalseTimeEnd *= FlashingSpeed;
				TrueTimeEnd *= FlashingSpeed;
				DecSwitch += 1.0f;

				if (DecSwitch >= 1.0f) {
					DecTime += 1.0f;//�{�^���������Ă���̎��Ԍv���J�n
					if (DecTime >= FlashingTime) {
						GetSharedGameObject<TitleSceneSprite>(L"A_Button")->SetActive(false);
						TrueTimePlus = 0.0f;//�_�ł��Ȃ��Ȃ�
						if (DecTime >= FlashingEnd) {
						}
					}
				}

				AddGameObject<FadeSprite>(FadeType::FadeOut, 0.01f, L"SelectScene");
			}
		}
	}
}