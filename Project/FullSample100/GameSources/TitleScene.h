/// ----------------------------------------<summary>
/// タイトル用のステージのヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	タイトルシーンのクラス
	//--------------------------------------------------------------------------------------
	class TitleScene : public Stage {
		//ビューの作成
		void CreateViewLight();
		//UIの作成
		void CreateUI();
		//背景の作成
		void CreateBackground();

		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;   //今選択してるステージ番号
		bool m_CntrolLock;    //スティックを一度倒したらロック

		float TrueTime;
		float FalseTime;
		float TrueTimeEnd = 45.0f;	//表示してる時間
		float FalseTimeEnd = 15.0f;	//透明にしてる時間
		float Switch = 1.0f;		//trueとfalseの切り替え用
		float TrueTimePlus = 1.0f;

		float DecTime;				//ボタン押してからの時間計測
		float DecSwitch = 0.0f;		//決定キーのスイッチ

		float FlashingSpeed = 0.2f;
		float FlashingTime = 80.0f;
		float FlashingEnd = 120.0f;

	public:
		//構築
		TitleScene() :Stage(),m_CntrolLock(false){}
		//破棄
		virtual ~TitleScene() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}