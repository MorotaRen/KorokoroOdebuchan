/// ----------------------------------------<summary>
/// �X�e�[�W�I�u�W�F�N�g
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	/// ----------------------------------------<summary>
	/// �R���X�g���N�^
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
	/// �f�X�g���N�^
	/// </summary>----------------------------------------
	StageObject::~StageObject() {

	}

	/// ----------------------------------------<summary>
	/// ����
	/// </summary>----------------------------------------
	void StageObject::OnCreate() {
		if (m_Type != 4) {
			auto TransComp = GetComponent<Transform>();
			auto DrawComp = AddComponent<BcPNTStaticModelDraw>();
			DrawComp->SetMeshResource(m_modelkey);


			//Y��180����]
			TransComp->SetQuaternion(m_quat);


			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
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

			//Y��180����]
			m_quat.rotationY(3.14);

			TransComp->SetQuaternion(m_quat);


			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
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
	/// �X�e�[�W�̓����蔻��̍쐬
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
		//�����v�Z
		PsConvexParam param;

		param.m_ConvexMeshResource = m_PsConvexMesh;
		param.m_Mass = 0.0f;
		//�����̌v�Z
		param.m_Inertia = BasePhysics::CalcInertiaBox(Vec3(0.5f),param.m_Mass);
		param.m_MotionType = PsMotionType::MotionTypeFixed;
		m_quat.rotationY(3.14);
		param.m_Quat = m_quat;
		param.m_Pos = m_pos;


		auto PsPtr = AddComponent<RigidbodyConvex>(param);
		//PsPtr->SetDrawActive(true);
	}

}