/*!
@file Result.h
@brief リザルトクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトスプライト
	//--------------------------------------------------------------------------------------
	class ResultSprite :public Sprite {
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		ResultSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~ResultSprite() {};
		virtual void OnCreate()override;
		void Transluc(bool Active);
	};

	//--------------------------------------------------------------------------------------
	//	タイマーの結果表示
	//--------------------------------------------------------------------------------------
	class ResultTimer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TimerScore = 0.0f;
		//桁数
		UINT m_NumberOfDigits;
		//バックアップ頂点データ
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		ResultTimer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~ResultTimer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

	//--------------------------------------------------------------------------------------
	// リザルトシーンのクラス
	//--------------------------------------------------------------------------------------
	//class ResultSprite;
	//class Player;

	class ResultScene : public Stage {
	private:
		//ビューの作成
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		vector<shared_ptr<ResultSprite>> m_SpVec;

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

