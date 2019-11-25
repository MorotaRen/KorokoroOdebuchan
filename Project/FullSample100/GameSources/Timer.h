/*!
@file Timer.h
@brief タイマーの行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Timer :public Sprite {
	private:
		float m_TotalTime;
		//文字列表示
		void DrawStrings();

	public:
		Timer(const shared_ptr<Stage>&StagePtr,
			const wstring& TextureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~Timer() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
	};
}

//end basecross

