/// ----------------------------------------<summary>
/// �^�C�g���p�̃X�e�[�W�̃w�b�_�[
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{
	class TitleScene : public Stage {
	private:
		//�r���[�̍쐬
		void CreateViewLight();

	public:
		//�\�z
		TitleScene() :Stage() {}
		//�j��
		~TitleScene() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}