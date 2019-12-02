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
		//フェードのタイプ
		FadeType m_Type;
		//遷移するステージへ
		wstring m_StageString;
	public:
		FadeSprite(const shared_ptr<Stage>&stagePtr,
			const FadeType& fadeType,
			const wstring&stageString);
		~FadeSprite() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

	};
}

//end basecross

