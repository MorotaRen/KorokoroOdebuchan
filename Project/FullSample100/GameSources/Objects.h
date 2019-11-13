#pragma once
#include "stdafx.h"
#include "Project.h"
/// ----------------------------------------<summary>
/// オブジェクト系列の元
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {
	class Objects : public GameObject
	{
	public:
		Objects(const shared_ptr<Stage>& ptrStage,Vec3 pos,Vec3 scale,Vec3 rotation);
		~Objects();
		//接触時のスピード低下
		void HittingToSpeedDown();
	private:
		//スピード低下の値
		float m_spdDownValue;
	};
	/// ----------------------------------------<summary>
	/// コンストラクタ
	/// </summary>----------------------------------------
	Objects::Objects(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Vec3 rotation) :GameObject(ptrStage)
	{
	}
	/// ----------------------------------------<summary>
	/// デストラクタ
	/// </summary>----------------------------------------
	Objects::~Objects()
	{
	}
	/// ----------------------------------------<summary>
	/// 接触時のスピード低下
	/// </summary>----------------------------------------
	void Objects::HittingToSpeedDown() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		player->ChangeRollingSpped(-0.5f);
	}
}