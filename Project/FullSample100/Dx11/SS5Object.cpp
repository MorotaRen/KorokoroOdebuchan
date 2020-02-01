#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z
	SS5Object::SS5Object(const shared_ptr<Stage> stageptr,const wstring& BaseDir,const wstring FileName,const wstring FirstAnim):
	SS5ssae(stageptr,BaseDir,FileName,FirstAnim,true){
		m_ToAnimeMatrix.affineTransformation(
			Vec3(10.0f, 10.0f, 10.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(1, 1, 1)
		);

	}
	//�j��
	SS5Object::~SS5Object() {

	}
	//����
	void SS5Object::OnCreate() {
		SetToAnimeMatrix(m_ToAnimeMatrix);
		auto TransComp = GetComponent<Transform>();
		TransComp->SetScale(5.0f,5.0f,5.0f);
		TransComp->SetPosition(0.0f,-10.0f,0.0f);

		SetLooped(true);
		SS5ssae::OnCreate();

	}
	void SS5Object::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);
	}
	//--------------------------------------------------------------------------------------
	// �Z���N�g�X�e�[�W�p��SS
	//--------------------------------------------------------------------------------------
		//�\�z
	SelectSS::SelectSS(const shared_ptr<Stage> stageptr,
		const wstring& BaseDir,
		const wstring FileName,
		const wstring FirstAnim,
		const Vec2& startScale,
		const Vec2& startPos) :
		SS5ssae(stageptr, BaseDir, FileName, FirstAnim,true),
		m_Scale(startScale),
		m_Position(startPos)
	{
	}
	//����
	void SelectSS::OnCreate() {
		SS5ssae::OnCreate();
		SetLooped(false);
		SetDrawLayer(2);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale.x, m_Scale.y, 1.0f);
		ptrTrans->SetPosition(m_Position.x, m_Position.y, 0.0f);

	}
	void SelectSS::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);
	}

	//--------------------------------------------------------------------------------------
	// �X�}�b�V���Q�[�W�p��SS
	//--------------------------------------------------------------------------------------
	//�\�z
	SmashGageSS::SmashGageSS(const shared_ptr<Stage> stageptr,
		const wstring& BaseDir,
		const wstring FileName,
		const wstring FirstAnim,
		const Vec2& startScale,
		const Vec2& startPos) :
		SS5ssae(stageptr, BaseDir, FileName, FirstAnim, true),
		m_Scale(startScale),
		m_Position(startPos)
	{}

	//����
	void SmashGageSS::OnCreate() {
		SS5ssae::OnCreate();
		SetLooped(true);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale.x, m_Scale.y, 1.0f);
		ptrTrans->SetPosition(m_Position.x, m_Position.y, 0.0f);

		////�����������
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(1000.0f, 100.0f, 1200.0f, 480.0f));
	}
	void SmashGageSS::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);

		//wstringstream ss;
		//ss << L"SmshePoint : " << GameSystems::GetInstans().GetSmashPoint() << std::endl;

		////������R���|�[�l���g�̎擾
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(ss.str());
	}
	void SmashGageSS::AllChangAnim(bool Active) {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"SpriteStudio\\SmashGage\\";
		if (Active==true) {
			//�����ƔR��������
			ChangeAnimation(L"Burning");
		}
		else {
			//�S�������
			ChangeAnimation(L"Normal");
		}
	}

	//--------------------------------------------------------------------------------------
	// SpriteStudio���C�Z���X
	//--------------------------------------------------------------------------------------
	SSCopyright::SSCopyright(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim) :
		SS5ssae(stageptr, BaseDir, FileName, FirstAnim, true)
	{
		//�ォ��X�P�[���A��](origin)�A��](vec)�A�|�W�V����
		m_ToAnimeMatrix.affineTransformation(
			Vec3(0.025f, 0.035f, 0.035f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f)
		);
	}

	void SSCopyright::OnCreate()
	{
		SS5ssae::OnCreate();

		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetPosition(Vec3(0,0,0));
		PtrTransform->SetScale(Vec3(1300, 800, 0.1f));
		PtrTransform->SetRotation(Vec3(0, 0, 0));
		SetToAnimeMatrix(m_ToAnimeMatrix);
		SetLooped(false);
		SetFps(30);
	}

	void SSCopyright::OnUpdate()
	{
		auto deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);

		if (IsAnimeEnd())
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"TitleScene");
		}
	}
}