/// ----------------------------------------<summary>
/// Sprite�I�u�W�F�N�g�w�b�_�[
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class Sprite : public GameObject {
	private:
		//�e�N�X�`���L�[
		wstring m_key;
		//�c�Ɖ��̕�
		Vec2 m_size;
		//�e�N�X�`���͈�
		Rect2D<float> m_rect;
		//Sprite���_
		vector<VertexPositionTexture> vertices;
	public:
		//�R���X�g���N�^(�ʏ�)
		Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size);
		//�R���X�g���N�^(�傫���w���)
		Sprite(const std::shared_ptr<Stage>& stage, const std::wstring& key, Vec2 size, const Rect2D<float>& rect);
		//�j��
		~Sprite();
		//�\�z
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
		//�ʒu�ݒ�
		void SetPos(const Vec2& position);
		//�����X�e�[�^�X�ݒ�
		void SettingStatus();

	};
}