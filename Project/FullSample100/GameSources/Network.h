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
		void Initialize(WSAData &wsad);
		//Soket�̍쐬
		SOCKET CreateSocket();


		struct sockaddr_in m_server;

	public:
		static NetWork& GetInstans() {
			static NetWork inst;
			return inst;
		}
		//���s
		void Main();
		//�ڑ�
		void Connection_Sending();
		//��M
		void Connection_Receiving();
	};
}