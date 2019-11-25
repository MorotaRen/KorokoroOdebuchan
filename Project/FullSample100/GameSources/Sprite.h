/*!
@file Sprite.h
@brief �X�v���C�g�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	2D�̃X�v���C�g
	//--------------------------------------------------------------------------------------
	class Sprite :public GameObject {
	protected:
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		Sprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~Sprite() {};
		virtual void OnCreate()override;
	};
}

//end basecross

