#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
///	ステージオブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {

	class StageObject : public GameObject {
	private:
		//位置
		Vec3 m_pos,
		//大きさ
			m_scale;
		//回転
		Quat m_quat;
	public:
		StageObject(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat);
		~StageObject();
		virtual void OnCreate()override;
	};

}