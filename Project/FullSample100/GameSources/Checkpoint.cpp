#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Checkpoint::Checkpoint(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat) : GameObject(ptrStage),m_pos(pos),m_scale(scale),m_quat(quat){

	}
	Checkpoint::~Checkpoint() {
	};
	void Checkpoint::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetPosition(m_pos);
		TransComp->SetScale(m_scale);
		TransComp->SetQuaternion(m_quat);

		auto ColliderComp = AddComponent<CollisionObb>();
		ColliderComp->SetAfterCollision(AfterCollision::None);

		//����\��
		ColliderComp->SetDrawActive(true);
		//�Œ�Փ˃I�u�W�F�N�g��
		//ColliderComp->SetFixed(true);
		//�����^�O�̒ǉ�
		ColliderComp->AddExcludeCollisionTag(L"Collider");

	}
	void Checkpoint::OnUpdate() {

	}
	void Checkpoint::OnCollisionEnter(shared_ptr<GameObject>& Other) {

	}
}