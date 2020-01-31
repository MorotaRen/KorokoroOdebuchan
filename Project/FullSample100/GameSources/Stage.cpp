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
	StageObject::StageObject(const shared_ptr<Stage>& ptrstage, Vec3 pos, Vec3 scale, Quat quat,wstring modelkey, int Type) : GameObject(ptrstage), m_pos(pos), m_scale(scale), m_quat(quat),m_modelkey(modelkey),m_Type(Type) {
		switch (Type)
		{
		case 0 :
			AddTag(L"Floor");
			break;
		case 1 :
			AddTag(L"WallL");
			break;
		case 2 :
			AddTag(L"WallR");
			break;
		default:
			break;
		}
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
		if (m_Type != 4) {
			auto TransComp = GetComponent<Transform>();
			auto DrawComp = AddComponent<BcPNTStaticModelDraw>();
			DrawComp->SetMeshResource(m_modelkey);


			//Y軸180°回転
			TransComp->SetQuaternion(m_quat);


			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);
			DrawComp->SetMeshToTransformMatrix(spanMat);
			if (m_Type != 5) {
				CreateStageCollider();
			}
		}
		else {
			auto TransComp = GetComponent<Transform>();
			auto DrawComp = AddComponent<BcPNTStaticModelDraw>();
			DrawComp->SetMultiMeshResource(m_modelkey);

			//Y軸180°回転
			m_quat.rotationY(3.14);

			TransComp->SetQuaternion(m_quat);


			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(1.0f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f)
			);
			DrawComp->SetMeshToTransformMatrix(spanMat);

		}

	}
	void StageObject::OnUpdate() {

	}
	/// ----------------------------------------<summary>
	/// ステージの当たり判定の作成
	/// </summary>----------------------------------------

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
		param.m_Mass = 0.0f;
		//慣性の計算
		param.m_Inertia = BasePhysics::CalcInertiaBox(Vec3(0.5f),param.m_Mass);
		param.m_MotionType = PsMotionType::MotionTypeFixed;
		m_quat.rotationY(3.14);
		param.m_Quat = m_quat;
		param.m_Pos = m_pos;


		auto PsPtr = AddComponent<RigidbodyConvex>(param);
		//PsPtr->SetDrawActive(true);
	}

}