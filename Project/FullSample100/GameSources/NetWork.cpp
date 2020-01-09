#include "stdafx.h"
#include <WinSock2.h>	//winsock�O��
#include <ws2tcpip.h>
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
		SOCKET sock = socket(AF_INET, SOCK_DGRAM,0);
		if (sock == INVALID_SOCKET) {
			MessageBox(0,L"Socket�̍쐬�Ɏ��s���܂���",0,0);
			return NULL;
		}else {
			return sock;
		}
	}
	//�ʐM�̊J�n
	void NetWork::Connection_Sending(Vec3 trans) {
		WSAData wsaData;
		WSAStartup(MAKEWORD(2,0),&wsaData);
		SOCKET sock = socket(AF_INET,SOCK_DGRAM,0);

		//�ڑ���w��p�\���̂̏���
		memset(&m_server,0,sizeof(m_server));
		m_server.sin_family = AF_INET;									//IPv4
		m_server.sin_port = htons(65530);								//�|�[�g�ԍ�
		m_server.sin_addr.S_un.S_addr = inet_addr("192.168.7.78");		//���M�A�h���X

		//���M�f�[�^�o�b�t�@
		char x[512], y[512], z[512];
		snprintf(x,2048,"%f",trans.x);
		snprintf(y,2048,"%f",trans.y);
		snprintf(z,2048,"%f",trans.z);
		char buf[2048] = {NULL};
		strcat(buf, x);
		strcat(buf, ",");
		strcat(buf, y);
		strcat(buf, ",");
		strcat(buf, z);


		//���M����
		// sendto(�\�P�b�g, ���M����f�[�^, �f�[�^�̃o�C�g��, �t���O, �A�h���X���, �A�h���X���̃T�C�Y);
		sendto(sock, buf, sizeof(buf), 0, (struct  sockaddr *)&m_server, sizeof(m_server));

	}
	//��M
	void NetWork::Connection_Receiving() {
		WSAData wsaData;
		Initialize(wsaData);

		SOCKET sock;
		sock = CreateSocket();

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(65530);
		addr.sin_addr.S_un.S_addr = inet_addr("192.168.7.78");

		//�o�C���h
		bind(sock, (struct sockaddr *) &m_server, sizeof(m_server));
		//��M
		char buf[2048];
		recvfrom(sock, buf, 2048, 0, NULL, NULL);
		GameSystems::GetInstans().NET_CharToVec3(buf);
		//socket�̔j��
		closesocket(sock);
		//�I��
		WSACleanup();
	}
}