#pragma once
#include "stdafx.h"
#include"Project.h"

namespace basecross {
	class TestBlock : public GameObject
	{

	private:

	protected:
		Vec3 m_pos;//位置
		Vec3 m_scale;//大きさ
		Vec3 m_rot;//回転

	public:
		//構造と破棄
		TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale);
		~TestBlock() {};

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}
