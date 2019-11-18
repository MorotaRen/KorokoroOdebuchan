#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void ColliderObjects::OnCreate() {
		auto colderComp = AddComponent<CollisionObb>();
		colderComp->SetDrawActive(true);
	}

}