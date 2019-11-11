#pragma once
/// ----------------------------------------<summary>
/// ゲーム全体で呼び出せる関数用ヘッダー
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class  GameSystems final {
	private:
		//コンストラクタ
		GameSystems() {};
		//コンストラクタ
		GameSystems(const GameSystems&);
		//デストラクタ
		~GameSystems() {};
		//コントローラー情報
		CONTROLER_STATE m_pad;
		//CSVファイル
		CsvFile m_modelCSV;
		//読み込んだモデルのデータ
		vector<wstring> m_modelData;
		//アニメーション保存用
		vector<vector<wstring>> m_animationData;
		//アニメーションデータの行
		int m_animationDataRow = 0;
		//プレイヤー格納ポインタ
		shared_ptr<Player>* m_player;
	public:

		//関数呼ぶときにここから
		static GameSystems& GetInstans() {
			static GameSystems inst;
			return inst;
		}
		//コントローラーが接続されていたらマウスカーソルを削除する
		void ControllerCheck_Cursor();
		//コントローラー情報更新
		void UpdatePadData();
		//モデルのCSVを読み込み
		void LoadModelCSV();
		//CSVから作成したデータからモデルの追加
		void CreateModelData(vector<wstring> data);
		//アニメーションデータ作成
		void CreateAnimationData(vector<wstring> data);
		//アニメーションデータの読み込み
		int LoadAnimationData(wstring keyname);
		//アニメーションデータのゲッター
		vector<vector<wstring>> GetAnimationData();

	};
}