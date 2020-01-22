/// ----------------------------------------<summary>
/// �^�C�g���p�̃X�e�[�W�̃w�b�_�[
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	//	�^�C�g���V�[���̃N���X
	//--------------------------------------------------------------------------------------
	class TitleScene : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//UI�̍쐬
		void CreateUI();
		//�w�i�̍쐬
		void CreateBackground();

		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;   //���I�����Ă�X�e�[�W�ԍ�
		bool m_CntrolLock;    //�X�e�B�b�N����x�|�����烍�b�N

		float TrueTime;
		float FalseTime;
		float TrueTimeEnd = 45.0f;	//�\�����Ă鎞��
		float FalseTimeEnd = 15.0f;	//�����ɂ��Ă鎞��
		float Switch = 1.0f;		//true��false�̐؂�ւ��p
		float TrueTimePlus = 1.0f;

		float DecTime;				//�{�^�������Ă���̎��Ԍv��
		float DecSwitch = 0.0f;		//����L�[�̃X�C�b�`

		float FlashingSpeed = 0.2f;
		float FlashingTime = 80.0f;
		float FlashingEnd = 120.0f;

	public:
		//�\�z
		TitleScene() :Stage(),m_CntrolLock(false){}
		//�j��
		virtual ~TitleScene() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}