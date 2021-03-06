#pragma once
/// ----------------------------------------<summary>
/// ゲーム全体で呼び出せる関数用ヘッダー
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class ColliderObjects;

	struct ObjectData
	{
		unsigned int GroupNum;
		wstring Tag;
		Vec3	Pos;
		Quat	Rotate;
		Vec3	Scale;
	};
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
		CsvFile m_modelCSV,m_stageCSV;
		//オブジェクトデータ
		ObjectData m_objectdata;
		//オブジェクトデータ配列
		vector<ObjectData> m_objectdatas;
		//読み込んだモデルのデータ
		vector<wstring> m_modelData;
		//アニメーション保存用
		vector<vector<wstring>> m_animationData;
		//アニメーションデータの行
		int m_animationDataRow = 0;
		//ステージのエリアごとの判定達
		vector<vector<shared_ptr<ColliderObjects>>> m_colobjs;

		Vec3 m_netvec;


		//
		bool m_COLON;
		//ステージナンバー
		int m_GameStageNum;
		//壁に当たった回数を入れておく
		int m_SmashPoint = 0;
		//プレイヤーのスピード
		float m_playerSpeed = 0;
		//スマッシュゲージを使ったかどうか
		bool m_UseedGage = false;
		//ステージ生成はしてあるか
		bool m_GenerationStage;
	public:
		void Setcol(bool t) {
			m_COLON = t;
		};
		bool Getcol() {
			return m_COLON;
		}
		//関数呼ぶときにここから
		static GameSystems& GetInstans() {
			static GameSystems inst;
			return inst;
		}
		//コントローラーが接続されていたらマウスカーソルを削除する
		void ControllerCheck_Cursor();
		//コントローラー情報更新
		void UpdatePadData();
		//コントローラーの状態を返す
		CONTROLER_STATE GetPad();
		//ステージのCSV読み込み
		void LoadStageCSV();
		//ステージ作成
		weak_ptr<Player> CreateStage();
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
		//送られてきたナンバーの判定をActiveにして前のやつをFalseに
		void ReleaseModelData();

		//ネットできた座標のVec3化
		void NET_CharToVec3(char* pos);
		Vec3 NET_GetVec3() {
			return m_netvec;
		}

		//ゲッター、セッター
		int GetSmashPoint() {return m_SmashPoint;}

		void SetSmashPoint(int i) { if (m_SmashPoint <= 5) { m_SmashPoint += i; } }

		float GetPlayerSpeed() { return m_playerSpeed; }

		void SetPlayerSeed(float s) { m_playerSpeed = s; }

		bool GetUseedGage() { return m_UseedGage; }

		void SetUseedGage(bool Active) { m_UseedGage = Active; }

		int GetGameStageNum() { return m_GameStageNum; };
		void SetGameStageNum(int num) { m_GameStageNum = num; };

		//値をリセット
		void ResetSmashPoint() { m_SmashPoint = 0; }
	};
}