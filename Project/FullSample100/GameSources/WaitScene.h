#pragma once
#include <stdafx.h>

namespace basecross {
	class WaitScene : public Stage {
		//ビューの作成
		void CreateViewLight();
		//リソースロード用のスレッド（スタティック関数）
		static void LoadResourceFunc();
		//リソースを読み込んだことを知らせるフラグ（スタティック変数）
		static bool m_Loaded;
		//ミューテックス
		static std::mutex mtx;
	public:
		//構築と破棄
		WaitScene() :Stage() {}
		virtual ~WaitScene() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
	};
}