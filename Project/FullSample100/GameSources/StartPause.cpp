#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	//	ポーズ用のメニュー
	//--------------------------------------------------------------------------------------
	StartPause::StartPause(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{}

	void StartPause::OnCreate()
	{

		//ボタンを生成する
		auto ptrStage = GetStage();
		//ptrStage->AddGameObject<>



		auto halfSize = 0.5f;
		//頂点の位置と色を指定して表示
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

		//描画のコンポーネント
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		//PtrDraw->SetTextureResource(L"PauseWindow.png");

		SetDrawLayer(4);
		SetDrawActive(false);
	}

	void StartPause::OnUpdate()
	{
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();

		//ポーズがオフの時
		if (m_isPause == false)
		{
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
			{
				Pause();
			}
		}

		//ポーズがオンの時
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

	//止める関数
	void StartPause::Pause()
	{
		auto ptrStage = GetStage();
		auto gameObjectVec = GetStage()->GetGameObjectVec();

		//ここでtrueに変更
		m_isPause = true;
		//表示する
		SetDrawActive(true);

		//動きを止めるもの
		//MyGameObject
		for (size_t i = 0; i < gameObjectVec.size(); i++)
		{
			auto obj = dynamic_pointer_cast<GameObject>(gameObjectVec[i]);
			if (obj)
			{
				obj->SetUpdateActive(false);
			}
		}
		//スポーンディレクター
		ptrStage->GetSharedObject(L"SpawnDirector")->SetUpdateActive(false);

		//背景の光




		//UI
		auto group = ptrStage->GetSharedObjectGroup(L"UI_Group");
		for (size_t i = 0; i < group->size(); i++)
		{
			group->at(i)->SetUpdateActive(true);
		}
	}

	//動かす関数
	void StartPause::Release()
	{
		auto ptrStage = GetStage();
		auto gameObjectVec = GetStage()->GetGameObjectVec();

		//ここでtrueに変更
		m_isPause = false;
		//表示する
		SetDrawActive(false);

		//動きを止めるもの
		//MyGameObject
		for (size_t i = 0; i < gameObjectVec.size(); i++)
		{
			auto obj = dynamic_pointer_cast<GameObject>(gameObjectVec[i]);
			if (obj)
			{
				obj->SetUpdateActive(true);
			}
		}
		//スポーンディレクター
		ptrStage->GetSharedObject(L"SpawnDirector")->SetUpdateActive(true);

		//背景の光も停止させなきゃ

		//UI
		auto group = ptrStage->GetSharedObjectGroup(L"UI_Group");
		for (size_t i = 0; i < group->size(); i++)
		{
			group->at(i)->SetUpdateActive(true);
		}
	}

}