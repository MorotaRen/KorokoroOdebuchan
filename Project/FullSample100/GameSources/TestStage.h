#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class MyCamera;

	class TestStage : public Stage {
		shared_ptr<EfkInterface> m_efkInterface;
		//�G�t�F�N�g�̔z��
		shared_ptr<EfkEffect> m_effect;

		weak_ptr<Player> m_ptrPlayer;
		shared_ptr<MyCamera> m_camera;
		shared_ptr<SoundItem> m_BGM;
		vector<weak_ptr<StartPause>>m_SpVec;
		//�r���[�̍쐬
		void CreateViewLight();
		//UI
		void CreateUI();

		bool m_IsCreateObject;
		bool m_updateFlag = false;
		bool m_Pause = false;
		bool m_cntlrock = false;
		//�X�^�[�g�摜���\�����ꂽ���ǂ���
		bool m_StartActive = false;
		float m_stopTime = 0.0f;    //���Ԃ��v��
		int PauseSelect = 0;      

	public:

		//�\�z�Ɣj��
		TestStage() :Stage(),m_SpVec(2){}
		virtual ~TestStage();
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void UpdateStage()override;
		virtual void OnDraw()override;


		shared_ptr<EfkInterface> GetEfkInterface() const { return m_efkInterface; }		

		void CreateEffect();

		//BGM�̍Đ�
		void PlayBGM(wstring key, float vol);
		//BGM�̒�~
		void StopBGM();
		//�摜�̖��邳
		void ChangePause(int num);

		//�R���g���[���[�̃��b�N�̃Q�b�^�[
		bool GetCntLock() { return m_cntlrock; }
		//�X�^�[�g�摜���\�����ꂽ���ǂ���
		bool GetStart() { return m_StartActive; }
		void SetStart(bool active) {
			m_StartActive = active;
		}

	};


}