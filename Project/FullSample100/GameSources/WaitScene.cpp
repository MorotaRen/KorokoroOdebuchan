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