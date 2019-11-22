#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// アイテム系は全部ここ
/// 管理者：諸田
/// </summary>----------------------------------------
namespace basecross {

	class ItemsEffect
	{
	private:

	public:
		ItemsEffect();
		~ItemsEffect();
		//HP回復
		void Healing_HP(unsigned int value);
		//スマッシュローリングゲージ回復
		void Healing_Gauge(unsigned int value);
	};
}