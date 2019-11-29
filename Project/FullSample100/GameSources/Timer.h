/*!
@file Timer.h
@brief �^�C�}�[�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���Ԍv��
	//--------------------------------------------------------------------------------------
	class Timer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Timer;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos,bool resultFlg=false);
		virtual ~Timer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	//	time�̉摜�\��
	//--------------------------------------------------------------------------------------
	class TextTime :public Sprite {
	public:
		TextTime(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~TextTime() {}
		virtual void OnCreate() override;

	};
}

//end basecross
