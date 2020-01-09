#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	IMPLEMENT_SINGLETON_INSTANCE(Vibration);

	//バイブレーションを設定
	void Vibration::SetVibration(float time, float leftSize, float rightSize, int cntlNum)
	{
		if (!m_isVib[cntlNum])
		{
			m_isVib[cntlNum] = true;
			m_vibInterval[cntlNum] = time;

			const WORD motorSpeed = 65535;	//モーターの回転速度

			XINPUT_VIBRATION state;
			state.wLeftMotorSpeed = (WORD)(motorSpeed * leftSize);		//左モーターの回転速度
			state.wRightMotorSpeed = (WORD)(motorSpeed * rightSize);	//右モーターの回転速度

			XInputSetState(cntlNum, &state);
		}
	}

	//更新
	void Vibration::Update()
	{
		//振動フラグの要素数分ループ
		for (int i = 0; i < ARRAYSIZE(m_isVib); i++)
		{
			if (m_isVib[i])
			{
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_vibCount[i] += elapsedTime;
				//設定した時間が経過したら
				if (m_vibCount[i] > m_vibInterval[i])
				{
					m_isVib[i] = false;
					m_vibCount[i] = 0;

					XINPUT_VIBRATION state;
					state.wLeftMotorSpeed = 0;	//左モーターの回転速度
					state.wRightMotorSpeed = 0;	//右モーターの回転速度
					XInputSetState(i, &state);
				}
			}
		}
	}
}