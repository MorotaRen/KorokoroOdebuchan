/*!
@file Fade.h
@brief �t�F�[�h�N���X
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
	// �t�F�[�h
	//--------------------------------------------------------------------------------------
	class FadeSprite :public Sprite {
	private:
		float m_FadeSpeed = 0.01f;
		//�t�F�[�h�̃^�C�v
		FadeType m_Type;
		//�J�ڂ���X�e�[�W��
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

