/*!
@file CountDown.h
@brief カウントダウンの行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	カウントダウン用の数字
	//--------------------------------------------------------------------------------------
	class CountDown :public Sprite {
	private :
		float m_TotalTime;
		float m_RemoveTime;
	public:
		CountDown(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startPos);

		virtual ~CountDown() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}

//end basecross

