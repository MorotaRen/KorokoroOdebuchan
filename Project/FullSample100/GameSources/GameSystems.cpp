/// ----------------------------------------<summary>
/// ゲーム全体で呼び出せる関数用ソース
/// 管理者：諸田
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// ----------------------------------------<summary>
	/// コントローラーが接続された場合カーソルを消す
	/// </summary>----------------------------------------
	void GameSystems::ControllerCheck_Cursor() {
		if (m_pad.bConnected) {
			::ShowCursor(false);
		}
	}

	/// ----------------------------------------<summary>
	/// コントローラーの状態の更新
	/// </summary>----------------------------------------
	void GameSystems::UpdatePadData() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		m_pad = device.GetControlerVec()[0];
	}

	/// ----------------------------------------<summary>
	/// コントローラーの状態の更新
	/// </summary>----------------------------------------
	CONTROLER_STATE GameSystems::GetPad() {
		return m_pad;
	}

	/// ----------------------------------------<summary>
	///	CSVに保存されたCSVデータを読み込みます
	/// </summary>----------------------------------------
	void GameSystems::LoadStageCSV() {
		unsigned int LoopNum = 0;
		wstring DataDir,FileDir;
		App::GetApp()->GetDataDirectory(DataDir);
		FileDir = DataDir + L"CSV\\Collider.csv";
		m_stageCSV.SetFileName(FileDir);
		m_stageCSV.ReadCsv();
		auto& LineVec = m_stageCSV.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < 1; j++) {
				switch (Tokens[0] == L"")
				{
				case false:
					//Tag
					if (LoopNum == 0) {
						m_objectdata.Tag = Tokens[0];
						LoopNum++;
						break;
					}
					//Pos
					else if (LoopNum == 1) {
						m_objectdata.Pos.x = stof(Tokens[0]);
						m_objectdata.Pos.y = stof(Tokens[1]);
						m_objectdata.Pos.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//Rot
					else if (LoopNum == 2) {
						m_objectdata.Rotate.x = stof(Tokens[0]);
						m_objectdata.Rotate.y = stof(Tokens[1]);
						m_objectdata.Rotate.z = stof(Tokens[2]);
						m_objectdata.Rotate.w = stof(Tokens[3]);
						LoopNum++;
						break;
					}
					//Scale
					else if (LoopNum == 3) {
						m_objectdata.Scale.x = stof(Tokens[0]);
						m_objectdata.Scale.y = stof(Tokens[1]);
						m_objectdata.Scale.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//*は子供
					else if (Tokens[0].find(L"*") != std::string::npos && LoopNum == 4) {
						m_objectdata.GroupNum++;
						m_objectdatas.push_back(m_objectdata);
						LoopNum = 0;
						break;
					}
					//-継続登録
					else if (Tokens[0].find(L"-") != std::string::npos && LoopNum == 4) {
						m_objectdatas.push_back(m_objectdata);
						LoopNum = 0;
						break;
					}
				default:
					break;
				}
			}
		}
	}

	///	----------------------------------------<summary>
	/// ステージを作成する
	/// </summary>----------------------------------------
	weak_ptr<Player> GameSystems::CreateStage() {
		auto Stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		Quat quat = Quat(0, 0, 0, 0);

		switch (m_GameStageNum)
		{
		case 1:
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor1", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor2", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor3", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor4", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor5", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor6", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor7", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor8", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor9", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor10", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringFloor11", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL1", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL2", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL3", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL5", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL7", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL8", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL9", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL10", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallL11", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR1", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_1", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_2", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_3", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_4", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_5", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_6", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_7", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_8", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_9", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_10", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_11", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_12", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_13", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_14", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_15", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_16", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_17", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_18", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_19", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_20", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_21", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_22", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_23", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_24", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR2_25", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, -0.9f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringGW1", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, -0.9f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringGW2", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, -0.9f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringGW3", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringGF", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR3", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR4", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR5", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR6", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR7", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR9", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringWallR11", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringGaTe", 4);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringCherry", 4);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MS_SpringSky", 4);
			break;
		case 2:
			quat.rotationY(3.14);

			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_BackFloor", 5);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_GoalGate", 5);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_Ground", 5);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_Ocean", 5);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_StartGate", 5);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Tree", 4);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Umbrellas", 4);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Wall1", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Wall2", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Wall3", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Wall4", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Floor", 0);

			break;
		default:
			break;
		}



		auto PlayerObj = Stage->AddGameObject<Player>(Vec3(0.0f,0.0f,0.0f),-470.0);
		Stage->SetSharedGameObject(L"Player", PlayerObj);
		PlayerObj->AddTag(L"Player");
		m_GenerationStage = true;
		return PlayerObj;
	}

	///	----------------------------------------<summary>
	/// モデルリソースの解放
	/// </summary>---------------------------------------
	void GameSystems::ReleaseModelData() {
		if (m_GenerationStage) {
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor1");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor2");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor3");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor4");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor5");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor6");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor7");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor8");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor9");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor10");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringFloor11");

			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL1");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL2");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL3");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL4");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL5");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL6");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL7");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL8");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL9");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL10");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallL11");

			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR1");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR3");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR4");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR5");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR6");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR7");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR8");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR9");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR10");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR11");

			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_1");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_2");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_3");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_4");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_5");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_6");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_7");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_8");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_9");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_10");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_11");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_12");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_13");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_14");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_15");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_16");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_17");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_18");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_19");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_20");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_21");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_22");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_23");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_24");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringWallR2_25");

			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringGW1");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringGW2");
			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringGW3");

			App::GetApp()->UnRegisterResource<MeshResource>(L"MS_SpringGF");


		}
	}

	///	----------------------------------------<summary>
	/// モデル情報があるCSVの読み込み
	/// </summary>----------------------------------------
	void GameSystems::LoadModelCSV() {
		wstring DataDir,FileDir;
		App::GetApp()->GetDataDirectory(DataDir) ;
		FileDir = DataDir + L"CSV\\model.csv";
		m_modelCSV.SetFileName(FileDir);
		m_modelCSV.ReadCsv();

		auto& LineVec = m_modelCSV.GetCsvVec();
		for (size_t i = 0; i < LineVec.size();i++) {
			vector<wstring> Tokens;
			m_modelData.clear();
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < Tokens.size();j++) {
				m_modelData.push_back(Tokens[j]);
				if (Tokens[j] == L"END") {
					CreateModelData(m_modelData);
				}
			}
		}
	}

	/// ----------------------------------------<summary>
	/// モデルのファイル名とキーネームの登録
	/// </summary>----------------------------------------
	void GameSystems::CreateModelData(vector<wstring> data) {
		//0はボーン
		if (data[0] == L"TRUE") {
			//1-2	ファイルとキーネーム
			wstring dataDir;
			App::GetApp()->GetDataDirectory(dataDir);
			wstring srtmodel = dataDir + L"Models\\";
			auto BoneModel = MeshResource::CreateBoneModelMesh(srtmodel, data[1]);
			App::GetApp()->RegisterResource(data[2], BoneModel);
		}else {
			wstring dataDir;
			App::GetApp()->GetDataDirectory(dataDir);
			wstring srtmodel = dataDir + L"Models\\";
			auto BoneModel = MeshResource::CreateStaticModelMesh(srtmodel, data[1]);
			App::GetApp()->RegisterResource(data[2], BoneModel);
		}
		CreateAnimationData(data);
	}

	/// ----------------------------------------<summary>
	/// アニメーションデータの作成
	/// </summary>----------------------------------------
	void GameSystems::CreateAnimationData(vector<wstring> data) {

		for (int i = 2;i < data.size(); i++) {
			m_animationData.push_back(vector<wstring>());
			if (data[i] != L"END") {
				m_animationData[m_animationDataRow].push_back(data[i]);
			}else {
				m_animationDataRow++;
				data.clear();
			}
		}
	}

	/// ----------------------------------------<summary>
	/// 作成したアニメーションデータの読み込み
	/// </summary>----------------------------------------
	/// <param name="keyname">取得したいキーネーム</param>
	int GameSystems::LoadAnimationData(wstring keyname) {
		for (int i = 0; i < m_animationData.size();i++) {
			if (m_animationData.at(i).at(0) == keyname) {
				return i;
			}
		}
		MessageBox(0,L"データを見つけることができませんでした。キーを間違っている可能性があります",0,0);
		return -99;
	}

	/// ----------------------------------------<summary>
	/// アニメーションデータのゲッター
	/// </summary>----------------------------------------
	vector<vector<wstring>> GameSystems::GetAnimationData() {
		return m_animationData;
	}

	void GameSystems::NET_CharToVec3(char* pos) {
		if (pos[0] == *"\0") {

		}else {
			Vec3 v_pos;
			int loopnum = 0;
			char *ptr, *ctx;
			ptr = strtok_s(pos, ",", &ctx);
			v_pos.x = (float)atof(ptr);

			while (ptr)
			{
				if (loopnum == 0) {
					ptr = strtok_s(nullptr, ",", &ctx);
					v_pos.y = (float)atof(ptr);
					loopnum++;
				}
				else {
					ptr = strtok_s(nullptr, ",", &ctx);
					v_pos.z = (float)atof(ptr);
					loopnum++;
				}

			}
			m_netvec = v_pos;
		}
	}
}