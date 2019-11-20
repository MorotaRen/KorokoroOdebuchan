#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
///	ステージオブジェクト
/// 管理者：諸田
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