#pragma once
/// ----------------------------------------<summary>
/// �Q�[���S�̂ŌĂяo����֐��p�w�b�_�[
/// ���F�V���O���g��
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class  GameSystems final {
	private:
		//�R���X�g���N�^
		GameSystems() {};
		//�R���X�g���N�^
		GameSystems(const GameSystems&);
		//�f�X�g���N�^
		~GameSystems() {};
		//�R���g���[���[���
		CONTROLER_STATE m_pad;
	public:
		//�������牺�ɒu���Ȃ��ƌĂяo���Ȃ���

		//�R���g���[���[���ڑ�����Ă�����}�E�X�J�[�\�����폜����
		void ControllerCheck_Cursor();
		//�R���g���[���[���X�V
		void UpdatePadData();
	};
}