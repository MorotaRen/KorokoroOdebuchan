#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// �`�F�b�N�|�C���g�p�I�u�W�F�N�g
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {
	class Checkpoint : public GameObject
	{
	private:
		Vec3 m_pos;//�ʒu
		Vec3 m_scale;//�傫��
		Quat m_quat;//��]
		unsigned int m_mynum;//�����̃G���A�i���o�[


	public:
		Checkpoint(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat);
		~Checkpoint();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
		void SetAreaNum(unsigned int setnum) { m_mynum = setnum; };

	};


}