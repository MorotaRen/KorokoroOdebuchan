#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		shared_ptr<SoundItem> m_BGM;
		vector<weak_ptr<StartPause>>m_SpVec;
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();
		//UI
		void CreateUI();

		bool m_IsCreateObject;
		bool m_updateFlag = false;
		bool m_Pause = false;
		bool m_PauseFade = false;
		bool m_cntlrock = false;
		float m_stopTime = 0.0f;    //ŠÔ‚ğŒv‘ª
		int PauseSelect = 0;        

	public:

		//\’z‚Æ”jŠü
		TestStage() :Stage(),m_SpVec(2){}
		virtual ~TestStage();
		//‰Šú‰»
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;

		//BGM‚ÌÄ¶
		void PlayBGM(wstring key, float vol);
		//BGM‚Ì’â~
		void StopBGM();
		//
		void ChangePause(int num);
	};


}