#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
///	ステージオブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------

namespace basecross {

	class StageObject : public GameObject {
	private:
		//位置
		Vec3 m_pos,
		//大きさ
			m_scale;
		//回転
		Quat m_quat;

		//描画用メッシュ
		static shared_ptr<MeshResource> m_ConvexMesh;
		//物理計算用メッシュ
		static shared_ptr<PsConvexMeshResource> m_PsConvexMesh;
	public:
		StageObject(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat);
		~StageObject();
		virtual void OnCreate()override;

		//ステージの当たり判定の作成
		void CreateStageCollider();

	};

}