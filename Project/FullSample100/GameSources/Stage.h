#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
///	�X�e�[�W�I�u�W�F�N�g
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {

	class StageObject : public GameObject {
	private:
		Vec3 m_pos, m_scale;
		Quat m_quat;
	public:
		StageObject(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat);
		virtual void OnCreate()override;
	};

}