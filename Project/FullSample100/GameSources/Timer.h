/*!
@file Timer.h
@brief タイマーの行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	時間計測
	//--------------------------------------------------------------------------------------
	class Timer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Timer=0.0f;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
		//リザルトに使う用
		float m_Score = 0.0f;
	public:
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos,bool resultFlg=false);
		virtual ~Timer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		float GetScore() {
			return m_Score;
		}
		//呼んだ時のタイムを記録
		void SetScore() {
			m_Score = m_Timer;
		}
	};

	//--------------------------------------------------------------------------------------
	//	timeの画像表示
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

