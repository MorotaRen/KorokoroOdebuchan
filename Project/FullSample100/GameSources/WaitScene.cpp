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
		int stagenum = GameSystems::GetInstans().GetGameStageNum();
		if (stagenum == 1) {
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
				{L"curve1.bmf",L"MS_SpringWallR2_1"},
				{L"curve2.bmf",L"MS_SpringWallR2_2"},
				{L"curve3.bmf",L"MS_SpringWallR2_3"},
				{L"curve4.bmf",L"MS_SpringWallR2_4"},
				{L"curve5.bmf",L"MS_SpringWallR2_5"},
				{L"curve6.bmf",L"MS_SpringWallR2_6"},
				{L"curve7.bmf",L"MS_SpringWallR2_7"},
				{L"curve8.bmf",L"MS_SpringWallR2_8"},
				{L"curve9.bmf",L"MS_SpringWallR2_9"},
				{L"curve10.bmf",L"MS_SpringWallR2_10"},
				{L"curve11.bmf",L"MS_SpringWallR2_11"},
				{L"curve12.bmf",L"MS_SpringWallR2_12"},
				{L"curve13.bmf",L"MS_SpringWallR2_13"},
				{L"curve14.bmf",L"MS_SpringWallR2_14"},
				{L"curve15.bmf",L"MS_SpringWallR2_15"},
				{L"curve16.bmf",L"MS_SpringWallR2_16"},
				{L"curve17.bmf",L"MS_SpringWallR2_17"},
				{L"curve18.bmf",L"MS_SpringWallR2_18"},
				{L"curve19.bmf",L"MS_SpringWallR2_19"},
				{L"curve20.bmf",L"MS_SpringWallR2_20"},
				{L"curve21.bmf",L"MS_SpringWallR2_21"},
				{L"curve22.bmf",L"MS_SpringWallR2_22"},
				{L"curve23.bmf",L"MS_SpringWallR2_23"},
				{L"curve24.bmf",L"MS_SpringWallR2_24"},
				{L"curve25.bmf",L"MS_SpringWallR2_25"},
				{L"Goal_Floor.bmf",L"MS_SpringGF"},
				{L"Goal_Wall1.bmf",L"MS_SpringGW1"},
				{L"Goal_Wall2.bmf",L"MS_SpringGW2"},
				{L"Goal_Wall3.bmf",L"MS_SpringGW3"},
			};
			for (auto model : models) {
				wstring srtmodel = dataDir + L"Models\\Spring_BMF\\";
				auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName, true);
				App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
			}
		}
		if (stagenum == 2) {
			InitializedParam models[] = {
				//{L"ファイル名",L"呼び出し時のキー"}
				{L"BackFloor.bmf",L"MSS_BackFloor"},
				{L"Floor_1.bmf",L"MSS_Floor"},
				{L"GoalGate.bmf",L"MSS_GoalGate"},
				{L"Ground.bmf",L"MSS_Ground"},
				{L"Ocean.bmf",L"MSS_Ocean"},
				{L"StartGate.bmf",L"MSS_StartGate"},
				{L"Walls_1.bmf",L"MSS_Wall1"},
				{L"Walls_2.bmf",L"MSS_Wall2"},
				{L"Walls_3.bmf",L"MSS_Wall3"},
				{L"Walls_4.bmf",L"MSS_Wall4"},

			};
			for (auto model : models) {
				wstring srtmodel = dataDir + L"Models\\Summer_BMF\\";
				auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName, true);
				App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
			}
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