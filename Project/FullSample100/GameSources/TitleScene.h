/// ----------------------------------------<summary>
/// �^�C�g���p�̃X�e�[�W�̃w�b�_�[
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross{
	//--------------------------------------------------------------------------------------
	//	�I�����Ă��鏊��\������X�v���C�g
	//--------------------------------------------------------------------------------------
	class SelectSpotSprite :public Sprite {
	public:
		SelectSpotSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectSpotSprite() {}
		bool SelectSpotFlag;
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		bool GetSelectSpotFlag() { return SelectSpotFlag; }
	};

	//--------------------------------------------------------------------------------------
	//	�^�C�g���V�[���̃N���X
	//--------------------------------------------------------------------------------------
	class TitleScene : public Stage {
	private:
		//�r���[�̍쐬
		void CreateViewLight();
		//UI�̍쐬
		void CreateUI();

		vector<shared_ptr<Sprite>> m_Spvec;
		shared_ptr<SelectSpotSprite> m_SpotSprite;

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
		vector<shared_ptr<Sprite>>GetSpVec()const { return m_Spvec; }
	};
}