/// ----------------------------------------<summary>
/// �^�C�g���p�̃X�e�[�W�̃\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
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
		auto stageNum = GetTypeStage<TitleScene>()->GetStageNum();
		// �z�u���Ă���X�e�[�W����A�X�e�[�W�X�v���C�g�̔z����擾
		auto spVec = GetTypeStage<TitleScene>()->GetSpVec();
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
		else if (moveY > -Pickdis&&moveY <= 0.0f) {
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
	//	�^�C�g���V�[���̃N���X
	//--------------------------------------------------------------------------------------
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

	void TitleScene::CreateBackground() {
		//�Q�[����ʃT�C�Y
		Vec2 gamesize = Vec2((float)App::GetApp()->GetGameWidth(),(float)App::GetApp()->GetGameHeight());
	}

	void TitleScene::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�^�C�g�����S
			m_Spvec[0] = AddGameObject<Sprite>(L"TitleLogo", Vec2(256.0f, 256.0f), Vec2(0, 0));
			//��Փx�̃X�v���C�g���쐬
			m_Spvec[1] = AddGameObject<Sprite>(L"Title_SpringStage", Vec2(640.0f, 400.0f),Vec2(-320,200));
			m_Spvec[2] = AddGameObject<Sprite>(L"Preparation", Vec2(640.0f, 400.0f), Vec2(320.0f, 200.0f));
			m_Spvec[3] = AddGameObject<Sprite>(L"Preparation", Vec2(640.0f, 400.0f), Vec2(-320.0f, -200.0f));
			m_Spvec[4] = AddGameObject<Sprite>(L"Preparation", Vec2(640.0f, 400.0f), Vec2(320.0f, -200.0f));

			//�}�X�N�X�v���C�g
			m_SpotSprite = AddGameObject<SelectSpotSprite>(L"Title_Mask", Vec2(1921.0f, 1201.0f), Vec2(-320.0f, 200.0f));
			m_SpotSprite->SetDrawLayer(10);

			//�`�揈�����L��
			m_Spvec[0]->SetDrawActive(true);
			m_Spvec[1]->SetDrawActive(true);
			m_Spvec[2]->SetDrawActive(true);
			m_Spvec[3]->SetDrawActive(true);
			m_Spvec[4]->SetDrawActive(true);
			
			m_Spvec[0]->SetDrawLayer(9);
			m_Spvec[1]->SetDrawLayer(1);
			m_Spvec[2]->SetDrawLayer(1);
			m_Spvec[3]->SetDrawLayer(1);
			m_Spvec[4]->SetDrawLayer(1);

			//UI�̍쐬
			CreateUI();

			CreateBackground();

			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.5f);

			AddGameObject<FadeSprite>(FadeType::FadeIn);
		}
		catch (...) {
			throw;
		}
	}
	void TitleScene::OnUpdate() {
		//
		bool SelectSpotFlag = m_SpotSprite->GetSelectSpotFlag();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (cntlVec.bConnected) {
			//1��X�e�B�b�N�|������߂��܂Ń��b�N����
			if (SelectSpotFlag == true) {
				if (!m_CntrolLock) {
					if (cntlVec.fThumbLX >= 0.8f) {
						if (m_StageNum != 3) {
							m_StageNum++;
							m_CntrolLock = true;

						}
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
			}
			//���
			if (m_StageNum == 4) {
				m_StageNum = 3;
			}
			else if (m_StageNum == -1) {
				m_StageNum = 0;
			}
		}

		//�V�[���J��
		if (cntlVec.wPressedButtons&XINPUT_GAMEPAD_A&&SelectSpotFlag == true || KeyState.m_bPressedKeyTbl[VK_SPACE]) {
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			XAPtr->Stop(m_BGM);
			AddGameObject<FadeSprite>(FadeType::FadeOut, L"ToTestStage");
		}
	}
}