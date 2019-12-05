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
		AddTag(L"TestFloor");
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

	}


	//構造と破棄
	TestWall::TestWall(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Vec3 rot) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_rot(rot)
	{
	}

	//初期化
	void TestWall::OnCreate() {
		AddTag(L"Wall");
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		ptrTrans->SetPosition(m_pos);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TestWall");
		ptrDraw->SetOwnShadowActive(true);
		//物理計算ボックス
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		//OBB衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
	}

	//更新
	void TestWall::OnUpdate() {

	}
}
