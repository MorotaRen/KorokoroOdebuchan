/*!
@file CountDown.h
@brief �J�E���g�_�E���̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�J�E���g�_�E���p�̐���
	//--------------------------------------------------------------------------------------
	class CountDown :public Sprite {
	private :
		float m_TotalTime;
		float m_RemoveTime;
	public:
		CountDown(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startPos);

		virtual ~CountDown() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}

//end basecross

