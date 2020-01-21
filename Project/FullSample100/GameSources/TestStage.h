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
		vector<weak_ptr<StartPause>>m_SpVec;
		//ビューの作成
		void CreateViewLight();
		//UI
		void CreateUI();

		bool m_IsCreateObject;
		bool m_updateFlag = false;
		bool m_Pause = false;
		bool m_cntlrock = false;
		//スタート画像が表示されたかどうか
		bool m_StartActive = false;
		float m_stopTime = 0.0f;    //時間を計測
		int PauseSelect = 0;      

	public:

		//構築と破棄
		TestStage() :Stage(),m_SpVec(2){}
		virtual ~TestStage();
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;
		virtual void OnDraw()override;


		shared_ptr<EfkInterface> GetEfkInterface() const { return m_efkInterface; }		

		void CreateEffect();

		//BGMの再生
		void PlayBGM(wstring key, float vol);
		//BGMの停止
		void StopBGM();
		//画像の明るさ
		void ChangePause(int num);

		//コントローラーのロックのゲッター
		bool GetCntLock() { return m_cntlrock; }
		//スタート画像が表示されたかどうか
		bool GetStart() { return m_StartActive; }
		void SetStart(bool active) {
			m_StartActive = active;
		}

	};


}