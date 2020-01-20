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

	void WaitScene::LoadResourceFunc()
	{
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		//読み込み

	}

	//構築
	WaitScene::WaitScene() {

	}
	//破棄
	WaitScene::~WaitScene() {

	}
	//生成
	void WaitScene::OnCreate() {
		CreateViewLight();
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"SpriteStudio\\";

		AddGameObject<SS5Object>(srtmodel, L"LoadingAnimation.ssae", L"anime_1");

		//その他リソースの読み込み
		std::thread LoadThread(LoadResourceFunc);
		//終了まで待たない
		LoadThread.detach();

	}
	//更新
	void WaitScene::OnUpdate() {

	}
}