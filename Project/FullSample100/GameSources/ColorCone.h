#pragma once
#include "stdafx.h"
#include "Objects.h"
/// ----------------------------------------<summary>
/// �ݒu���̃J���[�R�[���w�b�_�[
/// �Ǘ��ҁF���c
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