#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;

	class TestStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
	public:
		//�\�z�Ɣj��
		TestStage() :Stage() {}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;
	};


}