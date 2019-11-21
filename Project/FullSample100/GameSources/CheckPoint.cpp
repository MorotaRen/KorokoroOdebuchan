/// ----------------------------------------<summary>
/// チェックポイントソース
/// 管理者：諸田
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// コンストラクタ
	/// </summary>----------------------------------------
	CheckPoint::CheckPoint(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat) : GameObject(ptrstage) ,m_pos(pos),m_scale(scale),m_quat(quat){

	}

	/// ----------------------------------------<summary>
	/// デストラクタ
	/// </summary>----------------------------------------
	CheckPoint::~CheckPoint() {

	}

	/// ----------------------------------------<summary>
	/// 生成
	/// </summary>----------------------------------------
	void CheckPoint::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		TransComp->SetScale(m_scale);
		TransComp->SetQuaternion(m_quat);
		auto ColliderComp = AddComponent<CollisionObb>();
		ColliderComp->SetDrawActive(true);
		ColliderComp->AddExcludeCollisionTag(L"Collider");
	}

	/// ----------------------------------------<summary>
	/// 接触時
	/// </summary>----------------------------------------
	/// <param name="Other">接触オブジェクト</param>
	void CheckPoint::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		if (dynamic_pointer_cast<Player>(Other)) {
			//次のColliderエリアをActive
			GameSystems::GetInstans().ActiveNextCollision(m_nextpointNum);
		}
	}


}