#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構造と破棄
	TestBlock::TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Quat quat) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_quat(quat)
	{
	}

	//初期化
	void TestBlock::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetQuaternion(m_quat);
		ptrTrans->SetPosition(m_pos);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMultiMeshResource(L"M_Omikosi");
		ptrDraw->SetOwnShadowActive(true);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			Vec3(0.05f, 0.05f, 0.05f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.2f, 0.0f)
		);

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//物理計算ボックス
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetAutoGravity(true);

		//OBB衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetDrawActive(true);


		////物理計算ボックス
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(true);

	}

	//更新
	void TestBlock::OnUpdate() {
		if (m_isHit) {
			auto ptrTrans = GetComponent<Transform>();
			PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
			auto ptrThis = GetThis<TestBlock>();
			GetTypeStage<TestStage>()->RemoveGameObject<TestBlock>(ptrThis);

			//GetComponent<CollisionObb>()->SetUpdateActive(false);
			//GetComponent<RigidbodyBox>()->SetUpdateActive(false);
			//RemoveComponent<CollisionObb>();
			//RemoveComponent<RigidbodyBox>();
		}
	}

	void TestBlock::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			m_isHit = true;
		}
	}
}
