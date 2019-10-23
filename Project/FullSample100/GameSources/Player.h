/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include"Project.h"

namespace basecross {
	class Player : public GameObject
	{

	private:

	protected:
		Vec3 m_pos;//位置
		Vec3 m_scale;//大きさ
		Vec3 m_rot;//回転
		float m_calory;//カロリー

	public:
		//構造と破棄
		Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale);
		~Player() {};

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}

//end basecross

