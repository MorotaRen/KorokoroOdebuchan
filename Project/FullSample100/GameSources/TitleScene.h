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
	private:
		//�r���[�̍쐬
		void CreateViewLight();
		//UI�̍쐬
		void CreateUI();

		vector<shared_ptr<TitleSceneSprite>> m_Spvec;
		shared_ptr<SelectSpotSprite> m_SpotSprite;
		shared_ptr<SoundItem> m_BGM;
		int m_StageNum = 0;   //���I�����Ă�X�e�[�W�ԍ�
		bool m_CntrolLock;    //�X�e�B�b�N����x�|�����烍�b�N

		//�w�i�̍쐬
		void CreateBackground();

	public:
		//�\�z
		TitleScene() :Stage(),m_CntrolLock(false),m_Spvec(9) {}
		//�j��
		virtual ~TitleScene() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		int GetStageNum() { return m_StageNum; }
		vector<shared_ptr<TitleSceneSprite>>GetSpVec()const { return m_Spvec; }
	};
}