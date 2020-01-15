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
		Vec3 m_pos;//�ʒu
		Vec3 m_scale;//�傫��
		Quat m_quat;//��]
		bool m_isHit = false;
		const float m_destroyTime = 2.0f;
		float m_destroyElapese;

	public:
		//�\���Ɣj��
		TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Quat quat);
		~TestBlock() {};

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		void SetIsHit(bool f) { m_isHit = f; }
	};


	
}
