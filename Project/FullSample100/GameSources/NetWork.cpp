#include "stdafx.h"
#include <WinSock2.h>	//winsock前提
#include "Project.h"
#pragma comment(lib, "Ws2_32.lib")
namespace basecross {
	void NetWork::Main() {
		if (!Initialize()) {
			MessageBox(0,L"WinSockの初期化に失敗しました",0,0);
		}
	}
	//初期化をする
	bool NetWork::Initialize() {
		//winsockの初期化
		//(winsockバージョン,初期化したものを入れる所)
		int error;
		error = WSAStartup(MAKEWORD(2, 0), &m_pwsaData);
		if(error != 0){
			switch (error)
			{
			case WSASYSNOTREADY:
				MessageBox(0,L"ネットワークサブシステムが準備できていません",0,0);
				return 0;
			case WSAVERNOTSUPPORTED:
				MessageBox(0, L"WinSockのバージョンがサポートされいません", 0, 0);
				return 0;
			case WSAEINPROGRESS:
				MessageBox(0, L"ブロッキング処理中です", 0, 0);
				return 0;
			case WSAEPROCLIM:
				MessageBox(0, L"処理できる最大プロセスを超えました", 0, 0);
				return 0;
			case WSAEFAULT:
				MessageBox(0, L"格納用ポインタが不正です", 0, 0);
				return 0;
			default:
				return 1;
			}
		}
		return 1;
	}
}
