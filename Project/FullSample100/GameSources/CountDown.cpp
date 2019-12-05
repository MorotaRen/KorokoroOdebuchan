/*!
@file Sprite.cpp
@brief スプライト実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	2Dのスプライト
	//--------------------------------------------------------------------------------------
	CountDown::CountDown(const shared_ptr<Stage>&stagePtr,
		const wstring& textureKey,
		const Vec2& startPos) :
		Sprite(stagePtr, textureKey, Vec2(1280.0f, 512.0f), startPos),
		m_TotalTime(0.0f),
		m_RemoveTime(3.0f)
	{}

	void CountDown::OnCreate() {
		Sprite::OnCreate();
		}
	void CountDown::OnUpdate() {
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;

		auto ptrTrans = GetComponent<Transform>();
		auto pos = ptrTrans->GetPosition();
		auto scale = ptrTrans->GetScale();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		float removeTimeHalf = m_RemoveTime / 2.0f;

		float dis;
		if (m_TotalTime < removeTimeHalf) {
			dis = m_TotalTime / removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, dis));
		}
		else
		{
			dis = (m_TotalTime - removeTimeHalf)/removeTimeHalf;
			ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 1.0f - dis));
		}

		if (m_TotalTime > m_RemoveTime) {
			GetStage()->RemoveGameObject<GameObject>(GetThis<GameObject>());
		}
	}
}


//end basecross

