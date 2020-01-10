/// ----------------------------------------<summary>
/// ステージオブジェクト
/// 管理者：諸田
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// コンストラクタ
	/// </summary>----------------------------------------
	StageObject::StageObject(const shared_ptr<Stage>& ptrstage, Vec3 pos, Vec3 scale, Quat quat) : GameObject(ptrstage), m_pos(pos), m_scale(scale), m_quat(quat) {

	}

	/// ----------------------------------------<summary>
	/// デストラクタ
	/// </summary>----------------------------------------
	StageObject::~StageObject() {

	}

	/// ----------------------------------------<summary>
	/// 生成
	/// </summary>----------------------------------------
	void StageObject::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		//m_pos.x += 0.05f;
		m_pos.z += -0.0f;
		TransComp->SetPosition(m_pos);
		//大きいので調整
		TransComp->SetScale(Vec3(0.1f,0.1f,0.1f));
		//Y軸180°回転
		m_quat.rotationY(3.14);
		TransComp->SetQuaternion(m_quat);

		auto DrawComp = AddComponent<BcPNTStaticModelDraw>();
		DrawComp->SetMultiMeshResource(L"M_Spring");
		auto a = DrawComp->GetMultiMeshResource();
		size_t b = 0;
		auto d = a->GetMeshVec();
		d[1].m_Vertices;
		//auto c = a->GetVertexBuffer;
	}
}