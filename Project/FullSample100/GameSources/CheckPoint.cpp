/// ----------------------------------------<summary>
/// チェックポイントソース
/// 管理者：諸田
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	CheckPoint::CheckPoint(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat) : GameObject(ptrstage) ,m_pos(pos),m_scale(scale),m_quat(quat){

	}
	CheckPoint::~CheckPoint() {

	}
	void CheckPoint::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		TransComp->SetScale(m_scale);
		TransComp->SetQuaternion(m_quat);
		auto CollderComp = AddComponent<CollisionObb>();
		CollderComp->SetDrawActive(true);
		CollderComp->AddExcludeCollisionTag(L"Collider");
	}
	void CheckPoint::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (dynamic_pointer_cast<Player>(Other)) {
			GameSystems::GetInstans().ActiveNextCollision(m_nextpointNum);
		}
	}


}