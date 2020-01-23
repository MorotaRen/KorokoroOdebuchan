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
		//全体配列取得
		auto& LineVec = m_stageCSV.GetCsvVec();
		//行に分ける
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			//実際にスキャン開始
			for (size_t j = 0; j < 1; j++) {
				switch (Tokens[0] == L"")
				{
				case false:
					//0はタグ
					if (LoopNum == 0) {
						m_objectdata.Tag = Tokens[0];
						LoopNum++;
						break;
					}
					//1はPos
					else if (LoopNum == 1) {
						m_objectdata.Pos.x = stof(Tokens[0]);
						m_objectdata.Pos.y = stof(Tokens[1]);
						m_objectdata.Pos.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//2はRot
					else if (LoopNum == 2) {
						m_objectdata.Rotate.x = stof(Tokens[0]);
						m_objectdata.Rotate.y = stof(Tokens[1]);
						m_objectdata.Rotate.z = stof(Tokens[2]);
						m_objectdata.Rotate.w = stof(Tokens[3]);
						LoopNum++;
						break;
					}
					//3はSca
					else if (LoopNum == 3) {
						m_objectdata.Scale.x = stof(Tokens[0]);
						m_objectdata.Scale.y = stof(Tokens[1]);
						m_objectdata.Scale.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//*があったら以下子供
					else if (Tokens[0].find(L"*") != std::string::npos && LoopNum == 4) {
						//グループナンバー加算して登録
						m_objectdata.GroupNum++;
						m_objectdatas.push_back(m_objectdata);
						LoopNum = 0;
						break;
					}
					//-の時はそのまま継続登録
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
		m_colobjs.push_back(vector<shared_ptr<ColliderObjects>>());
		for each (ObjectData objdata in m_objectdatas)
		{
			//プレイヤー開始地点
			if (objdata.Tag == L"PlayerStartPos") {
				//Stage->AddGameObject<TestBlock>(objdata.Pos,objdata.Scale,objdata.Rotate.toRotVec());
				auto PlayerObj = Stage->AddGameObject<Player>(objdata.Pos,Vec3(0.1f,0.1f,0.1f));
				Stage->SetSharedGameObject(L"Player", PlayerObj);
				PlayerObj->AddTag(L"Player");
				return PlayerObj;
			//オブジェクトの判定
			}else if (objdata.Tag == L"ObjectCollider") {
				//auto ColliderObj = Stage->AddGameObject<ColliderObjects>(objdata.Pos,objdata.Scale,objdata.Rotate);
				//無視用のタグ設定
				//ColliderObj->AddTag(L"WallCollider");
				//ColliderObj->AddTag(L"Wall");
				//初期状態では更新を切っておく(デバック専用)
				////ColliderObj->SetUpdateActive(false);
				//エリア分け
				//m_colobjs[objdata.GroupNum-1].push_back(ColliderObj);
			//ステージ壁
			}else if (objdata.Tag == L"Stage") {
				Stage->AddGameObject<StageObject>(objdata.Pos, objdata.Scale, objdata.Rotate);
			//ステージオブジェクト
			}else if (objdata.Tag == L"StageObject") {
				auto obj = Stage->AddGameObject<TestBlock>(objdata.Pos,objdata.Scale,objdata.Rotate);
				obj->AddTag(L"CourseObject");
			//床
			}else if(objdata.Tag == L"GroundCollider"){
				auto ColliderObj = Stage->AddGameObject<ColliderObjects>(objdata.Pos,objdata.Scale,objdata.Rotate);
				ColliderObj->AddTag(L"Collider");
			}else if(objdata.Tag == L"GoalCollider"){
				//auto ColliderObj = Stage->AddGameObject<ColliderObjects>(objdata.Pos,objdata.Scale,objdata.Rotate);
				//ColliderObj->AddTag(L"GoalCollider");
			//なんでもなかったら
			}else {
				m_colobjs.push_back(vector<shared_ptr<ColliderObjects>>());
			}
		}
	}

	///	----------------------------------------<summary>
	/// 送られてきた番号のColliderObjct達を起動する
	/// </summary>---------------------------------------
	/// <param name="nextnum">起動する番号</param>
	void GameSystems::ActiveNextCollision(unsigned int nextnum) {
		for each (auto obj in m_colobjs[nextnum])
		{
			obj->SetUpdateActive(true);
		}
		//前の数字が存在する(-1とかじゃないなら)
		if ((nextnum - 1) < 0) {
			for each (auto backobj in m_colobjs[nextnum-1])
			{
				backobj->SetUpdateActive(false);
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

		//全体配列取得
		auto& LineVec = m_modelCSV.GetCsvVec();
		//行に分ける
		for (size_t i = 0; i < LineVec.size();i++) {
			vector<wstring> Tokens;
			m_modelData.clear();
			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			//実際にスキャン開始
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
		//0ボーンか
		if (data[0] == L"TRUE") {
			//1-2	ファイル名とキーネーム
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
	/// <returns>キーネームの</returns>
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