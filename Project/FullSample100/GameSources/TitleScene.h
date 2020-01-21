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
	private:
		//ビューの作成
		void CreateViewLight();
		//UIの作成
		void CreateUI();

		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;   //今選択してるステージ番号
		bool m_CntrolLock;    //スティックを一度倒したらロック

		//背景の作成
		void CreateBackground();

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