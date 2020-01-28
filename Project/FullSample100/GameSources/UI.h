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
		virtual void OnCreate()override;

		void SetActive(bool Active);
		void ProtType();
	};

	/***************************************************************************************
									  セレクトシーンのUI
	***************************************************************************************/
	class SelectSceneSprite :public Sprite
	{
	public:
		SelectSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectSceneSprite() {};

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

	//--------------------------------------------------------------------------------------
	//	カウントダウン
	//--------------------------------------------------------------------------------------
	class CountDown :public Sprite {
	private:
		float m_TotalTime;
		float m_RemoveTime;
		int m_Count;
	public:
		CountDown(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~CountDown() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
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
	//	スマッシュゲージがたまったことをお知らせ
	//--------------------------------------------------------------------------------------
	class GaugeMax :public Sprite {
	public:
		GaugeMax(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~GaugeMax() {};
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	スピードメーターのUI
	//--------------------------------------------------------------------------------------
	class SpeedMeter :public GameObject{
	public:
		SpeedMeter(const shared_ptr<Stage>&stagePtr);

		virtual ~SpeedMeter() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class SpeedMeterNeedle :public GameObject {
		float m_speed;
		float m_rotate;

	public:
		SpeedMeterNeedle(const shared_ptr<Stage>&stagePtr);

		virtual ~SpeedMeterNeedle() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//プレイヤーのスピードを取得する
		void SetSpeed(float s) { m_speed = s; }
	};
	//--------------------------------------------------------------------------------------
	//	スピードメーター用の数字
	//--------------------------------------------------------------------------------------
	class SpeedMeterNumber :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Speed;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		SpeedMeterNumber(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, bool resultFlg = false);
		virtual ~SpeedMeterNumber() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
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

