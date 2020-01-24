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
			{L"CourseSpring_Box_floor_1.bmf",L"MS_SpringFloor1"},
			{L"CourseSpring_Box_floor_2.bmf",L"MS_SpringFloor2"},
			{L"CourseSpring_Box_floor_3.bmf",L"MS_SpringFloor3"},
			{L"CourseSpring_Box_floor_4.bmf",L"MS_SpringFloor4"},
			{L"CourseSpring_Box_floor_5.bmf",L"MS_SpringFloor5"},
			{L"CourseSpring_Box_floor_6.bmf",L"MS_SpringFloor6"},
			{L"CourseSpring_Box_floor_7.bmf",L"MS_SpringFloor7"},
			{L"CourseSpring_Box_floor_8.bmf",L"MS_SpringFloor8"},
			{L"CourseSpring_Box_floor_9.bmf",L"MS_SpringFloor9"},
			{L"CourseSpring_Box_floor_10.bmf",L"MS_SpringFloor10"},
			{L"CourseSpring_Box_floor_11.bmf",L"MS_SpringFloor11"},
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\Spring_BMF\\";
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