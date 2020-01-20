#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void WaitScene::CreateViewLight() {
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

	//�\�z
	WaitScene::WaitScene() {

	}
	//�j��
	WaitScene::~WaitScene() {

	}
	//����
	void WaitScene::OnCreate() {
		CreateViewLight();
	}
	//�X�V
	void WaitScene::OnUpdate() {
		wstring DataDir;
		App::GetApp()->GetAssetsDirectory(DataDir);
		//�ҋ@�f�[�^�����ǂݍ���
		wstring strdata = DataDir + L"";
	}
}