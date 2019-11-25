/*!
@file Timer.h
@brief タイマーの行動クラス
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
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
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

