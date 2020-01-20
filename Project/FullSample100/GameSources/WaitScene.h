#pragma once
#include <stdafx.h>

namespace basecross {
	class WaitScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
		static void LoadResourceFunc();
		//���\�[�X��ǂݍ��񂾂��Ƃ�m�点��t���O�i�X�^�e�B�b�N�ϐ��j
		static bool m_Loaded;
		//�~���[�e�b�N�X
		static std::mutex mtx;
	public:
		//�\�z�Ɣj��
		WaitScene() :Stage() {}
		virtual ~WaitScene() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override;
	};
}