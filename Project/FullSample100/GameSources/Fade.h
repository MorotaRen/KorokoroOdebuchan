/*!
@file Fade.h
@brief フェードクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum FadeType
	{
		FadeIn,
		FadeOut
	};
	//--------------------------------------------------------------------------------------
	// フェード
	//--------------------------------------------------------------------------------------
	class FadeSprite :public Sprite {
	private:
		float m_FadeSpeed = 0.01f;
		//フェードのタイプ
		FadeType m_Type;
		//遷移するステージへ
		wstring m_StageString=L"";
	public:
		FadeSprite(const shared_ptr<Stage>&stagePtr,
			const FadeType& fadeType,
			const wstring&stageString=L"");
		~FadeSprite() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}

//end basecross

