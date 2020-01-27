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
		wstring m_StageString=L"";

		//�t�F�[�h�����ǂ���
		bool m_isFade = true;

		float m_FadeSpeed;
	public:
		FadeSprite(const shared_ptr<Stage>&stagePtr,
			const FadeType& fadeType,
			float fadeSpeed = 0.0f ,
			const wstring&stageString=L""
		);
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

