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

			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_CourseSummer_Ambient", 6);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSS_Surrounding", 6);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer1", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer2", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer3", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer4", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer5", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer6", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer7", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer8", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer9", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer10", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer11", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer12", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer13", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer14", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer15", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer16", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer17", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer18", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer19", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer20", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer21", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer22", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer23", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer24", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer25", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer26", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer27", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer28", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer29", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer30", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer31", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer32", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer33", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer34", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer35", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer36", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer37", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer38", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer39", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer40", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer41", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer42", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer43", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer44", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer45", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer46", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.6f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer47", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer48", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer49", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer50", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer51", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer52", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer53", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer54", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer55", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer56", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer57", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer58", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer59", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer60", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer61", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer62", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer63", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer64", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer65", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer66", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer67", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer68", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer69", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer70", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer71", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer72", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer73", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer74", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer75", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer76", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer77", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer78", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer79", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer80", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer81", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer82", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer83", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer84", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer85", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer86", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer87", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer88", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer89", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer90", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer91", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer92", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer93", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer94", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer95", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer96", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer97", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer98", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer99", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer100", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer101", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer102", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer103", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer104", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer105", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer106", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer107", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer108", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer109", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer110", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer111", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer112", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer113", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer114", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer115", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer116", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer117", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer118", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer119", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer120", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer121", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer122", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer123", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer124", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer125", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer126", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer127", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer128", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer129", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer130", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer131", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer132", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer133", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer134", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer135", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer136", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer137", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer138", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer139", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer140", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSS_Summer141", 2);

			break;
		case 3:
			quat.rotationY(3.14);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSA_Skys", 6);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), quat, L"MSA_Trees", 6);

			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki1", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki2", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki3", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki4", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki5", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki6", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki7", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki8", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki9", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki10", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki11", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki12", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki13", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki14", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki15", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki16", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki17", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki18", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki19", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki20", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki21", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki22", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki23", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki24", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki25", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki26", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki27", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki28", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki29", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki30", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki31", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki32", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki33", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki34", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki35", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki36", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki37", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki38", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki39", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki40", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki41", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki42", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki43", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki44", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki45", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki46", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki47", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki48", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki49", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki50", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki51", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki52", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki53", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki54", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki55", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki56", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki57", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki58", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki59", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki60", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki61", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki62", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki63", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki64", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki65", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki66", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki67", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki68", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki69", 0);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki70", 0);

			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki71", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki72", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki73", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki74", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki75", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki76", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki77", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki78", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki79", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki80", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki81", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki82", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki83", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki84", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki85", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki86", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki87", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki88", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki89", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki90", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki91", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki92", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki93", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki94", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki95", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki96", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki97", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki98", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki99", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki100", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki101", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki102", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki103", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki104", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki105", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki106", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki107", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki108", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki109", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki110", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki111", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki112", 1);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki113", 1);

			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki114", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki115", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki116", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki117", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki118", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki119", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki120", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki121", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki122", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki123", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki124", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki125", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki126", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki127", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki128", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki129", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki130", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki131", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki132", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki133", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki134", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki135", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki136", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki137", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki138", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki139", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki140", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki141", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki142", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki143", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki144", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki145", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki146", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki147", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki148", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki149", 2);
			Stage->AddGameObject<StageObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f, 0.0f), L"MSA_Aki150", 2);


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
			if (m_GameStageNum  == 1) {
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
			if (m_GameStageNum == 2) {
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer1");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer2");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer3");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer4");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer5");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer6");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer7");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer8");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer9");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer10");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer11");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer12");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer13");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer14");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer15");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer16");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer17");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer18");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer19");
				App::GetApp()->UnRegisterResource<MeshResource>(L"MSS_Summer20");

			}
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