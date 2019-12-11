#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	StartPause::StartPause(const shared_ptr<Stage>& StagePtr,
			const wstring&textureKey,
			const Vec2& startScale,
			const Vec2& startPos):
		Sprite(StagePtr,textureKey,startScale,startPos)
	{}

	void StartPause::OnCreate()
	{
		Sprite::OnCreate();
		AddTag(L"StartPause");
		SetDrawLayer(100);
		SetDrawActive(false);
	}

	void StartPause::OnUpdate()
	{

	}
	void StartPause::Akarusa(bool flg) 
	{
		GetComponent<PCTSpriteDraw>()->SetDiffuse(Col4(1, 1, 1, 1.0f));
	}

}