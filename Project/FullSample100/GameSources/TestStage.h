#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;
	class ResultSprite;

	class TestStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		vector<shared_ptr<ResultSprite>> m_SpVec;
		bool m_IsCreateObject;
		bool m_updateFlag = false;
		float m_deltTime = 0.0f;	//���Ԃ��v��
		float m_stopTime = 0.0f;
		int m_StageNum = 0;   //���I�����Ă�X�e�[�W�ԍ�
		bool m_CntrolLock;    //�X�e�B�b�N����x�|�����烍�b�N

		void CreateUI();


	public:

		//�\�z�Ɣj��
		TestStage() :Stage(),m_CntrolLock(false), m_SpVec(2) {}
		virtual ~TestStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;
	};


}