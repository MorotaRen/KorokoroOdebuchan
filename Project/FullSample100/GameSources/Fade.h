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
		//�t�F�[�h�̃^�C�v
		FadeType m_Type;
		//�J�ڂ���X�e�[�W��
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

