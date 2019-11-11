#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void TestStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5.0f);
		const Vec3 at(0.0f, 0.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void TestStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();


			AddGameObject<TestBlock>(Vec3(0, 0, 0), Vec3(20, 1, 500), Vec3(10, 0, 0));
			auto player = AddGameObject<Player>(Vec3(0, 1, 0), Vec3(1, 1, 1));
			SetSharedGameObject(L"Player",player);
		}
		catch (...) {
			throw;
		}
	}

}
