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

		//�{�^���𐶐�����
		auto ptrStage = GetStage();
		//ptrStage->AddGameObject<>



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

		SetDrawLayer(4);
		SetDrawActive(false);
	}

	void StartPause::OnUpdate()
	{
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//�|�[�Y���I�t�̎�
		if (m_isPause == false)
		{
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
			{
				Pause();
			}
		}

		//�|�[�Y���I���̎�
		else if (m_isPause == true)
		{
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_START || cntVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				Release();
			}
			else if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				Decision();
			}


			if (cntVec[0].fThumbLY != 0.0f && m_once == false)
			{
				Selection();
			}
			else if (cntVec[0].fThumbLY == 0.0f && m_once == true)
			{
				m_once = false;
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

		//�������~�߂����
		//MyGameObject
		for (size_t i = 0; i < gameObjectVec.size(); i++)
		{
			auto obj = dynamic_pointer_cast<GameObject>(gameObjectVec[i]);
			if (obj)
			{
				obj->SetUpdateActive(false);
			}
		}
		//�X�|�[���f�B���N�^�[
		ptrStage->GetSharedObject(L"SpawnDirector")->SetUpdateActive(false);

		//�w�i�̌�




		//UI
		auto group = ptrStage->GetSharedObjectGroup(L"UI_Group");
		for (size_t i = 0; i < group->size(); i++)
		{
			group->at(i)->SetUpdateActive(true);
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

		//�������~�߂����
		//MyGameObject
		for (size_t i = 0; i < gameObjectVec.size(); i++)
		{
			auto obj = dynamic_pointer_cast<GameObject>(gameObjectVec[i]);
			if (obj)
			{
				obj->SetUpdateActive(true);
			}
		}
		//�X�|�[���f�B���N�^�[
		ptrStage->GetSharedObject(L"SpawnDirector")->SetUpdateActive(true);

		//�w�i�̌�����~�����Ȃ���

		//UI
		auto group = ptrStage->GetSharedObjectGroup(L"UI_Group");
		for (size_t i = 0; i < group->size(); i++)
		{
			group->at(i)->SetUpdateActive(true);
		}
	}

}