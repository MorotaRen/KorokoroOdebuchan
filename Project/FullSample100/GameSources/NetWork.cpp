#include "stdafx.h"
#include <WinSock2.h>	//winsock前提
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
	void NetWork::Initialize(WSAData wsad) {
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
		SOCKET sock = socket(AF_INET,SOCK_STREAM,0);
		if (sock == INVALID_SOCKET) {
			MessageBox(0,L"Socketの作成に失敗しました",0,0);
			return NULL;
		}else {
			return sock;
		}
	}
	//通信の開始
	void NetWork::Connection_Sending() {
		WSAData wsaData;
		Initialize(wsaData);
		SOCKET socket = CreateSocket();

		//接続先指定用構造体の準備
		m_server.sin_family = AF_INET;								//IPv4
		m_server.sin_port = htons(12345);							//ポート番号
		m_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		//送信アドレス

		//送信データバッファ
		char buf[2048] = "HELLO";

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
		Initialize(wsaData);

		SOCKET sock;
		sock = CreateSocket();

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(12345);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;

		//バインド
		bind(sock,(struct sockaddr *)&addr,sizeof(addr));

		//ブロッキングの設定
		//0 ブロッキングモード(受信されるまで待機)
		//1 ノンブロッキング(受信されなくても次へ)
		u_long val = 1;
		ioctlsocket(sock, FIONBIO, &val);

		//受信データ用バッファ
		char buf[2048];

		//テスト表示
		MessageBox(0, (LPCWSTR)buf,0,0);

		//残らないように一回Clear
		memset(buf,0,sizeof(buf));


		//socketの破棄
		closesocket(sock);
		//終了
		WSACleanup();
	}
}
