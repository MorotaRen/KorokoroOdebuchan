#include "stdafx.h"
#include "Project.h"

namespace basecross {


	ColliderObjects::ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat) :GameObject(ptrStage), m_pos(pos), m_quat(quat), m_scale(scale)
	{
	}

	ColliderObjects::~ColliderObjects()
	{
	}


	void ColliderObjects::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		TransComp->SetScale(m_scale);
		TransComp->SetQuaternion(m_quat);
		auto ColliderComp = AddComponent<CollisionObb>();
		ColliderComp->SetDrawActive(true);
		ColliderComp->SetFixed(true);
		ColliderComp->AddExcludeCollisionTag(L"Collider");
	}
	void ColliderObjects::OnUpdate() {

	}

}