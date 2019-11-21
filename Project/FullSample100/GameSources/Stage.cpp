/// ----------------------------------------<summary>
/// ステージオブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// コンストラクタ
	/// </summary>----------------------------------------
	StageObject::StageObject(const shared_ptr<Stage>& ptrstage, Vec3 pos, Vec3 scale, Quat quat, bool iswall) : GameObject(ptrstage), m_pos(pos), m_scale(scale), m_quat(quat), m_iswall(iswall) {

	}

	/// ----------------------------------------<summary>
	/// デストラクタ
	/// </summary>----------------------------------------
	StageObject::~StageObject() {

	}

	/// ----------------------------------------<summary>
	/// 生成
	/// </summary>----------------------------------------
	void StageObject::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		//大きいので調整
		TransComp->SetScale(Vec3(0.01f,0.01f,0.01f));
		//Y軸180°回転
		m_quat.rotationY(3.14);
		TransComp->SetQuaternion(m_quat);

		auto DrawComp = AddComponent<BcPNTStaticDraw>();
		if (m_iswall) {
			DrawComp->SetMeshResource(L"Easycurve_Wall");
		}
		else {
			DrawComp->SetMeshResource(L"Easycurve_Ground");
			auto ColliderComp = AddComponent<CollisionObb>();
			ColliderComp->SetDrawActive(true);
			ColliderComp->AddExcludeCollisionTag(L"Collider");
		}
	}
}