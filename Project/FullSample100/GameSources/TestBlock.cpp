#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\���Ɣj��
	TestBlock::TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Vec3 rot) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_rot(rot)
	{
	}

	//������
	void TestBlock::OnCreate() {
		AddTag(L"TestFloor");
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		ptrTrans->SetPosition(m_pos);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		//auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"TestFloor");
		//ptrDraw->SetOwnShadowActive(true);
		////�����v�Z�{�b�N�X
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//OBB�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//�ǂ𐶐�
		GetStage()->AddGameObject<TestWall>(Vec3(m_pos.x + m_scale.x / 2, m_pos.y, m_pos.z), Vec3(2, 10, m_scale.z), m_rot);
		GetStage()->AddGameObject<TestWall>(Vec3(m_pos.x - m_scale.x / 2, m_pos.y, m_pos.z), Vec3(2, 10, m_scale.z), m_rot);

		auto drawcomp = AddComponent<PNTStaticModelDraw>();
		drawcomp->SetMeshResource(L"SampleCourse");
		drawcomp->SetOwnShadowActive(true);
		auto ptrColl = AddComponent < CollisionObb > ();
		ptrColl->SetAfterCollision(AfterCollision::None);
		ptrColl->SetDrawActive(true);


		//�����v�Z�{�b�N�X
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetDrawActive(true);

	}

	//�X�V
	void TestBlock::OnUpdate() {

	}


	//�\���Ɣj��
	TestWall::TestWall(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Vec3 rot) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_rot(rot)
	{
	}

	//������
	void TestWall::OnCreate() {
		AddTag(L"Wall");
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		ptrTrans->SetPosition(m_pos);

		//�e������
		auto ptrShadow = AddComponent<Shadowmap>();
		ptrShadow->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TestWall");
		ptrDraw->SetOwnShadowActive(true);
		//�����v�Z�{�b�N�X
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		//OBB�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
	}

	//�X�V
	void TestWall::OnUpdate() {

	}
}
