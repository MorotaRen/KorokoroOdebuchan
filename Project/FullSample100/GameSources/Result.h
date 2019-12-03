/*!
@file Result.h
@brief リザルトクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルト背景
	//--------------------------------------------------------------------------------------
	class ResultBG :public Sprite {
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		ResultBG(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~ResultBG() {};
		virtual void OnCreate()override;

	};

	//--------------------------------------------------------------------------------------
	//	タイマーの結果表示
	//--------------------------------------------------------------------------------------
	class ResultTimer :public Timer {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TimerScore = 0.0f;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		ResultTimer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~ResultTimer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};
	//--------------------------------------------------------------------------------------
	//	タイトルに戻る
	//--------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------
	//	リトライ
	//--------------------------------------------------------------------------------------

}

//end basecross

