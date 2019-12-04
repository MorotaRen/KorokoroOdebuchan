#pragma once
#pragma once
#include "stdafx.h"

namespace basecross
{

	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	class StartPause : public GameObject
	{

		//ポーズされているかどうか
		bool m_isPause;


	public:
		StartPause(const shared_ptr<Stage>& StagePtr);
		~StartPause() {};

		virtual void OnCreate()override;
		virtual void OnUpdate();

		//ポーズ状態を管理するフラグ
		bool GetPause() { return m_isPause; }

		//時間を止める関数
		void Pause();

		//時間を動かす関数
		void Release();

	};
}