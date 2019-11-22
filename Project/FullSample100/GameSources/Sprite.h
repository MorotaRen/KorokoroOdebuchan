/// ----------------------------------------<summary>
/// Spriteオブジェクトヘッダー
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite : public GameObject {
	private:
		//テクスチャキー
		wstring m_key;
		//縦と横の幅
		Vec2 m_size;
		//テクスチャ範囲
		Rect2D<float> m_rect;
		//Sprite頂点
		vector<VertexPositionTexture> vertices;
	public:
		//コンストラクタ(通常)
		Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size);
		//コンストラクタ(大きさ指定版)
		Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size, const Rect2D<float>& rect);
		//破棄
		~Sprite();
		//構築
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//位置設定
		void SetPos(const Vec2& position);
		//初期ステータス設定
		void SettingStatus();

	};
}