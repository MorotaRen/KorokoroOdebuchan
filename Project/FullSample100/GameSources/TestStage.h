#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		bool m_IsCreateObject;
		float m_deltTime = 0.0f;
		// UI‚Ìì¬
		void CreateUI();


	public:

		//\’z‚Æ”jŠü
		TestStage() :Stage(){}
		virtual ~TestStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}