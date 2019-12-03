#pragma once
#pragma once
#include "stdafx.h"

namespace basecross
{
	//選ばれている選択肢の情報
	enum class Choice
	{
		NextStage,
		BackToGame,
		Restart,
		GoToSelect
	};

	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	class StartPause : public GameObject
	{
		vector<VertexPositionColorTexture> m_backupVertices;

		//ポーズされているかどうか
		bool m_isPause;

		//スティック倒し一度を識別するための変数
		bool m_once;

		//選ばれている選択肢
		Choice m_choice = Choice::BackToGame;


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