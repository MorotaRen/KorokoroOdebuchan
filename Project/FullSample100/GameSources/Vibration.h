#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	// バイブレーション
	//--------------------------------------------------------------------------------------
	class Vibration
	{
	protected:
		bool m_isVib[4] = {};			//振動フラグ
		float m_vibInterval[4] = {};	//振動する時間
		float m_vibCount[4] = {};		//経過時間
	public:
		DECLARE_SINGLETON_INSTANCE(Vibration)

		//バイブレーションを設定
		void SetVibration(float time, float leftSize, float rightSize, int cntlNum = 0);/*cntlNumは何も渡されなければ0*/
		//更新
		void Update();
	};
}