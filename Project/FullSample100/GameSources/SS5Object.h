#pragma once

#include "stdafx.h"

namespace basecross{
	class SS5Object : public SS5ssae {
	public:
		//構築
		SS5Object(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim);
		//破棄
		~SS5Object();
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		Mat4x4 m_ToAnimeMatrix;
	};

	//--------------------------------------------------------------------------------------
	// セレクトステージ用のSS
	//--------------------------------------------------------------------------------------
	class SelectSS : public SS5ssae {
	protected:
		Vec2 m_Scale;
		Vec2 m_Position;
	public:
		//構築
		SelectSS(const shared_ptr<Stage> stageptr,
			const wstring& BaseDir, 
			const wstring FileName, 
			const wstring FirstAnim, 
			const Vec2& startScale,
			const Vec2& startPos);
		//破棄
		~SelectSS() {};
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	// スマッシュゲージ用のSS
	//--------------------------------------------------------------------------------------
	class SmashGageSS :public SS5ssae {
	public:
		//構築
		SmashGageSS(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim);
		//破棄
		~SmashGageSS(){};
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
	};
}