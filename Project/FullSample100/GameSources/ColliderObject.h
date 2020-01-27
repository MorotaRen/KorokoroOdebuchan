#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// �����蔻��p�I�u�W�F�N�g
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {
	class ColliderObjects : public GameObject
	{
	private:
		Vec3 m_pos;//�ʒu
		Vec3 m_scale;//�傫��
		Quat m_quat;//��]


	public:
		ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat);
		~ColliderObjects();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
