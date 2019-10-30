#pragma once
#include "stdafx.h"
#include"Project.h"

namespace basecross {
	class TestBlock : public GameObject
	{

	private:

	protected:
		Vec3 m_pos;//�ʒu
		Vec3 m_scale;//�傫��
		Vec3 m_rot;//��]

	public:
		//�\���Ɣj��
		TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale);
		~TestBlock() {};

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}
