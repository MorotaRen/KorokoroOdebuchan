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
		const wstring&stageString):
		Sprite(stagePtr,L"Black",Vec2(1280.0f,800.0f),Vec2(0.0f,0.0f)),
		m_Type(fadeType),
		m_StageString(stageString)
	{}

}

//end basecross

