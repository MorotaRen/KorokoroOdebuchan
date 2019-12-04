#pragma once
#pragma once
#include "stdafx.h"

namespace basecross
{
	//�I�΂�Ă���I�����̏��
	enum class Choice
	{
		NextStage,
		BackToGame,
		Restart,
		GoToSelect
	};

	//--------------------------------------------------------------------------------------
	//	�|�[�Y�p�̃��j���[
	//--------------------------------------------------------------------------------------
	class StartPause : public GameObject
	{
		vector<VertexPositionColorTexture> m_backupVertices;

		//�|�[�Y����Ă��邩�ǂ���
		bool m_isPause;

		//�X�e�B�b�N�|����x�����ʂ��邽�߂̕ϐ�
		bool m_once;

		//�I�΂�Ă���I����
		Choice m_choice = Choice::BackToGame;


	public:
		StartPause(const shared_ptr<Stage>& StagePtr);
		~StartPause() {};

		virtual void OnCreate()override;
		virtual void OnUpdate();

		//�|�[�Y��Ԃ��Ǘ�����t���O
		bool GetPause() { return m_isPause; }

		//���Ԃ��~�߂�֐�
		void Pause();

		//���Ԃ𓮂����֐�
		void Release();

	};



}