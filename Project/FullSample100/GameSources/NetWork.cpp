#include "stdafx.h"
#include <WinSock2.h>	//winsock前提
#include <ws2tcpip.h>
#include "Project.h"
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable:4996)
/// <summary>
/// 色々考えた結果UDPにする
/// </summary>
namespace basecross {
	void NetWork::Main() {
	}
	//初期化をする
	void NetWork::Initialize(WSAData &wsad) {
		//winsockの初期化
		//(winsockバージョン,初期化したものを入れる所)
		int error;
		error = WSAStartup(MAKEWORD(2, 0), &wsad);
		if(error != 0){
			switch (error)
			{
			case WSASYSNOTREADY:
				MessageBox(0,L"ネットワークサブシステムが準備できていません",0,0);
				break;
			case WSAVERNOTSUPPORTED:
				MessageBox(0, L"WinSockのバージョンがサポートされいません", 0, 0);
				break;
			case WSAEINPROGRESS:
				MessageBox(0, L"ブロッキング処理中です", 0, 0);
				break;
			case WSAEPROCLIM:
				MessageBox(0, L"処理できる最大プロセスを超えました", 0, 0);
				break;
			case WSAEFAULT:
				MessageBox(0, L"格納用ポインタが不正です", 0, 0);
				break;
			default:
				break;
			}
		}
	}
	//Socketの作成
	SOCKET NetWork::CreateSocket() {
		SOCKET sock = socket(AF_INET, SOCK_DGRAM,0);
		if (sock == INVALID_SOCKET) {
			MessageBox(0,L"Socketの作成に失敗しました",0,0);
			return NULL;
		}else {
			return sock;
		}
	}
	//通信の開始
	void NetWork::Connection_Sending(Vec3 trans) {
		WSAData wsaData;
		Initialize(wsaData);
		SOCKET socket = CreateSocket();
		unsigned short port = 65530;

		//接続先指定用構造体の準備
		memset(&m_server,0,sizeof(m_server));
		m_server.sin_family = AF_INET;									//IPv4
		m_server.sin_port = htons(port);								//ポート番号
		m_server.sin_addr.S_un.S_addr = inet_addr("192.168.7.78");		//送信アドレス

		//送信データバッファ
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


		//送信する
		// sendto(ソケット, 送信するデータ, データのバイト数, フラグ, アドレス情報, アドレス情報のサイズ);
		sendto(socket, buf, sizeof(buf), 0, (struct  sockaddr *)&m_server, sizeof(m_server));

		//socketの破棄
		closesocket(socket);
		//終了
		WSACleanup();
	}
	//受信
	void NetWork::Connection_Receiving() {
		WSAData wsaData;
		WSAStartup(MAKEWORD(2, 0), &wsaData);

		SOCKET sock;
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock == INVALID_SOCKET) {
			MessageBox(0,L"ソケット作成に失敗！",0,0);
		}
		char r_buf[2048] = { NULL };

		unsigned short port = 65530;
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.S_un.S_addr = inet_addr("192.168.7.78");
		//バインド
		bind(sock, (struct sockaddr *) &addr, sizeof(addr));

		//受信
		recvfrom(sock, r_buf, 2048, 0, NULL, NULL);
		GameSystems::GetInstans().NET_CharToVec3(r_buf);
	}
}
