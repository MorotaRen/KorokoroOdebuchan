#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	class TestBlock : public GameObject
	{

	private:

	protected:
		shared_ptr<EfkEffect> m_efkEffect;
		shared_ptr<EfkPlay> m_efkPlay;
		Vec3 m_pos;//位置
		Vec3 m_scale;//大きさ
		Quat m_quat;//回転
		bool m_isHit = false;
		const float m_destroyTime = 2.0f;
		float m_destroyElapese;

	public:
		//構造と破棄
		TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Quat quat);
		~TestBlock() {};

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void SetIsHit(bool f) { m_isHit = f; }
	};


	
}
