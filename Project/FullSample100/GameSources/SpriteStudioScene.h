/// ----------------------------------------<summary>
/// タイトル用のステージのヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	タイトルシーンのクラス
	//--------------------------------------------------------------------------------------
	class SpriteStudio : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築
		SpriteStudio() :Stage(){}
		//破棄
		virtual ~SpriteStudio() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}