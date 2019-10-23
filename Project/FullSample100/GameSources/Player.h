/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include"Project.h"

namespace basecross {
	class Player : public GameObject
	{

	private:

	protected:
		Vec3 m_pos;//�ʒu
		Vec3 m_scale;//�傫��
		Vec3 m_rot;//��]
		float m_calory;//�J�����[

	public:
		//�\���Ɣj��
		Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale);
		~Player() {};

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}

//end basecross

