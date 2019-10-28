#pragma once
/// ----------------------------------------<summary>
/// ゲームで使うことが多いものをまとめたもの
/// (シングルトン)
/// 管理者：諸田
/// </summary>----------------------------------------
/// ----------------------------------------<summary>
/// ゲーム全体で呼び出せる関数用ヘッダー
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"
#include "GameSystems.h"

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
		CONTROLER_STATE m_Pad;
	public:
		//ここから下に置かないと呼び出せないぞ

		//コントローラーが接続されていたらマウスカーソルを削除する
		void ControllerCheck_Cursor();
		//コントローラー情報更新
		void UpdatePadData();
	};
}