#pragma once
#pragma once
#include "stdafx.h"

namespace basecross
{

	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	class StartPause : public Sprite
	{
	public:
		StartPause(const shared_ptr<Stage>& StagePtr,
			const wstring&textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		~StartPause() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Akarusa(bool flg);
	};
}