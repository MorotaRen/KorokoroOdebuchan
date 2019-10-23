#pragma once
/// ----------------------------------------<summary>
/// ゲームで使うことが多いものをまとめたもの
/// (シングルトン)
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


	public:
		//コントローラーが接続されていたらマウスカーソルを削除する
		void ControllerCheck_Cursor();
	};
}