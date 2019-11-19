#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// 当たり判定用オブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {
	class ColliderObjects : public GameObject
	{
	public:
		ColliderObjects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation);
		~ColliderObjects();
	private:
		virtual void OnCreate()override;
		Vec3 m_pos;//位置
		Vec3 m_scale;//大きさ
		Vec3 m_rot;//回転

	};


}
