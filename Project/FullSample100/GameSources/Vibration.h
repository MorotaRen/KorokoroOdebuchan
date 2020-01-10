#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	// �o�C�u���[�V����
	//--------------------------------------------------------------------------------------
	class Vibration
	{
	protected:
		bool m_isVib[4] = {};			//�U���t���O
		float m_vibInterval[4] = {};	//�U�����鎞��
		float m_vibCount[4] = {};		//�o�ߎ���
	public:
		DECLARE_SINGLETON_INSTANCE(Vibration)

		//�o�C�u���[�V������ݒ�
		void SetVibration(float time, float leftSize, float rightSize, int cntlNum = 0);/*cntlNum�͉����n����Ȃ����0*/
		//�X�V
		void Update();
	};
}