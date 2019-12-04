#pragma once
#pragma once
#include "stdafx.h"

namespace basecross
{

	//--------------------------------------------------------------------------------------
	//	�|�[�Y�p�̃��j���[
	//--------------------------------------------------------------------------------------
	class StartPause : public GameObject
	{

		//�|�[�Y����Ă��邩�ǂ���
		bool m_isPause;


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