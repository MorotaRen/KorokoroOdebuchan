#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		shared_ptr<EfkInterface> m_efkInterface;
		//エフェクトの配列
		shared_ptr<EfkEffect> m_effect;

		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		shared_ptr<SoundItem> m_BGM;
		//ビューの作成
		void CreateViewLight();
		//UI
		void CreateUI();

		bool m_IsCreateObject;
		bool m_updateFlag = false;
		float m_deltTime = 0.0f;	//時間を計測
		float m_stopTime = 0.0f;

	public:

		//構築と破棄
		TestStage() :Stage(){}
		virtual ~TestStage();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;
		virtual void OnDraw()override;


		shared_ptr<EfkInterface> GetEfkInterface() const { return m_efkInterface; }		

		void CreateEffect();

		void PlayBGM(wstring key, float vol);
		void StopBGM();
	};


}