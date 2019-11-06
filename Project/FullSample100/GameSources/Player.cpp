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
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		drawcomp->SetMeshResource(L"TestModel");
		int animrow = GameSystems::GetInstans().LoadAnimationData(L"TestModel");
		auto AnimData = GameSystems::GetInstans().GetAnimationData();
		drawcomp->AddAnimation(AnimData[animrow].at(1),std::stoi(AnimData[animrow].at(2)), std::stoi(AnimData[animrow].at(3)),true,10.0f);

	}

	//更新
	void Player::OnUpdate() {

	}
}
//end basecross

