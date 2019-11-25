/*!
@file Timer.h
@brief �^�C�}�[�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Timer :public Sprite {
	private:
		float m_TotalTime;
		//������\��
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

