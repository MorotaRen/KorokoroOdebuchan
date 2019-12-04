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
		//フェード中かどうか
		bool m_isFade = true;
	public:
		FadeSprite(const shared_ptr<Stage>&stagePtr,
			const FadeType& fadeType,
			const wstring&stageString=L"");
		~FadeSprite() {}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		bool GetIsFade()
		{
			return m_isFade;
		}
		void SetIsFade(bool isFade)
		{
			m_isFade = isFade;
		}

	};
}

//end basecross

