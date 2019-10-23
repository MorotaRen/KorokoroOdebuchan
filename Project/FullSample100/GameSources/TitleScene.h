/// ----------------------------------------<summary>
/// タイトル用のステージのヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{
	class TitleScene : public Stage {
	private:
		//ビューの作成
		void CreateViewLight();

	public:
		//構築
		TitleScene() :Stage() {}
		//破棄
		~TitleScene() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}