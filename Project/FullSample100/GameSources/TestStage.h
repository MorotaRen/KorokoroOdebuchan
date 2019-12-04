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
		bool m_updateFlag = false;
		float m_deltTime = 0.0f;	//時間を計測
		float m_stopTime = 0.0f;
		bool m_UpdateAct = true;
		bool m_StartPos = false;	//スタート地点についたか
		// UIの作成
		void CreateUI();


	public:

		//構築と破棄
		TestStage() :Stage(){}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;
	};


}