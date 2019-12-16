/*!
@file Result.h
@brief ���U���g�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class WinPlayer;
	//--------------------------------------------------------------------------------------
	//	player�v���r���[
	//--------------------------------------------------------------------------------------
	class WinPlayer :public GameObject {
	public:
		WinPlayer(const shared_ptr<Stage>&stagePtr);
		~WinPlayer(){}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

	};

	//--------------------------------------------------------------------------------------
	// ���U���g�V�[���̃N���X
	//--------------------------------------------------------------------------------------

	class ResultScene : public Stage {
	private:
		//�r���[�̍쐬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		vector<shared_ptr<ResultSceneSprite>> m_SpVec;

		int m_StageNum = 0;   //���I�����Ă�X�e�[�W�ԍ�
		bool m_CntrolLock;    //�X�e�B�b�N����x�|�����烍�b�N

		//�w�i�̍쐬
		void CreateBackground();

	public:
		//�\�z
		ResultScene() :Stage(), m_CntrolLock(false), m_SpVec(2) {}
		//�j��
		virtual ~ResultScene() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};

}

//end basecross

