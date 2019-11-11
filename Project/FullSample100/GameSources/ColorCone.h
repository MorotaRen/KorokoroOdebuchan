#pragma once
#include "stdafx.h"
#include "Objects.h"
/// ----------------------------------------<summary>
/// 設置物のカラーコーンヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------
namespace basecross{
	class ColorCone : Objects
	{
	public:
		ColorCone(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation)
			:Objects(ptrStage, pos, scale, rotation) {};
		~ColorCone() {};
	private:
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}