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
				{L"CourseSummer_Concave_1_1.bmf",L"MSS_Summer1"},
				{L"CourseSummer_Concave_1_2.bmf",L"MSS_Summer2"},
				{L"CourseSummer_Concave_1_3.bmf",L"MSS_Summer3"},
				{L"CourseSummer_Concave_1_4.bmf",L"MSS_Summer4"},
				{L"CourseSummer_Concave_1_5.bmf",L"MSS_Summer5"},
				{L"CourseSummer_Concave_2_1.bmf",L"MSS_Summer6"},
				{L"CourseSummer_Concave_2_2.bmf",L"MSS_Summer7"},
				{L"CourseSummer_Concave_2_3.bmf",L"MSS_Summer8"},
				{L"CourseSummer_Concave_2_4.bmf",L"MSS_Summer9"},
				{L"CourseSummer_Concave_2_5.bmf",L"MSS_Summer10"},
				{L"CourseSummer_Concave_3_1.bmf",L"MSS_Summer11"},
				{L"CourseSummer_Concave_3_2.bmf",L"MSS_Summer12"},
				{L"CourseSummer_Concave_3_3.bmf",L"MSS_Summer13"},
				{L"CourseSummer_Concave_3_4.bmf",L"MSS_Summer14"},
				{L"CourseSummer_Concave_3_5.bmf",L"MSS_Summer15"},
				{L"CourseSummer_Concave_4_1.bmf",L"MSS_Summer16"},
				{L"CourseSummer_Concave_4_2.bmf",L"MSS_Summer17"},
				{L"CourseSummer_Concave_4_3.bmf",L"MSS_Summer18"},
				{L"CourseSummer_Concave_4_4.bmf",L"MSS_Summer19"},
				{L"CourseSummer_Concave_4_5.bmf",L"MSS_Summer20"},
				{L"CourseSummer_Concave_5_1.bmf",L"MSS_Summer21"},
				{L"CourseSummer_Concave_5_2.bmf",L"MSS_Summer22"},
				{L"CourseSummer_Concave_5_3.bmf",L"MSS_Summer23"},
				{L"CourseSummer_Concave_5_4.bmf",L"MSS_Summer24"},
				{L"CourseSummer_Concave_5_5.bmf",L"MSS_Summer25"},
				{L"CourseSummer_Concave_6_1.bmf",L"MSS_Summer26"},
				{L"CourseSummer_Concave_6_2.bmf",L"MSS_Summer27"},
				{L"CourseSummer_Concave_6_3.bmf",L"MSS_Summer28"},
				{L"CourseSummer_Concave_6_4.bmf",L"MSS_Summer29"},
				{L"CourseSummer_Concave_6_5.bmf",L"MSS_Summer30"},
				{L"CourseSummer_Concave_7_1.bmf",L"MSS_Summer31"},
				{L"CourseSummer_Concave_7_2.bmf",L"MSS_Summer32"},
				{L"CourseSummer_Concave_7_3.bmf",L"MSS_Summer33"},
				{L"CourseSummer_Concave_7_4.bmf",L"MSS_Summer34"},
				{L"CourseSummer_Concave_7_5.bmf",L"MSS_Summer35"},
				{L"CourseSummer_Concave_8_1.bmf",L"MSS_Summer36"},
				{L"CourseSummer_Concave_8_2.bmf",L"MSS_Summer37"},
				{L"CourseSummer_Concave_8_3.bmf",L"MSS_Summer38"},
				{L"CourseSummer_Concave_8_4.bmf",L"MSS_Summer39"},
				{L"CourseSummer_Concave_8_5.bmf",L"MSS_Summer40"},
				{L"CourseSummer_Concave_9_1.bmf",L"MSS_Summer41"},
				{L"CourseSummer_Concave_9_2.bmf",L"MSS_Summer42"},
				{L"CourseSummer_Concave_9_3.bmf",L"MSS_Summer43"},
				{L"CourseSummer_Concave_9_4.bmf",L"MSS_Summer44"},
				{L"CourseSummer_Concave_9_5.bmf",L"MSS_Summer45"},


			{L"CourseSummer_CurveFloor_1_1.bmf",L"MSS_Summer46"},
			{L"CourseSummer_CurveFloor_1_2.bmf",L"MSS_Summer47"},
			{L"CourseSummer_CurveFloor_1_3.bmf",L"MSS_Summer48"},
			{L"CourseSummer_CurveFloor_1_4.bmf",L"MSS_Summer49"},
			{L"CourseSummer_CurveFloor_1_5.bmf",L"MSS_Summer50"},
			{L"CourseSummer_CurveFloor_2_1.bmf",L"MSS_Summer51"},
			{L"CourseSummer_CurveFloor_2_2.bmf",L"MSS_Summer52"},
			{L"CourseSummer_CurveFloor_2_3.bmf",L"MSS_Summer53"},
			{L"CourseSummer_CurveFloor_2_4.bmf",L"MSS_Summer54"},
			{L"CourseSummer_CurveFloor_2_5.bmf",L"MSS_Summer55"},
			{L"CourseSummer_CurveFloor_3_1.bmf",L"MSS_Summer56"},
			{L"CourseSummer_CurveFloor_3_2.bmf",L"MSS_Summer57"},
			{L"CourseSummer_CurveFloor_3_3.bmf",L"MSS_Summer58"},
			{L"CourseSummer_CurveFloor_3_4.bmf",L"MSS_Summer59"},
			{L"CourseSummer_CurveFloor_3_5.bmf",L"MSS_Summer60"},
			{L"CourseSummer_CurveFloor_4_1.bmf",L"MSS_Summer61"},
			{L"CourseSummer_CurveFloor_4_2.bmf",L"MSS_Summer62"},
			{L"CourseSummer_CurveFloor_4_3.bmf",L"MSS_Summer63"},
			{L"CourseSummer_CurveFloor_4_4.bmf",L"MSS_Summer64"},
			{L"CourseSummer_CurveFloor_4_5.bmf",L"MSS_Summer65"},
			{L"CourseSummer_CurveFloor_5_1.bmf",L"MSS_Summer66"},
			{L"CourseSummer_CurveFloor_5_2.bmf",L"MSS_Summer67"},
			{L"CourseSummer_CurveFloor_5_3.bmf",L"MSS_Summer68"},
			{L"CourseSummer_CurveFloor_5_4.bmf",L"MSS_Summer69"},
			{L"CourseSummer_CurveFloor_5_5.bmf",L"MSS_Summer70"},
			{L"CourseSummer_CurveFloor_6_1.bmf",L"MSS_Summer71"},
			{L"CourseSummer_CurveFloor_6_2.bmf",L"MSS_Summer72"},
			{L"CourseSummer_CurveFloor_6_3.bmf",L"MSS_Summer73"},
			{L"CourseSummer_CurveFloor_6_4.bmf",L"MSS_Summer74"},
			{L"CourseSummer_CurveFloor_6_5.bmf",L"MSS_Summer75"},
			{L"CourseSummer_CurveFloor_7_1.bmf",L"MSS_Summer76"},
			{L"CourseSummer_CurveFloor_7_2.bmf",L"MSS_Summer77"},
			{L"CourseSummer_CurveFloor_7_3.bmf",L"MSS_Summer78"},
			{L"CourseSummer_CurveFloor_7_4.bmf",L"MSS_Summer79"},
			{L"CourseSummer_CurveFloor_7_5.bmf",L"MSS_Summer80"},
			{L"CourseSummer_CurveFloor_8_1.bmf",L"MSS_Summer81"},
			{L"CourseSummer_CurveFloor_8_2.bmf",L"MSS_Summer82"},
			{L"CourseSummer_CurveFloor_8_3.bmf",L"MSS_Summer83"},
			{L"CourseSummer_CurveFloor_8_4.bmf",L"MSS_Summer84"},
			{L"CourseSummer_CurveFloor_8_5.bmf",L"MSS_Summer85"},
			{L"CourseSummer_CurveFloor_9_1.bmf",L"MSS_Summer86"},
			{L"CourseSummer_CurveFloor_9_2.bmf",L"MSS_Summer87"},
			{L"CourseSummer_CurveFloor_9_3.bmf",L"MSS_Summer88"},
			{L"CourseSummer_CurveFloor_9_4.bmf",L"MSS_Summer89"},
			{L"CourseSummer_CurveFloor_9_5.bmf",L"MSS_Summer90"},

				{L"CourseSummer_Floor_1.bmf",L"MSS_Summer91"},
				{L"CourseSummer_Floor_2.bmf",L"MSS_Summer92"},
				{L"CourseSummer_Floor_3.bmf",L"MSS_Summer93"},
				{L"CourseSummer_Floor_4.bmf",L"MSS_Summer94"},
				{L"CourseSummer_Floor_5.bmf",L"MSS_Summer95"},
				{L"CourseSummer_Floor_6.bmf",L"MSS_Summer96"},
				{L"CourseSummer_Floor_7.bmf",L"MSS_Summer97"},
				{L"CourseSummer_Floor_8.bmf",L"MSS_Summer98"},
				{L"CourseSummer_Floor_9.bmf",L"MSS_Summer99"},
				{L"CourseSummer_Floor_10.bmf",L"MSS_Summer100"},
				{L"CourseSummer_Floor_11.bmf",L"MSS_Summer101"},
				{L"CourseSummer_Floor_12.bmf",L"MSS_Summer102"},
				{L"CourseSummer_Floor_13.bmf",L"MSS_Summer103"},
				{L"CourseSummer_Floor_14.bmf",L"MSS_Summer104"},
				{L"CourseSummer_Floor_15.bmf",L"MSS_Summer105"},
				{L"CourseSummer_Floor_16.bmf",L"MSS_Summer106"},
				{L"CourseSummer_Floor_17.bmf",L"MSS_Summer107"},
				{L"CourseSummer_Wall_L_1.bmf",L"MSS_Summer108"},
				{L"CourseSummer_Wall_L_2.bmf",L"MSS_Summer109"},
				{L"CourseSummer_Wall_L_3.bmf",L"MSS_Summer110"},
				{L"CourseSummer_Wall_L_4.bmf",L"MSS_Summer111"},
				{L"CourseSummer_Wall_L_5.bmf",L"MSS_Summer112"},
				{L"CourseSummer_Wall_L_6.bmf",L"MSS_Summer113"},
				{L"CourseSummer_Wall_L_7.bmf",L"MSS_Summer114"},
				{L"CourseSummer_Wall_L_8.bmf",L"MSS_Summer115"},
				{L"CourseSummer_Wall_L_9.bmf",L"MSS_Summer116"},
				{L"CourseSummer_Wall_L_10.bmf",L"MSS_Summer117"},
				{L"CourseSummer_Wall_L_11.bmf",L"MSS_Summer118"},
				{L"CourseSummer_Wall_L_12.bmf",L"MSS_Summer119"},
				{L"CourseSummer_Wall_L_13.bmf",L"MSS_Summer120"},
				{L"CourseSummer_Wall_L_14.bmf",L"MSS_Summer121"},
				{L"CourseSummer_Wall_L_15.bmf",L"MSS_Summer122"},
				{L"CourseSummer_Wall_L_16.bmf",L"MSS_Summer123"},
				{L"CourseSummer_Wall_L_17.bmf",L"MSS_Summer124"},
				{L"CourseSummer_Wall_R_1.bmf",L"MSS_Summer125"},
				{L"CourseSummer_Wall_R_2.bmf",L"MSS_Summer126"},
				{L"CourseSummer_Wall_R_3.bmf",L"MSS_Summer127"},
				{L"CourseSummer_Wall_R_4.bmf",L"MSS_Summer128"},
				{L"CourseSummer_Wall_R_5.bmf",L"MSS_Summer129"},
				{L"CourseSummer_Wall_R_6.bmf",L"MSS_Summer130"},
				{L"CourseSummer_Wall_R_7.bmf",L"MSS_Summer131"},
				{L"CourseSummer_Wall_R_8.bmf",L"MSS_Summer132"},
				{L"CourseSummer_Wall_R_9.bmf",L"MSS_Summer133"},
				{L"CourseSummer_Wall_R_10.bmf",L"MSS_Summer134"},
				{L"CourseSummer_Wall_R_11.bmf",L"MSS_Summer135"},
				{L"CourseSummer_Wall_R_12.bmf",L"MSS_Summer136"},
				{L"CourseSummer_Wall_R_13.bmf",L"MSS_Summer137"},
				{L"CourseSummer_Wall_R_14.bmf",L"MSS_Summer138"},
				{L"CourseSummer_Wall_R_15.bmf",L"MSS_Summer139"},
				{L"CourseSummer_Wall_R_16.bmf",L"MSS_Summer140"},
				{L"CourseSummer_Wall_R_17.bmf",L"MSS_Summer141"},


			};
			for (auto model : models) {
				wstring srtmodel = dataDir + L"Models\\Summer_BMF\\";
				auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName, true);
				App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
			}
		}
		if (stagenum == 3) {
			InitializedParam models[] = {
				//{L"ファイル名",L"呼び出し時のキー"}
				{L"CourseAki_CurveFloor_1_1.bmf",L"MSA_Aki1"},
				{L"CourseAki_CurveFloor_1_2.bmf",L"MSA_Aki2"},
				{L"CourseAki_CurveFloor_1_3.bmf",L"MSA_Aki3"},
				{L"CourseAki_CurveFloor_1_4.bmf",L"MSA_Aki4"},
				{L"CourseAki_CurveFloor_1_5.bmf",L"MSA_Aki5"},
				{L"CourseAki_CurveFloor_1_6.bmf",L"MSA_Aki6"},
				{L"CourseAki_CurveFloor_1_7.bmf",L"MSA_Aki7"},
				{L"CourseAki_CurveFloor_1_8.bmf",L"MSA_Aki8"},
				{L"CourseAki_CurveFloor_1_9.bmf",L"MSA_Aki9"},
				{L"CourseAki_CurveFloor_1_10.bmf",L"MSA_Aki10"},
				{L"CourseAki_CurveFloor_2_1.bmf",L"MSA_Aki11"},
				{L"CourseAki_CurveFloor_2_2.bmf",L"MSA_Aki12"},
				{L"CourseAki_CurveFloor_2_3.bmf",L"MSA_Aki13"},
				{L"CourseAki_CurveFloor_2_4.bmf",L"MSA_Aki14"},
				{L"CourseAki_CurveFloor_2_5.bmf",L"MSA_Aki15"},
				{L"CourseAki_CurveFloor_2_6.bmf",L"MSA_Aki16"},
				{L"CourseAki_CurveFloor_2_7.bmf",L"MSA_Aki17"},
				{L"CourseAki_CurveFloor_2_8.bmf",L"MSA_Aki18"},
				{L"CourseAki_CurveFloor_2_9.bmf",L"MSA_Aki19"},
				{L"CourseAki_CurveFloor_2_10.bmf",L"MSA_Aki20"},
				{L"CourseAki_CurveFloor_3_1.bmf",L"MSA_Aki21"},
				{L"CourseAki_CurveFloor_3_2.bmf",L"MSA_Aki22"},
				{L"CourseAki_CurveFloor_3_3.bmf",L"MSA_Aki23"},
				{L"CourseAki_CurveFloor_3_4.bmf",L"MSA_Aki24"},
				{L"CourseAki_CurveFloor_3_5.bmf",L"MSA_Aki25"},
				{L"CourseAki_CurveFloor_3_6.bmf",L"MSA_Aki26"},
				{L"CourseAki_CurveFloor_3_7.bmf",L"MSA_Aki27"},
				{L"CourseAki_CurveFloor_3_8.bmf",L"MSA_Aki28"},
				{L"CourseAki_CurveFloor_3_9.bmf",L"MSA_Aki29"},
				{L"CourseAki_CurveFloor_3_10.bmf",L"MSA_Aki30"},
				{L"CourseAki_CurveFloor_3_11.bmf",L"MSA_Aki31"},
				{L"CourseAki_CurveFloor_3_12.bmf",L"MSA_Aki32"},
				{L"CourseAki_CurveFloor_3_13.bmf",L"MSA_Aki33"},
				{L"CourseAki_CurveFloor_3_14.bmf",L"MSA_Aki34"},
				{L"CourseAki_CurveFloor_3_15.bmf",L"MSA_Aki35"},
				{L"CourseAki_CurveFloor_3_16.bmf",L"MSA_Aki36"},
				{L"CourseAki_CurveFloor_3_17.bmf",L"MSA_Aki37"},
				{L"CourseAki_CurveFloor_3_18.bmf",L"MSA_Aki38"},
				{L"CourseAki_CurveFloor_3_19.bmf",L"MSA_Aki39"},
				{L"CourseAki_CurveFloor_3_20.bmf",L"MSA_Aki40"},
				{L"CourseAki_CurveFloor_3_21.bmf",L"MSA_Aki41"},
				{L"CourseAki_CurveFloor_3_22.bmf",L"MSA_Aki42"},
				{L"CourseAki_CurveFloor_3_23.bmf",L"MSA_Aki43"},
				{L"CourseAki_CurveFloor_3_24.bmf",L"MSA_Aki44"},
				{L"CourseAki_CurveFloor_3_25.bmf",L"MSA_Aki45"},
				{L"CourseAki_CurveFloor_3_26.bmf",L"MSA_Aki46"},
				{L"CourseAki_CurveFloor_3_27.bmf",L"MSA_Aki47"},
				{L"CourseAki_CurveFloor_3_28.bmf",L"MSA_Aki48"},
				{L"CourseAki_CurveFloor_3_29.bmf",L"MSA_Aki49"},
				{L"CourseAki_CurveFloor_3_30.bmf",L"MSA_Aki50"},
				{L"CourseAki_CurveFloor_3_31.bmf",L"MSA_Aki51"},
				{L"CourseAki_CurveFloor_3_32.bmf",L"MSA_Aki52"},
				{L"CourseAki_CurveFloor_3_33.bmf",L"MSA_Aki53"},
				{L"CourseAki_CurveFloor_3_34.bmf",L"MSA_Aki54"},
				{L"CourseAki_CurveFloor_3_35.bmf",L"MSA_Aki55"},
				{L"CourseAki_CurveFloor_3_36.bmf",L"MSA_Aki56"},
				{L"CourseAki_CurveFloor_3_37.bmf",L"MSA_Aki57"},
				{L"CourseAki_CurveFloor_3_38.bmf",L"MSA_Aki58"},
				{L"CourseAki_CurveFloor_3_39.bmf",L"MSA_Aki59"},
				{L"CourseAki_CurveFloor_3_40.bmf",L"MSA_Aki60"},
				{L"CourseAki_CurveFloor_4_1.bmf",L"MSA_Aki61"},
				{L"CourseAki_CurveFloor_4_2.bmf",L"MSA_Aki62"},
				{L"CourseAki_CurveFloor_4_3.bmf",L"MSA_Aki63"},
				{L"CourseAki_CurveFloor_4_4.bmf",L"MSA_Aki64"},
				{L"CourseAki_CurveFloor_4_5.bmf",L"MSA_Aki65"},

				{L"CourseAki_Floor_1.bmf",L"MSA_Aki66"},
				{L"CourseAki_Floor_2.bmf",L"MSA_Aki67"},
				{L"CourseAki_Floor_3.bmf",L"MSA_Aki68"},
				{L"CourseAki_Floor_4.bmf",L"MSA_Aki69"},
				{L"CourseAki_Floor_5.bmf",L"MSA_Aki70"},

				{L"CourseAki_Wall_L_1.bmf",L"MSA_Aki71"},
				{L"CourseAki_Wall_L_2_1.bmf",L"MSA_Aki72"},
				{L"CourseAki_Wall_L_2_2.bmf",L"MSA_Aki73"},
				{L"CourseAki_Wall_L_2_3.bmf",L"MSA_Aki74"},
				{L"CourseAki_Wall_L_2_4.bmf",L"MSA_Aki75"},
				{L"CourseAki_Wall_L_2_5.bmf",L"MSA_Aki76"},
				{L"CourseAki_Wall_L_2_6.bmf",L"MSA_Aki77"},
				{L"CourseAki_Wall_L_2_7.bmf",L"MSA_Aki78"},
				{L"CourseAki_Wall_L_2_8.bmf",L"MSA_Aki79"},
				{L"CourseAki_Wall_L_2_9.bmf",L"MSA_Aki80"},
				{L"CourseAki_Wall_L_2_10.bmf",L"MSA_Aki81"},
				{L"CourseAki_Wall_L_3.bmf",L"MSA_Aki82"},
				{L"CourseAki_Wall_L_4.bmf",L"MSA_Aki83"},
				{L"CourseAki_Wall_L_5.bmf",L"MSA_Aki84"},
				{L"CourseAki_Wall_L_6_1.bmf",L"MSA_Aki85"},
				{L"CourseAki_Wall_L_6_2.bmf",L"MSA_Aki86"},
				{L"CourseAki_Wall_L_6_3.bmf",L"MSA_Aki87"},
				{L"CourseAki_Wall_L_6_4.bmf",L"MSA_Aki88"},
				{L"CourseAki_Wall_L_6_5.bmf",L"MSA_Aki89"},
				{L"CourseAki_Wall_L_6_6.bmf",L"MSA_Aki90"},
				{L"CourseAki_Wall_L_6_7.bmf",L"MSA_Aki91"},
				{L"CourseAki_Wall_L_6_8.bmf",L"MSA_Aki92"},
				{L"CourseAki_Wall_L_6_9.bmf",L"MSA_Aki93"},
				{L"CourseAki_Wall_L_6_10.bmf",L"MSA_Aki94"},
				{L"CourseAki_Wall_L_6_11.bmf",L"MSA_Aki95"},
				{L"CourseAki_Wall_L_6_12.bmf",L"MSA_Aki96"},
				{L"CourseAki_Wall_L_6_13.bmf",L"MSA_Aki97"},
				{L"CourseAki_Wall_L_6_14.bmf",L"MSA_Aki98"},
				{L"CourseAki_Wall_L_6_15.bmf",L"MSA_Aki99"},
				{L"CourseAki_Wall_L_6_16.bmf",L"MSA_Aki100"},
				{L"CourseAki_Wall_L_6_17.bmf",L"MSA_Aki101"},
				{L"CourseAki_Wall_L_6_18.bmf",L"MSA_Aki102"},
				{L"CourseAki_Wall_L_6_19.bmf",L"MSA_Aki103"},
				{L"CourseAki_Wall_L_6_20.bmf",L"MSA_Aki104"},
				{L"CourseAki_Wall_L_6_21.bmf",L"MSA_Aki105"},
				{L"CourseAki_Wall_L_6_22.bmf",L"MSA_Aki106"},
				{L"CourseAki_Wall_L_6_23.bmf",L"MSA_Aki107"},
				{L"CourseAki_Wall_L_6_24.bmf",L"MSA_Aki108"},
				{L"CourseAki_Wall_L_6_25.bmf",L"MSA_Aki109"},
				{L"CourseAki_Wall_L_7.bmf",L"MSA_Aki110"},
				{L"CourseAki_Wall_L_8.bmf",L"MSA_Aki111"},
				{L"CourseAki_Wall_L_9.bmf",L"MSA_Aki112"},
				{L"CourseAki_Wall_L_10.bmf",L"MSA_Aki113"},

				{L"CourseAki_Wall_R_1.bmf",L"MSA_Aki114"},
				{L"CourseAki_Wall_R_2.bmf",L"MSA_Aki115"},
				{L"CourseAki_Wall_R_3.bmf",L"MSA_Aki116"},
				{L"CourseAki_Wall_R_4_1.bmf",L"MSA_Aki117"},
				{L"CourseAki_Wall_R_4_2.bmf",L"MSA_Aki118"},
				{L"CourseAki_Wall_R_4_3.bmf",L"MSA_Aki119"},
				{L"CourseAki_Wall_R_4_4.bmf",L"MSA_Aki120"},
				{L"CourseAki_Wall_R_4_5.bmf",L"MSA_Aki121"},
				{L"CourseAki_Wall_R_4_6.bmf",L"MSA_Aki122"},
				{L"CourseAki_Wall_R_4_7.bmf",L"MSA_Aki123"},
				{L"CourseAki_Wall_R_4_8.bmf",L"MSA_Aki124"},
				{L"CourseAki_Wall_R_4_9.bmf",L"MSA_Aki125"},
				{L"CourseAki_Wall_R_4_10.bmf",L"MSA_Aki126"},
				{L"CourseAki_Wall_R_5.bmf",L"MSA_Aki127"},
				{L"CourseAki_Wall_R_6.bmf",L"MSA_Aki128"},
				{L"CourseAki_Wall_R_7_1.bmf",L"MSA_Aki129"},
				{L"CourseAki_Wall_R_7_2.bmf",L"MSA_Aki130"},
				{L"CourseAki_Wall_R_7_3.bmf",L"MSA_Aki131"},
				{L"CourseAki_Wall_R_7_4.bmf",L"MSA_Aki132"},
				{L"CourseAki_Wall_R_7_5.bmf",L"MSA_Aki133"},
				{L"CourseAki_Wall_R_7_6.bmf",L"MSA_Aki134"},
				{L"CourseAki_Wall_R_7_7.bmf",L"MSA_Aki135"},
				{L"CourseAki_Wall_R_7_8.bmf",L"MSA_Aki136"},
				{L"CourseAki_Wall_R_7_9.bmf",L"MSA_Aki137"},
				{L"CourseAki_Wall_R_7_10.bmf",L"MSA_Aki138"},
				{L"CourseAki_Wall_R_7_11.bmf",L"MSA_Aki139"},
				{L"CourseAki_Wall_R_7_12.bmf",L"MSA_Aki140"},
				{L"CourseAki_Wall_R_7_13.bmf",L"MSA_Aki141"},
				{L"CourseAki_Wall_R_7_14.bmf",L"MSA_Aki142"},
				{L"CourseAki_Wall_R_7_15.bmf",L"MSA_Aki143"},
				{L"CourseAki_Wall_R_8.bmf",L"MSA_Aki144"},
				{L"CourseAki_Wall_R_9_1.bmf",L"MSA_Aki145"},
				{L"CourseAki_Wall_R_9_2.bmf",L"MSA_Aki146"},
				{L"CourseAki_Wall_R_9_3.bmf",L"MSA_Aki147"},
				{L"CourseAki_Wall_R_9_4.bmf",L"MSA_Aki148"},
				{L"CourseAki_Wall_R_9_5.bmf",L"MSA_Aki149"},
				{L"CourseAki_Wall_R_10.bmf",L"MSA_Aki150"},
			};
			for (auto model : models) {
				wstring srtmodel = dataDir + L"Models\\Aki_BMF\\";
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