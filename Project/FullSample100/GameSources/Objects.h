#pragma once
#include "stdafx.h"
#include "Project.h"
/// ----------------------------------------<summary>
/// �I�u�W�F�N�g�n��̌�
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {
	class Objects : public GameObject
	{
	public:
		Objects(const shared_ptr<Stage>& ptrStage,Vec3 pos,Vec3 scale,Vec3 rotation);
		~Objects();
		//�ڐG���̃X�s�[�h�ቺ
		void HittingToSpeedDown();
	private:
		//�X�s�[�h�ቺ�̒l
		float m_spdDownValue;
	};
	/// ----------------------------------------<summary>
	/// �R���X�g���N�^
	/// </summary>----------------------------------------
	Objects::Objects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation) :GameObject(ptrStage)
	{
	}
	/// ----------------------------------------<summary>
	/// �f�X�g���N�^
	/// </summary>----------------------------------------
	Objects::~Objects()
	{
	}
	/// ----------------------------------------<summary>
	/// �ڐG���̃X�s�[�h�ቺ
	/// </summary>----------------------------------------
	void Objects::HittingToSpeedDown() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		player->ChangeRollingSpped(-0.5f);
	}
}