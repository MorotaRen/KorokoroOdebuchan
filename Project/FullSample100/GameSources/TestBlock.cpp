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
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(m_rot);
		ptrTrans->SetPosition(m_pos);

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
}
