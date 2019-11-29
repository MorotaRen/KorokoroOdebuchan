/// ----------------------------------------<summary>
/// タイトル用のステージのヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{
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
	//	タイトルシーンのクラス
	//--------------------------------------------------------------------------------------
	class TitleScene : public Stage {
	private:
		//ビューの作成
		void CreateViewLight();
		//UIの作成
		void CreateUI();

		vector<shared_ptr<Sprite>> m_Spvec;
		shared_ptr<SelectSpotSprite> m_SpotSprite;

		int m_StageNum = 0;   //今選択してるステージ番号
		bool m_CntrolLock;    //スティックを一度倒したらロック

		//背景の作成
		void CreateBackground();

	public:
		//構築
		TitleScene() :Stage(),m_CntrolLock(false),m_Spvec(9) {}
		//破棄
		virtual ~TitleScene() {}
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		int GetStageNum() { return m_StageNum; }
		vector<shared_ptr<Sprite>>GetSpVec()const { return m_Spvec; }
	};
}