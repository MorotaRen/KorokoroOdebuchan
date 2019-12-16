/*!
@file Fade.cpp
@brief フェードクラス実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	// フェード
	//--------------------------------------------------------------------------------------
	FadeSprite::FadeSprite(const shared_ptr<Stage>&stagePtr,
		const FadeType& fadeType,
		float fadeSpeed,
		const wstring&stageString) :
		Sprite(stagePtr, L"Black", Vec2(1280.0f, 800.0f), Vec2(0.0f, 0.0f)),
		m_Type(fadeType),
		m_FadeSpeed(fadeSpeed),
		m_StageString(stageString)
	{}

	void FadeSprite::OnCreate() {
		Sprite::OnCreate();
		AddTag(L"Fade");
		SetDrawLayer(150);
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		switch (m_Type)
		{
		case FadeIn:
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case FadeOut:
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0, 0.0f));
			break;
		default:
			break;
		}
	}
	void FadeSprite::OnUpdate() {

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		Col4 color = ptrDraw->GetDiffuse();
		switch (m_Type)
		{
		case FadeIn:
			color.w -= m_FadeSpeed;
			ptrDraw->SetDiffuse(color);
			if (color.w < 0.0f) {
				SetIsFade(false);
				//GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
			break;
		case FadeOut:
			color.w += m_FadeSpeed;
			ptrDraw->SetDiffuse(color);
			if (color.w > 1.0f) {
				SetIsFade(false);
				GetStage()->PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), m_StageString);
				GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
			}
			break;
		default:
			break;
		}
	}

}

//end basecross

