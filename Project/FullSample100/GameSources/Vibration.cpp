#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	IMPLEMENT_SINGLETON_INSTANCE(Vibration);

	//�o�C�u���[�V������ݒ�
	void Vibration::SetVibration(float time, float leftSize, float rightSize, int cntlNum)
	{
		if (!m_isVib[cntlNum])
		{
			m_isVib[cntlNum] = true;
			m_vibInterval[cntlNum] = time;

			const WORD motorSpeed = 65535;	//���[�^�[�̉�]���x

			XINPUT_VIBRATION state;
			state.wLeftMotorSpeed = (WORD)(motorSpeed * leftSize);		//�����[�^�[�̉�]���x
			state.wRightMotorSpeed = (WORD)(motorSpeed * rightSize);	//�E���[�^�[�̉�]���x

			XInputSetState(cntlNum, &state);
		}
	}

	//�X�V
	void Vibration::Update()
	{
		//�U���t���O�̗v�f�������[�v
		for (int i = 0; i < ARRAYSIZE(m_isVib); i++)
		{
			if (m_isVib[i])
			{
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_vibCount[i] += elapsedTime;
				//�ݒ肵�����Ԃ��o�߂�����
				if (m_vibCount[i] > m_vibInterval[i])
				{
					m_isVib[i] = false;
					m_vibCount[i] = 0;

					XINPUT_VIBRATION state;
					state.wLeftMotorSpeed = 0;	//�����[�^�[�̉�]���x
					state.wRightMotorSpeed = 0;	//�E���[�^�[�̉�]���x
					XInputSetState(i, &state);
				}
			}
		}
	}
}