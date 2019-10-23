/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//構造と破棄
	Player::Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale)
	{
	}

	//初期化
	void Player::OnCreate() {

	}

	//更新
	void Player::OnUpdate() {

	}
}
//end basecross

