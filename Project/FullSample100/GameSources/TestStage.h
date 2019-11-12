#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;

	class TestStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
	public:
		//\’z‚Æ”jŠü
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
	};


}