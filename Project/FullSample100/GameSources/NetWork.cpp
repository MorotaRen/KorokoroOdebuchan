#include "stdafx.h"
#include <WinSock2.h>	//winsock�O��
#include "Project.h"
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4996)
/// <summary>
/// �F�X�l��������UDP�ɂ���
/// </summary>
namespace basecross {
	void NetWork::Main() {
	}
	//������������
	void NetWork::Initialize(WSAData &wsad) {
		//winsock�̏�����
		//(winsock�o�[�W����,�������������̂����鏊)
		int error;
		error = WSAStartup(MAKEWORD(2, 0), &wsad);
		if(error != 0){
			switch (error)
			{
			case WSASYSNOTREADY:
				MessageBox(0,L"�l�b�g���[�N�T�u�V�X�e���������ł��Ă��܂���",0,0);
				break;
			case WSAVERNOTSUPPORTED:
				MessageBox(0, L"WinSock�̃o�[�W�������T�|�[�g���ꂢ�܂���", 0, 0);
				break;
			case WSAEINPROGRESS:
				MessageBox(0, L"�u���b�L���O�������ł�", 0, 0);
				break;
			case WSAEPROCLIM:
				MessageBox(0, L"�����ł���ő�v���Z�X�𒴂��܂���", 0, 0);
				break;
			case WSAEFAULT:
				MessageBox(0, L"�i�[�p�|�C���^���s���ł�", 0, 0);
				break;
			default:
				break;
			}
		}
	}
	//Socket�̍쐬
	SOCKET NetWork::CreateSocket() {
		SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
		if (sock == INVALID_SOCKET) {
			MessageBox(0,L"Socket�̍쐬�Ɏ��s���܂���",0,0);
			return NULL;
		}else {
			return sock;
		}
	}
	//�ʐM�̊J�n
	void NetWork::Connection_Sending() {
		WSAData wsaData;
		Initialize(wsaData);
		SOCKET socket = CreateSocket();

		//�ڑ���w��p�\���̂̏���
		m_server.sin_family = AF_INET;								//IPv4
		m_server.sin_port = htons(12345);							//�|�[�g�ԍ�
		m_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		//���M�A�h���X

		//���M�f�[�^�o�b�t�@
		char buf[2048] = "HELLO";

		//���M����
		// sendto(�\�P�b�g, ���M����f�[�^, �f�[�^�̃o�C�g��, �t���O, �A�h���X���, �A�h���X���̃T�C�Y);
		sendto(socket, buf, sizeof(buf), 0, (struct  sockaddr *)&m_server, sizeof(m_server));

		//socket�̔j��
		closesocket(socket);
		//�I��
		WSACleanup();
	}
	//��M
	void NetWork::Connection_Receiving() {
		WSAData wsaData;
		Initialize(wsaData);

		SOCKET sock;
		sock = CreateSocket();

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(12345);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;

		//�o�C���h
		bind(sock,(struct sockaddr *)&addr,sizeof(addr));

		//�u���b�L���O�̐ݒ�
		//0 �u���b�L���O���[�h(��M�����܂őҋ@)
		//1 �m���u���b�L���O(��M����Ȃ��Ă�����)
		u_long val = 1;
		ioctlsocket(sock, FIONBIO, &val);

		//��M�f�[�^�p�o�b�t�@
		char buf[2048];
			//�e�X�g�\��
			MessageBox(0, (LPCWSTR)buf, 0, 0);
		//�c��Ȃ��悤�Ɉ��Clear
		memset(buf,0,sizeof(buf));


		//socket�̔j��
		closesocket(sock);
		//�I��
		WSACleanup();
	}
}
