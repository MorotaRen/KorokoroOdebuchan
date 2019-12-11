#pragma once
/// ----------------------------------------<summary>
/// ネットワーク関連
/// 注：シングルトン
/// 管理者：諸田
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class  NetWork final {
	private:
		//コンストラクタ
		NetWork() {};
		//コンストラクタ
		NetWork(const NetWork&);
		//デストラクタ
		~NetWork() {};
		//初期化
		void Initialize(WSAData &wsad);
		//Soketの作成
		SOCKET CreateSocket();


		struct sockaddr_in m_server;

	public:
		static NetWork& GetInstans() {
			static NetWork inst;
			return inst;
		}
		//実行
		void Main();
		//接続
		void Connection_Sending();
		//受信
		void Connection_Receiving();
	};
}