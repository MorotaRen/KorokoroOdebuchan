#include "stdafx.h"
#include "Project.h"
#include "WaitScene.h"

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

	bool WaitScene::m_Loaded = false;
	std::mutex WaitScene::mtx;


	void WaitScene::LoadResourceFunc()
	{
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		//�ǂݍ���
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
			{L"OBJ_CourseSpring_Road.bmf",L"MS_Spring"}
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\";
			auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName, true);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
		mtx.lock();
		m_Loaded = true;
		mtx.unlock();

	}

	//����
	void WaitScene::OnCreate() {
		CreateViewLight();
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"SpriteStudio\\";

		AddGameObject<SS5Object>(srtmodel, L"LoadingAnimation.ssae", L"LoadAnim");

		//���̑����\�[�X�̓ǂݍ���
		std::thread LoadThread(LoadResourceFunc);
		//�I���܂ő҂��Ȃ�
		LoadThread.detach();

	}
	//�X�V
	void WaitScene::OnUpdate() {
		if (m_Loaded) {
			//���\�[�X�̃��[�h���I��������^�C�g���X�e�[�W�Ɉڍs
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTestStage");
		}
	}
}