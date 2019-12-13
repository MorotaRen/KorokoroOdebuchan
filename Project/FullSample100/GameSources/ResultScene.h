/*!
@file Result.h
@brief リザルトクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WinPlayer;
	//--------------------------------------------------------------------------------------
	//	playerプレビュー
	//--------------------------------------------------------------------------------------
	class WinPlayer :public GameObject {
	public:
		WinPlayer(const shared_ptr<Stage>&stagePtr);
		~WinPlayer(){}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	// リザルトシーンのクラス
	//--------------------------------------------------------------------------------------

	class ResultScene : public Stage {
	private:
		//ビューの作成
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		vector<shared_ptr<ResultSceneSprite>> m_SpVec;

		int m_StageNum = 0;   //今選択してるステージ番号
		bool m_CntrolLock;    //スティックを一度倒したらロック

		//背景の作成
		void CreateBackground();

	public:
		//構築
		ResultScene() :Stage(), m_CntrolLock(false), m_SpVec(2) {}
		//破棄
		virtual ~ResultScene() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

}

//end basecross

