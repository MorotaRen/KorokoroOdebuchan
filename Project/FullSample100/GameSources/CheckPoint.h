#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// チェックポイントヘッダー
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {

	class CheckPoint : public GameObject
	{
	private:
		//次のCollisionエリアナンバー
		unsigned int m_nextpointNum;
		//初期位置
		Vec3 m_pos,
		//初期スケール
			m_scale;
		//初期回転
		Quat m_quat;
	public:
		//コンストラクタ
		CheckPoint(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat);
		//デストラクタ
		~CheckPoint();
		//生成
		virtual void OnCreate()override;
		//接触時
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
		//m_nextpointの設定
		void SetNextPointNum(unsigned int num) { m_nextpointNum = num; };
		//m_nextpointの取得
		unsigned int GetNextPointNum() { return m_nextpointNum; };
	};
}