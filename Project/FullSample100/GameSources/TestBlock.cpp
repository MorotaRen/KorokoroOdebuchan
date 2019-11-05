#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構造と破棄
	TestBlock::TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale)
	{
	}

	//初期化
	void TestBlock::OnCreate() {

	}

	//更新
	void TestBlock::OnUpdate() {

	}
}
