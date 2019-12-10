#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;

		//�r���[�̍쐬
		void CreateViewLight();
		//UI
		void CreateUI();
		//�G�t�F�N�g�̍쐬
		void CreateEffect();

		bool m_IsCreateObject;
		bool m_updateFlag = false;
		float m_deltTime = 0.0f;	//���Ԃ��v��
		float m_stopTime = 0.0f;

	public:

		//�\�z�Ɣj��
		TestStage() :Stage(){}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;

	};


}