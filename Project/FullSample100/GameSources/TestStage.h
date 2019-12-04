#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		bool m_IsCreateObject;
		// UI�̍쐬
		void CreateUI();


	public:

		//�\�z�Ɣj��
		TestStage() :Stage(){}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}