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
		bool Initialize();

		WSADATA m_pwsaData;

	public:
		static NetWork& GetInstans() {
			static NetWork inst;
			return inst;
		}
		//実行
		void Main();

	};
}