#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構造と破棄
	TestBlock::TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Vec3 rot) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_rot(rot)
	{
	}

	//初期化
	void TestBlock::OnCreate() {
		AddTag(L"TestFloor");
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		ptrTrans->SetPosition(m_pos);

		//影をつける
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"TestFloor");
		//ptrDraw->SetOwnShadowActive(true);
		////物理計算ボックス
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//OBB衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//壁を生成
		GetStage()->AddGameObject<TestWall>(Vec3(m_pos.x + m_scale.x / 2, m_pos.y, m_pos.z), Vec3(2, 10, m_scale.z), m_rot);
		GetStage()->AddGameObject<TestWall>(Vec3(m_pos.x - m_scale.x / 2, m_pos.y, m_pos.z), Vec3(2, 10, m_scale.z), m_rot);

		auto drawcomp = AddComponent<PNTStaticModelDraw>();
		drawcomp->SetMeshResource(L"SampleCourse");
		drawcomp->SetOwnShadowActive(true);
		auto ptrColl = AddComponent < CollisionObb > ();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);


		//物理計算ボックス
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);

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
