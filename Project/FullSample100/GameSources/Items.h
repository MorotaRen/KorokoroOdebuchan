#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// �A�C�e���n�͑S������
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------
namespace basecross {

	class ItemsEffect
	{
	private:

	public:
		ItemsEffect();
		~ItemsEffect();
		//HP��
		void Healing_HP(unsigned int value);
		//�X�}�b�V�����[�����O�Q�[�W��
		void Healing_Gauge(unsigned int value);
	};
}