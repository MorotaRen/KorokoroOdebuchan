#pragma once
#include "stdafx.h"

namespace basecross {

	
	class TestStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
	public:
		//\’z‚Æ”jŠü
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;
	};


}