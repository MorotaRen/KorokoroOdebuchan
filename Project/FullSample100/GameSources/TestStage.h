#pragma once
#include "stdafx.h"

namespace basecross {

	
	class TestStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}