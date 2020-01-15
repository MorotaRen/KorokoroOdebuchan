#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// ----------------------------------------<summary>
	/// �R���X�g���N�^
	/// </summary>----------------------------------------
	ColliderObjects::ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat) :GameObject(ptrStage), m_pos(pos), m_quat(quat), m_scale(scale)
	{
	}

	/// ----------------------------------------<summary>
	/// �f�X�g���N�^
	/// </summary>----------------------------------------
	ColliderObjects::~ColliderObjects()
	{
	}

	/// ----------------------------------------<summary>
	/// ����
	/// </summary>----------------------------------------
	void ColliderObjects::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		TransComp->SetScale(m_scale);
		TransComp->SetQuaternion(m_quat);

		auto ColliderComp = AddComponent<CollisionObb>();
	//	ColliderComp->SetAfterCollision(AfterCollision::Auto);

		PsBoxParam param(TransComp->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto  ptrRigid = AddComponent<RigidbodyBox>(param);
		//����\��
		//ColliderComp->SetDrawActive(true);
		//�Œ�Փ˃I�u�W�F�N�g��
		//ColliderComp->SetFixed(true);
		//�����^�O�̒ǉ�
		ColliderComp->AddExcludeCollisionTag(L"WallCollider");
		ColliderComp->AddExcludeCollisionTag(L"Collider");
	}

	/// ----------------------------------------<summary>
	/// �X�V
	/// </summary>----------------------------------------
	void ColliderObjects::OnUpdate() {

	}

}