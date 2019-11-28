#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// ----------------------------------------<summary>
	/// コンストラクタ
	/// </summary>----------------------------------------
	ColliderObjects::ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat) :GameObject(ptrStage), m_pos(pos), m_quat(quat), m_scale(scale)
	{
	}

	/// ----------------------------------------<summary>
	/// デストラクタ
	/// </summary>----------------------------------------
	ColliderObjects::~ColliderObjects()
	{
	}

	/// ----------------------------------------<summary>
	/// 生成
	/// </summary>----------------------------------------
	void ColliderObjects::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		TransComp->SetScale(m_scale);
		TransComp->SetQuaternion(m_quat);

		auto ColliderComp = AddComponent<CollisionObb>();
		ColliderComp->SetAfterCollision(AfterCollision::Auto);
		
		PsBoxParam param(TransComp->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeFixed);
		auto  ptrRigid = AddComponent<RigidbodyBox>(param);
		//判定表示
		ColliderComp->SetDrawActive(true);
		//固定衝突オブジェクト化
		ColliderComp->SetFixed(true);
		//無視タグの追加
		ColliderComp->AddExcludeCollisionTag(L"Collider");
	}

	/// ----------------------------------------<summary>
	/// 更新
	/// </summary>----------------------------------------
	void ColliderObjects::OnUpdate() {

	}

}