/// ----------------------------------------<summary>
/// Sprite�I�u�W�F�N�g�\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// �R���X�g���N�^(�w��Ȃ�)
	/// </summary>---------------------------------------
	/// <param name="key">�e�N�X�`���L�[</param>
	/// <param name="size">�����T�C�Y</param>
	Sprite::Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size)
		: GameObject(stage), m_key(key), m_size(size), m_rect(0, 0, size.x, size.y)
	{
	}

	/// ----------------------------------------<summary>
	/// �R���X�g���N�^(�傫���w��)
	/// </summary>----------------------------------------
	/// <param name="key">�e�N�X�`���L�[</param>
	/// <param name="size">�����T�C�Y</param>
	/// <param name="rect">�����e�N�X�`���T�C�Y</param>
	Sprite::Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size, const Rect2D<float>& rect)
		:GameObject(stage), m_key(key), m_size(size), m_rect(rect)
	{
	}

	/// ----------------------------------------<summary>
	/// �f�X�g���N�^
	/// </summary>----------------------------------------
	Sprite::~Sprite() {

	}

	/// ----------------------------------------<summary>
	/// �\�z
	/// </summary>----------------------------------------
	void Sprite::OnCreate() {
		SettingStatus();
	}

	/// ----------------------------------------<summary>
	/// �X�V
	/// </summary>----------------------------------------
	void Sprite::OnUpdate() {

	}

	/// ----------------------------------------<summary>
	/// �ʒu�ݒ�
	/// </summary>----------------------------------------
	/// <param name="pos">�ݒ�ʒu(Vec2)</param>
	void Sprite::SetPos(const Vec2& position) {
		auto& app = App::GetApp();
		Vec2 scrSize((float)app->GetGameWidth(), (float)app->GetGameHeight());
		Vec2 scrHalf = scrSize * 0.5f;

		auto transComp = GetComponent<Transform>();
		Vec2 pos = position - scrHalf;
		transComp->SetPosition(pos.x, pos.y, 0);

	}

	/// ----------------------------------------<summary>
	/// �X�e�[�^�X�ݒ�
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

		//���_�z��̍쐬
		vertices = {
			{VertexPositionTexture(Vec3(-half_w,+half_h,0.0f),Vec2(start_x,start_y))},
			{VertexPositionTexture(Vec3(+half_w,+half_h,0.0f),Vec2(end_x,start_y))},
			{VertexPositionTexture(Vec3(-half_w,-half_h,0.0f),Vec2(start_x,end_y))},
			{VertexPositionTexture(Vec3(+half_w,-half_h,0.0f),Vec2(end_x,end_y))},
		};
		//���_�C���f�b�N�X
		vector<uint16_t> indices{
			0,1,2,
			1,3,2
		};
		//�`��R���|�[�l���g�̒ǉ�
		auto drawComp = AddComponent<PTSpriteDraw>(vertices,indices);
		drawComp->SetTextureResource(m_key);
		//�����x�̗L����
		SetAlphaActive(true);

		this->SetPos(Vec2(0, 0));

	}

}