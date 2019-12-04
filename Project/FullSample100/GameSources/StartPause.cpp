#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	�|�[�Y�p�̃��j���[
	//--------------------------------------------------------------------------------------
	StartPause::StartPause(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void StartPause::OnCreate()
	{
		auto halfSize = 0.5f;
		//���_�̈ʒu�ƐF���w�肵�ĕ\��
		vector<VertexPositionColorTexture> vertices =
		{
			{ VertexPositionColorTexture(Vec3(-halfSize,halfSize,0),Col4(1.0f,1.0f,1.0f,0.0f),Vec2(0.0f,0.0f)) },
			{ VertexPositionColorTexture(Vec3(halfSize,halfSize,0),Col4(1.0f,1.0f,1.0f,0.0f),Vec2(1.0f,0.0f)) },
			{ VertexPositionColorTexture(Vec3(-halfSize,-halfSize,0),Col4(1.0f,1.0f,1.0f,0.0f),Vec2(0.0f,1.0f)) },
			{ VertexPositionColorTexture(Vec3(halfSize,-halfSize,0),Col4(1.0f,1.0f,1.0f,0.0f),Vec2(1.0f,1.0f)) }

		};
		vector<uint16_t> indices = { 0,1,2,1,3,2 };

		SetAlphaActive(true);

		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
		PtrTransform->SetScale(Vec3(600.0f, 300.0f, 0.0f));
		PtrTransform->SetRotation(Vec3(0.0f, 0.0f, 0.0f));

		//�`��̃R���|�[�l���g
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		//PtrDraw->SetTextureResource(L"PauseWindow.png");

		SetDrawLayer(100);
		SetDrawActive(false);
	}

	void StartPause::OnUpdate()
	{
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];

		//�|�[�Y���I�t�̎�
		if (m_isPause == false)
		{
			if (cntVec.wPressedButtons & XINPUT_GAMEPAD_START)
			{
				//�~�߂�֐�
				Pause();
			}
		}

		//�|�[�Y���I���̎�
		else if (m_isPause == true)
		{
			if (cntVec.wPressedButtons & XINPUT_GAMEPAD_START || cntVec.wPressedButtons & XINPUT_GAMEPAD_B)
			{
				//�������֐�
				Release();
			}
		}

	}

	//�~�߂�֐�
	void StartPause::Pause()
	{
		auto ptrStage = GetStage();
		auto gameObjectVec = GetStage()->GetGameObjectVec();

		//������true�ɕύX
		m_isPause = true;
		//�\������
		SetDrawActive(true);

		for (auto v : gameObjectVec)
		{
			v->SetUpdateActive(false);
		}
	}

	//�������֐�
	void StartPause::Release()
	{
		auto ptrStage = GetStage();
		auto gameObjectVec = GetStage()->GetGameObjectVec();

		//������true�ɕύX
		m_isPause = false;
		//�\������
		SetDrawActive(false);

		for (auto v : gameObjectVec)
		{
			v->SetUpdateActive(true);
		}
	}
}