/// ----------------------------------------<summary>
/// Spriteオブジェクトソース
/// 管理者：諸田
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// コンストラクタ(指定なし)
	/// </summary>---------------------------------------
	/// <param name="key">テクスチャキー</param>
	/// <param name="size">初期サイズ</param>
	Sprite::Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size)
		: GameObject(stage), m_key(key), m_size(size), m_rect(0, 0, size.x, size.y)
	{
	}

	/// ----------------------------------------<summary>
	/// コンストラクタ(大きさ指定)
	/// </summary>----------------------------------------
	/// <param name="key">テクスチャキー</param>
	/// <param name="size">初期サイズ</param>
	/// <param name="rect">初期テクスチャサイズ</param>
	Sprite::Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size, const Rect2D<float>& rect)
		:GameObject(stage), m_key(key), m_size(size), m_rect(rect)
	{
	}

	/// ----------------------------------------<summary>
	/// デストラクタ
	/// </summary>----------------------------------------
	Sprite::~Sprite() {

	}

	/// ----------------------------------------<summary>
	/// 構築
	/// </summary>----------------------------------------
	void Sprite::OnCreate() {
		SettingStatus();
	}

	/// ----------------------------------------<summary>
	/// 更新
	/// </summary>----------------------------------------
	void Sprite::OnUpdate() {

	}

	/// ----------------------------------------<summary>
	/// 位置設定
	/// </summary>----------------------------------------
	/// <param name="pos">設定位置(Vec2)</param>
	void Sprite::SetPos(const Vec2& position) {
		auto& app = App::GetApp();
		Vec2 scrSize((float)app->GetGameWidth(), (float)app->GetGameHeight());
		Vec2 scrHalf = scrSize * 0.5f;

		auto transComp = GetComponent<Transform>();
		Vec2 pos = position - scrHalf;
		transComp->SetPosition(pos.x, pos.y, 0);

	}

	/// ----------------------------------------<summary>
	/// ステータス設定
	/// </summary>----------------------------------------
	void Sprite::SettingStatus() {
		float sprite_w = m_rect.right - m_rect.left;
		float sprite_h = m_rect.bottom - m_rect.top;

		float half_w = sprite_w * 0.5f;
		float half_h = sprite_h * 0.5f;

		float start_x = m_rect.left / m_size.x;
		float end_x = m_rect.right / m_size.x;

		float start_y = m_rect.top / m_size.y;
		float end_y = m_rect.left / m_size.y;

		//頂点配列の作成
		vertices = {
			{VertexPositionTexture(Vec3(-half_w,+half_h,0.0f),Vec2(start_x,start_y))},
			{VertexPositionTexture(Vec3(+half_w,+half_h,0.0f),Vec2(end_x,start_y))},
			{VertexPositionTexture(Vec3(-half_w,-half_h,0.0f),Vec2(start_x,end_y))},
			{VertexPositionTexture(Vec3(+half_w,-half_h,0.0f),Vec2(end_x,end_y))},
		};
		//頂点インデックス
		vector<uint16_t> indices{
			0,1,2,
			1,3,2
		};
		//描画コンポーネントの追加
		auto drawComp = AddComponent<PTSpriteDraw>(vertices,indices);
		drawComp->SetTextureResource(m_key);
		//透明度の有効化
		SetAlphaActive(true);

		this->SetPos(Vec2(0, 0));

	}

}