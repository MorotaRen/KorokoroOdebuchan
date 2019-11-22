#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// 当たり判定用オブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {
	class ColliderObjects : public GameObject
	{
	private:
		Vec3 m_pos;//位置
		Vec3 m_scale;//大きさ
		Quat m_quat;//回転


	public:
		ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat);
		~ColliderObjects();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
