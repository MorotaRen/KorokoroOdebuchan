/*!
@file UI.h
@brief UIクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	/***************************************************************************************
									  タイトルシーンのUI
	***************************************************************************************/
	class TitleSceneSprite :public Sprite
	{
	public:
		TitleSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~TitleSceneSprite() {};

	};

	//--------------------------------------------------------------------------------------
	//	選択している所を表示するスプライト
	//--------------------------------------------------------------------------------------
	class SelectSpotSprite :public Sprite {
	public:
		SelectSpotSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectSpotSprite() {}
		bool SelectSpotFlag;
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		bool GetSelectSpotFlag() { return SelectSpotFlag; }
	};


	/***************************************************************************************
				                      メインシーンのUI
	***************************************************************************************/
	class MainSceneSprite :public Sprite
	{
	public:
		MainSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~MainSceneSprite() {};

	};
	//--------------------------------------------------------------------------------------
	//	スタートを表示
	//--------------------------------------------------------------------------------------
	class CountDown :public Sprite {
	private:
		float m_TotalTime;
		float m_RemoveTime;
	public:
		CountDown(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~CountDown() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	class StartPause : public Sprite
	{
	public:
		StartPause(const shared_ptr<Stage>& StagePtr,
			const wstring&textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		~StartPause() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Akarusa(bool flg);
	};

	//--------------------------------------------------------------------------------------
	//	時間計測
	//--------------------------------------------------------------------------------------
	class Timer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Timer;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, bool resultFlg = false);
		virtual ~Timer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		float GetTimer() {
			return m_Timer;
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

	//--------------------------------------------------------------------------------------
	//	スマッシュゲージのUI
	//--------------------------------------------------------------------------------------
	class SmashGauge :public Sprite {
		float m_MaxSmashPoint = 10;
		float m_MinSmashPoint = 0;
		float m_SmashPoint = m_MinSmashPoint;
		float ElapsedTime = 0.0f;
		float m_rate = 0.0;
		bool m_Active = false; //ゲージを使うためのスイッチ
		bool m_UsePoint = false;//UseSmashPointを使っているかを判定
		bool m_IsUsable = false;//UseSmashPointを使えるか判定

	public:
		SmashGauge(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~SmashGauge() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void CargeSmashPoint(float f);
		void UseSmashPoint();
		void SetActive(bool active) {
			m_Active = active;
		}
		float GetSmashPoint() { return m_SmashPoint; }
		bool GetUsable() { return m_IsUsable; }
	};

	/***************************************************************************************
									  リザルトシーンのUI
	***************************************************************************************/
	class ResultSceneSprite :public Sprite {
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		ResultSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~ResultSceneSprite() {};
		virtual void OnCreate()override;
		void Transluc(bool Active);
	};

	//--------------------------------------------------------------------------------------
	//	タイマーの結果表示
	//--------------------------------------------------------------------------------------
	class ResultTimer :public GameObject {
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

}

//end basecross

