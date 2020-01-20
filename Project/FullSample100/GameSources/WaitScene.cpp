#include "stdafx.h"
#include "Project.h"

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

	//構築
	WaitScene::WaitScene() {

	}
	//破棄
	WaitScene::~WaitScene() {

	}
	//生成
	void WaitScene::OnCreate() {
		CreateViewLight();
	}
	//更新
	void WaitScene::OnUpdate() {
		wstring DataDir;
		App::GetApp()->GetAssetsDirectory(DataDir);
		//待機データだけ読み込み
		wstring strdata = DataDir + L"";
	}
}