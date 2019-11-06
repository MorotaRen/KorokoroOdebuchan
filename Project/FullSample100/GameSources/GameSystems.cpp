/// ----------------------------------------<summary>
/// ゲーム全体で呼び出せる関数用ソース
/// 管理者：諸田
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// ----------------------------------------<summary>
	/// ゲーム全体で呼び出せる関数用ソース
	/// 管理者：諸田
	/// </summary>----------------------------------------
	void GameSystems::ControllerCheck_Cursor() {
		if (m_pad.bConnected) {
			::ShowCursor(false);
		}
	}

	void GameSystems::UpdatePadData() {
		//アプリケーションからゲームコントローラーの状態をとってくる
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		m_pad = device.GetControlerVec()[0];
	}

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

	void GameSystems::CreateModelData(vector<wstring> data) {
		//0ボーンか
		if (data[0] == L"True") {
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

	//アニメーション保存データを作成
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

	int GameSystems::LoadAnimationData(wstring keyname) {
		for (int i = 0; i < m_animationData.size();i++) {
			if (m_animationData.at(i).at(0) == keyname) {
				return i;
			}
		}
		MessageBox(0,L"データを見つけることができませんでした。キーを間違っている可能性があります",0,0);
		return -99;
	}

	vector<vector<wstring>> GameSystems::GetAnimationData() {
		return m_animationData;
	}



}