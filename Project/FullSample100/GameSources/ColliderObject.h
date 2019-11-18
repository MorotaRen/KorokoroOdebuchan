#pragma once
#include "stdafx.h"
/// ----------------------------------------<summary>
/// �����蔻��p�I�u�W�F�N�g
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {
	class ColliderObjects : public GameObject
	{
	public:
		ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation);
		~ColliderObjects();
	private:
		virtual void OnCreate()override;
		Vec3 m_pos;//�ʒu
		Vec3 m_scale;//�傫��
		Vec3 m_rot;//��]

	};
	/// ----------------------------------------<summary>
	/// �R���X�g���N�^
	/// </summary>----------------------------------------
	ColliderObjects::ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation) :GameObject(ptrStage),m_pos(pos),m_rot(rotation),m_scale(scale)
	{
	}
	/// ----------------------------------------<summary>
	/// �f�X�g���N�^
	/// </summary>----------------------------------------
	ColliderObjects::~ColliderObjects()
	{
	}

}
