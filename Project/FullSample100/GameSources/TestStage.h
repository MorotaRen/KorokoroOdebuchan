#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		bool m_IsCreateObject;
		// UIの作成
		void CreateUI();
		//リザルト画面
		void CreateResult();
	public:
		//構築と破棄
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}