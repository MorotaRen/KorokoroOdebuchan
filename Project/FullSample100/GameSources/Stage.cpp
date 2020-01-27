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
	StageObject::StageObject(const shared_ptr<Stage>& ptrstage, Vec3 pos, Vec3 scale, Quat quat,wstring modelkey) : GameObject(ptrstage), m_pos(pos), m_scale(scale), m_quat(quat),m_modelkey(modelkey) {

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
		auto TransComp = GetComponent<Transform>();
		auto DrawComp = AddComponent<BcPNTStaticModelDraw>();
		//DrawComp->SetMultiMeshResource(L"M_Spring");
		DrawComp->SetMeshResource(m_modelkey);


		//�傫���̂Œ���
		//TransComp->SetScale(Vec3(0.1f,0.1f,0.1f));
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

		CreateStageCollider();

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
		PsPtr->SetDrawActive(true);

	}

}