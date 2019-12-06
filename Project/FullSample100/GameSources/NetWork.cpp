#include "stdafx.h"
#include <WinSock2.h>	//winsock�O��
#include "Project.h"
#pragma comment(lib, "Ws2_32.lib")
namespace basecross {
	void NetWork::Main() {
		if (!Initialize()) {
			MessageBox(0,L"WinSock�̏������Ɏ��s���܂���",0,0);
		}
	}
	//������������
	bool NetWork::Initialize() {
		//winsock�̏�����
		//(winsock�o�[�W����,�������������̂����鏊)
		int error;
		error = WSAStartup(MAKEWORD(2, 0), &m_pwsaData);
		if(error != 0){
			switch (error)
			{
			case WSASYSNOTREADY:
				MessageBox(0,L"�l�b�g���[�N�T�u�V�X�e���������ł��Ă��܂���",0,0);
				return 0;
			case WSAVERNOTSUPPORTED:
				MessageBox(0, L"WinSock�̃o�[�W�������T�|�[�g���ꂢ�܂���", 0, 0);
				return 0;
			case WSAEINPROGRESS:
				MessageBox(0, L"�u���b�L���O�������ł�", 0, 0);
				return 0;
			case WSAEPROCLIM:
				MessageBox(0, L"�����ł���ő�v���Z�X�𒴂��܂���", 0, 0);
				return 0;
			case WSAEFAULT:
				MessageBox(0, L"�i�[�p�|�C���^���s���ł�", 0, 0);
				return 0;
			default:
				return 1;
			}
		}
		return 1;
	}
}
