#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
///	�X�e�[�W�I�u�W�F�N�g
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {

	class StageObject : public GameObject {
	private:
		//�ʒu
		Vec3 m_pos,
		//�傫��
			m_scale;
		//��]
		Quat m_quat;

		//�`��p���b�V��
		static shared_ptr<MeshResource> m_ConvexMesh;
		//�����v�Z�p���b�V��
		static shared_ptr<PsConvexMeshResource> m_PsConvexMesh;
	public:
		StageObject(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat);
		~StageObject();
		virtual void OnCreate()override;

		//�X�e�[�W�̓����蔻��̍쐬
		void CreateStageCollider();

	};

}