#include "stdafx.h"
#include "Project.h"
#include "WaitScene.h"

namespace basecross {
	void WaitScene::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(0.0f, 0.0f, 0.0f);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	bool WaitScene::m_Loaded = false;
	std::mutex WaitScene::mtx;


	void WaitScene::LoadResourceFunc()
	{
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		//読み込み
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
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

			{L"CourseSpring_Box_Wall_L_1.bmf",L"MS_SpringWallL1"},
			{L"CourseSpring_Box_Wall_L_2.bmf",L"MS_SpringWallL2"},
			{L"CourseSpring_Box_Wall_L_3.bmf",L"MS_SpringWallL3"},
			{L"CourseSpring_Box_Wall_L_4.bmf",L"MS_SpringWallL4"},
			{L"CourseSpring_Box_Wall_L_5.bmf",L"MS_SpringWallL5"},
			{L"CourseSpring_Box_Wall_L_6.bmf",L"MS_SpringWallL6"},
			{L"CourseSpring_Box_Wall_L_7.bmf",L"MS_SpringWallL7"},
			{L"CourseSpring_Box_Wall_L_8.bmf",L"MS_SpringWallL8"},
			{L"CourseSpring_Box_Wall_L_9.bmf",L"MS_SpringWallL9"},
			{L"CourseSpring_Box_Wall_L_10.bmf",L"MS_SpringWallL10"},
			{L"CourseSpring_Box_Wall_L_11.bmf",L"MS_SpringWallL11"},

			{L"CourseSpring_Box_Wall_R_1.bmf",L"MS_SpringWallR1"},
			{L"CourseSpring_Box_Wall_R_2.bmf",L"MS_SpringWallR2"},
			{L"CourseSpring_Box_Wall_R_3.bmf",L"MS_SpringWallR3"},
			{L"CourseSpring_Box_Wall_R_4.bmf",L"MS_SpringWallR4"},
			{L"CourseSpring_Box_Wall_R_5.bmf",L"MS_SpringWallR5"},
			{L"CourseSpring_Box_Wall_R_6.bmf",L"MS_SpringWallR6"},
			{L"CourseSpring_Box_Wall_R_7.bmf",L"MS_SpringWallR7"},
			{L"CourseSpring_Box_Wall_R_8.bmf",L"MS_SpringWallR8"},
			{L"CourseSpring_Box_Wall_R_9.bmf",L"MS_SpringWallR9"},
			{L"CourseSpring_Box_Wall_R_10.bmf",L"MS_SpringWallR10"},
			{L"CourseSpring_Box_Wall_R_11.bmf",L"MS_SpringWallR11"},
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

	//生成
	void WaitScene::OnCreate() {
		CreateViewLight();
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"SpriteStudio\\";

		AddGameObject<SS5Object>(srtmodel, L"LoadingAnimation.ssae", L"LoadAnim");

		//その他リソースの読み込み
		std::thread LoadThread(LoadResourceFunc);
		//終了まで待たない
		LoadThread.detach();

	}
	//更新
	void WaitScene::OnUpdate() {
		if (m_Loaded) {
			//リソースのロードが終了したらタイトルステージに移行
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTestStage");
		}
	}
}