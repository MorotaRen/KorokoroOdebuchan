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
		//���f���L�[
		wstring m_modelkey;
	public:
		StageObject(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat,wstring modelkey);
		~StageObject();
		virtual void OnCreate()override;

		//�X�e�[�W�̓����蔻��̍쐬
		void CreateStageCollider();
		//�`��p���b�V��
		shared_ptr<MeshResource> m_ConvexMesh = nullptr;
		//�����v�Z�p���b�V��
		shared_ptr<PsConvexMeshResource> m_PsConvexMesh = nullptr;

	};

}