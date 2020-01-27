/// ----------------------------------------<summary>
/// タイトル用のステージのヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	セレクトシーンのクラス
	//--------------------------------------------------------------------------------------
	class SelectScene : public Stage {
	private:
		//ビューの作成
		void CreateViewLight();
		//UIの作成
		void CreateUI();

		vector<shared_ptr<SelectSceneSprite>> m_Spvec;
		shared_ptr<SelectSpotSprite> m_SpotSprite;
		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;   //今選択してるステージ番号
		bool m_CntrolLock;    //スティックを一度倒したらロック

		//背景の作成
		void CreateBackground();

	public:
		//構築
		SelectScene() :Stage(),m_CntrolLock(false),m_Spvec(9) {}
		//破棄
		virtual ~SelectScene() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		int GetStageNum() { return m_StageNum; }
		vector<shared_ptr<SelectSceneSprite>>GetSpVec()const { return m_Spvec; }
	};
}