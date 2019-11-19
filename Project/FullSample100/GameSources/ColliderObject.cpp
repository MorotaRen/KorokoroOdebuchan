#include "stdafx.h"
#include "Project.h"

namespace basecross {


	ColliderObjects::ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation) :GameObject(ptrStage), m_pos(pos), m_rot(rotation), m_scale(scale)
	{
	}

	ColliderObjects::~ColliderObjects()
	{
	}


	void ColliderObjects::OnCreate() {
		auto colderComp = AddComponent<CollisionObb>();
		colderComp->SetDrawActive(true);
	}

}