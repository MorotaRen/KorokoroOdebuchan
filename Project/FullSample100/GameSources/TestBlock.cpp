#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\���Ɣj��
	TestBlock::TestBlock(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale)
	{
	}

	//������
	void TestBlock::OnCreate() {

	}

	//�X�V
	void TestBlock::OnUpdate() {

	}
}
