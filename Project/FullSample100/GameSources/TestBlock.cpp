#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\���Ɣj��
	TestBlock::TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale, const Quat quat) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_quat(quat)
	{
	}

	//������
	void TestBlock::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetQuaternion(m_quat);
		ptrTrans->SetPosition(m_pos);

		auto ptrDraw = AddComponent<BcPNTStaticModelDraw>();
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetMultiMeshResource(L"M_Omikosi");
		ptrDraw->SetOwnShadowActive(true);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.05f, 0.05f, 0.05f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.2f, 0.0f)
		);

		ptrDraw->SetMeshToTransformMatrix(spanMat);

		//�����v�Z�{�b�N�X
		PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		auto PsPtr = AddComponent<RigidbodyBox>(param);
		PsPtr->SetAutoGravity(true);

		//OBB�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetDrawActive(true);


		////�����v�Z�{�b�N�X
		//PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
		//auto PsPtr = AddComponent<RigidbodyBox>(param);
		//PsPtr->SetDrawActive(true);

	}

	//�X�V
	void TestBlock::OnUpdate() {
		if (m_isHit) {
			auto ptrTrans = GetComponent<Transform>();
			PsBoxParam param(ptrTrans->GetWorldMatrix(), 0.0f, true, PsMotionType::MotionTypeFixed);
			RemoveComponent<RigidbodyBox>();
		}
	}
}
