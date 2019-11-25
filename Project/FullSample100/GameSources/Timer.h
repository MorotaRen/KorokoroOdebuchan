/*!
@file Timer.h
@brief �^�C�}�[�̍s���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Timer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Totaltime;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~Timer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};
}

//end basecross

