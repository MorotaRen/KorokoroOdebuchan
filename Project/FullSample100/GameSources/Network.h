#pragma once
/// ----------------------------------------<summary>
/// �l�b�g���[�N�֘A
/// ���F�V���O���g��
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class  NetWork final {
	private:
		//�R���X�g���N�^
		NetWork() {};
		//�R���X�g���N�^
		NetWork(const NetWork&);
		//�f�X�g���N�^
		~NetWork() {};
		//������
		bool Initialize();

		WSADATA m_pwsaData;

	public:
		static NetWork& GetInstans() {
			static NetWork inst;
			return inst;
		}
		//���s
		void Main();

	};
}