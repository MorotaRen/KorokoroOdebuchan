/*!
@file Timer.cpp
@brief タイマー実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	Timer::Timer(const shared_ptr<Stage>& stagePtr,
		const wstring& textureKey,
		const Vec2& startScale,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, startScale, startPos),
		m_TotalTime(0.0f)
	{}
	void Timer::OnCreate() {
		Sprite::OnCreate();

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(1000.0f, 16.0f, 1200.0f, 480.0f));
	}	
	void Timer::OnUpdate() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
	}
	void Timer::OnUpdate2() {
		DrawStrings();
	}

	void Timer::DrawStrings() {
		wstringstream ss;
		ss << L"Timer : " << m_TotalTime << std::endl;

		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(ss.str());
	}
}

//end basecross

