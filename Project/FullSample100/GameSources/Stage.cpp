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
		auto DrawComp = AddComponent<BcPNTStaticModelDraw>();
		//DrawComp->SetMultiMeshResource(L"M_Spring");
		DrawComp->SetMeshResource(L"MS_Spring");
		CreateStageCollider();


		//大きいので調整
		TransComp->SetScale(Vec3(0.1f,0.1f,0.1f));
		//Y軸180°回転
		TransComp->SetQuaternion(m_quat);


	}
	/// ----------------------------------------<summary>
	/// ステージの当たり判定の作成
	/// </summary>----------------------------------------
	shared_ptr<MeshResource> StageObject::m_ConvexMesh = nullptr;
	shared_ptr<PsConvexMeshResource> StageObject::m_PsConvexMesh = nullptr;
	void StageObject::CreateStageCollider()
	{
		auto DrawComp = GetComponent<BcPNTStaticModelDraw>();
		auto Mesh = DrawComp->GetMeshResource();

		if (!m_ConvexMesh || !m_PsConvexMesh) {
			vector<VertexPositionNormalTexture> vertices = Mesh->GetBackupVerteces<VertexPositionNormalTexture>();
			vector<uint16_t> indices = Mesh->GetBackupIndices<VertexPositionNormalTexture>();

			//MeshUtill::CreateDodecahedron(0.5,vertices,indices);
			m_ConvexMesh = MeshResource::CreateMeshResource(vertices,indices,true);
			m_PsConvexMesh = PsConvexMeshResource::CreateMeshResource(vertices,indices);
		}
		//物理計算
		PsConvexParam param;

		param.m_ConvexMeshResource = m_PsConvexMesh;
		param.m_Mass = 1.0f;
		//慣性の計算
		param.m_Inertia = BasePhysics::CalcInertiaBox(Vec3(0.5f),param.m_Mass);
		param.m_MotionType = PsMotionType::MotionTypeFixed;
		m_quat.rotationY(3.14);
		param.m_Quat = m_quat;
		m_pos.y -= 1.0f;
		param.m_Pos = m_pos;
		auto PsPtr = AddComponent<RigidbodyConvex>(param);
		PsPtr->SetDrawActive(true);

	}

}