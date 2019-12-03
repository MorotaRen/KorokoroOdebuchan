#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// チェックポイント用オブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {
	class Checkpoint : public GameObject
	{
	private:
		Vec3 m_pos;//位置
		Vec3 m_scale;//大きさ
		Quat m_quat;//回転
		unsigned int m_mynum;//自分のエリアナンバー


	public:
		Checkpoint(const shared_ptr<Stage>& ptrStage, Vec3 pos, Vec3 scale, Quat quat);
		~Checkpoint();
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
		void SetAreaNum(unsigned int setnum) { m_mynum = setnum; };

	};


}